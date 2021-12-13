sinclude $(TOP_DIR)/tools/config.mk

CC = "$(TOOL_CHAIN)gcc"
CXX = "$(TOOL_CHAIN)g++"
LINK = "$(TOOL_CHAIN)gcc"


CCFLAGS := -Wall \
    -march=rv32imac \
    -mabi=ilp32 \
    -msmall-data-limit=8 \
    -mno-save-restore \
    -Os \
    -fmessage-length=0 \
    -fsigned-char \
    -ffunction-sections \
    -fdata-sections \
    -fno-common \
    -Wunused \
    -Wuninitialized \
    -g \
    -std=gnu99 \
    -MMD -MP

CXXFLAGS := -Wall \
    -std=gnu++11

ASMFLAGS := -Wall


CSRC ?= $(wildcard ${DIR}/*.c)
CPPSRC ?= $(wildcard ${DIR}/*.cpp)
ASRCS ?= $(wildcard ${DIR}/*.S)

