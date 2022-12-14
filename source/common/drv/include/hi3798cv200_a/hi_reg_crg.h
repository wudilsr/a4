//****************************************************************************** 
// Copyright     :  Copyright (C) 2014, Hisilicon Technologies Co., Ltd.
// File name     :  hi_reg_crg.h
// Author        :  xxx
// Version       :  1.0 
// Date          :  2014-09-23
// Description   :  Define all registers/tables for S40V200
// Others        :  Generated automatically by nManager V4.0 
// History       :  xxx 2014-09-23 Create file
//******************************************************************************

#ifndef __HI_REG_CRG_H__
#define __HI_REG_CRG_H__

/* Define the union U_PERI_CRG_PLL0 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cpu_pll_cfg0_apb      : 31  ; /* [30..0]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG_PLL0;

/* Define the union U_PERI_CRG_PLL1 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cpu_pll_cfg1_apb      : 28  ; /* [27..0]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG_PLL1;

/* Define the union U_PERI_CRG_PLL2 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    bpll_ctrl0            : 31  ; /* [30..0]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG_PLL2;

/* Define the union U_PERI_CRG_PLL3 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    bpll_ctrl1            : 28  ; /* [27..0]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG_PLL3;

/* Define the union U_PERI_CRG_PLL4 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ddr_pll_cfg0_apb      : 31  ; /* [30..0]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG_PLL4;

/* Define the union U_PERI_CRG_PLL5 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ddr_pll_cfg1_apb      : 28  ; /* [27..0]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG_PLL5;

/* Define the union U_PERI_CRG_PLL8 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vpll_ctrl0            : 31  ; /* [30..0]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG_PLL8;

/* Define the union U_PERI_CRG_PLL9 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vpll_ctrl1            : 28  ; /* [27..0]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG_PLL9;

/* Define the union U_PERI_CRG_PLL10 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hpll_ctrl0            : 31  ; /* [30..0]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG_PLL10;

/* Define the union U_PERI_CRG_PLL11 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hpll_ctrl1            : 28  ; /* [27..0]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG_PLL11;

/* Define the union U_PERI_CRG_PLL12 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    epll_ctrl0            : 31  ; /* [30..0]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG_PLL12;

/* Define the union U_PERI_CRG_PLL13 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    epll_ctrl1            : 28  ; /* [27..0]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG_PLL13;

/* Define the union U_PERI_CRG_PLL14 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mpll_ctrl0            : 31  ; /* [30..0]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG_PLL14;

/* Define the union U_PERI_CRG_PLL15 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mpll_ctrl1            : 28  ; /* [27..0]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG_PLL15;

/* Define the union U_PERI_CRG18 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cpu_freq_sel_cfg_crg  : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 6   ; /* [8..3]  */
        unsigned int    cpu_begin_cfg_bypass  : 1   ; /* [9]  */
        unsigned int    cpu_sw_begin_cfg      : 1   ; /* [10]  */
        unsigned int    reserved_1            : 1   ; /* [11]  */
        unsigned int    cpu_clk_pctrl         : 1   ; /* [12]  */
        unsigned int    reserved_2            : 19  ; /* [31..13]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG18;

/* Define the union U_PERI_CRG19 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    timeout_plllock       : 12  ; /* [11..0]  */
        unsigned int    lock_bypass           : 1   ; /* [12]  */
        unsigned int    pll_cfg_bypass        : 1   ; /* [13]  */
        unsigned int    reserved_0            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG19;

/* Define the union U_PERI_CRG20 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    a17_aclkm_cken        : 1   ; /* [0]  */
        unsigned int    a17_l2ram_cken        : 1   ; /* [1]  */
        unsigned int    a17_corepo_cken       : 1   ; /* [2]  */
        unsigned int    a17_toppdbg_cken      : 1   ; /* [3]  */
        unsigned int    a17_core0_cken        : 1   ; /* [4]  */
        unsigned int    a17_core1_cken        : 1   ; /* [5]  */
        unsigned int    a17_core2_cken        : 1   ; /* [6]  */
        unsigned int    a17_core3_cken        : 1   ; /* [7]  */
        unsigned int    a17_core_srst_req     : 4   ; /* [11..8]  */
        unsigned int    a17_corepo_srst_req   : 4   ; /* [15..12]  */
        unsigned int    a17_corepdbg_srst_req : 4   ; /* [19..16]  */
        unsigned int    a17_l2ram_srst_req    : 1   ; /* [20]  */
        unsigned int    a17_toppdbg_srst_req  : 1   ; /* [21]  */
        unsigned int    clk_div_peri          : 3   ; /* [24..22]  */
        unsigned int    l2_clk_div            : 2   ; /* [26..25]  */
        unsigned int    aclkm_clk_div         : 1   ; /* [27]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG20;

/* Define the union U_PERI_CRG22 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    core_bus_clk_sel      : 2   ; /* [1..0]  */
        unsigned int    mde0_clk_sel          : 2   ; /* [3..2]  */
        unsigned int    mde1_clk_sel          : 2   ; /* [5..4]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    mde2_clk_sel          : 2   ; /* [9..8]  */
        unsigned int    mde3_clk_sel          : 2   ; /* [11..10]  */
        unsigned int    core_bus_clk_div      : 2   ; /* [13..12]  */
        unsigned int    reserved_1            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG22;

/* Define the union U_PERI_CRG23 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sfc_nand_cken         : 1   ; /* [0]  */
        unsigned int    sfc_nand_srst_req     : 1   ; /* [1]  */
        unsigned int    sfc_nand_clk2x_sel    : 3   ; /* [4..2]  */
        unsigned int    sfc_nor_cken          : 1   ; /* [5]  */
        unsigned int    sfc_nor_srst_req      : 1   ; /* [6]  */
        unsigned int    sfc_nor_clk2x_sel     : 3   ; /* [9..7]  */
        unsigned int    reserved_0            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG23;

/* Define the union U_PERI_CRG24 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    nfc_cken              : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    nfc_srst_req          : 1   ; /* [4]  */
        unsigned int    reserved_1            : 3   ; /* [7..5]  */
        unsigned int    nfc_clk2x_sel         : 2   ; /* [9..8]  */
        unsigned int    reserved_2            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG24;

/* Define the union U_PERI_CRG25 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ddr_cken              : 1   ; /* [0]  */
        unsigned int    hipack0_cken          : 1   ; /* [1]  */
        unsigned int    hipack1_cken          : 1   ; /* [2]  */
        unsigned int    ddrc_cken             : 1   ; /* [3]  */
        unsigned int    reserved_0            : 4   ; /* [7..4]  */
        unsigned int    hipack0_srst_req      : 1   ; /* [8]  */
        unsigned int    hipack1_srst_req      : 1   ; /* [9]  */
        unsigned int    ddrc_srst_req         : 1   ; /* [10]  */
        unsigned int    ddrt_srst_req         : 1   ; /* [11]  */
        unsigned int    ddrt_cken             : 1   ; /* [12]  */
        unsigned int    reserved_1            : 19  ; /* [31..13]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG25;

/* Define the union U_PERI_CRG26 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    uart0_cken            : 1   ; /* [0]  */
        unsigned int    uart0_srst_req        : 1   ; /* [1]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    uart2_cken            : 1   ; /* [4]  */
        unsigned int    uart2_srst_req        : 1   ; /* [5]  */
        unsigned int    uart3_cken            : 1   ; /* [6]  */
        unsigned int    uart3_srst_req        : 1   ; /* [7]  */
        unsigned int    uart4_cken            : 1   ; /* [8]  */
        unsigned int    uart4_srst_req        : 1   ; /* [9]  */
        unsigned int    reserved_1            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG26;

/* Define the union U_PERI_CRG27 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    i2c_qam_cken          : 1   ; /* [0]  */
        unsigned int    i2c_qam_srst_req      : 1   ; /* [1]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    i2c0_cken             : 1   ; /* [4]  */
        unsigned int    i2c0_srst_req         : 1   ; /* [5]  */
        unsigned int    reserved_1            : 2   ; /* [7..6]  */
        unsigned int    i2c1_cken             : 1   ; /* [8]  */
        unsigned int    i2c1_srst_req         : 1   ; /* [9]  */
        unsigned int    reserved_2            : 2   ; /* [11..10]  */
        unsigned int    i2c2_cken             : 1   ; /* [12]  */
        unsigned int    i2c2_srst_req         : 1   ; /* [13]  */
        unsigned int    reserved_3            : 2   ; /* [15..14]  */
        unsigned int    i2c3_cken             : 1   ; /* [16]  */
        unsigned int    i2c3_srst_req         : 1   ; /* [17]  */
        unsigned int    reserved_4            : 2   ; /* [19..18]  */
        unsigned int    i2c4_cken             : 1   ; /* [20]  */
        unsigned int    i2c4_srst_req         : 1   ; /* [21]  */
        unsigned int    reserved_5            : 2   ; /* [23..22]  */
        unsigned int    i2c5_cken             : 1   ; /* [24]  */
        unsigned int    i2c5_srst_req         : 1   ; /* [25]  */
        unsigned int    reserved_6            : 2   ; /* [27..26]  */
        unsigned int    i2c_adc_cken          : 1   ; /* [28]  */
        unsigned int    i2c_adc_srst_req      : 1   ; /* [29]  */
        unsigned int    reserved_7            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG27;

/* Define the union U_PERI_CRG28 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ssp0_cken             : 1   ; /* [0]  */
        unsigned int    ssp0_srst_req         : 1   ; /* [1]  */
        unsigned int    ssp1_cken             : 1   ; /* [2]  */
        unsigned int    ssp1_srst_req         : 1   ; /* [3]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG28;

/* Define the union U_PERI_CRG29 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sci0_cken             : 1   ; /* [0]  */
        unsigned int    sci0_srst_req         : 1   ; /* [1]  */
        unsigned int    reserved_0            : 30  ; /* [31..2]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG29;

/* Define the union U_PERI_CRG30 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vdh_cken              : 1   ; /* [0]  */
        unsigned int    vdhdsp_cken           : 1   ; /* [1]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    vdh_all_srst_req      : 1   ; /* [4]  */
        unsigned int    vdh_scd_srst_req      : 1   ; /* [5]  */
        unsigned int    vdh_mfd_srst_req      : 1   ; /* [6]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    vdh_clk_sel           : 2   ; /* [9..8]  */
        unsigned int    reserved_2            : 2   ; /* [11..10]  */
        unsigned int    vdhclk_skipcfg        : 5   ; /* [16..12]  */
        unsigned int    vdhclk_loaden         : 1   ; /* [17]  */
        unsigned int    reserved_3            : 14  ; /* [31..18]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG30;

/* Define the union U_PERI_CRG31 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    jpgd_cken             : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    jpgd_srst_req         : 1   ; /* [4]  */
        unsigned int    reserved_1            : 3   ; /* [7..5]  */
        unsigned int    jpgd_clk_sel          : 1   ; /* [8]  */
        unsigned int    reserved_2            : 23  ; /* [31..9]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG31;

/* Define the union U_PERI_CRG33 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pgd_cken              : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    pgd_srst_req          : 1   ; /* [4]  */
        unsigned int    reserved_1            : 27  ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG33;

