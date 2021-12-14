sinclude $(TOP_DIR)/tools/config.mk

CC = "$(TOOL_CHAIN)gcc"
CXX = "$(TOOL_CHAIN)g++"
LINK = "$(TOOL_CHAIN)gcc"

OBJCOPY = "$(TOOL_CHAIN)objcopy"

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
CCFLAGS += -nostartfiles

CXXFLAGS += -Wall#               #
CXXFLAGS += -std=gnu++11#        #

ASMFLAGS += -Wall#               #


CSRC ?= $(wildcard ${DIR}/*.c)
CPPSRC ?= $(wildcard ${DIR}/*.cpp)
ASRCS ?= $(wildcard ${DIR}/*.S)

