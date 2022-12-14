/******************************************************************************
*    Copyright (c) 2014 by Hisilicon.
*    All rights reserved.
* ***
*    Create By hisilicon
******************************************************************************/

#ifndef HISFC_SPI_IDSH
#define HISFC_SPI_IDSH

/*****************************************************************************/
#define INFINITE			(0xFFFFFFFF)

#define READ_ID_LEN			8
#define MAX_SPI_NAND_OP			8

#define BBP_LAST_PAGE			0x01
#define BBP_FIRST_PAGE			0x02

/*****************************************************************************/
#define SPI_IF_READ_STD			(0x01)
#define SPI_IF_READ_FAST		(0x02)
#define SPI_IF_READ_DUAL		(0x04)
#define SPI_IF_READ_DUAL_ADDR		(0x08)
#define SPI_IF_READ_QUAD		(0x10)
#define SPI_IF_READ_QUAD_ADDR		(0x20)

#define SPI_IF_WRITE_STD		(0x01)
#define SPI_IF_WRITE_DUAL		(0x02)
#define SPI_IF_WRITE_DUAL_ADDR		(0x04)
#define SPI_IF_WRITE_QUAD		(0x08)
#define SPI_IF_WRITE_QUAD_ADDR		(0x10)

#define SPI_IF_ERASE_SECTOR_128K	(0x08)  /* 128K */
#define SPI_IF_ERASE_SECTOR_256K	(0x10)  /* 256K */

/******************************************************************************/
#define HIFMC100_SPI_NAND_SUPPORT_READ	(SPI_IF_READ_STD \
					 | SPI_IF_READ_FAST \
					 | SPI_IF_READ_DUAL \
					 | SPI_IF_READ_DUAL_ADDR \
					 | SPI_IF_READ_QUAD \
					 | SPI_IF_READ_QUAD_ADDR)

#define HIFMC100_SPI_NAND_SUPPORT_WRITE	(SPI_IF_WRITE_STD \
					 | SPI_IF_WRITE_DUAL \
					 | SPI_IF_WRITE_DUAL_ADDR \
					 | SPI_IF_WRITE_QUAD \
					 | SPI_IF_WRITE_QUAD_ADDR)

#define HIFMC100_SPI_NAND_SUPPORT_MAX_DUMMY	8

#define SPI_NAND_READ			0
#define SPI_NAND_WRITE			1

/*****************************************************************************/
#define SPI_CMD_WREN			0x06   /* Write Enable */
#define SPI_CMD_WRDI			0x04   /* Write Disable */

#define SPI_CMD_GET_FEATURE		0x0F   /* Get Features */
#define SPI_CMD_SET_FEATURE		0x1F   /* Set Feature */

#define SPI_CMD_PAGE_READ		0x13   /* Page Read to Cache */
#define SPI_CMD_READ_STD	0x03   /* Read From Cache at Standard Speed */
#define SPI_CMD_READ_FAST	0x0B   /* Read From Cache at Higher Speed */
#define SPI_CMD_READ_DUAL	0x3B   /* Read From Cache at Dual Output */
#define SPI_CMD_READ_QUAD	0x6B   /* Read From Cache at Quad Output */
#define SPI_CMD_READ_DUAL_ADDR	0xBB   /* Read From Cache at Dual I/O */
#define SPI_CMD_READ_QUAD_ADDR	0xEB   /* Read From Cache at Quad I/O */

#define SPI_CMD_RDID			0x9F   /* Read Identification */

#define SPI_CMD_WRITE_STD	0x02   /* Page Load at Standard Input */
#define SPI_CMD_WRITE_QUAD	0x32   /* Page Load at Quad Input */

#define SPI_CMD_SE_128K			0xD8   /* 128KB sector Erase */
#define SPI_CMD_SE_256K			0xD8   /* 256KB sector Erase */

#define SPI_CMD_RESET			0xff   /* Reset the device */

/*****************************************************************************/
#define GET_FEATURE			0 /* get feature */
#define SET_FEATURE			1 /* set feature */

/* spi-nand chip registers. */
#define PROTECTION_REGISTER			0xa0
#define WRITE_PROTECTION_ENABLE_GIGA		((0x1f << 1) | (1 << 7))
#define WRITE_PROTECTION_ENABLE_WINBOND		(0xff)

#define FEATURE_REGISTER			0xb0
/* only WINBOND chip support Buffer Read Mode and Continuous Read Mode */
#define FEATURE_BUF_ENABLE			(1 << 3)
#define FEATURE_ECC_ENABLE			(1 << 4)
#define FEATURE_OTP_ENABLE			(1 << 6)
#define FEATURE_QUAD_ENABLE			(1 << 0)

#define STATUS_REGISTER				0xc0

/*****************************************************************************/

/* SPI operation information */
struct spi_op_info {
	unsigned char  iftype;
	unsigned char  cmd;
	unsigned char  dummy;
	unsigned int   size;
	unsigned int   clock;
};

struct spi_nand_driver;

struct hifmc_op {
	void *host;
	struct spi_nand_driver *driver;
	struct spi_op_info  read[1];
	struct spi_op_info  write[1];
	struct spi_op_info  erase[MAX_SPI_NAND_OP];
};

struct spi_nand_driver {
	int (*wait_ready)(struct hifmc_op *spi);
	int (*write_enable)(struct hifmc_op *spi);
	int (*quad_enable)(struct hifmc_op *spi);
};

struct hifmc_chip_info {
	char *name;
	unsigned char id[READ_ID_LEN];
	unsigned char id_len;
	unsigned long long chipsize;
	unsigned int erasesize;
	unsigned int pagesize;
	unsigned int oobsize;
	unsigned int badblock_pos;
	struct spi_op_info *read[MAX_SPI_NAND_OP];
	struct spi_op_info *write[MAX_SPI_NAND_OP];
	struct spi_op_info *erase[MAX_SPI_NAND_OP];
	struct spi_nand_driver *driver;
};

/*****************************************************************************/
void spi_nand_ids_register(void);

void hifmc100_spi_nand_get_best_clock(unsigned int *clock);

struct hifmc_host;

void spi_nand_feature_op(struct hifmc_host *host, unsigned char op,
			unsigned char addr, unsigned char *val);

/******************************************************************************/

#endif /* HISFC_SPI_IDSH */