/* Define the union U_PERI_CRG34 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    bpd_cken              : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    bpd_srst_req          : 1   ; /* [4]  */
        unsigned int    reserved_1            : 27  ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG34;

/* Define the union U_PERI_CRG35 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    venc_cken             : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    venc_srst_req         : 1   ; /* [4]  */
        unsigned int    reserved_1            : 2   ; /* [6..5]  */
        unsigned int    venc_clk_sel          : 2   ; /* [8..7]  */
        unsigned int    reserved_2            : 23  ; /* [31..9]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG35;

/* Define the union U_PERI_CRG36 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    jpge_cken             : 1   ; /* [0]  */
        unsigned int    jpge_clk_sel          : 2   ; /* [2..1]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    jpge_srst_req         : 1   ; /* [4]  */
        unsigned int    reserved_1            : 27  ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG36;

/* Define the union U_PERI_CRG37 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    tde_cken              : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    tde_srst_req          : 1   ; /* [4]  */
        unsigned int    reserved_1            : 3   ; /* [7..5]  */
        unsigned int    tde_clk_sel           : 2   ; /* [9..8]  */
        unsigned int    reserved_2            : 2   ; /* [11..10]  */
        unsigned int    tdeclk_skipcfg        : 5   ; /* [16..12]  */
        unsigned int    tdeclk_loaden         : 1   ; /* [17]  */
        unsigned int    reserved_3            : 14  ; /* [31..18]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG37;

/* Define the union U_PERI_CRG39 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sdio0_bus_cken        : 1   ; /* [0]  */
        unsigned int    sdio0_cken            : 1   ; /* [1]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    sdio0_srst_req        : 1   ; /* [4]  */
        unsigned int    reserved_1            : 3   ; /* [7..5]  */
        unsigned int    sdio0_clk_sel         : 3   ; /* [10..8]  */
        unsigned int    reserved_2            : 1   ; /* [11]  */
        unsigned int    sdio0_sap_ps_sel      : 3   ; /* [14..12]  */
        unsigned int    reserved_3            : 1   ; /* [15]  */
        unsigned int    sdio0_drv_ps_sel      : 3   ; /* [18..16]  */
        unsigned int    sdio0_clk_mode        : 1   ; /* [19]  */
        unsigned int    reserved_4            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG39;

/* Define the union U_PERI_CRG40 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sdio2_bus_cken        : 1   ; /* [0]  */
        unsigned int    sdio2_cken            : 1   ; /* [1]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    sdio2_srst_req        : 1   ; /* [4]  */
        unsigned int    reserved_1            : 3   ; /* [7..5]  */
        unsigned int    sdio2_clk_sel         : 3   ; /* [10..8]  */
        unsigned int    reserved_2            : 1   ; /* [11]  */
        unsigned int    sdio2_sap_ps_sel      : 3   ; /* [14..12]  */
        unsigned int    reserved_3            : 1   ; /* [15]  */
        unsigned int    sdio2_drv_ps_sel      : 3   ; /* [18..16]  */
        unsigned int    sdio2_clk_mode        : 1   ; /* [19]  */
        unsigned int    reserved_4            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG40;

/* Define the union U_PERI_CRG42 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sata_bus_cken         : 1   ; /* [0]  */
        unsigned int    sata_rx0_cken         : 1   ; /* [1]  */
        unsigned int    sata_cko_alive_cken   : 1   ; /* [2]  */
        unsigned int    sata_tx0_cken         : 1   ; /* [3]  */
        unsigned int    reserved_0            : 4   ; /* [7..4]  */
        unsigned int    sata_bus_srst_req     : 1   ; /* [8]  */
        unsigned int    sata_cko_alive_srst_req : 1   ; /* [9]  */
        unsigned int    sata_rx0_srst_req     : 1   ; /* [10]  */
        unsigned int    sata0_srst_req        : 1   ; /* [11]  */
        unsigned int    reserved_1            : 5   ; /* [16..12]  */
        unsigned int    sata_rx1_cken         : 1   ; /* [17]  */
        unsigned int    reserved_2            : 1   ; /* [18]  */
        unsigned int    sata_tx1_cken         : 1   ; /* [19]  */
        unsigned int    reserved_3            : 6   ; /* [25..20]  */
        unsigned int    sata_rx1_srst_req     : 1   ; /* [26]  */
        unsigned int    sata1_srst_req        : 1   ; /* [27]  */
        unsigned int    reserved_4            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG42;

/* Define the union U_PERI_CRG44 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    usb3_bus_cken         : 1   ; /* [0]  */
        unsigned int    usb3_ref_cken         : 1   ; /* [1]  */
        unsigned int    usb3_suspend_cken     : 1   ; /* [2]  */
        unsigned int    usb3_pipe_cken        : 1   ; /* [3]  */
        unsigned int    usb3_utmi_cken        : 1   ; /* [4]  */
        unsigned int    usb3_bus_gs_cken      : 1   ; /* [5]  */
        unsigned int    usb3_bus_gm_cken      : 1   ; /* [6]  */
        unsigned int    reserved_0            : 5   ; /* [11..7]  */
        unsigned int    usb3_vcc_srst_req     : 1   ; /* [12]  */
        unsigned int    reserved_1            : 3   ; /* [15..13]  */
        unsigned int    usb3_bus_cken1        : 1   ; /* [16]  */
        unsigned int    usb3_ref_cken1        : 1   ; /* [17]  */
        unsigned int    usb3_suspend_cken1    : 1   ; /* [18]  */
        unsigned int    usb3_pipe_cken1       : 1   ; /* [19]  */
        unsigned int    usb3_utmi_cken1       : 1   ; /* [20]  */
        unsigned int    usb3_bus_gs_cken1     : 1   ; /* [21]  */
        unsigned int    usb3_bus_gm_cken1     : 1   ; /* [22]  */
        unsigned int    reserved_2            : 5   ; /* [27..23]  */
        unsigned int    usb3_vcc_srst_req1    : 1   ; /* [28]  */
        unsigned int    reserved_3            : 3   ; /* [31..29]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG44;

/* Define the union U_PERI_CRG46 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    usb2_bus_cken         : 1   ; /* [0]  */
        unsigned int    usb2_ohci48m_cken     : 1   ; /* [1]  */
        unsigned int    usb2_ohci12m_cken     : 1   ; /* [2]  */
        unsigned int    usb2_otg_utmi_cken    : 1   ; /* [3]  */
        unsigned int    usb2_hst_phy_cken     : 1   ; /* [4]  */
        unsigned int    usb2_utmi0_cken       : 1   ; /* [5]  */
        unsigned int    reserved_0            : 6   ; /* [11..6]  */
        unsigned int    usb2_bus_srst_req     : 1   ; /* [12]  */
        unsigned int    usb2_utmi0_srst_req   : 1   ; /* [13]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    usb2_hst_phy_srst_req : 1   ; /* [16]  */
        unsigned int    usb2_otg_phy_srst_req : 1   ; /* [17]  */
        unsigned int    reserved_2            : 2   ; /* [19..18]  */
        unsigned int    usb2_clk48_sel        : 1   ; /* [20]  */
        unsigned int    reserved_3            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG46;

/* Define the union U_PERI_CRG47 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    usb2_phy01_ref_cken   : 1   ; /* [0]  */
        unsigned int    reserved_0            : 1   ; /* [1]  */
        unsigned int    usb2_phy2_ref_cken    : 1   ; /* [2]  */
        unsigned int    usb2_phy3_ref_cken    : 1   ; /* [3]  */
        unsigned int    usb2_phy01_srst_req   : 1   ; /* [4]  */
        unsigned int    reserved_1            : 1   ; /* [5]  */
        unsigned int    usb2_phy2_srst_req    : 1   ; /* [6]  */
        unsigned int    usb2_phy3_srst_req    : 1   ; /* [7]  */
        unsigned int    usb2_phy01_srst_treq0 : 1   ; /* [8]  */
        unsigned int    usb2_phy01_srst_treq1 : 1   ; /* [9]  */
        unsigned int    usb2_phy2_srst_treq   : 1   ; /* [10]  */
        unsigned int    usb2_phy3_srst_treq   : 1   ; /* [11]  */
        unsigned int    usb2_phy01_refclk_sel : 1   ; /* [12]  */
        unsigned int    reserved_2            : 1   ; /* [13]  */
        unsigned int    usb2_phy2_refclk_sel  : 1   ; /* [14]  */
        unsigned int    usb2_phy3_refclk_sel  : 1   ; /* [15]  */
        unsigned int    reserved_3            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG47;

/* Define the union U_PERI_CRG48 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 9   ; /* [8..0]  */
        unsigned int    ca_ci_srst_req        : 1   ; /* [9]  */
        unsigned int    otp_srst_req          : 1   ; /* [10]  */
        unsigned int    reserved_1            : 1   ; /* [11]  */
        unsigned int    ca_ci_clk_sel         : 1   ; /* [12]  */
        unsigned int    reserved_2            : 19  ; /* [31..13]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG48;

/* Define the union U_PERI_CRG49 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sha_cken              : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    sha_srst_req          : 1   ; /* [4]  */
        unsigned int    reserved_1            : 27  ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG49;

/* Define the union U_PERI_CRG50 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pmc_cken              : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    pmc_srst_req          : 1   ; /* [4]  */
        unsigned int    reserved_1            : 27  ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG50;

/* Define the union U_PERI_CRG51 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gsf_bus_s_cken        : 1   ; /* [0]  */
        unsigned int    gsf_bus_m0_cken       : 1   ; /* [1]  */
        unsigned int    gsf_bus_m1_cken       : 1   ; /* [2]  */
        unsigned int    gsf_ge0_cken          : 1   ; /* [3]  */
        unsigned int    gsf_ge1_cken          : 1   ; /* [4]  */
        unsigned int    gsf_pub_cken          : 1   ; /* [5]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    gsf_p0_srst_req       : 1   ; /* [8]  */
        unsigned int    gsf_p1_srst_req       : 1   ; /* [9]  */
        unsigned int    gsf_mac0_srst_req     : 1   ; /* [10]  */
        unsigned int    gsf_mac1_srst_req     : 1   ; /* [11]  */
        unsigned int    gsf_rmii0_rst_out     : 1   ; /* [12]  */
        unsigned int    gsf_rmii1_rst_out     : 1   ; /* [13]  */
        unsigned int    reserved_1            : 1   ; /* [14]  */
        unsigned int    reserved_2            : 1   ; /* [15]  */
        unsigned int    gsf_rmii2_rst_out     : 1   ; /* [16]  */
        unsigned int    reserved_3            : 1   ; /* [17]  */
        unsigned int    gsf_bus_s_cken1       : 1   ; /* [18]  */
        unsigned int    gsf_bus_m0_cken1      : 1   ; /* [19]  */
        unsigned int    gsf_ge0_cken1         : 1   ; /* [20]  */
        unsigned int    gsf_pub_cken1         : 1   ; /* [21]  */
        unsigned int    gsf_p0_srst_req1      : 1   ; /* [22]  */
        unsigned int    gsf_mac0_srst_req1    : 1   ; /* [23]  */
        unsigned int    mac_if0_cken          : 1   ; /* [24]  */
        unsigned int    mac_if1_cken          : 1   ; /* [25]  */
        unsigned int    mac_if2_cken          : 1   ; /* [26]  */
        unsigned int    reserved_4            : 5   ; /* [31..27]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG51;

/* Define the union U_PERI_CRG53 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gpu_cken              : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    gpu_srst_req          : 1   ; /* [4]  */
        unsigned int    reserved_1            : 27  ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG53;

