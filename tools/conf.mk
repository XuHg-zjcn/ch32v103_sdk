sinclude $(TOP_DIR)/tools/config.mk

ASM = $(TOOL_CHAIN)gcc
CC = $(TOOL_CHAIN)gcc
CXX = $(TOOL_CHAIN)g++
LINK = $(TOOL_CHAIN)gcc

OBJCOPY = $(TOOL_CHAIN)objcopy

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

