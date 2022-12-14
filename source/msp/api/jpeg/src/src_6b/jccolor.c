/*
 * jccolor.c
 *
 * Copyright (C) 1991-1996, Thomas G. Lane.
 * This file is part of the Independent JPEG Group's software.
 * For conditions of distribution and use, see the accompanying README file.
 *
 * This file contains input colorspace conversion routines.
 */

#define JPEG_INTERNALS
#include "jinclude.h"
#include "jpeglib.h"
#include "hi_type.h"

#ifdef CONFIG_JPEG_ADD_GOOGLEFUNCTION
/** this enables unrolling null_convert's loop, and reading/write ints for speed **/
#define ENABLE_ANDROID_NULL_CONVERT
#endif /** CONFIG_JPEG_ADD_GOOGLEFUNCTION **/

/* Private subobject */

typedef struct {
  struct jpeg_color_converter pub; /* public fields */

  /* Private state for RGB->YCC conversion */
  INT32 * rgb_ycc_tab;		/* => table for RGB to YCbCr conversion */
} my_color_converter;

typedef my_color_converter * my_cconvert_ptr;


/**************** RGB -> YCbCr conversion: most common case **************/

/*
 * YCbCr is defined per CCIR 601-1, except that Cb and Cr are
 * normalized to the range 0..MAXJSAMPLE rather than -0.5 .. 0.5.
 * The conversion equations to be implemented are therefore
 *	Y  =  0.29900 * R + 0.58700 * G + 0.11400 * B
 *	Cb = -0.16874 * R - 0.33126 * G + 0.50000 * B  + CENTERJSAMPLE
 *	Cr =  0.50000 * R - 0.41869 * G - 0.08131 * B  + CENTERJSAMPLE
 * (These numbers are derived from TIFF 6.0 section 21, dated 3-June-92.)
 * Note: older versions of the IJG code used a zero offset of MAXJSAMPLE/2,
 * rather than CENTERJSAMPLE, for Cb and Cr.  This gave equal positive and
 * negative swings for Cb/Cr, but meant that grayscale values (Cb=Cr=0)
 * were not represented exactly.  Now we sacrifice exact representation of
 * maximum red and maximum blue in order to get exact grayscales.
 *
 * To avoid floating-point arithmetic, we represent the fractional constants
 * as integers scaled up by 2^16 (about 4 digits precision); we have to divide
 * the products by 2^16, with appropriate rounding, to get the correct answer.
 *
 * For even more speed, we avoid doing any multiplications in the inner loop
 * by precalculating the constants times R,G,B for all possible values.
 * For 8-bit JSAMPLEs this is very reasonable (only 256 entries per table);
 * for 12-bit samples it is still acceptable.  It's not very reasonable for
 * 16-bit samples, but if you want lossless storage you shouldn't be changing
 * colorspace anyway.
 * The CENTERJSAMPLE offsets and the rounding fudge-factor of 0.5 are included
 * in the tables to save adding them separately in the inner loop.
 */

#define SCALEBITS	16	/* speediest right-shift on some machines */
#define CBCR_OFFSET	((INT32) CENTERJSAMPLE << SCALEBITS)
#define ONE_HALF	((INT32) 1 << (SCALEBITS-1))
#define FIX(x)		((INT32) ((x) * (1L<<SCALEBITS) + 0.5))

/* We allocate one big table and divide it up into eight parts, instead of
 * doing eight alloc_small requests.  This lets us use a single table base
 * address, which can be held in a register in the inner loops on many
 * machines (more than can hold all eight addresses, anyway).
 */

#define R_Y_OFF		0			/* offset to R => Y section */
#define G_Y_OFF		(1*(MAXJSAMPLE+1))	/* offset to G => Y section */
#define B_Y_OFF		(2*(MAXJSAMPLE+1))	/* etc. */
#define R_CB_OFF	(3*(MAXJSAMPLE+1))
#define G_CB_OFF	(4*(MAXJSAMPLE+1))
#define B_CB_OFF	(5*(MAXJSAMPLE+1))
#define R_CR_OFF	B_CB_OFF		/* B=>Cb, R=>Cr are the same */
#define G_CR_OFF	(6*(MAXJSAMPLE+1))
#define B_CR_OFF	(7*(MAXJSAMPLE+1))
#define TABLE_SIZE	(8*(MAXJSAMPLE+1))


