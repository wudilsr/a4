/******************************************************************************
 *    NAND Flash Controller V610 Device Driver
 *    Copyright (c) 2009-2010 by Hisilicon.
 *    All rights reserved.
 * ***
 *    Create By Czyong.
 *
******************************************************************************/

#include <common.h>
#include <nand.h>
#include <asm/io.h>
#include <asm/errno.h>
#include <malloc.h>
#include <linux/mtd/nand.h>
#include <hinfc_gen.h>

#include "hifmc100_nand.h"
#include "hifmcv100_reg.h"

/*****************************************************************************/

static char * hifmc100_hynix_bg_cdie_otp_check(char *otp)
{
	int index = 0;
	int ix, jx;
	char *ptr = NULL;
	int min, cur;
	char *otp_origin, *otp_inverse;

	min = 64;
	for (ix = 0; ix < 8; ix++, otp += 128) {

		otp_origin  = otp;
		otp_inverse = otp + 64;
		cur = 0;

		for (jx = 0; jx < 64; jx++, otp_origin++, otp_inverse++) {
			if (((*otp_origin) ^ (*otp_inverse)) == 0xFF)
				continue;
			cur ++;
		}

		if (cur < min) {
			min = cur;
			index = ix;
			ptr = otp;
			if (!cur)
				break;
		}
	}

	printf("RR select parameter %d from %d, error %d\n",
		index, ix, min);
	return ptr;
}
/*****************************************************************************/

