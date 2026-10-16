# Makefile for SovereignX (minimal, safe, and explicit)

# Toolchain variables (override when invoking make, e.g. `make CC=gcc`)
CC ?= x86_64-elf-gcc
LD ?= x86_64-elf-ld
NASM ?= nasm
OBJCOPY ?= objcopy

OUTDIR := build

# Minimal kernel build: only build a tiny kernel from kernel.c so users can reproduce a kernel.elf
KERNEL_SRCS := kernel.c
KERNEL_OBJS := $(patsubst %.c,$(OUTDIR)/%.o,$(KERNEL_SRCS))

CFLAGS := -ffreestanding -fno-builtin -m64 -Wall -Wextra -O2 -I.
LDFLAGS := -T linker.ld

.PHONY: all check-tools kernel clean info
all: check-tools kernel

check-tools:
	@command -v $(CC) >/dev/null 2>&1 || { echo >&2 "Error: $(CC) not found. Install a cross or native x86_64 toolchain (example: x86_64-elf-gcc)."; exit 1; }
	@command -v $(LD) >/dev/null 2>&1 || { echo >&2 "Error: $(LD) not found. Install binutils (ld)."; exit 1; }
	@echo "Tools available: $(CC) $(LD)"

$(OUTDIR):
	@mkdir -p $(OUTDIR)

$(OUTDIR)/%.o: %.c | $(OUTDIR)
	@echo "CC $< -> $@"
	$(CC) $(CFLAGS) -c $< -o $@

kernel: $(KERNEL_OBJS)
	@echo "LINK -> $(OUTDIR)/kernel.elf"
	$(LD) $(LDFLAGS) -o $(OUTDIR)/kernel.elf $(KERNEL_OBJS)
	@echo "Built: $(OUTDIR)/kernel.elf"

info:
	@echo "SovereignX minimal Makefile"
	@echo "  - Default CC=$(CC), LD=$(LD)"
	@echo "  - Build a tiny kernel from: $(KERNEL_SRCS)"
	@echo "  - To build: make"
	@echo "  - To use a different toolchain: make CC=gcc LD=ld"

clean:
	rm -rf $(OUTDIR)

# Notes:
# - This Makefile purposefully builds a minimal kernel (kernel.c) which defines kernel_main.
# - Many other source files exist in the repository but may require additional dependencies or
#   link-time symbols. Extend KERNEL_SRCS cautiously.
# - Building UEFI/EFI images and a complete boot flow is not implemented here; see BUILDING.md.