/*
 * Initialize for RGB->YCC colorspace conversion.
 */

METHODDEF(void)
rgb_ycc_start (j_compress_ptr cinfo)
{
  my_cconvert_ptr cconvert = (my_cconvert_ptr) cinfo->cconvert;
  INT32 * rgb_ycc_tab;
  INT32 i;

  /* Allocate and fill in the conversion tables. */
  cconvert->rgb_ycc_tab = rgb_ycc_tab = (INT32 *)
    (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				(TABLE_SIZE * SIZEOF(INT32)));

  for (i = 0; i <= MAXJSAMPLE; i++) {
    rgb_ycc_tab[i+R_Y_OFF] = FIX(0.29900) * i;
    rgb_ycc_tab[i+G_Y_OFF] = FIX(0.58700) * i;
    rgb_ycc_tab[i+B_Y_OFF] = FIX(0.11400) * i     + ONE_HALF;
    rgb_ycc_tab[i+R_CB_OFF] = (-FIX(0.16874)) * i;
    rgb_ycc_tab[i+G_CB_OFF] = (-FIX(0.33126)) * i;
    /* We use a rounding fudge-factor of 0.5-epsilon for Cb and Cr.
     * This ensures that the maximum output will round to MAXJSAMPLE
     * not MAXJSAMPLE+1, and thus that we don't have to range-limit.
     */
    rgb_ycc_tab[i+B_CB_OFF] = FIX(0.50000) * i    + CBCR_OFFSET + ONE_HALF-1;
/*  B=>Cb and R=>Cr tables are the same
    rgb_ycc_tab[i+R_CR_OFF] = FIX(0.50000) * i    + CBCR_OFFSET + ONE_HALF-1;
*/
    rgb_ycc_tab[i+G_CR_OFF] = (-FIX(0.41869)) * i;
    rgb_ycc_tab[i+B_CR_OFF] = (-FIX(0.08131)) * i;
  }
}


/*
 * Convert some rows of samples to the JPEG colorspace.
 *
 * Note that we change from the application's interleaved-pixel format
 * to our internal noninterleaved, one-plane-per-component format.
 * The input buffer is therefore three times as wide as the output buffer.
 *
 * A starting row offset is provided only for the output buffer.  The caller
 * can easily adjust the passed input_buf value to accommodate any row
 * offset required on that side.
 */

METHODDEF(void)
rgb_ycc_convert (j_compress_ptr cinfo,
		 JSAMPARRAY input_buf, JSAMPIMAGE output_buf,
		 JDIMENSION output_row, int num_rows)
{

		my_cconvert_ptr cconvert = (my_cconvert_ptr) cinfo->cconvert;
		register int r = 0, g = 0, b = 0;
		register int r_temp = 0,g_temp = 0,b_temp = 0,offset = 0;
		register INT32 * ctab = cconvert->rgb_ycc_tab;
		register JSAMPROW inptr;
		register JSAMPROW outptr0, outptr1, outptr2;
		register JDIMENSION col;
		JDIMENSION num_cols = cinfo->image_width;
		switch(cinfo->in_color_space)
		{
		   case JCS_RGB:
				r_temp = RGB_RED;
				g_temp = RGB_GREEN;
				b_temp = RGB_BLUE;
				offset = RGB_PIXELSIZE;
			    break;
		   case JCS_BGR:
				r_temp = RGB_BLUE;
				g_temp = RGB_GREEN;
				b_temp = RGB_RED;
				offset = RGB_PIXELSIZE;
				break;
			case JCS_ARGB_8888:
				r_temp = RGB_RED;
				g_temp = RGB_GREEN;
				b_temp = RGB_BLUE;
				offset = 4;
				break;
		     case JCS_ABGR_8888:
			 	r_temp = RGB_BLUE;
				g_temp = RGB_GREEN;
				b_temp = RGB_RED;
				offset = 4;
				break;
			  default:
			  	ERREXIT(cinfo, JERR_BAD_IN_COLORSPACE);
			  	break;
		}
		while (--num_rows >= 0) 
		{
			inptr = *input_buf++;
			outptr0 = output_buf[0][output_row];
			outptr1 = output_buf[1][output_row];
			outptr2 = output_buf[2][output_row];
			output_row++;
			
			for (col = 0; col < num_cols; col++) 
			{
				r = GETJSAMPLE(inptr[r_temp]);
				g = GETJSAMPLE(inptr[g_temp]);
				b = GETJSAMPLE(inptr[b_temp]);
				inptr += offset;
				
				/* If the inputs are 0..MAXJSAMPLE, the outputs of these equations
				* must be too; we do not need an explicit range-limiting operation.
				* Hence the value being shifted is never negative, and we don't
				* need the general RIGHT_SHIFT macro.
				*/
				/* Y */
				outptr0[col] = (JSAMPLE)((ctab[r+R_Y_OFF] + ctab[g+G_Y_OFF] + ctab[b+B_Y_OFF])>> SCALEBITS);
				/* Cb */
				outptr1[col] = (JSAMPLE)((ctab[r+R_CB_OFF] + ctab[g+G_CB_OFF] + ctab[b+B_CB_OFF])>> SCALEBITS);
				/* Cr */
				outptr2[col] = (JSAMPLE)((ctab[r+R_CR_OFF] + ctab[g+G_CR_OFF] + ctab[b+B_CR_OFF])>> SCALEBITS);
			}
			
		}
  
}