static int hifmc100_hynix_bg_cdie_get_rr_param(void *host)
{
	char *otp;
	u32 regval;
	struct hifmc_host *hifmc_host = (struct hifmc_host *)host;

	hifmc_host->enable_ecc_randomizer(hifmc_host, DISABLE, DISABLE);
	/* step1: reset the chip */
	hifmc_host->send_cmd_reset(hifmc_host, hifmc_host->chipselect);

	/* step2: cmd: 0x36, address: 0xAE, data: 0x00 */
	hifmc_write(hifmc_host, 1, HIFMC100_DATA_NUM);/* data length 1 */
	writel(0x00, hifmc_host->chip->IO_ADDR_R); /* data: 0x00 */
	hifmc_write(hifmc_host, 0xAE, HIFMC100_ADDRL);/* address: 0xAE */
	hifmc_write(hifmc_host, 0x36, HIFMC100_CMD);  /* cmd: 0x36 */

	regval = HIFMC100_OP_CFG_FM_CS(hifmc_host->chipselect)
			| HIFMC100_OP_CFG_ADDR_NUM(1);
	hifmc_write(hifmc_host, regval, HIFMC100_OP_CFG);

	/* according to hynix doc, no need to config HIFMC100_OP_WAIT_READY_EN */
	hifmc_write(hifmc_host, HIFMC100_WRITE_1CMD_1ADD_DATA, HIFMC100_OP);

	FMC_CMD_WAIT_CPU_FINISH(hifmc_host);

	/* step3: address: 0xB0, data: 0x4D */
	hifmc_write(hifmc_host, 1, HIFMC100_DATA_NUM);/* data length 1 */
	writel(0x4D, hifmc_host->chip->IO_ADDR_R); /* data: 0x4d */
	hifmc_write(hifmc_host, 0xB0, HIFMC100_ADDRL);/* address: 0xB0 */
	/* only address and data, without cmd */
	/* according to hynix doc, no need to config HIFMC100_OP_WAIT_READY_EN */
	hifmc_write(hifmc_host, HIFMC100_WRITE_0CMD_1ADD_DATA, HIFMC100_OP);
	FMC_CMD_WAIT_CPU_FINISH(hifmc_host);

	/* step4: cmd: 0x16, 0x17, 0x04, 0x19 */
	hifmc_write(hifmc_host, 0x17 << 8 | 0x16, HIFMC100_CMD);
	/* according to hynix doc, no need to config HIFMC100_OP_WAIT_READY_EN */
	hifmc_write(hifmc_host, HIFMC100_WRITE_2CMD_0ADD_NODATA, HIFMC100_OP);
	FMC_CMD_WAIT_CPU_FINISH(hifmc_host);

	hifmc_write(hifmc_host, 0x19 << 8 | 0x04, HIFMC100_CMD);
	/* according to hynix doc, no need to config HIFMC100_OP_WAIT_READY_EN */
	hifmc_write(hifmc_host, HIFMC100_WRITE_2CMD_0ADD_NODATA, HIFMC100_OP);
	FMC_CMD_WAIT_CPU_FINISH(hifmc_host);

	/* step5: cmd: 0x00 0x30, address: 0x02 00 00 00 */
	hifmc_write(hifmc_host, 0x2000000, HIFMC100_ADDRL);
	hifmc_write(hifmc_host, 0x00, HIFMC100_ADDRH);
	hifmc_write(hifmc_host, 0x30 << 8 | 0x00, HIFMC100_CMD);
	hifmc_write(hifmc_host, 0x800, HIFMC100_DATA_NUM);

	regval = HIFMC100_OP_CFG_FM_CS(hifmc_host->chipselect)
			| HIFMC100_OP_CFG_ADDR_NUM(5);
	hifmc_write(hifmc_host, regval, HIFMC100_OP_CFG);
	/* according to hynix doc, need to config HIFMC100_OP_WAIT_READY_EN */
	hifmc_write(hifmc_host, HIFMC100_READ_2CMD_5ADD, HIFMC100_OP);
	FMC_CMD_WAIT_CPU_FINISH(hifmc_host);

	/*step6 save otp read retry table to mem*/
	otp = hifmc100_hynix_bg_cdie_otp_check(hifmc_host->chip->IO_ADDR_R + 2);
	if (!otp) {
		printf("Read Retry select parameter failed, "
		       "this Nand Chip may be unstable!\n");
		return -1;
	}
	memcpy(hifmc_host->rr_data, otp, 64);
	hifmc_host->need_rr_data = 1;

	/* step7: reset the chip */
	hifmc_host->send_cmd_reset(hifmc_host, hifmc_host->chipselect);

	/* step8: cmd: 0x38 */
	hifmc_write(hifmc_host, 0x38, HIFMC100_CMD);
	/* according to hynix doc, need to config HIFMC100_OP_WAIT_READY_EN */
	hifmc_write(hifmc_host, HIFMC100_WRITE_1CMD_0ADD_NODATA_WAIT_READY, HIFMC100_OP);
	FMC_CMD_WAIT_CPU_FINISH(hifmc_host);

	hifmc_host->enable_ecc_randomizer(hifmc_host, ENABLE, ENABLE);
	/* get hynix otp table finish */
	return 0;
}
/*****************************************************************************/
static char hifmc100_hynix_bg_cdie_rr_reg[8] = {
	0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7};

