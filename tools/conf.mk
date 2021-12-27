###########################################################################
#    编译高级设置
#    Copyright (C) 2021  Xu Ruijun
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU Lesser General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public License
#    along with this program.  If not, see <https://www.gnu.org/licenses/>.
###########################################################################

sinclude $(TOP_DIR)/tools/config.mk

ifeq ($(VERBOSE),YES)
    ASM     = $(TOOL_CHAIN)gcc
    CC      = $(TOOL_CHAIN)gcc
    CXX     = $(TOOL_CHAIN)g++
    LINK    = $(TOOL_CHAIN)gcc
    OBJCOPY = $(TOOL_CHAIN)objcopy
else
    ASM     = @echo "ASM      $<"; $(TOOL_CHAIN)gcc
    CC      = @echo "CC       $<"; $(TOOL_CHAIN)gcc
    CXX     = @echo "CXX      $<"; $(TOOL_CHAIN)g++
    LINK    = @echo "LINK     $<"; $(TOOL_CHAIN)gcc
    OBJCOPY = @echo "OBJCOPY  $<"; $(TOOL_CHAIN)objcopy
endif


CCFLAGS += -march=rv32imac#      #架构
CCFLAGS += -mabi=ilp32#          #
CCFLAGS += -msmall-data-limit=8# #
CCFLAGS += -mno-save-restore#    #
CCFLAGS += -Os#                  #最小文件大小优化
CCFLAGS += -fmessage-length=0#   #
CCFLAGS += -fsigned-char#        #
CCFLAGS += -ffunction-sections#  #
CCFLAGS += -fdata-sections#      #
CCFLAGS += -fno-common#          #
CCFLAGS += -Wunused#             #
CCFLAGS += -Wuninitialized#      #
CCFLAGS += -g#                   #调试
CCFLAGS += -std=gnu99#           #标准
CCFLAGS += -T .ld#               #链接器脚本
CCFLAGS += -nostartfiles
CCFLAGS += -Xlinker
CCFLAGS += --gc-sections
CCFLAGS += -Wl,-Map,"$(TARGET).map"#链接器参数
CCFLAGS += --specs=nano.specs
CCFLAGS += --specs=nosys.specs

CXXFLAGS += -Wall#               #
CXXFLAGS += -std=gnu++11#        #

ASMFLAGS += -Wall#               #


OCDFLAGS += -f $(OCD_CFG)


CSRC ?= $(wildcard ${DIR}/*.c)
CPPSRC ?= $(wildcard ${DIR}/*.cpp)
ASRCS ?= $(wildcard ${DIR}/*.S)