static inline HI_U8  From565To8(HI_U16 p,HI_S32 start,HI_S32 bits)
{
    HI_U8 c = (p >> start) & ((1 << bits) - 1);
    return (c << (8 - bits)) | (c >> (bits - (8 - bits)));
}
static inline HI_U8  From1555To8(HI_U16 p,HI_S32 start,HI_S32 bits)
{
    HI_U8 c = (p >> start) & ((1 << bits) - 1);
    return (c << (8 - bits)) | (c >> (bits - (8 - bits)));
}

METHODDEF(void)
rgb16_2_ycc_convert (j_compress_ptr cinfo,
		 JSAMPARRAY input_buf, JSAMPIMAGE output_buf,
		 JDIMENSION output_row, int num_rows)
{

		my_cconvert_ptr cconvert = (my_cconvert_ptr) cinfo->cconvert;
		UINT8 r = 0, g = 0, b = 0;
		HI_U16 *src = NULL;
		register INT32 * ctab = cconvert->rgb_ycc_tab;
		register JSAMPROW inptr;
		register JSAMPROW outptr0, outptr1, outptr2;
		register JDIMENSION col;
		JDIMENSION num_cols = cinfo->image_width;

		while (--num_rows >= 0) 
		{
			inptr = *input_buf++;
			src   = (HI_U16 *)inptr;
			outptr0 = output_buf[0][output_row];
			outptr1 = output_buf[1][output_row];
			outptr2 = output_buf[2][output_row];
			output_row++;
			
			for (col = 0; col < num_cols; col++) 
			{
				switch(cinfo->in_color_space)
				{
				   case JCS_RGB_565:
						r = From565To8(*src, 11, 5);
            			g = From565To8(*src, 5, 6);
            			b = From565To8(*src, 0, 5);
						r = GETJSAMPLE(r);
						g = GETJSAMPLE(g);
						b = GETJSAMPLE(b);
						src++;
					    break;
				   case JCS_BGR_565:
				   	    b = From565To8(*src, 11, 5);
            			g = From565To8(*src, 5, 6);
            			r = From565To8(*src, 0, 5);
						r = GETJSAMPLE(r);
						g = GETJSAMPLE(g);
						b = GETJSAMPLE(b);
						src++;
						break;
					case JCS_ARGB_1555:
						r = From565To8(*src, 10, 5);
            			g = From565To8(*src, 5, 5);
            			b = From565To8(*src, 0, 5);
						r = GETJSAMPLE(r);
						g = GETJSAMPLE(g);
						b = GETJSAMPLE(b);
						src++;
						break;
				     case JCS_ABGR_1555:
					 	b = From565To8(*src, 10, 5);
            			g = From565To8(*src, 5, 5);
            			r = From565To8(*src, 0, 5);
						r = GETJSAMPLE(r);
						g = GETJSAMPLE(g);
						b = GETJSAMPLE(b);
						src++;
						break;
					  default:
					  	ERREXIT(cinfo, JERR_BAD_IN_COLORSPACE);
					  	break;
				}
				#if 0
				/* ?????????????????????????????????????? */
				printf("inptr[0] = 0x%x,inptr[1] = 0x%x, rgb = 0x%x,r = 0x%x,g = 0x%x,b = 0x%x\n",inptr[RGB_RED],inptr[RGB_GREEN],rgb,r,g,b);
				#endif
				
				inptr += 2;
				
				/* If the inputs are 0..MAXJSAMPLE, the outputs of these equations
				* must be too; we do not need an explicit range-limiting operation.
				* Hence the value being shifted is never negative, and we don't
				* need the general RIGHT_SHIFT macro.
				*/
				/* Y */
				outptr0[col] = (JSAMPLE)((ctab[r+R_Y_OFF] + ctab[g+G_Y_OFF] + ctab[b+B_Y_OFF])>> SCALEBITS);
				/* Cb */
				outptr1[col] = (JSAMPLE)((ctab[r+R_CB_OFF] + ctab[g+G_CB_OFF] + ctab[b+B_CB_OFF])>> SCALEBITS);
				/* Cr */
				outptr2[col] = (JSAMPLE)((ctab[r+R_CR_OFF] + ctab[g+G_CR_OFF] + ctab[b+B_CR_OFF])>> SCALEBITS);
			}
			
		}
  
}