/* Define the union U_PERI_CRG54 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vo_bus_cken           : 1   ; /* [0]  */
        unsigned int    vo_hd_sub_cken        : 1   ; /* [1]  */
        unsigned int    vo_sd_cken            : 1   ; /* [2]  */
        unsigned int    vo_sdate_cken         : 1   ; /* [3]  */
        unsigned int    vo_hd_cken            : 1   ; /* [4]  */
        unsigned int    vo_hdate_cken         : 1   ; /* [5]  */
        unsigned int    vdac_ch0_cken         : 1   ; /* [6]  */
        unsigned int    vdac_ch1_cken         : 1   ; /* [7]  */
        unsigned int    vdac_ch2_cken         : 1   ; /* [8]  */
        unsigned int    vdac_ch3_cken         : 1   ; /* [9]  */
        unsigned int    sd_ppc_cken           : 1   ; /* [10]  */
        unsigned int    hd_ppc_cken           : 1   ; /* [11]  */
        unsigned int    vo_sd_clk_sel         : 1   ; /* [12]  */
        unsigned int    hdmi_fifo_cken        : 1   ; /* [13]  */
        unsigned int    vo_sd_clk_div         : 2   ; /* [15..14]  */
        unsigned int    vo_hd_clk_sel         : 1   ; /* [16]  */
        unsigned int    hdmi_clk_sel_ssc      : 1   ; /* [17]  */
        unsigned int    vo_hd_clk_div         : 2   ; /* [19..18]  */
        unsigned int    vdac_ch0_clk_sel      : 1   ; /* [20]  */
        unsigned int    vdac_ch1_clk_sel      : 1   ; /* [21]  */
        unsigned int    vdac_ch2_clk_sel      : 1   ; /* [22]  */
        unsigned int    vdac_ch3_clk_sel      : 1   ; /* [23]  */
        unsigned int    vo_ppc_cken           : 1   ; /* [24]  */
        unsigned int    hdmi_clk_sel          : 1   ; /* [25]  */
        unsigned int    vo_sd_hdmi_clk_sel    : 1   ; /* [26]  */
        unsigned int    vdp_clk_sel           : 2   ; /* [28..27]  */
        unsigned int    vo_hd_hdmi_clk_sel    : 1   ; /* [29]  */
        unsigned int    vou_srst_req          : 1   ; /* [30]  */
        unsigned int    vdp_cfg_cken          : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG54;

/* Define the union U_PERI_CRG55 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vi_bus_cken           : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    vi_bus_srst_req       : 1   ; /* [4]  */
        unsigned int    reserved_1            : 4   ; /* [8..5]  */
        unsigned int    vicap_clk_sel         : 2   ; /* [10..9]  */
        unsigned int    reserved_2            : 1   ; /* [11]  */
        unsigned int    vi_ppc0_cken          : 1   ; /* [12]  */
        unsigned int    vi_ppc0_srst_req      : 1   ; /* [13]  */
        unsigned int    vi_p0_cken            : 1   ; /* [14]  */
        unsigned int    vi_p0_srst_req        : 1   ; /* [15]  */
        unsigned int    reserved_3            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG55;

/* Define the union U_PERI_CRG56 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    qtc_bus_cken          : 1   ; /* [0]  */
        unsigned int    qtc_cken              : 1   ; /* [1]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    qtc_srst_req          : 1   ; /* [4]  */
        unsigned int    reserved_1            : 3   ; /* [7..5]  */
        unsigned int    qtc_clk_pctrl         : 1   ; /* [8]  */
        unsigned int    reserved_2            : 23  ; /* [31..9]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG56;

/* Define the union U_PERI_CRG58 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    qamc_demo_cken        : 1   ; /* [0]  */
        unsigned int    qamc_adc_cken         : 1   ; /* [1]  */
        unsigned int    qamc_srst_req         : 1   ; /* [2]  */
        unsigned int    qamadc_clk_pctrl      : 1   ; /* [3]  */
        unsigned int    qamadc_srst_req       : 1   ; /* [4]  */
        unsigned int    reserved_0            : 5   ; /* [9..5]  */
        unsigned int    qamctrl_clk_sel       : 1   ; /* [10]  */
        unsigned int    reserved_1            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG58;

/* Define the union U_PERI_CRG60 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vpss_cken             : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    vpss_srst_req         : 1   ; /* [4]  */
        unsigned int    reserved_1            : 3   ; /* [7..5]  */
        unsigned int    vpss_clk_sel          : 2   ; /* [9..8]  */
        unsigned int    reserved_2            : 2   ; /* [11..10]  */
        unsigned int    vpssclk_skipcfg       : 5   ; /* [16..12]  */
        unsigned int    vpssclk_loaden        : 1   ; /* [17]  */
        unsigned int    reserved_3            : 14  ; /* [31..18]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG60;

/* Define the union U_PERI_CRG61 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hwc_cken              : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    hwc_srst_req          : 1   ; /* [4]  */
        unsigned int    reserved_1            : 3   ; /* [7..5]  */
        unsigned int    hwc_clk_sel           : 2   ; /* [9..8]  */
        unsigned int    hwcclk_skipcfg        : 5   ; /* [14..10]  */
        unsigned int    hwcclk_loaden         : 1   ; /* [15]  */
        unsigned int    reserved_2            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG61;

/* Define the union U_PERI_CRG63 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pvr_bus_cken          : 1   ; /* [0]  */
        unsigned int    pvr_dmx_cken          : 1   ; /* [1]  */
        unsigned int    pvr_27m_cken          : 1   ; /* [2]  */
        unsigned int    pvr_tsi1_cken         : 1   ; /* [3]  */
        unsigned int    pvr_tsi2_cken         : 1   ; /* [4]  */
        unsigned int    pvr_tsi3_cken         : 1   ; /* [5]  */
        unsigned int    pvr_tsi4_cken         : 1   ; /* [6]  */
        unsigned int    pvr_tsi5_cken         : 1   ; /* [7]  */
        unsigned int    pvr_tsi6_cken         : 1   ; /* [8]  */
        unsigned int    pvr_tsi7_cken         : 1   ; /* [9]  */
        unsigned int    pvr_ts0_cken          : 1   ; /* [10]  */
        unsigned int    reserved_0            : 1   ; /* [11]  */
        unsigned int    pvr_tsout0_cken       : 1   ; /* [12]  */
        unsigned int    reserved_1            : 1   ; /* [13]  */
        unsigned int    pvr_tsi10_pctrl       : 1   ; /* [14]  */
        unsigned int    pvr_tsi11_pctrl       : 1   ; /* [15]  */
        unsigned int    pvr_tsi2_pctrl        : 1   ; /* [16]  */
        unsigned int    pvr_tsi3_pctrl        : 1   ; /* [17]  */
        unsigned int    pvr_tsi4_pctrl        : 1   ; /* [18]  */
        unsigned int    pvr_tsi5_pctrl        : 1   ; /* [19]  */
        unsigned int    pvr_tsi6_pctrl        : 1   ; /* [20]  */
        unsigned int    pvr_tsi7_pctrl        : 1   ; /* [21]  */
        unsigned int    pvr_tsi8_pctrl        : 1   ; /* [22]  */
        unsigned int    pvr_tsi9_pctrl        : 1   ; /* [23]  */
        unsigned int    pvr_srst_req          : 1   ; /* [24]  */
        unsigned int    pvr_tsi8_cken         : 1   ; /* [25]  */
        unsigned int    pvr_tsi9_cken         : 1   ; /* [26]  */
        unsigned int    pvr_tsi10_cken        : 1   ; /* [27]  */
        unsigned int    pvr_tsi11_cken        : 1   ; /* [28]  */
        unsigned int    pvr_tsi12_cken        : 1   ; /* [29]  */
        unsigned int    pvr_tsi12_pctrl       : 1   ; /* [30]  */
        unsigned int    pvr_tsi13_pctrl       : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG63;

/* Define the union U_PERI_CRG64 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pvr_tsout0_pctrl      : 1   ; /* [0]  */
        unsigned int    reserved_0            : 1   ; /* [1]  */
        unsigned int    pvr_dmx_clk_sel       : 1   ; /* [2]  */
        unsigned int    pvr_tsi13_cken        : 1   ; /* [3]  */
        unsigned int    sw_dmx_clk_div        : 5   ; /* [8..4]  */
        unsigned int    sw_dmxclk_loaden      : 1   ; /* [9]  */
        unsigned int    pvr_dmx_clkdiv_cfg    : 1   ; /* [10]  */
        unsigned int    reserved_1            : 1   ; /* [11]  */
        unsigned int    pvr_ts0_clk_sel       : 2   ; /* [13..12]  */
        unsigned int    reserved_2            : 2   ; /* [15..14]  */
        unsigned int    pvr_ts0_clk_div       : 4   ; /* [19..16]  */
        unsigned int    reserved_3            : 4   ; /* [23..20]  */
        unsigned int    clk_tsi03_com_sel     : 3   ; /* [26..24]  */
        unsigned int    reserved_4            : 1   ; /* [27]  */
        unsigned int    clk_tsi47_com_sel     : 3   ; /* [30..28]  */
        unsigned int    reserved_5            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG64;

/* Define the union U_PERI_CRG67 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdmitx_ctrl_bus_cken  : 1   ; /* [0]  */
        unsigned int    hdmitx_ctrl_cec_cken  : 1   ; /* [1]  */
        unsigned int    hdmitx_ctrl_id_cken   : 1   ; /* [2]  */
        unsigned int    hdmitx_ctrl_mhl_cken  : 1   ; /* [3]  */
        unsigned int    hdmitx_ctrl_os_cken   : 1   ; /* [4]  */
        unsigned int    hdmitx_ctrl_as_cken   : 1   ; /* [5]  */
        unsigned int    hdmitx_ctrl_mhl_clk_pctrl : 1   ; /* [6]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    hdmitx_ctrl_bus_srst_req : 1   ; /* [8]  */
        unsigned int    hdmitx_ctrl_srst_req  : 1   ; /* [9]  */
        unsigned int    reserved_1            : 4   ; /* [13..10]  */
        unsigned int    hdmitx_ctrl_asclk_sel : 1   ; /* [14]  */
        unsigned int    reserved_2            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG67;

/* Define the union U_PERI_CRG68 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 4   ; /* [3..0]  */
        unsigned int    hdmitx_phy_srst_req   : 1   ; /* [4]  */
        unsigned int    reserved_1            : 27  ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG68;

/* Define the union U_PERI_CRG69 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    adac_cken             : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    adac_srst_req         : 1   ; /* [4]  */
        unsigned int    reserved_1            : 27  ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG69;

