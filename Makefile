# Toolchain
CC = arm-none-eabi-gcc
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy

# Flags
CFLAGS = -mcpu=cortex-m4 -mthumb -Wall -g -O2 \
         -ffunction-sections -fdata-sections \
         -I. -ICMSIS/Inc \
         -ICMSIS/Include \
         -ICMSIS/Device/ST/STM32F4xx/Include

LDFLAGS = -T STM32F407VGTX_FLASH.ld -nostdlib -Wl,--gc-sections -Wl,-Map=build/blink.map \
          -nostartfiles -nodefaultlibs  # Disable default startup and libc

# Source files
SRCS = Src/main.c \
       CMSIS/Src/system_stm32f4xx.c \
       Startup/startup_stm32f407vgtx.s

# Object files in build/
OBJS = $(patsubst %.c, build/%.o, $(filter %.c,$(SRCS))) \
       $(patsubst %.s, build/%.o, $(filter %.s,$(SRCS)))

# Output
TARGET = build/blink.elf
BIN = build/blink.bin

# Default target
all: $(BIN)

# Linking
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

# Convert ELF to BIN
$(BIN): $(TARGET)
	$(OBJCOPY) -O binary $< $@

# Compile C files
build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Assemble startup file
build/%.o: %.s
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf build

.PHONY: all clean