/**************** Cases other than RGB -> YCbCr **************/


/*
 * Convert some rows of samples to the JPEG colorspace.
 * This version handles RGB->grayscale conversion, which is the same
 * as the RGB->Y portion of RGB->YCbCr.
 * We assume rgb_ycc_start has been called (we only use the Y tables).
 */

METHODDEF(void)
rgb_gray_convert (j_compress_ptr cinfo,
		  JSAMPARRAY input_buf, JSAMPIMAGE output_buf,
		  JDIMENSION output_row, int num_rows)
{
  my_cconvert_ptr cconvert = (my_cconvert_ptr) cinfo->cconvert;
  register int r, g, b;
  register INT32 * ctab = cconvert->rgb_ycc_tab;
  register JSAMPROW inptr;
  register JSAMPROW outptr;
  register JDIMENSION col;
  JDIMENSION num_cols = cinfo->image_width;

  while (--num_rows >= 0) {
    inptr = *input_buf++;
    outptr = output_buf[0][output_row];
    output_row++;
    for (col = 0; col < num_cols; col++) {
      r = GETJSAMPLE(inptr[RGB_RED]);
      g = GETJSAMPLE(inptr[RGB_GREEN]);
      b = GETJSAMPLE(inptr[RGB_BLUE]);
      inptr += RGB_PIXELSIZE;
      /* Y */
      outptr[col] = (JSAMPLE)
		((ctab[r+R_Y_OFF] + ctab[g+G_Y_OFF] + ctab[b+B_Y_OFF])
		 >> SCALEBITS);
    }
  }
}


/*
 * Convert some rows of samples to the JPEG colorspace.
 * This version handles Adobe-style CMYK->YCCK conversion,
 * where we convert R=1-C, G=1-M, and B=1-Y to YCbCr using the same
 * conversion as above, while passing K (black) unchanged.
 * We assume rgb_ycc_start has been called.
 */

