#MRS工具链路径，安装时需要修改成您自己的路径
MRS_BASE = "/home/xrj/MRS/MounRiver Studio/toolchain"

TOOL_CHAIN = $(MRS_BASE)"/RISC-V Embedded GCC/bin/riscv-none-embed-"
OPENOCD = $(MRS_BASE)/OpenOCD/bin/openocd
OCD_CFG = $(MRS_BASE)/OpenOCD/bin/wch-riscv.cfg

#从xPack下载的编译器，版本较新。如需使用，请修改路径。
#TOOL_CHAIN = "/home/xrj/elec/xpack-riscv-none-embed-gcc-10.2.0-1.2/bin/riscv-none-embed-"

#输出文件目录
OBJODIR = obj
TARGET = obj/target
