################################################################################
#    Copyright (C) 2014 Hisilicon STB Development Dept
#    All rights reserved.
#####
#    Create by Cai Zhiyong
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#    http://www.apache.org/licenses/LICENSE-2.0
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#
################################################################################

CFLAGS += -I$(SRCDIR)../

SRCS-y := nand_spl_ids.c nand_ids.c nand_ctrl.c nand_init.c nfc_if.c drv_if.c \
	nfc_unif.c
SRCS-$(CONFIG_CMDLINE) += cmd_nand.c
SRCS-$(CONFIG_NAND_HINFC504) += hinfc504/
SRCS-$(CONFIG_NAND_HINFC610) += hinfc610/
