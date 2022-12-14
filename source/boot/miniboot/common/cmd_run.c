/******************************************************************************
 *    Copyright (C) 2014 Hisilicon STB Development Dept
 *    All rights reserved.
 * ***
 *    Create by Czyong
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *   http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
******************************************************************************/

#include <boot.h>
#include <compile.h>
#include <stdio.h>
#include <stddef.h>
#include <command.h>
#include <cmd-words.h>
#include <run.h>

/*****************************************************************************/

static int do_go(struct cmd_t *cmd)
{
	int ret;
	char *param = NULL;
	char *addr = (char *)param_int32(cmd, 1);

	if (param_count(cmd) == 3)
		param = param_str(cmd, 2);

	printf("Runing image at 0x%08X\n", (uint32)addr);
	ret = image_load(addr, param);
	printf("Runing image terminated, return %d\n", ret);

	return 0;
}
CMD({&cw_go, NULL},
    {&cw_addr, _T("miniboot start address."), do_go},
    {&cw_string, 0, do_go})
/*****************************************************************************/

static int do_boot(struct cmd_t *cmd)
{
	uint32 addr = param_int32(cmd, 1);

#ifdef CONFIG_TEE_SUPPORT
	/* Load Trustedcore OS */
	char *buf = (char *)addr;
	if (is_trustedcore_img(buf)) {
		return do_load_secure_os((u32)buf, 0, 0, 0, NULL);
	}
#ifdef CONFIG_SUPPORT_CA_RELEASE
	else if (!memcmp((char *)buf, HI_ADVCA_MAGIC, HI_ADVCA_MAGIC_SIZE) && is_trustedcore_img(buf + HI_ADVCA_HEADER_SIZE)) {
		printf("Boot Hisilicon ADVCA SecureOS Image ...\n");
		return do_load_secure_os((u32)buf, HI_ADVCA_HEADER_SIZE, 0, 0, NULL);
	}
#endif
#endif

	kern_load((char *)addr);
	return 0;
}
CMD({&cw_boot, NULL},
    {&cw_addr, _T("uImage start address."), do_boot})