/* Define the union U_PERI_CRG70 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    aiao_cken             : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    aiao_srst_req         : 1   ; /* [4]  */
        unsigned int    reserved_1            : 7   ; /* [11..5]  */
        unsigned int    aiaoclk_skipcfg       : 5   ; /* [16..12]  */
        unsigned int    aiaoclk_loaden        : 1   ; /* [17]  */
        unsigned int    reserved_2            : 2   ; /* [19..18]  */
        unsigned int    aiao_mclk_sel         : 2   ; /* [21..20]  */
        unsigned int    reserved_3            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG70;

/* Define the union U_PERI_CRG71 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vdac_chop_cken        : 1   ; /* [0]  */
        unsigned int    reserved_0            : 15  ; /* [15..1]  */
        unsigned int    vdac_0_clk_pctrl      : 1   ; /* [16]  */
        unsigned int    vdac_1_clk_pctrl      : 1   ; /* [17]  */
        unsigned int    vdac_2_clk_pctrl      : 1   ; /* [18]  */
        unsigned int    vdac_3_clk_pctrl      : 1   ; /* [19]  */
        unsigned int    reserved_1            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG71;

/* Define the union U_PERI_CRG72 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fephy_cken            : 1   ; /* [0]  */
        unsigned int    reserved_0            : 3   ; /* [3..1]  */
        unsigned int    fephy_srst_req        : 1   ; /* [4]  */
        unsigned int    reserved_1            : 3   ; /* [7..5]  */
        unsigned int    fephy_clk_sel         : 1   ; /* [8]  */
        unsigned int    reserved_2            : 23  ; /* [31..9]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG72;

/* Define the union U_PERI_CRG73 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gpu_freq_sel_cfg_crg  : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 6   ; /* [8..3]  */
        unsigned int    gpu_begin_cfg_bypass  : 1   ; /* [9]  */
        unsigned int    gpu_sw_begin_cfg      : 1   ; /* [10]  */
        unsigned int    reserved_1            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG73;

/* Define the union U_PERI_CRG74 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ddr_freq_sel_cfg_crg  : 3   ; /* [2..0]  */
        unsigned int    reserved_0            : 6   ; /* [8..3]  */
        unsigned int    ddr_begin_cfg_bypass  : 1   ; /* [9]  */
        unsigned int    ddr_sw_begin_cfg      : 1   ; /* [10]  */
        unsigned int    reserved_1            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG74;

/* Define the union U_PERI_CRG75 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    apll_ssmod_ctrl       : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG75;

/* Define the union U_PERI_CRG76 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    bpll_ssmod_ctrl       : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG76;

/* Define the union U_PERI_CRG77 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dpll_ssmod_ctrl       : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG77;

/* Define the union U_PERI_CRG79 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vpll_ssmod_ctrl       : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG79;

/* Define the union U_PERI_CRG80 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hpll_ssmod_ctrl       : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG80;

/* Define the union U_PERI_CRG81 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    epll_ssmod_ctrl       : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG81;

/* Define the union U_PERI_CRG82 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mpll_ssmod_ctrl       : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG82;

/* Define the union U_PERI_CRG84 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pll_lock              : 10  ; /* [9..0]  */
        unsigned int    reserved_0            : 22  ; /* [31..10]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG84;

/* Define the union U_PERI_CRG85 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cpu_clk_sw_ok_crg     : 1   ; /* [0]  */
        unsigned int    cpu_clk_mux           : 3   ; /* [3..1]  */
        unsigned int    gpu_clk_sw_ok_crg     : 1   ; /* [4]  */
        unsigned int    gpu_clk_mux           : 3   ; /* [7..5]  */
        unsigned int    ddr_clk_sw_ok_crg     : 1   ; /* [8]  */
        unsigned int    ddr_clk_mux           : 3   ; /* [11..9]  */
        unsigned int    core_bus_clk_seled    : 2   ; /* [13..12]  */
        unsigned int    sdio0_clk_seled       : 3   ; /* [16..14]  */
        unsigned int    sdio1_clk_seled       : 3   ; /* [19..17]  */
        unsigned int    mde0_clk_seled        : 2   ; /* [21..20]  */
        unsigned int    mde1_clk_seled        : 2   ; /* [23..22]  */
        unsigned int    mde2_clk_seled        : 2   ; /* [25..24]  */
        unsigned int    mde3_clk_seled        : 2   ; /* [27..26]  */
        unsigned int    reserved_0            : 1   ; /* [28]  */
        unsigned int    vdh_clk_seled         : 2   ; /* [30..29]  */
        unsigned int    reserved_1            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG85;

/* Define the union U_PERI_CRG_PLL86 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cpu_pll_cfg0_sw       : 31  ; /* [30..0]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG_PLL86;

/* Define the union U_PERI_CRG_PLL87 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cpu_pll_cfg1_sw       : 28  ; /* [27..0]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG_PLL87;

/* Define the union U_PERI_CRG_PLL88 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ddr_pll_cfg0_sw       : 31  ; /* [30..0]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG_PLL88;

/* Define the union U_PERI_CRG_PLL89 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ddr_pll_cfg1_sw       : 28  ; /* [27..0]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG_PLL89;

/* Define the union U_PERI_CRG90 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    slic_rst0_out         : 1   ; /* [0]  */
        unsigned int    fe_rstn_out           : 1   ; /* [1]  */
        unsigned int    dem_rst0_out          : 1   ; /* [2]  */
        unsigned int    mute_ctrl_out         : 1   ; /* [3]  */
        unsigned int    slic_rst1_out         : 1   ; /* [4]  */
        unsigned int    dem_rst1_out          : 1   ; /* [5]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG90;

/* Define the union U_PERI_CRG93 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vdh_all_rst_ok        : 1   ; /* [0]  */
        unsigned int    vdh_scd_rst_ok        : 1   ; /* [1]  */
        unsigned int    vdh_mfd_rst_ok        : 1   ; /* [2]  */
        unsigned int    vdh1_all_rst_ok       : 1   ; /* [3]  */
        unsigned int    vdh1_scd_rst_ok       : 1   ; /* [4]  */
        unsigned int    vdh1_mfd_rst_ok       : 1   ; /* [5]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG93;

/* Define the union U_PERI_CRG94 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    wdg0_cken             : 1   ; /* [0]  */
        unsigned int    wdg1_cken             : 1   ; /* [1]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    wdg0_srst_req         : 1   ; /* [4]  */
        unsigned int    wdg1_srst_req         : 1   ; /* [5]  */
        unsigned int    reserved_1            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG94;

/* Define the union U_PERI_CRG95 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pll_test_en           : 1   ; /* [0]  */
        unsigned int    test_clk_sel          : 1   ; /* [1]  */
        unsigned int    test_clk_en           : 1   ; /* [2]  */
        unsigned int    hdmitx_phy_test_clk_en : 1   ; /* [3]  */
        unsigned int    hdmirx_phy_test_clk_en : 1   ; /* [4]  */
        unsigned int    fephy_test_clk_en     : 1   ; /* [5]  */
        unsigned int    reserved_0            : 26  ; /* [31..6]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG95;

/* Define the union U_PERI_CRG96 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mem_adjust_cpu        : 28  ; /* [27..0]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG96;

/* Define the union U_PERI_CRG97 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mem_adjust_gpu        : 16  ; /* [15..0]  */
        unsigned int    gpu_mem_uhd_emaa      : 3   ; /* [18..16]  */
        unsigned int    gpu_mem_uhd_emasa     : 1   ; /* [19]  */
        unsigned int    gpu_mem_uhd_emawb     : 2   ; /* [21..20]  */
        unsigned int    reserved_0            : 10  ; /* [31..22]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG97;

/* Define the union U_PERI_CRG98 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    combphy0_ref_cken     : 1   ; /* [0]  */
        unsigned int    combphy0_refclk_sel   : 3   ; /* [3..1]  */
        unsigned int    combphy0_srst_req     : 1   ; /* [4]  */
        unsigned int    combphy0_rstn_sel_ctrl : 1   ; /* [5]  */
        unsigned int    reserved_0            : 2   ; /* [7..6]  */
        unsigned int    combphy1_ref_cken     : 1   ; /* [8]  */
        unsigned int    combphy1_refclk_sel   : 3   ; /* [11..9]  */
        unsigned int    combphy1_srst_req     : 1   ; /* [12]  */
        unsigned int    combphy1_rstn_sel_ctrl : 1   ; /* [13]  */
        unsigned int    reserved_1            : 2   ; /* [15..14]  */
        unsigned int    combphy2_ref_cken     : 1   ; /* [16]  */
        unsigned int    combphy2_refclk_sel   : 3   ; /* [19..17]  */
        unsigned int    combphy2_srst_req     : 1   ; /* [20]  */
        unsigned int    combphy2_rstn_sel_ctrl : 1   ; /* [21]  */
        unsigned int    reserved_2            : 2   ; /* [23..22]  */
        unsigned int    combphy3_ref_cken     : 1   ; /* [24]  */
        unsigned int    combphy3_refclk_sel   : 3   ; /* [27..25]  */
        unsigned int    combphy3_srst_req     : 1   ; /* [28]  */
        unsigned int    combphy3_rstn_sel_ctrl : 1   ; /* [29]  */
        unsigned int    reserved_3            : 2   ; /* [31..30]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG98;

/* Define the union U_PERI_CRG99 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    pcie0_bus_cken        : 1   ; /* [0]  */
        unsigned int    pcie0_sys_cken        : 1   ; /* [1]  */
        unsigned int    pcie0_pipe_cken       : 1   ; /* [2]  */
        unsigned int    pcie0_aux_cken        : 1   ; /* [3]  */
        unsigned int    pcie0_bus_srst_req    : 1   ; /* [4]  */
        unsigned int    pcie0_sys_srst_req    : 1   ; /* [5]  */
        unsigned int    pcie0_srst_req        : 1   ; /* [6]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    pcie1_bus_cken        : 1   ; /* [8]  */
        unsigned int    pcie1_sys_cken        : 1   ; /* [9]  */
        unsigned int    pcie1_pipe_cken       : 1   ; /* [10]  */
        unsigned int    pcie1_aux_cken        : 1   ; /* [11]  */
        unsigned int    pcie1_bus_srst_req    : 1   ; /* [12]  */
        unsigned int    pcie1_sys_srst_req    : 1   ; /* [13]  */
        unsigned int    pcie1_srst_req        : 1   ; /* [14]  */
        unsigned int    reserved_1            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG99;