static int hifmc100_hynix_bg_cdie_set_rr_reg(struct hifmc_host *host,
					     char *val)
{
	int i;
	u32 regval;
	host->enable_ecc_randomizer(host, DISABLE, DISABLE);

	hifmc_write(host, 1, HIFMC100_DATA_NUM);/* data length 1 */
	regval = HIFMC100_OP_CFG_FM_CS(host->chipselect)
			| HIFMC100_OP_CFG_ADDR_NUM(1);
	hifmc_write(host, regval, HIFMC100_OP_CFG);

	for (i = 0; i <= 8; i++) {
		switch (i) {
		case 0:
			writel(val[i], host->chip->IO_ADDR_R);
			hifmc_write(host,
				hifmc100_hynix_bg_cdie_rr_reg[i],
				HIFMC100_ADDRL);
			hifmc_write(host,
				0x36, HIFMC100_CMD);
			/*
			 * no need to config HIFMC100_OP_WAIT_READY_EN, here not config this bit.
			 */
			hifmc_write(host,
				HIFMC100_WRITE_1CMD_1ADD_DATA,
				HIFMC100_OP);
			break;
		case 8:
			hifmc_write(host,
				0x16, HIFMC100_CMD);
			/*
			 * according to hynix doc, only 1 cmd: 0x16. 
			 * And no need to config HIFMC100_OP_WAIT_READY_EN, here not config this bit.
			 */
			hifmc_write(host,
				HIFMC100_WRITE_1CMD_0ADD_NODATA,
				HIFMC100_OP);
			break;
		default:
			writel(val[i], host->chip->IO_ADDR_R);
			hifmc_write(host,
				hifmc100_hynix_bg_cdie_rr_reg[i],
				HIFMC100_ADDRL);
			/*
			 * no need to config HIFMC100_OP_WAIT_READY_EN, here not config this bit.
			 */
			hifmc_write(host,
				HIFMC100_WRITE_0CMD_1ADD_DATA,
				HIFMC100_OP);
			break;
		}
		FMC_CMD_WAIT_CPU_FINISH(host);
	}
	host->enable_ecc_randomizer(host, ENABLE, ENABLE);
	return 0;
}
/*****************************************************************************/
#if 0
static void hifmc100_hynix_bg_cdie_get_rr(struct hifmc_host *host)
{
	int index;
	u32 regval;

	host->enable_ecc_randomizer(host, DISABLE, DISABLE);
	hifmc_write(host, 1, HIFMC100_DATA_NUM);

	regval = HIFMC100_OP_CFG_FM_CS(host->chipselect)
			| HIFMC100_OP_CFG_ADDR_NUM(1);
	hifmc_write(host, regval, HIFMC100_OP_CFG);

	for (index = 0; index < 8; index++) {
		memset(host->chip->IO_ADDR_R, 0xff, 32);
		hifmc_write(host,
			0x37, HIFMC100_CMD);
		hifmc_write(host,
			hifmc100_hynix_bg_cdie_rr_reg[index],
			HIFMC100_ADDRL);
		hifmc_write(host,
			HIFMC100_READ_1CMD_1ADD_DATA,
			HIFMC100_OP);

		FMC_CMD_WAIT_CPU_FINISH(host);

		printf("%02X ", readl(host->chip->IO_ADDR_R) & 0xff);
	}

	host->enable_ecc_randomizer(host, ENABLE, ENABLE);
}
#endif
/*****************************************************************************/

static int hifmc100_hynix_bg_cdie_set_rr_param(void *host, int param)
{
	unsigned char *rr;
	struct hifmc_host *hifmc_host = (struct hifmc_host *)host;

	if (!(hifmc_host->rr_data[0] | hifmc_host->rr_data[1]
	    | hifmc_host->rr_data[2] | hifmc_host->rr_data[3]) || !param)
		return -1;

	rr = (unsigned char *)&hifmc_host->rr_data[((param & 0x07) << 3)];

	/* set the read retry regs to adjust reading level */
	return hifmc100_hynix_bg_cdie_set_rr_reg(hifmc_host, (char *)rr);
}
/*****************************************************************************/

static int hifmc100_hynix_bg_cdie_reset_rr_param(void *host)
{
	return hifmc100_hynix_bg_cdie_set_rr_param((struct hifmc_host *)host, 0);
}
/*****************************************************************************/

static char HYNIX_BG_CDIE_ESLC_PARAM[4];

