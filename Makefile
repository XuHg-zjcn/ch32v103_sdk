TOP_DIR = .

sinclude $(TOP_DIR)/tools/conf.mk
sinclude $(TOP_DIR)/tools/inc.mk
sinclude $(TOP_DIR)/tools/src.mk


CSRC = $(shell find $(SDIR) -name *.c)
ASRC = $(shell find $(SDIR) -name *.S)

OBJF = $(CSRC:%.c=obj/%.o) \
       $(ASRC:%.S=obj/%.o)

all: hex erase down verify reset

obj/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CCFLAGS) $(INCS) -c -o "$@" "$<"

obj/%.o: %.S
	@mkdir -p $(dir $@)
	@$(ASM) $(ASMFLAGS) $(INCS) -c -o "$@" "$<"

$(TARGET).elf: $(OBJF)
	@$(CC) $(CCFLAGS) $(INCS) -o "$@" $^

hex: $(TARGET).elf
	@$(OBJCOPY) -O ihex "$(TARGET).elf"  "$(TARGET).hex"

erase:
	@$(OPENOCD) $(OCDFLAGS) -c init -c halt -c "flash erase_sector wch_riscv 0 last" -c exit

down:
	@$(OPENOCD) $(OCDFLAGS) -c init -c halt -c "program \"$(TARGET).hex\" 0x08000000" -c exit

verify:
	@$(OPENOCD) $(OCDFLAGS) -c init -c halt -c "verify_image \"$(TARGET).hex\"" -c exit

reset:
	@$(OPENOCD) $(OCDFLAGS) -c init -c reset -c exit
