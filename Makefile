# Target file
ELF=$(notdir $(CURDIR)).elf

# Compiler
CC=arm-none-eabi-g++

# Directories
BUILD_DIR := ./build
SRC_DIRS := ./src

SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# MCU info
CHIPSET = LPC845M301JBD48
TARGET = BAREMETAL
CPU = cortex-m0plus

# Compilation Flags
DEBUG_FLAGS := -g -DDEBUG
LDFLAGS+= -D$(CHIPSET) -mcpu=$(CPU) -DSDK_OS_$(TARGET) -mthumb --specs=nano.specs $(DEBUG_FLAGS)
CPPFLAGS+=  -D$(CHIPSET) -mcpu=$(CPU) -DSDK_OS_$(TARGET) -mthumb --specs=nano.specs $(DEBUG_FLAGS)
CPPFLAGS+= $(INC_FLAGS) -MMD -MP -Wall -pedantic

$(BUILD_DIR)/$(ELF): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

-include $(OBJS:.o=.d)