/* Define the union U_PERI_CRG102 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    usb2_bus_cken1        : 1   ; /* [0]  */
        unsigned int    usb2_ohci48m_cken1    : 1   ; /* [1]  */
        unsigned int    usb2_ohci12m_cken1    : 1   ; /* [2]  */
        unsigned int    reserved_0            : 1   ; /* [3]  */
        unsigned int    usb2_hst_phy_cken1    : 1   ; /* [4]  */
        unsigned int    usb2_utmi0_cken1      : 1   ; /* [5]  */
        unsigned int    reserved_1            : 6   ; /* [11..6]  */
        unsigned int    usb2_bus_srst_req1    : 1   ; /* [12]  */
        unsigned int    reserved_2            : 1   ; /* [13]  */
        unsigned int    usb2_utmi0_srst_req1  : 1   ; /* [14]  */
        unsigned int    reserved_3            : 1   ; /* [15]  */
        unsigned int    usb2_hst_phy_srst_req1 : 1   ; /* [16]  */
        unsigned int    reserved_4            : 3   ; /* [19..17]  */
        unsigned int    usb2_clk48_sel1       : 1   ; /* [20]  */
        unsigned int    reserved_5            : 11  ; /* [31..21]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG102;

/* Define the union U_PERI_CRG_PLL103 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    apll_ctrl0            : 31  ; /* [30..0]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG_PLL103;

/* Define the union U_PERI_CRG_PLL104 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    apll_ctrl1            : 28  ; /* [27..0]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG_PLL104;

/* Define the union U_PERI_CRG105 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    apll_tune_int_cfg     : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG105;

/* Define the union U_PERI_CRG106 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    apll_tune_frac_cfg    : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG106;

/* Define the union U_PERI_CRG107 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    apll_tune_step_int    : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG107;

/* Define the union U_PERI_CRG108 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    apll_tune_step_frac   : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG108;

/* Define the union U_PERI_CRG109 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    apll_tune_cken        : 1   ; /* [0]  */
        unsigned int    apll_tune_srst_req    : 1   ; /* [1]  */
        unsigned int    apll_tune_mode        : 1   ; /* [2]  */
        unsigned int    apll_tune_en          : 1   ; /* [3]  */
        unsigned int    apll_tune_divval      : 4   ; /* [7..4]  */
        unsigned int    apll_tune_soft_cfg    : 1   ; /* [8]  */
        unsigned int    reserved_0            : 23  ; /* [31..9]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG109;

/* Define the union U_PERI_CRG110 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    bpll_tune_int_cfg     : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG110;

/* Define the union U_PERI_CRG111 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    bpll_tune_frac_cfg    : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG111;

/* Define the union U_PERI_CRG112 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    bpll_tune_step_int    : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG112;

/* Define the union U_PERI_CRG113 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    bpll_tune_step_frac   : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG113;

/* Define the union U_PERI_CRG114 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    bpll_tune_cken        : 1   ; /* [0]  */
        unsigned int    bpll_tune_srst_req    : 1   ; /* [1]  */
        unsigned int    bpll_tune_mode        : 1   ; /* [2]  */
        unsigned int    bpll_tune_en          : 1   ; /* [3]  */
        unsigned int    bpll_tune_divval      : 4   ; /* [7..4]  */
        unsigned int    bpll_tune_soft_cfg    : 1   ; /* [8]  */
        unsigned int    reserved_0            : 23  ; /* [31..9]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG114;

/* Define the union U_PERI_CRG115 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dpll_tune_int_cfg     : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG115;

/* Define the union U_PERI_CRG116 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dpll_tune_frac_cfg    : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG116;

/* Define the union U_PERI_CRG117 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dpll_tune_step_int    : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG117;

/* Define the union U_PERI_CRG118 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dpll_tune_step_frac   : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG118;

/* Define the union U_PERI_CRG119 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dpll_tune_cken        : 1   ; /* [0]  */
        unsigned int    dpll_tune_srst_req    : 1   ; /* [1]  */
        unsigned int    dpll_tune_mode        : 1   ; /* [2]  */
        unsigned int    dpll_tune_en          : 1   ; /* [3]  */
        unsigned int    dpll_tune_divval      : 4   ; /* [7..4]  */
        unsigned int    dpll_tune_soft_cfg    : 1   ; /* [8]  */
        unsigned int    reserved_0            : 23  ; /* [31..9]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG119;

/* Define the union U_PERI_CRG120 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    epll_tune_int_cfg     : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG120;

/* Define the union U_PERI_CRG121 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    epll_tune_frac_cfg    : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG121;

/* Define the union U_PERI_CRG122 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    epll_tune_step_int    : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG122;

/* Define the union U_PERI_CRG123 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    epll_tune_step_frac   : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG123;

/* Define the union U_PERI_CRG124 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    epll_tune_cken        : 1   ; /* [0]  */
        unsigned int    epll_tune_srst_req    : 1   ; /* [1]  */
        unsigned int    epll_tune_mode        : 1   ; /* [2]  */
        unsigned int    epll_tune_en          : 1   ; /* [3]  */
        unsigned int    epll_tune_divval      : 4   ; /* [7..4]  */
        unsigned int    epll_tune_soft_cfg    : 1   ; /* [8]  */
        unsigned int    reserved_0            : 23  ; /* [31..9]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG124;

/* Define the union U_PERI_CRG125 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cpll_tune_int_cfg     : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG125;

/* Define the union U_PERI_CRG126 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cpll_tune_frac_cfg    : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG126;

/* Define the union U_PERI_CRG127 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cpll_tune_step_int    : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG127;

/* Define the union U_PERI_CRG128 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cpll_tune_step_frac   : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG128;

/* Define the union U_PERI_CRG129 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cpll_tune_cken        : 1   ; /* [0]  */
        unsigned int    cpll_tune_srst_req    : 1   ; /* [1]  */
        unsigned int    cpll_tune_mode        : 1   ; /* [2]  */
        unsigned int    cpll_tune_en          : 1   ; /* [3]  */
        unsigned int    cpll_tune_divval      : 4   ; /* [7..4]  */
        unsigned int    cpll_tune_soft_cfg    : 1   ; /* [8]  */
        unsigned int    reserved_0            : 23  ; /* [31..9]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG129;

/* Define the union U_PERI_CRG130 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gpll_tune_int_cfg     : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG130;

/* Define the union U_PERI_CRG131 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gpll_tune_frac_cfg    : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG131;

/* Define the union U_PERI_CRG132 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gpll_tune_step_int    : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG132;

/* Define the union U_PERI_CRG133 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gpll_tune_step_frac   : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG133;

/* Define the union U_PERI_CRG134 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gpll_tune_cken        : 1   ; /* [0]  */
        unsigned int    gpll_tune_srst_req    : 1   ; /* [1]  */
        unsigned int    gpll_tune_mode        : 1   ; /* [2]  */
        unsigned int    gpll_tune_en          : 1   ; /* [3]  */
        unsigned int    gpll_tune_divval      : 4   ; /* [7..4]  */
        unsigned int    gpll_tune_soft_cfg    : 1   ; /* [8]  */
        unsigned int    reserved_0            : 23  ; /* [31..9]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG134;

/* Define the union U_PERI_CRG135 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hpll_tune_int_cfg     : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG135;

/* Define the union U_PERI_CRG136 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hpll_tune_frac_cfg    : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG136;

/* Define the union U_PERI_CRG137 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hpll_tune_step_int    : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG137;

/* Define the union U_PERI_CRG138 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hpll_tune_step_frac   : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG138;

/* Define the union U_PERI_CRG139 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hpll_tune_cken        : 1   ; /* [0]  */
        unsigned int    hpll_tune_srst_req    : 1   ; /* [1]  */
        unsigned int    hpll_tune_mode        : 1   ; /* [2]  */
        unsigned int    hpll_tune_en          : 1   ; /* [3]  */
        unsigned int    hpll_tune_divval      : 4   ; /* [7..4]  */
        unsigned int    hpll_tune_soft_cfg    : 1   ; /* [8]  */
        unsigned int    reserved_0            : 23  ; /* [31..9]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG139;

/* Define the union U_PERI_CRG140 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vpll_tune_int_cfg     : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG140;

/* Define the union U_PERI_CRG141 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vpll_tune_frac_cfg    : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG141;

/* Define the union U_PERI_CRG142 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vpll_tune_step_int    : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG142;

/* Define the union U_PERI_CRG143 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vpll_tune_step_frac   : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG143;

/* Define the union U_PERI_CRG144 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vpll_tune_cken        : 1   ; /* [0]  */
        unsigned int    vpll_tune_srst_req    : 1   ; /* [1]  */
        unsigned int    vpll_tune_mode        : 1   ; /* [2]  */
        unsigned int    vpll_tune_en          : 1   ; /* [3]  */
        unsigned int    vpll_tune_divval      : 4   ; /* [7..4]  */
        unsigned int    vpll_tune_soft_cfg    : 1   ; /* [8]  */
        unsigned int    reserved_0            : 23  ; /* [31..9]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG144;

/* Define the union U_PERI_CRG145 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gpu_pll_cfg0_apb      : 31  ; /* [30..0]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG145;

/* Define the union U_PERI_CRG146 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gpu_pll_cfg1_apb      : 28  ; /* [27..0]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG146;

/* Define the union U_PERI_CRG147 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gpu_pll_cfg0_sw       : 31  ; /* [30..0]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG147;

/* Define the union U_PERI_CRG148 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gpu_pll_cfg1_sw       : 28  ; /* [27..0]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG148;

/* Define the union U_PERI_CRG149 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    bpll_ssc_mem_apb_wdata : 8   ; /* [7..0]  */
        unsigned int    bpll_ssc_mem_apb_addr : 8   ; /* [15..8]  */
        unsigned int    bpll_ssc_mem_cken     : 1   ; /* [16]  */
        unsigned int    bpll_ssc_mem_apb_rden : 1   ; /* [17]  */
        unsigned int    bpll_ssc_mem_apb_wren : 1   ; /* [18]  */
        unsigned int    bpll_ssc_mem_soft_cfg : 1   ; /* [19]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG149;

/* Define the union U_PERI_CRG150 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    bpll_ssc_mem_apb_rdata : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG150;

/* Define the union U_PERI_CRG151 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dpll_ssc_mem_apb_wdata : 8   ; /* [7..0]  */
        unsigned int    dpll_ssc_mem_apb_addr : 8   ; /* [15..8]  */
        unsigned int    dpll_ssc_mem_cken     : 1   ; /* [16]  */
        unsigned int    dpll_ssc_mem_apb_rden : 1   ; /* [17]  */
        unsigned int    dpll_ssc_mem_apb_wren : 1   ; /* [18]  */
        unsigned int    dpll_ssc_mem_soft_cfg : 1   ; /* [19]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG151;

/* Define the union U_PERI_CRG152 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dpll_ssc_mem_apb_rdata : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG152;

/* Define the union U_PERI_CRG153 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mpll_ssc_mem_apb_wdata : 8   ; /* [7..0]  */
        unsigned int    mpll_ssc_mem_apb_addr : 8   ; /* [15..8]  */
        unsigned int    mpll_ssc_mem_cken     : 1   ; /* [16]  */
        unsigned int    mpll_ssc_mem_apb_rden : 1   ; /* [17]  */
        unsigned int    mpll_ssc_mem_apb_wren : 1   ; /* [18]  */
        unsigned int    mpll_ssc_mem_soft_cfg : 1   ; /* [19]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG153;

/* Define the union U_PERI_CRG154 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mpll_ssc_mem_apb_rdata : 8   ; /* [7..0]  */
        unsigned int    reserved_0            : 24  ; /* [31..8]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG154;

/* Define the union U_PERI_CRG155 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cpll_ssmod_ctrl       : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG155;

/* Define the union U_PERI_CRG156 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gpll_ssmod_ctrl       : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG156;

/* Define the union U_PERI_CRG157 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdmirx_otp_pclk_cken  : 1   ; /* [0]  */
        unsigned int    hdmirx_2p0_sheman_cken : 1   ; /* [1]  */
        unsigned int    hdmirx_2p0_prif_cken  : 1   ; /* [2]  */
        unsigned int    hdmirx_2p0_osc_cken   : 1   ; /* [3]  */
        unsigned int    hdmirx_2p0_hdcp2x_eclk_cken : 1   ; /* [4]  */
        unsigned int    hdmirx_2p0_hdcp2x_cclk_cken : 1   ; /* [5]  */
        unsigned int    hdmirx_2p0_fiona_osc_cken : 1   ; /* [6]  */
        unsigned int    hdmirx_2p0_ext_apll_cken : 1   ; /* [7]  */
        unsigned int    hdmirx_2p0_edid_cken  : 1   ; /* [8]  */
        unsigned int    hdmirx_2p0_div20sync_cken : 1   ; /* [9]  */
        unsigned int    hdmirx_2p0_dcclk_cken : 1   ; /* [10]  */
        unsigned int    hdmirx_2p0_dc_refck_cken : 1   ; /* [11]  */
        unsigned int    hdmirx_2p0_dacr_refclk_cken : 1   ; /* [12]  */
        unsigned int    hdmirx_2p0_clk1x_cken : 1   ; /* [13]  */
        unsigned int    hdmirx_2p0_cec_cken   : 1   ; /* [14]  */
        unsigned int    hdmirx_2p0_cbus_cken  : 1   ; /* [15]  */
        unsigned int    hdmirx_2p0_apll_ref_cken : 1   ; /* [16]  */
        unsigned int    hdmirx_otp_pclk_srst_req : 1   ; /* [17]  */
        unsigned int    hdmirx_2p0_srst_req   : 1   ; /* [18]  */
        unsigned int    hdmirx_2p0_sheman_srst_req : 1   ; /* [19]  */
        unsigned int    hdmirx_2p0_prif_srst_req : 1   ; /* [20]  */
        unsigned int    hdmirx_2p0_osc_srst_req : 1   ; /* [21]  */
        unsigned int    hdmirx_2p0_hdcp2x_eclk_srst_req : 1   ; /* [22]  */
        unsigned int    hdmirx_2p0_hdcp2x_cclk_srst_req : 1   ; /* [23]  */
        unsigned int    hdmirx_2p0_fiona_osc_srst_req : 1   ; /* [24]  */
        unsigned int    hdmirx_2p0_cec_srst_req : 1   ; /* [25]  */
        unsigned int    hdmirx_2p0_cec_cksel  : 1   ; /* [26]  */
        unsigned int    hdmirx_2p0_edid_cksel : 1   ; /* [27]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG157;

/* Define the union U_PERI_CRG158 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hdmitx_ctrl_xclk_cken : 1   ; /* [0]  */
        unsigned int    hdmitx_ctrl_pixelnx_cken : 1   ; /* [1]  */
        unsigned int    hdmitx_ctrl_pixel_cken : 1   ; /* [2]  */
        unsigned int    hdmitx_ctrl_pixel_cksel : 1   ; /* [3]  */
        unsigned int    hdmitx_ctrl_pixelnx_cksel : 1   ; /* [4]  */
        unsigned int    hdmitx_ctrl_osclk_sel : 1   ; /* [5]  */
        unsigned int    hdmitx_ctrl_id_cksel  : 1   ; /* [6]  */
        unsigned int    hdmitx_ctrl_cec_clk_sel : 1   ; /* [7]  */
        unsigned int    hdmitx_ctrl_pixel_div : 2   ; /* [9..8]  */
        unsigned int    hdmitx_ctrl_pixelnx_div : 2   ; /* [11..10]  */
        unsigned int    hdmitx_ctrl_id_div    : 2   ; /* [13..12]  */
        unsigned int    reserved_0            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG158;