METHODDEF(void)
cmyk_ycck_convert (j_compress_ptr cinfo,
		   JSAMPARRAY input_buf, JSAMPIMAGE output_buf,
		   JDIMENSION output_row, int num_rows)
{
  my_cconvert_ptr cconvert = (my_cconvert_ptr) cinfo->cconvert;
  register int r, g, b;
  register INT32 * ctab = cconvert->rgb_ycc_tab;
  register JSAMPROW inptr;
  register JSAMPROW outptr0, outptr1, outptr2, outptr3;
  register JDIMENSION col;
  JDIMENSION num_cols = cinfo->image_width;

  while (--num_rows >= 0) {
    inptr = *input_buf++;
    outptr0 = output_buf[0][output_row];
    outptr1 = output_buf[1][output_row];
    outptr2 = output_buf[2][output_row];
    outptr3 = output_buf[3][output_row];
    output_row++;
    for (col = 0; col < num_cols; col++) {
      r = MAXJSAMPLE - GETJSAMPLE(inptr[0]);
      g = MAXJSAMPLE - GETJSAMPLE(inptr[1]);
      b = MAXJSAMPLE - GETJSAMPLE(inptr[2]);
      /* K passes through as-is */
      outptr3[col] = inptr[3];	/* don't need GETJSAMPLE here */
      inptr += 4;
      /* If the inputs are 0..MAXJSAMPLE, the outputs of these equations
       * must be too; we do not need an explicit range-limiting operation.
       * Hence the value being shifted is never negative, and we don't
       * need the general RIGHT_SHIFT macro.
       */
      /* Y */
      outptr0[col] = (JSAMPLE)
		((ctab[r+R_Y_OFF] + ctab[g+G_Y_OFF] + ctab[b+B_Y_OFF])
		 >> SCALEBITS);
      /* Cb */
      outptr1[col] = (JSAMPLE)
		((ctab[r+R_CB_OFF] + ctab[g+G_CB_OFF] + ctab[b+B_CB_OFF])
		 >> SCALEBITS);
      /* Cr */
      outptr2[col] = (JSAMPLE)
		((ctab[r+R_CR_OFF] + ctab[g+G_CR_OFF] + ctab[b+B_CR_OFF])
		 >> SCALEBITS);
    }
  }
}


/*
 * Convert some rows of samples to the JPEG colorspace.
 * This version handles grayscale output with no conversion.
 * The source can be either plain grayscale or YCbCr (since Y == gray).
 */

METHODDEF(void)
grayscale_convert (j_compress_ptr cinfo,
		   JSAMPARRAY input_buf, JSAMPIMAGE output_buf,
		   JDIMENSION output_row, int num_rows)
{
  register JSAMPROW inptr;
  register JSAMPROW outptr;
  register JDIMENSION col;
  JDIMENSION num_cols = cinfo->image_width;
  int instride = cinfo->input_components;

  while (--num_rows >= 0) {
    inptr = *input_buf++;
    outptr = output_buf[0][output_row];
    output_row++;
    for (col = 0; col < num_cols; col++) {
      outptr[col] = inptr[0];	/* don't need GETJSAMPLE() here */
      inptr += instride;
    }
  }
}


#if defined(CONFIG_JPEG_ADD_GOOGLEFUNCTION) && defined(ENABLE_ANDROID_NULL_CONVERT)
    typedef unsigned int UINT32; /** support 64bit **/
	#define B0(n)   ((n) & 0xFF)
	#define B1(n)   (((n) >> 8) & 0xFF)
	#define B2(n)   (((n) >> 16) & 0xFF)
	#define B3(n)   ((n) >> 24)
	#define PACK(a, b, c, d)    ((a) | ((b) << 8) | ((c) << 16) | ((d) << 24))

	static int ptr_is_quad(const void* p)
	{
	    return (((const char*)p - (const char*)0) & 3) == 0;
	}
	static void copyquads(const UINT32 in[], UINT32 out0[], UINT32 out1[], UINT32 out2[], int col4)
	{
	    do {
	        UINT32 src0 = *in++;
	        UINT32 src1 = *in++;
	        UINT32 src2 = *in++;
	        // LEndian
	        *out0++ = PACK(B0(src0), B3(src0), B2(src1), B1(src2));
	        *out1++ = PACK(B1(src0), B0(src1), B3(src1), B2(src2));
	        *out2++ = PACK(B2(src0), B1(src1), B0(src2), B3(src2));
	    } while (--col4 != 0);
	}
#endif /** CONFIG_JPEG_ADD_GOOGLEFUNCTION ENABLE_ANDROID_NULL_CONVERT **/


/*
 * Convert some rows of samples to the JPEG colorspace.
 * This version handles multi-component colorspaces without conversion.
 * We assume input_components == num_components.
 */

