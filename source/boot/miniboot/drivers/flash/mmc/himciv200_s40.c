
static void hi_mci_sys_init(void)
{
	unsigned int tmp_reg;

	HIMCI_DEBUG_FUN("Function Call");

	/* SDIO clock phase */
	if (_HI3716C_V200ES == get_chipid()) {
		tmp_reg = himci_readl(REG_BASE_CRG + REG_PERI_CRG40);
		tmp_reg &= ~(SDIO1_CLK_SEL_MASK | SDIO1_DRV_PS_SEL_MASK
				| SDIO1_SAP_PS_SEL_MASK);
		tmp_reg |= SDIO1_CLK_SEL_50M | SDIO1_DRV_PS_SEL_45;
		himci_writel(tmp_reg, REG_BASE_CRG + REG_PERI_CRG40);
	} else {
		tmp_reg = himci_readl(REG_BASE_CRG + REG_PERI_CRG40);
		tmp_reg &= ~SDIO1_CLK_SEL_MASK;
		tmp_reg |= SDIO1_CLK_SEL_50M;
		himci_writel(tmp_reg, REG_BASE_CRG + REG_PERI_CRG40);
	}

	/* SDIO soft reset */
	tmp_reg |= SDIO1_SRST_REQ;
	himci_writel(tmp_reg, REG_BASE_CRG + REG_PERI_CRG40);
	udelay(1000);
	tmp_reg &= ~SDIO1_SRST_REQ;
	tmp_reg |= SDIO1_CKEN | SDIO1_BUS_CKEN;
	himci_writel(tmp_reg, REG_BASE_CRG + REG_PERI_CRG40);
	
	udelay(1000);
}
