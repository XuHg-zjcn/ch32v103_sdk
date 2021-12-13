sinclude $(TOP_DIR)/tools/conf.mk
sinclude $(TOP_DIR)/tools/inc.mk

subdir_path := $(subst $(abspath $(TOP_DIR))/,,$(shell pwd))

CSRC := $(wildcard *.c)
CPPSRC := $(wildcard *.cpp)
ASRCS := $(wildcard *.S)

SUBDIRS ?= $(patsubst %/,%,$(dir $(wildcard */Makefile)))
OBJS ?= $(patsubst %.c,$(TOP_DIR)/$(OBJODIR)/$(subdir_path)/%.o, $(CSRC))

all: .subdirs $(OBJS)

.subdirs:
	$(foreach d, $(SUBDIRS), make -C $(d);)

$(TOP_DIR)/$(OBJODIR)/$(subdir_path)/%.o: %.c
	@mkdir -p $(TOP_DIR)/$(OBJODIR)/$(subdir_path)
	@echo $@
	$(CC) $(CCFLAGS) $(INCS) -c "$<" -o "$@"