METHODDEF(void)
null_convert (j_compress_ptr cinfo,
	      JSAMPARRAY input_buf, JSAMPIMAGE output_buf,
	      JDIMENSION output_row, int num_rows)
{
  register JSAMPROW inptr;
  register JSAMPROW outptr;
  register JDIMENSION col;
  register int ci;
  int nc = cinfo->num_components;
  JDIMENSION num_cols = cinfo->image_width;

  #if defined(CONFIG_JPEG_ADD_GOOGLEFUNCTION) && defined(ENABLE_ANDROID_NULL_CONVERT)
	  if (1 == num_rows && 3 == nc && num_cols > 0) 
	  {
	  
		  JSAMPROW inptr   = *input_buf;
		  JSAMPROW outptr0 = output_buf[0][output_row];
		  JSAMPROW outptr1 = output_buf[1][output_row];
		  JSAMPROW outptr2 = output_buf[2][output_row];
		  int col = num_cols;
		  int col4 = col >> 2;
		  if (col4 > 0 && ptr_is_quad(inptr) && ptr_is_quad(outptr0) &&
						  ptr_is_quad(outptr1) && ptr_is_quad(outptr2)) 
		  {
			  
			  const UINT32* in = (const UINT32*)inptr;
			  UINT32* out0     = (UINT32*)outptr0;
			  UINT32* out1     = (UINT32*)outptr1;
			  UINT32* out2     = (UINT32*)outptr2;
			  copyquads(in, out0, out1, out2, col4);
			  col &= 3;

			  if (0 == col)
			  {
				  return;
			  }
			  col4 <<= 2;
			  inptr += col4 * 3;  /* we read this 3 times per in copyquads */
			  outptr0 += col4;
			  outptr1 += col4;
			  outptr2 += col4;
			  /* fall through to while-loop */
		  }
		  
		  do 
		  {
			  *outptr0++ = *inptr++;
			  *outptr1++ = *inptr++;
			  *outptr2++ = *inptr++;
			  
		  } while (--col != 0);
		  
		  return;
		  
	  }
		  
  #endif /** CONFIG_JPEG_ADD_GOOGLEFUNCTION ENABLE_ANDROID_NULL_CONVERT **/

  while (--num_rows >= 0) {
    /* It seems fastest to make a separate pass for each component. */
    for (ci = 0; ci < nc; ci++) {
      inptr = *input_buf;
      outptr = output_buf[ci][output_row];
      for (col = 0; col < num_cols; col++) {
	outptr[col] = inptr[ci]; /* don't need GETJSAMPLE() here */
	inptr += nc;
      }
    }
    input_buf++;
    output_row++;
  }
}


/*
 * Empty method for start_pass.
 */

METHODDEF(void)
null_method (j_compress_ptr cinfo)
{
  /* no work needed */
  if(cinfo->progressive_mode)/** deal with warning **/
  	return;
}


/*
 * Module initialization routine for input colorspace conversion.
 */