/* Define the union U_PERI_CRG159 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mem_adjust_cpu_1      : 28  ; /* [27..0]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG159;

/* Define the union U_PERI_CRG160 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sdio2_dll_mdly_tap_flag : 8   ; /* [7..0]  */
        unsigned int    sdio2_dll_locked_flag : 1   ; /* [8]  */
        unsigned int    sdio2_dll_ready_flag  : 1   ; /* [9]  */
        unsigned int    sdio2_dll_overflow_flag : 1   ; /* [10]  */
        unsigned int    reserved_0            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG160;

/* Define the union U_PERI_CRG161 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    reserved_0            : 2   ; /* [1..0]  */
        unsigned int    nfc_clk2x_seled       : 2   ; /* [3..2]  */
        unsigned int    sdio2_clk_seled       : 3   ; /* [6..4]  */
        unsigned int    vdh1_clk_seled        : 2   ; /* [8..7]  */
        unsigned int    sfc2x_nand_clk_seled  : 1   ; /* [9]  */
        unsigned int    sfc2x_nor_clk_seled   : 1   ; /* [10]  */
        unsigned int    reserved_1            : 21  ; /* [31..11]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG161;

/* Define the union U_PERI_CRG162 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vdh1_cken             : 1   ; /* [0]  */
        unsigned int    vdh1dsp_cken          : 1   ; /* [1]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    vdh1_all_srst_req     : 1   ; /* [4]  */
        unsigned int    vdh1_scd_srst_req     : 1   ; /* [5]  */
        unsigned int    vdh1_mfd_srst_req     : 1   ; /* [6]  */
        unsigned int    reserved_1            : 1   ; /* [7]  */
        unsigned int    vdh1_clk_sel          : 2   ; /* [9..8]  */
        unsigned int    reserved_2            : 2   ; /* [11..10]  */
        unsigned int    vdh1clk_skipcfg       : 5   ; /* [16..12]  */
        unsigned int    vdh1clk_loaden        : 1   ; /* [17]  */
        unsigned int    reserved_3            : 14  ; /* [31..18]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG162;

/* Define the union U_PERI_CRG163 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sdio1_bus_cken        : 1   ; /* [0]  */
        unsigned int    sdio1_cken            : 1   ; /* [1]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    sdio1_srst_req        : 1   ; /* [4]  */
        unsigned int    reserved_1            : 3   ; /* [7..5]  */
        unsigned int    sdio1_clk_sel         : 3   ; /* [10..8]  */
        unsigned int    reserved_2            : 1   ; /* [11]  */
        unsigned int    sdio1_sap_ps_sel      : 3   ; /* [14..12]  */
        unsigned int    reserved_3            : 1   ; /* [15]  */
        unsigned int    sdio1_drv_ps_sel      : 3   ; /* [18..16]  */
        unsigned int    sdio1_clk_mode        : 1   ; /* [19]  */
        unsigned int    reserved_4            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG163;

/* Define the union U_PERI_CRG164 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    sdio2_dll_cken        : 1   ; /* [0]  */
        unsigned int    sdio2_dll_srst_req    : 1   ; /* [1]  */
        unsigned int    sdio2_dll_dsel        : 2   ; /* [3..2]  */
        unsigned int    sdio2_dll_tune        : 4   ; /* [7..4]  */
        unsigned int    sdio2_dll_dllssel     : 8   ; /* [15..8]  */
        unsigned int    sdio2_dll_dllmode     : 1   ; /* [16]  */
        unsigned int    sdio2_dll_bypass      : 1   ; /* [17]  */
        unsigned int    sdio2_dll_stop        : 1   ; /* [18]  */
        unsigned int    sdio2_dll_slave_en    : 1   ; /* [19]  */
        unsigned int    reserved_0            : 12  ; /* [31..20]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG164;

/* Define the union U_PERI_CRG165 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    apll_tune_int         : 12  ; /* [11..0]  */
        unsigned int    apll_tune_sw_ok       : 1   ; /* [12]  */
        unsigned int    apll_tune_busy        : 1   ; /* [13]  */
        unsigned int    reserved_0            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG165;

/* Define the union U_PERI_CRG166 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    apll_tune_frac        : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG166;

/* Define the union U_PERI_CRG167 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    bpll_tune_int         : 12  ; /* [11..0]  */
        unsigned int    bpll_tune_sw_ok       : 1   ; /* [12]  */
        unsigned int    bpll_tune_busy        : 1   ; /* [13]  */
        unsigned int    reserved_0            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG167;

/* Define the union U_PERI_CRG168 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    bpll_tune_frac        : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG168;

/* Define the union U_PERI_CRG169 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dpll_tune_int         : 12  ; /* [11..0]  */
        unsigned int    dpll_tune_sw_ok       : 1   ; /* [12]  */
        unsigned int    dpll_tune_busy        : 1   ; /* [13]  */
        unsigned int    reserved_0            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG169;

/* Define the union U_PERI_CRG170 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    dpll_tune_frac        : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG170;

/* Define the union U_PERI_CRG171 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    epll_tune_int         : 12  ; /* [11..0]  */
        unsigned int    epll_tune_sw_ok       : 1   ; /* [12]  */
        unsigned int    epll_tune_busy        : 1   ; /* [13]  */
        unsigned int    reserved_0            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG171;

/* Define the union U_PERI_CRG172 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    epll_tune_frac        : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG172;

/* Define the union U_PERI_CRG173 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cpll_tune_int         : 12  ; /* [11..0]  */
        unsigned int    cpll_tune_sw_ok       : 1   ; /* [12]  */
        unsigned int    cpll_tune_busy        : 1   ; /* [13]  */
        unsigned int    reserved_0            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG173;

/* Define the union U_PERI_CRG174 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cpll_tune_frac        : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG174;

/* Define the union U_PERI_CRG175 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gpll_tune_int         : 12  ; /* [11..0]  */
        unsigned int    gpll_tune_sw_ok       : 1   ; /* [12]  */
        unsigned int    gpll_tune_busy        : 1   ; /* [13]  */
        unsigned int    reserved_0            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG175;

/* Define the union U_PERI_CRG176 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gpll_tune_frac        : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG176;

/* Define the union U_PERI_CRG177 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hpll_tune_int         : 12  ; /* [11..0]  */
        unsigned int    hpll_tune_sw_ok       : 1   ; /* [12]  */
        unsigned int    hpll_tune_busy        : 1   ; /* [13]  */
        unsigned int    reserved_0            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG177;

/* Define the union U_PERI_CRG178 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    hpll_tune_frac        : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG178;

/* Define the union U_PERI_CRG179 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vpll_tune_int         : 12  ; /* [11..0]  */
        unsigned int    vpll_tune_sw_ok       : 1   ; /* [12]  */
        unsigned int    vpll_tune_busy        : 1   ; /* [13]  */
        unsigned int    reserved_0            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG179;

