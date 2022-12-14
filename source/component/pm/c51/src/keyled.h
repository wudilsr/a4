#ifndef __KEYLED_H__
#define __KEYLED_H__

#include "REG51.h"

#define KEYLED_CT1642_INNER
/*
#define KEYLED_74HC164
#define KEYLED_PT6964
#define KEYLED_CT1642_INNER
#define KEYLED_CT1642
#define KEYLED_PT6961
#define KEYLED_FD650
#define KEYLED_ANSG08
*/

#define NO_DISPLAY 0
#define DIGITAL_DISPLAY 1
#define TIME_DISPLAY 2

typedef enum  hiUNF_KEYLED_TYPE_E
{
    HI_UNF_KEYLED_TYPE_74HC164 = 0x0, /**<KEYLED type:74HC164*/  
    HI_UNF_KEYLED_TYPE_PT6961,    /**<KEYLED type: PT6961*/      
    HI_UNF_KEYLED_TYPE_CT1642,    /**<KEYLED type: CT1642*/      
    HI_UNF_KEYLED_TYPE_PT6964,	  /**<KEYLED type: PT6964*/     
    HI_UNF_KEYLED_TYPE_FD650,     /**<KEYLED type: FD650*/  
    HI_UNF_KEYLED_TYPE_BUTT
}HI_UNF_KEYLED_TYPE_E;


//extern HI_U8  kltype;  
//extern HI_U8  klPmocVal;

/*variable*/
//extern HI_U8  time_hour;
//extern HI_U8  time_minute;
//extern HI_U8  time_second;
//extern HI_U8  time_dot;
//extern HI_U8  time_type;
//extern DATA_U32_S  channum;

//extern HI_VOID keyled_resetParam(HI_VOID);
extern HI_VOID KEYLED_Early_Display(HI_VOID);
extern HI_VOID timer_display(HI_VOID);
extern HI_VOID chan_display(HI_VOID);
extern HI_VOID no_display(HI_VOID); 
extern HI_VOID dbg_display(HI_U16 val);

extern HI_VOID KEYLED_Init(HI_VOID);
//extern HI_VOID keyled_enable(HI_U8 type);
extern HI_VOID KEYLED_Disable(HI_VOID);
extern HI_VOID KEYLED_Isr(HI_VOID);

#endif