static int hifmc100_hynix_bg_cdie_eslc_enable(void *host, int enable)
{
	int ix;
	u32 regval;
	char HYNIX_BG_CDIE_ESLC_REG[4] = {0xA0, 0xA1, 0xA7, 0xA8};
	struct hifmc_host *hifmc_host = (struct hifmc_host *)host;

	hifmc_host->enable_ecc_randomizer(hifmc_host, DISABLE, DISABLE);
	hifmc_write(hifmc_host, 1, HIFMC100_DATA_NUM);

	regval = HIFMC100_OP_CFG_FM_CS(hifmc_host->chipselect)
			| HIFMC100_OP_CFG_ADDR_NUM(1);
	hifmc_write(hifmc_host, regval, HIFMC100_OP_CFG);

	for (ix = 0; enable && ix < 4; ix++) {
		memset(hifmc_host->chip->IO_ADDR_R, 0xff, 32);
		hifmc_write(hifmc_host,
			0x37, HIFMC100_CMD);
		hifmc_write(hifmc_host,
			HYNIX_BG_CDIE_ESLC_REG[ix],
			HIFMC100_ADDRL);
		/*
		 * no need to config HIFMC100_OP_WAIT_READY_EN, here not config this bit.
		 */
		hifmc_write(hifmc_host,
			HIFMC100_READ_1CMD_1ADD_DATA,
			HIFMC100_OP);
		FMC_CMD_WAIT_CPU_FINISH(hifmc_host);

		HYNIX_BG_CDIE_ESLC_PARAM[ix] =
			(char)(readl(hifmc_host->chip->IO_ADDR_R) & 0xff);
	}

	for (ix = 0; ix <= 4; ix++) {
		int offset = enable ? 0x0A : 0x00;
		switch (ix) {
		case 0:
			writel(HYNIX_BG_CDIE_ESLC_PARAM[ix] + offset,
				hifmc_host->chip->IO_ADDR_R);
			hifmc_write(hifmc_host,
				HYNIX_BG_CDIE_ESLC_REG[ix],
				HIFMC100_ADDRL);
			hifmc_write(hifmc_host,
				0x36, HIFMC100_CMD);
			/*
			 * no need to config HIFMC100_OP_WAIT_READY_EN, here not config this bit.
			 */
			hifmc_write(hifmc_host,
				HIFMC100_WRITE_1CMD_1ADD_DATA,
				HIFMC100_OP);
			break;
		case 4:
			hifmc_write(hifmc_host,
				0x16, HIFMC100_CMD);
			/*
			 * only have 1 cmd: 0x16
			 * no need to config HIFMC100_OP_WAIT_READY_EN, here not config this bit.
			 */
			hifmc_write(hifmc_host,
				HIFMC100_WRITE_1CMD_0ADD_NODATA,
				HIFMC100_OP);
			break;
		default:
			writel(HYNIX_BG_CDIE_ESLC_PARAM[ix] + offset,
				hifmc_host->chip->IO_ADDR_R);
			hifmc_write(hifmc_host,
				HYNIX_BG_CDIE_ESLC_REG[ix], HIFMC100_ADDRL);
			/*
			 * no need to config HIFMC100_OP_WAIT_READY_EN, here not config this bit.
			 */
			hifmc_write(hifmc_host,
				HIFMC100_WRITE_0CMD_1ADD_DATA,
				HIFMC100_OP);
			break;
		}
		FMC_CMD_WAIT_CPU_FINISH(hifmc_host);
	}

	hifmc_host->enable_ecc_randomizer(hifmc_host, ENABLE, ENABLE);

	if (!enable) {
		hifmc_write(hifmc_host,
			hifmc_host->addr_value[0] & 0xffff0000,
			HIFMC100_ADDRL);
		hifmc_write(hifmc_host,
			hifmc_host->addr_value[1],
			HIFMC100_ADDRH);
		hifmc_write(hifmc_host,
			NAND_CMD_READSTART << 8 | NAND_CMD_READ0,
			HIFMC100_CMD);

		regval = HIFMC100_OP_CFG_FM_CS(hifmc_host->chipselect)
				| HIFMC100_OP_CFG_ADDR_NUM(5);
		hifmc_write(hifmc_host, regval, HIFMC100_OP_CFG);
		/*
		 * need to config HIFMC100_OP_WAIT_READY_EN, here config this bit.
		 */
		hifmc_write(hifmc_host,
			HIFMC100_READ_2CMD_5ADD,
			HIFMC100_OP);

		FMC_CMD_WAIT_CPU_FINISH(hifmc_host);
	}

	return 0;
}
/*****************************************************************************/

struct read_retry_t hifmc100_hynix_bg_cdie_read_retry = {
	.type = NAND_RR_HYNIX_BG_CDIE,
	.count = 8,
	.set_rr_param = hifmc100_hynix_bg_cdie_set_rr_param,
	.get_rr_param = hifmc100_hynix_bg_cdie_get_rr_param,
	.reset_rr_param = hifmc100_hynix_bg_cdie_reset_rr_param,
	.enable_enhanced_slc = hifmc100_hynix_bg_cdie_eslc_enable,
};