/* Define the union U_PERI_CRG180 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    vpll_tune_frac        : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG180;

/* Define the union U_PERI_CRG181 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    cpu_sm_sw_mode        : 1   ; /* [0]  */
        unsigned int    cpu_sw_step_slow_up_ref : 3   ; /* [3..1]  */
        unsigned int    cpu_sw_step_slow_down_ref : 3   ; /* [6..4]  */
        unsigned int    reserved_0            : 1   ; /* [7]  */
        unsigned int    gpu_sm_sw_mode        : 1   ; /* [8]  */
        unsigned int    gpu_sw_step_slow_up_ref : 3   ; /* [11..9]  */
        unsigned int    gpu_sw_step_slow_down_ref : 3   ; /* [14..12]  */
        unsigned int    reserved_1            : 17  ; /* [31..15]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG181;

/* Define the union U_PERI_CRG182 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    clk_cpu_sm_sw_seled   : 1   ; /* [0]  */
        unsigned int    cpu_sm_sw_busy        : 1   ; /* [1]  */
        unsigned int    clk_gpu_sm_sw_seled   : 1   ; /* [2]  */
        unsigned int    gpu_sm_sw_busy        : 1   ; /* [3]  */
        unsigned int    reserved_0            : 28  ; /* [31..4]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG182;

/* Define the union U_PERI_CRG183 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gmac_if_sys_ctrl      : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG183;

/* Define the union U_PERI_CRG184 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    gmac_if_sys_stat      : 16  ; /* [15..0]  */
        unsigned int    reserved_0            : 16  ; /* [31..16]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG184;

/* Define the union U_PERI_CRG_PLL185 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fpll_ctrl0            : 31  ; /* [30..0]  */
        unsigned int    reserved_0            : 1   ; /* [31]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG_PLL185;

/* Define the union U_PERI_CRG_PLL186 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fpll_ctrl1            : 28  ; /* [27..0]  */
        unsigned int    reserved_0            : 4   ; /* [31..28]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG_PLL186;

/* Define the union U_PERI_CRG187 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fpll_ssmod_ctrl       : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG187;

/* Define the union U_PERI_CRG188 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fpll_tune_int_cfg     : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG188;

/* Define the union U_PERI_CRG189 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fpll_tune_frac_cfg    : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG189;

/* Define the union U_PERI_CRG190 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fpll_tune_step_int    : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG190;

/* Define the union U_PERI_CRG191 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fpll_tune_step_frac   : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG191;

/* Define the union U_PERI_CRG192 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fpll_tune_cken        : 1   ; /* [0]  */
        unsigned int    fpll_tune_srst_req    : 1   ; /* [1]  */
        unsigned int    fpll_tune_mode        : 1   ; /* [2]  */
        unsigned int    fpll_tune_en          : 1   ; /* [3]  */
        unsigned int    fpll_tune_divval      : 4   ; /* [7..4]  */
        unsigned int    fpll_tune_soft_cfg    : 1   ; /* [8]  */
        unsigned int    reserved_0            : 23  ; /* [31..9]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG192;

/* Define the union U_PERI_CRG193 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fpll_tune_int         : 12  ; /* [11..0]  */
        unsigned int    fpll_tune_sw_ok       : 1   ; /* [12]  */
        unsigned int    fpll_tune_busy        : 1   ; /* [13]  */
        unsigned int    reserved_0            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG193;

/* Define the union U_PERI_CRG194 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    fpll_tune_frac        : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG194;

/* Define the union U_PERI_CRG195 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mpll_tune_int_cfg     : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG195;

/* Define the union U_PERI_CRG196 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mpll_tune_frac_cfg    : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG196;

/* Define the union U_PERI_CRG197 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mpll_tune_step_int    : 12  ; /* [11..0]  */
        unsigned int    reserved_0            : 20  ; /* [31..12]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG197;

/* Define the union U_PERI_CRG198 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mpll_tune_step_frac   : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG198;

/* Define the union U_PERI_CRG199 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mpll_tune_cken        : 1   ; /* [0]  */
        unsigned int    mpll_tune_srst_req    : 1   ; /* [1]  */
        unsigned int    mpll_tune_mode        : 1   ; /* [2]  */
        unsigned int    mpll_tune_en          : 1   ; /* [3]  */
        unsigned int    mpll_tune_divval      : 4   ; /* [7..4]  */
        unsigned int    mpll_tune_soft_cfg    : 1   ; /* [8]  */
        unsigned int    reserved_0            : 23  ; /* [31..9]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG199;

/* Define the union U_PERI_CRG200 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mpll_tune_int         : 12  ; /* [11..0]  */
        unsigned int    mpll_tune_sw_ok       : 1   ; /* [12]  */
        unsigned int    mpll_tune_busy        : 1   ; /* [13]  */
        unsigned int    reserved_0            : 18  ; /* [31..14]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG200;

/* Define the union U_PERI_CRG201 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    mpll_tune_frac        : 24  ; /* [23..0]  */
        unsigned int    reserved_0            : 8   ; /* [31..24]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG201;

/* Define the union U_PERI_CRG202 */
typedef union
{
    /* Define the struct bits */
    struct
    {
        unsigned int    ci_cken               : 1   ; /* [0]  */
        unsigned int    ci_cksel              : 1   ; /* [1]  */
        unsigned int    reserved_0            : 2   ; /* [3..2]  */
        unsigned int    ci_srst_req           : 1   ; /* [4]  */
        unsigned int    reserved_1            : 27  ; /* [31..5]  */
    } bits;

    /* Define an unsigned member */
    unsigned int    u32;

} U_PERI_CRG202;