GLOBAL(void)
jinit_color_converter (j_compress_ptr cinfo)
{

	  my_cconvert_ptr cconvert;

	  cconvert = (my_cconvert_ptr)
	    (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
					SIZEOF(my_color_converter));
	  cinfo->cconvert = (struct jpeg_color_converter *) cconvert;
	  /* set start_pass to null method until we find out differently */
	  cconvert->pub.start_pass = null_method;

	  /* Make sure input_components agrees with in_color_space */
	  switch (cinfo->in_color_space) 
	  {
		  case JCS_GRAYSCALE:
			    if (cinfo->input_components != 1)
			    {
			    	  ERREXIT(cinfo, JERR_BAD_IN_COLORSPACE);
			    }
			    break;

	 	   case JCS_RGB:
		   case JCS_BGR:
    			if (cinfo->input_components != RGB_PIXELSIZE)
    			{
     			 	ERREXIT(cinfo, JERR_BAD_IN_COLORSPACE);
    			}
    			break;
	 		case JCS_YCbCr:
	   			if (cinfo->input_components != 3)
	   			{
	      			ERREXIT(cinfo, JERR_BAD_IN_COLORSPACE);
	   			}
	    		break;
            case JCS_ARGB_8888:
  			case JCS_ABGR_8888:
			    if (cinfo->input_components != 4)
    			{
     			 	ERREXIT(cinfo, JERR_BAD_IN_COLORSPACE);
    			}
    			break;
			case JCS_RGB_565:
			case JCS_BGR_565:
			case JCS_ARGB_1555:
  			case JCS_ABGR_1555:
			    if (cinfo->input_components != 2)
    			{
     			 	ERREXIT(cinfo, JERR_BAD_IN_COLORSPACE);
    			}
    			break;
	  		 case JCS_CMYK:
	  		 case JCS_YCCK:
	    		if (cinfo->input_components != 4)
	    		{
	      			ERREXIT(cinfo, JERR_BAD_IN_COLORSPACE);
	    		}
	    		break;

	  		 default:/* JCS_UNKNOWN can be anything */
	    		if (cinfo->input_components < 1)
	    		{
	      			ERREXIT(cinfo, JERR_BAD_IN_COLORSPACE);
	    		}
	    		break;
	  }

	  /* Check num_components, set conversion method based on requested space */
	  /** ??????????????????????YCbCr, ????????jpeg_set_colorspace????????**/
	  switch (cinfo->jpeg_color_space) 
	  {
		  case JCS_GRAYSCALE:
			    if (cinfo->num_components != 1)
			    {
			          ERREXIT(cinfo, JERR_BAD_J_COLORSPACE);
			    }
			    if (cinfo->in_color_space == JCS_GRAYSCALE)
			    {
			          cconvert->pub.color_convert = grayscale_convert;
			    }
			    else if (cinfo->in_color_space == JCS_RGB)
				{
				      cconvert->pub.start_pass = rgb_ycc_start;
				      cconvert->pub.color_convert = rgb_gray_convert;
			    } 
				else if (cinfo->in_color_space == JCS_YCbCr)
				{
			      	  cconvert->pub.color_convert = grayscale_convert;
				}
			    else
			    {
			     	   ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
			    }
			    break;
		  case JCS_RGB:
			    if (cinfo->num_components != 3)
			    {
			      		ERREXIT(cinfo, JERR_BAD_J_COLORSPACE);
			    }
			    if (cinfo->in_color_space == JCS_RGB && RGB_PIXELSIZE == 3)
			    {
			      		cconvert->pub.color_convert = null_convert;
			    }
			    else
			    {
			      		ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
			    }
			    break;
		  case JCS_YCbCr:
			    if (cinfo->num_components != 3)
			    {
			      		ERREXIT(cinfo, JERR_BAD_J_COLORSPACE);
			    }
			    if (  (cinfo->in_color_space == JCS_RGB) || (cinfo->in_color_space == JCS_BGR)
					||(cinfo->in_color_space == JCS_ARGB_8888) || (cinfo->in_color_space == JCS_ABGR_8888)) 
				{
					    cconvert->pub.start_pass = rgb_ycc_start;
					    cconvert->pub.color_convert = rgb_ycc_convert;
			    }
				else if (  (cinfo->in_color_space == JCS_RGB_565) || (cinfo->in_color_space == JCS_BGR_565)
					||(cinfo->in_color_space == JCS_ARGB_1555) || (cinfo->in_color_space == JCS_ABGR_1555)) 
				{
					    cconvert->pub.start_pass = rgb_ycc_start;
					    cconvert->pub.color_convert = rgb16_2_ycc_convert;
			    }
				else if (cinfo->in_color_space == JCS_YCbCr)
				{
			      		cconvert->pub.color_convert = null_convert;
				}
			    else
			    {
			      		 ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
			    }
			    break;

		  case JCS_CMYK:
			    if (cinfo->num_components != 4)
			    {
			      		ERREXIT(cinfo, JERR_BAD_J_COLORSPACE);
			    }
			    if (cinfo->in_color_space == JCS_CMYK)
			    {
			      		cconvert->pub.color_convert = null_convert;
			    }
			    else
			    {
			      		ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
			    }
			    break;
		  case JCS_YCCK:
			    if (cinfo->num_components != 4)
			    {
			      		ERREXIT(cinfo, JERR_BAD_J_COLORSPACE);
			    }
			    if (cinfo->in_color_space == JCS_CMYK) 
				{
					    cconvert->pub.start_pass = rgb_ycc_start;
					    cconvert->pub.color_convert = cmyk_ycck_convert;
			    } 
				else if (cinfo->in_color_space == JCS_YCCK)
				{
			    	    cconvert->pub.color_convert = null_convert;
				}
			    else
			    {
			      		ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
			    }
			    break;
		  default:/* allow null conversion of JCS_UNKNOWN */
			    if (cinfo->jpeg_color_space != cinfo->in_color_space || cinfo->num_components != cinfo->input_components)
			    {
			      	ERREXIT(cinfo, JERR_CONVERSION_NOTIMPL);
			    }
			    cconvert->pub.color_convert = null_convert;
			    break;
		  }
	  
}
