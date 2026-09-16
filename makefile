TARGET := JourneyThroughARM

SOURCES := $(wildcard src/*.c) $(wildcard src/*.s)
OBJECTS := $(SOURCES:src/%.c=build/%.o)
OBJECTS := $(OBJECTS:src/%.s=build/%.o)

OUTDIR := bin

ELF := $(OUTDIR)/$(TARGET).elf
GBA := $(OUTDIR)/$(TARGET).gba

ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. Export DEVKITARM=<path to>devkitARM")
endif

include $(DEVKITARM)/gba_rules

CFLAGS  := -mthumb -mthumb-interwork -O2 -Wall -Iinclude
ASFLAGS := -mthumb-interwork -Iinclude

.PHONY: all clean

all: $(GBA)

$(GBA): $(ELF)
	@mkdir -p $(dir $@)
	$(OBJCOPY) -O binary $< $@
	gbafix $@

$(ELF): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) -specs=gba.specs $^ -o $@

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

build/%.o: src/%.s
	@mkdir -p $(dir $@)
	$(CC) $(ASFLAGS) -c $< -o $@

clean:
	rm -rf build $(OUTDIR)