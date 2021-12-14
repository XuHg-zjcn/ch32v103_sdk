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
