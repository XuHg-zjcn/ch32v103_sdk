TOP_DIR = .

sinclude $(TOP_DIR)/tools/conf.mk
sinclude $(TOP_DIR)/tools/inc.mk

SDIR += Core
SDIR += Startup
SDIR += Peripheral
SDIR += Debug
SDIR += User

CSRC = $(shell find $(SDIR) -name *.c)

all: $(CSRC)
	@$(CC) $(CCFLAGS) $(INCS) $^ -o "$(TARGET).elf"

hex: all
	@$(OBJCOPY) -O ihex "$(TARGET).elf"  "$(TARGET).hex"

erase:
	@$(OPENOCD) $(OCDFLAGS) -c "flash erase_sector wch_riscv 0 last" -c exit

down:
	@$(OPENOCD) $(OCDFLAGS) -c "program \"$(TARGET).hex\" 0x08000000" -c exit

verify:
	@$(OPENOCD) $(OCDFLAGS) -c "verify_image \"$(TARGET).hex\"" -c exit

reset:
	@$(OPENOCD) $(OCDFLAGS) -c reset -c exit
