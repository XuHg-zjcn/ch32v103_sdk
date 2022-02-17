##########################################################################
# 用于编译和下载的Makefile
# Copyright (C) 2021-2022  Xu Ruijun
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
##########################################################################

TOP_DIR = .

sinclude $(TOP_DIR)/tools/conf.mk
sinclude $(TOP_DIR)/tools/inc.mk
sinclude $(TOP_DIR)/tools/src.mk


CSRC = $(shell find $(SDIR) -name *.c)
CXXSRC = $(shell find $(SDIR) -name *.cpp)
ASRC = $(shell find $(SDIR) -name *.S)

OBJF = $(CSRC:%.c=obj/%.o) \
       $(CXXSRC:%.cpp=obj/%.o) \
       $(ASRC:%.S=obj/%.o)

all: $(TARGET).hex erase down verify reset

obj/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) $(INCS) -c -o "$@" "$<"

obj/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCS) -c -o "$@" "$<"

obj/%.o: %.S
	@mkdir -p $(dir $@)
	$(ASM) $(ASMFLAGS) $(INCS) -c -o "$@" "$<"

$(TARGET).elf: $(OBJF)
	$(LINK) $(LDFLAGS) -o "$@" $^

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex "$<" "$@"

erase:
	@$(OPENOCD) $(OCDFLAGS) -c init -c halt -c "flash erase_sector wch_riscv 0 last" -c exit

down: $(TARGET).hex
	@$(OPENOCD) $(OCDFLAGS) -c init -c halt -c "program \"$<\" 0x08000000" -c exit

verify: $(TARGET).hex
	@$(OPENOCD) $(OCDFLAGS) -c init -c halt -c "verify_image \"$<\"" -c exit

reset:
	@$(OPENOCD) $(OCDFLAGS) -c init -c reset -c exit

clean:
	@rm -rf $(OBJODIR)/*
	@rm -f $(TARGET)*
