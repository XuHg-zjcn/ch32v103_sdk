TOP_DIR = .

sinclude $(TOP_DIR)/tools/conf.mk
sinclude $(TOP_DIR)/tools/inc.mk

SDIR += Core
SDIR += Startup
SDIR += Peripheral
SDIR += Debug
SDIR += User

CSRC = $(shell find $(SDIR) -name *.c)
ASRC = $(shell find $(SDIR) -name *.S)

all: build hex erase down verify reset

build: $(CSRC) $(ASRC)
	@$(CC) $(CCFLAGS) $(INCS) $^ -o "$(TARGET).elf"

hex: build
	@$(OBJCOPY) -O ihex "$(TARGET).elf"  "$(TARGET).hex"

erase:
	@$(OPENOCD) $(OCDFLAGS) -c init -c halt -c "flash erase_sector wch_riscv 0 last" -c exit

down:
	@$(OPENOCD) $(OCDFLAGS) -c init -c halt -c "program \"$(TARGET).hex\" 0x08000000" -c exit

verify:
	@$(OPENOCD) $(OCDFLAGS) -c init -c halt -c "verify_image \"$(TARGET).hex\"" -c exit

reset:
	@$(OPENOCD) $(OCDFLAGS) -c init -c reset -c exit