//==============================================================================
/* Define the global struct */
typedef struct
{
    volatile U_PERI_CRG_PLL0        PERI_CRG_PLL0            ; /* 0x0 */
    volatile U_PERI_CRG_PLL1        PERI_CRG_PLL1            ; /* 0x4 */
    volatile U_PERI_CRG_PLL2        PERI_CRG_PLL2            ; /* 0x8 */
    volatile U_PERI_CRG_PLL3        PERI_CRG_PLL3            ; /* 0xc */
    volatile U_PERI_CRG_PLL4        PERI_CRG_PLL4            ; /* 0x10 */
    volatile U_PERI_CRG_PLL5        PERI_CRG_PLL5            ; /* 0x14 */
    volatile unsigned int           reserved_0[2]                     ; /* 0x18~0x1c */
    volatile U_PERI_CRG_PLL8        PERI_CRG_PLL8            ; /* 0x20 */
    volatile U_PERI_CRG_PLL9        PERI_CRG_PLL9            ; /* 0x24 */
    volatile U_PERI_CRG_PLL10       PERI_CRG_PLL10           ; /* 0x28 */
    volatile U_PERI_CRG_PLL11       PERI_CRG_PLL11           ; /* 0x2c */
    volatile U_PERI_CRG_PLL12       PERI_CRG_PLL12           ; /* 0x30 */
    volatile U_PERI_CRG_PLL13       PERI_CRG_PLL13           ; /* 0x34 */
    volatile U_PERI_CRG_PLL14       PERI_CRG_PLL14           ; /* 0x38 */
    volatile U_PERI_CRG_PLL15       PERI_CRG_PLL15           ; /* 0x3c */
    volatile unsigned int           reserved_1[2]                     ; /* 0x40~0x44 */
    volatile U_PERI_CRG18           PERI_CRG18               ; /* 0x48 */
    volatile U_PERI_CRG19           PERI_CRG19               ; /* 0x4c */
    volatile U_PERI_CRG20           PERI_CRG20               ; /* 0x50 */
    volatile unsigned int           reserved_2                     ; /* 0x54 */
    volatile U_PERI_CRG22           PERI_CRG22               ; /* 0x58 */
    volatile U_PERI_CRG23           PERI_CRG23               ; /* 0x5c */
    volatile U_PERI_CRG24           PERI_CRG24               ; /* 0x60 */
    volatile U_PERI_CRG25           PERI_CRG25               ; /* 0x64 */
    volatile U_PERI_CRG26           PERI_CRG26               ; /* 0x68 */
    volatile U_PERI_CRG27           PERI_CRG27               ; /* 0x6c */
    volatile U_PERI_CRG28           PERI_CRG28               ; /* 0x70 */
    volatile U_PERI_CRG29           PERI_CRG29               ; /* 0x74 */
    volatile U_PERI_CRG30           PERI_CRG30               ; /* 0x78 */
    volatile U_PERI_CRG31           PERI_CRG31               ; /* 0x7c */
    volatile unsigned int           reserved_3                     ; /* 0x80 */
    volatile U_PERI_CRG33           PERI_CRG33               ; /* 0x84 */
    volatile U_PERI_CRG34           PERI_CRG34               ; /* 0x88 */
    volatile U_PERI_CRG35           PERI_CRG35               ; /* 0x8c */
    volatile U_PERI_CRG36           PERI_CRG36               ; /* 0x90 */
    volatile U_PERI_CRG37           PERI_CRG37               ; /* 0x94 */
    volatile unsigned int           reserved_4                     ; /* 0x98 */
    volatile U_PERI_CRG39           PERI_CRG39               ; /* 0x9c */
    volatile U_PERI_CRG40           PERI_CRG40               ; /* 0xa0 */
    volatile unsigned int           reserved_5                     ; /* 0xa4 */
    volatile U_PERI_CRG42           PERI_CRG42               ; /* 0xa8 */
    volatile unsigned int           reserved_6                     ; /* 0xac */
    volatile U_PERI_CRG44           PERI_CRG44               ; /* 0xb0 */
    volatile unsigned int           reserved_7                     ; /* 0xb4 */
    volatile U_PERI_CRG46           PERI_CRG46               ; /* 0xb8 */
    volatile U_PERI_CRG47           PERI_CRG47               ; /* 0xbc */
    volatile U_PERI_CRG48           PERI_CRG48               ; /* 0xc0 */
    volatile U_PERI_CRG49           PERI_CRG49               ; /* 0xc4 */
    volatile U_PERI_CRG50           PERI_CRG50               ; /* 0xc8 */
    volatile U_PERI_CRG51           PERI_CRG51               ; /* 0xcc */
    volatile unsigned int           reserved_8                     ; /* 0xd0 */
    volatile U_PERI_CRG53           PERI_CRG53               ; /* 0xd4 */
    volatile U_PERI_CRG54           PERI_CRG54               ; /* 0xd8 */
    volatile U_PERI_CRG55           PERI_CRG55               ; /* 0xdc */
    volatile U_PERI_CRG56           PERI_CRG56               ; /* 0xe0 */
    volatile unsigned int           reserved_9                     ; /* 0xe4 */
    volatile U_PERI_CRG58           PERI_CRG58               ; /* 0xe8 */
    volatile unsigned int           reserved_10                     ; /* 0xec */
    volatile U_PERI_CRG60           PERI_CRG60               ; /* 0xf0 */
    volatile U_PERI_CRG61           PERI_CRG61               ; /* 0xf4 */
    volatile unsigned int           reserved_11                     ; /* 0xf8 */
    volatile U_PERI_CRG63           PERI_CRG63               ; /* 0xfc */
    volatile U_PERI_CRG64           PERI_CRG64               ; /* 0x100 */
    volatile unsigned int           reserved_12[2]                     ; /* 0x104~0x108 */
    volatile U_PERI_CRG67           PERI_CRG67               ; /* 0x10c */
    volatile U_PERI_CRG68           PERI_CRG68               ; /* 0x110 */
    volatile U_PERI_CRG69           PERI_CRG69               ; /* 0x114 */
    volatile U_PERI_CRG70           PERI_CRG70               ; /* 0x118 */
    volatile U_PERI_CRG71           PERI_CRG71               ; /* 0x11c */
    volatile U_PERI_CRG72           PERI_CRG72               ; /* 0x120 */
    volatile U_PERI_CRG73           PERI_CRG73               ; /* 0x124 */
    volatile U_PERI_CRG74           PERI_CRG74               ; /* 0x128 */
    volatile U_PERI_CRG75           PERI_CRG75               ; /* 0x12c */
    volatile U_PERI_CRG76           PERI_CRG76               ; /* 0x130 */
    volatile U_PERI_CRG77           PERI_CRG77               ; /* 0x134 */
    volatile unsigned int           reserved_13                     ; /* 0x138 */
    volatile U_PERI_CRG79           PERI_CRG79               ; /* 0x13c */
    volatile U_PERI_CRG80           PERI_CRG80               ; /* 0x140 */
    volatile U_PERI_CRG81           PERI_CRG81               ; /* 0x144 */
    volatile U_PERI_CRG82           PERI_CRG82               ; /* 0x148 */
    volatile unsigned int           reserved_14                     ; /* 0x14c */
    volatile U_PERI_CRG84           PERI_CRG84               ; /* 0x150 */
    volatile U_PERI_CRG85           PERI_CRG85               ; /* 0x154 */
    volatile U_PERI_CRG_PLL86       PERI_CRG_PLL86           ; /* 0x158 */
    volatile U_PERI_CRG_PLL87       PERI_CRG_PLL87           ; /* 0x15c */
    volatile U_PERI_CRG_PLL88       PERI_CRG_PLL88           ; /* 0x160 */
    volatile U_PERI_CRG_PLL89       PERI_CRG_PLL89           ; /* 0x164 */
    volatile U_PERI_CRG90           PERI_CRG90               ; /* 0x168 */
    volatile unsigned int           reserved_15[2]                     ; /* 0x16c~0x170 */
    volatile U_PERI_CRG93           PERI_CRG93               ; /* 0x174 */
    volatile U_PERI_CRG94           PERI_CRG94               ; /* 0x178 */
    volatile U_PERI_CRG95           PERI_CRG95               ; /* 0x17c */
    volatile U_PERI_CRG96           PERI_CRG96               ; /* 0x180 */
    volatile U_PERI_CRG97           PERI_CRG97               ; /* 0x184 */
    volatile U_PERI_CRG98           PERI_CRG98               ; /* 0x188 */
    volatile U_PERI_CRG99           PERI_CRG99               ; /* 0x18c */
    volatile unsigned int           reserved_16[2]                     ; /* 0x190~0x194 */
    volatile U_PERI_CRG102          PERI_CRG102              ; /* 0x198 */
    volatile U_PERI_CRG_PLL103      PERI_CRG_PLL103          ; /* 0x19c */
    volatile U_PERI_CRG_PLL104      PERI_CRG_PLL104          ; /* 0x1a0 */
    volatile U_PERI_CRG105          PERI_CRG105              ; /* 0x1a4 */
    volatile U_PERI_CRG106          PERI_CRG106              ; /* 0x1a8 */
    volatile U_PERI_CRG107          PERI_CRG107              ; /* 0x1ac */
    volatile U_PERI_CRG108          PERI_CRG108              ; /* 0x1b0 */
    volatile U_PERI_CRG109          PERI_CRG109              ; /* 0x1b4 */
    volatile U_PERI_CRG110          PERI_CRG110              ; /* 0x1b8 */
    volatile U_PERI_CRG111          PERI_CRG111              ; /* 0x1bc */
    volatile U_PERI_CRG112          PERI_CRG112              ; /* 0x1c0 */
    volatile U_PERI_CRG113          PERI_CRG113              ; /* 0x1c4 */
    volatile U_PERI_CRG114          PERI_CRG114              ; /* 0x1c8 */
    volatile U_PERI_CRG115          PERI_CRG115              ; /* 0x1cc */
    volatile U_PERI_CRG116          PERI_CRG116              ; /* 0x1d0 */
    volatile U_PERI_CRG117          PERI_CRG117              ; /* 0x1d4 */
    volatile U_PERI_CRG118          PERI_CRG118              ; /* 0x1d8 */
    volatile U_PERI_CRG119          PERI_CRG119              ; /* 0x1dc */
    volatile U_PERI_CRG120          PERI_CRG120              ; /* 0x1e0 */
    volatile U_PERI_CRG121          PERI_CRG121              ; /* 0x1e4 */
    volatile U_PERI_CRG122          PERI_CRG122              ; /* 0x1e8 */
    volatile U_PERI_CRG123          PERI_CRG123              ; /* 0x1ec */
    volatile U_PERI_CRG124          PERI_CRG124              ; /* 0x1f0 */
    volatile U_PERI_CRG125          PERI_CRG125              ; /* 0x1f4 */
    volatile U_PERI_CRG126          PERI_CRG126              ; /* 0x1f8 */
    volatile U_PERI_CRG127          PERI_CRG127              ; /* 0x1fc */
    volatile U_PERI_CRG128          PERI_CRG128              ; /* 0x200 */
    volatile U_PERI_CRG129          PERI_CRG129              ; /* 0x204 */
    volatile U_PERI_CRG130          PERI_CRG130              ; /* 0x208 */
    volatile U_PERI_CRG131          PERI_CRG131              ; /* 0x20c */
    volatile U_PERI_CRG132          PERI_CRG132              ; /* 0x210 */
    volatile U_PERI_CRG133          PERI_CRG133              ; /* 0x214 */
    volatile U_PERI_CRG134          PERI_CRG134              ; /* 0x218 */
    volatile U_PERI_CRG135          PERI_CRG135              ; /* 0x21c */
    volatile U_PERI_CRG136          PERI_CRG136              ; /* 0x220 */
    volatile U_PERI_CRG137          PERI_CRG137              ; /* 0x224 */
    volatile U_PERI_CRG138          PERI_CRG138              ; /* 0x228 */
    volatile U_PERI_CRG139          PERI_CRG139              ; /* 0x22c */
    volatile U_PERI_CRG140          PERI_CRG140              ; /* 0x230 */
    volatile U_PERI_CRG141          PERI_CRG141              ; /* 0x234 */
    volatile U_PERI_CRG142          PERI_CRG142              ; /* 0x238 */
    volatile U_PERI_CRG143          PERI_CRG143              ; /* 0x23c */
    volatile U_PERI_CRG144          PERI_CRG144              ; /* 0x240 */
    volatile U_PERI_CRG145          PERI_CRG145              ; /* 0x244 */
    volatile U_PERI_CRG146          PERI_CRG146              ; /* 0x248 */
    volatile U_PERI_CRG147          PERI_CRG147              ; /* 0x24c */
    volatile U_PERI_CRG148          PERI_CRG148              ; /* 0x250 */
    volatile U_PERI_CRG149          PERI_CRG149              ; /* 0x254 */
    volatile U_PERI_CRG150          PERI_CRG150              ; /* 0x258 */
    volatile U_PERI_CRG151          PERI_CRG151              ; /* 0x25c */
    volatile U_PERI_CRG152          PERI_CRG152              ; /* 0x260 */
    volatile U_PERI_CRG153          PERI_CRG153              ; /* 0x264 */
    volatile U_PERI_CRG154          PERI_CRG154              ; /* 0x268 */
    volatile U_PERI_CRG155          PERI_CRG155              ; /* 0x26c */
    volatile U_PERI_CRG156          PERI_CRG156              ; /* 0x270 */
    volatile U_PERI_CRG157          PERI_CRG157              ; /* 0x274 */
    volatile U_PERI_CRG158          PERI_CRG158              ; /* 0x278 */
    volatile U_PERI_CRG159          PERI_CRG159              ; /* 0x27c */
    volatile U_PERI_CRG160          PERI_CRG160              ; /* 0x280 */
    volatile U_PERI_CRG161          PERI_CRG161              ; /* 0x284 */
    volatile U_PERI_CRG162          PERI_CRG162              ; /* 0x288 */
    volatile U_PERI_CRG163          PERI_CRG163              ; /* 0x28c */
    volatile U_PERI_CRG164          PERI_CRG164              ; /* 0x290 */
    volatile U_PERI_CRG165          PERI_CRG165              ; /* 0x294 */
    volatile U_PERI_CRG166          PERI_CRG166              ; /* 0x298 */
    volatile U_PERI_CRG167          PERI_CRG167              ; /* 0x29c */
    volatile U_PERI_CRG168          PERI_CRG168              ; /* 0x2a0 */
    volatile U_PERI_CRG169          PERI_CRG169              ; /* 0x2a4 */
    volatile U_PERI_CRG170          PERI_CRG170              ; /* 0x2a8 */
    volatile U_PERI_CRG171          PERI_CRG171              ; /* 0x2ac */
    volatile U_PERI_CRG172          PERI_CRG172              ; /* 0x2b0 */
    volatile U_PERI_CRG173          PERI_CRG173              ; /* 0x2b4 */
    volatile U_PERI_CRG174          PERI_CRG174              ; /* 0x2b8 */
    volatile U_PERI_CRG175          PERI_CRG175              ; /* 0x2bc */
    volatile U_PERI_CRG176          PERI_CRG176              ; /* 0x2c0 */
    volatile U_PERI_CRG177          PERI_CRG177              ; /* 0x2c4 */
    volatile U_PERI_CRG178          PERI_CRG178              ; /* 0x2c8 */
    volatile U_PERI_CRG179          PERI_CRG179              ; /* 0x2cc */
    volatile U_PERI_CRG180          PERI_CRG180              ; /* 0x2d0 */
    volatile U_PERI_CRG181          PERI_CRG181              ; /* 0x2d4 */
    volatile U_PERI_CRG182          PERI_CRG182              ; /* 0x2d8 */
    volatile U_PERI_CRG183          PERI_CRG183              ; /* 0x2dc */
    volatile U_PERI_CRG184          PERI_CRG184              ; /* 0x2e0 */
    volatile U_PERI_CRG_PLL185      PERI_CRG_PLL185          ; /* 0x2e4 */
    volatile U_PERI_CRG_PLL186      PERI_CRG_PLL186          ; /* 0x2e8 */
    volatile U_PERI_CRG187          PERI_CRG187              ; /* 0x2ec */
    volatile U_PERI_CRG188          PERI_CRG188              ; /* 0x2f0 */
    volatile U_PERI_CRG189          PERI_CRG189              ; /* 0x2f4 */
    volatile U_PERI_CRG190          PERI_CRG190              ; /* 0x2f8 */
    volatile U_PERI_CRG191          PERI_CRG191              ; /* 0x2fc */
    volatile U_PERI_CRG192          PERI_CRG192              ; /* 0x300 */
    volatile U_PERI_CRG193          PERI_CRG193              ; /* 0x304 */
    volatile U_PERI_CRG194          PERI_CRG194              ; /* 0x308 */
    volatile U_PERI_CRG195          PERI_CRG195              ; /* 0x30c */
    volatile U_PERI_CRG196          PERI_CRG196              ; /* 0x310 */
    volatile U_PERI_CRG197          PERI_CRG197              ; /* 0x314 */
    volatile U_PERI_CRG198          PERI_CRG198              ; /* 0x318 */
    volatile U_PERI_CRG199          PERI_CRG199              ; /* 0x31c */
    volatile U_PERI_CRG200          PERI_CRG200              ; /* 0x320 */
    volatile U_PERI_CRG201          PERI_CRG201              ; /* 0x324 */
    volatile U_PERI_CRG202          PERI_CRG202              ; /* 0x328 */

} S_CRG_REGS_TYPE;

#endif /* __HI_REG_CRG_H__ */
