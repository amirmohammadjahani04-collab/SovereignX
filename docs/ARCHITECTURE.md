# SovereignX architecture (confirmed from source)

This document records the architecture and implementation details that can be directly established from the repository sources as of the current commit. The goal is to be precise and conservative: only state what the code implements or clearly implies, and call out unknowns and assumptions.

Summary (one-sentence):
SovereignX is an early-stage x86_64 experimental operating-system project containing a minimal kernel entry, a simple bump allocator, syscall skeletons, NASM-style assembly stubs for interrupts/context switching, and assorted experimental subsystem sources.

Confirmed platform and tooling
- Architecture: x86_64 (evidence: BOOTX64.EFI filename, efi_main signature in main.c, use of 64-bit registers in assembly, and typical x86_64 conventions).
- Assembler format: NASM (Intel) style. Assembly files use "global", "section .text", and Intel operand order (e.g., mov [rdi+0], r15), so assemble with nasm -felf64.
- Linker script: linker.ld sets ENTRY(kernel_main) and places sections starting at physical address 0x200000.

High-level components (what each top-level source represents)
- main.c: UEFI application stub (efi_main). Confirmed: it has the standard UEFI entry signature but its body is a placeholder (infinite loop); it does not implement kernel loading/handoff.
- BOOTX64.EFI: Prebuilt UEFI binary included in the repository. UNSURE: whether this binary performs kernel loading; do not assume it does without disassembling/inspecting the PE/COFF.
- kernel.c: kernel_main implementation which writes characters to legacy VGA text buffer at 0xb8000 and then loops. CONFIRMED: kernel_main writes to VGA text memory (legacy VGA text-mode assumption).
- linker.ld: linker script with origin 0x200000 and ENTRY(kernel_main). CONFIRMED: kernel expects to be linked at 0x200000 with symbol kernel_main as entry.
- memory.c/memory.h: a trivial bump allocator. CONFIRMED: kmalloc returns current heap and increments heap by size with no alignment or bounds checks; kfree is a no-op.
- syscall.c/syscall.h: syscall handler skeleton with placeholder case values (IDs 1 and 2). CONFIRMED: skeleton only, not a full syscall API.
- Assembly stubs: context.asm, switch.asm, irq.asm, isr.asm. CONFIRMED: NASM-style assembly implementing context save/restore and IRQ/ISR stubs; they reference external C handlers such as irq0_handler and interrupt_handler which must exist in C sources.
- Subsystems (gdt.c/h, idt.c/h, pic.c/h, scheduler.c, process.c, task.c, filesystem.*, driver.*, keyboard.c, gui_event.c, etc.): present as source files. STATUS: many are experimental or partial — their presence is NOT proof of a fully working subsystem.

Linker / symbol assumptions
- ENTRY(kernel_main) required by linker. kernel_main is present in kernel.c.
- Assembly externs such as irq0_handler and interrupt_handler MUST be defined by the C side at link time; otherwise linking the full kernel will fail.
- There are two context-switch related symbols in assembly: switch_context (exported by context.asm) and context_switch (exported by switch.asm). Confirm callers' names before linking the full kernel to avoid naming mismatches.

Memory layout assumptions (confirmed vs. unknown)
- Confirmed constants in code:
  - Kernel link/load origin: 0x200000 (linker.ld)
  - VGA text buffer: 0xB8000 (kernel.c writes directly here)
  - Heap base: memory.c sets heap = 0x01000000 (0x1000000) (confirmed)
- Unknowns / assumptions that must be validated at runtime:
  - Whether the physical RAM layout at runtime maps the kernel link origin (0x200000) to available RAM at that address — typically a loader must place code there or map it.
  - Whether the UEFI execution environment will make 0xB8000 available as a VGA text buffer — UEFI commonly uses a framebuffer (GOP); 0xB8000 is a BIOS artifact and is not guaranteed under UEFI.
  - Whether the heap base 0x01000000 is safe to use on a given platform without prior initialization by a bootloader or kernel memory manager.

Boot and loader status
- UEFI loader (main.c) exists as a minimal stub with the efi_main signature but does NOT implement kernel loading/handoff. CONFIRMED: no handoff present in source.
- BOOTX64.EFI binary exists in the repository but is UNVERIFIED. Do not assume it loads the kernel without inspecting the binary.
- The kernel is not confirmed to be Multiboot-compatible; no Multiboot header is present in the inspected sources. To boot in QEMU, either a suitable loader (GRUB/Multiboot) or a verified UEFI image is required.

Interrupts, context switching, and concurrency
- Assembly stubs provide interrupt entry/exit scaffolding and context-save/restore routines. CONFIRMED: ISR and IRQ stubs save registers and call C handlers.
- The scheduler and process/task code files are present but require deeper review and testing before claiming multitasking is implemented. STATUS: experimental/partial.

Filesystem, drivers, GUI, networking
- The repository contains source files for filesystem and drivers (filesystem.c, filemanager.c, ata.c, dir.c, driver.c, etc.) and GUI-related code (gui_event.c, click.c). STATUS: experimental/partial. Their correctness and integration are NOT verified by code presence alone.

Security-sensitive notes (confirmed issues)
- Heap allocator (kmalloc) has no bounds checking or alignment; using it in production may cause memory corruption. kfree is a noop.
- Direct writes to 0xB8000 assume VGA text-mode; this may not be valid under UEFI and can produce no output or undefined behavior.
- Assembly and interrupt code must be audited carefully for calling conventions, stack alignment and register preservation.

What is missing or required to make a reproducible full build
- A documented and reproducible sequence that: assembles .asm files (nasm -felf64), compiles all C files with proper freestanding flags and link order, and links them together with exact LD flags.
- A verified bootloader or UEFI application that actually loads kernel.elf at its expected load address and performs any required relocation.
- Documentation of the intended physical memory map and any helpers for setting up page tables if virtual memory is planned.

Recommended immediate developer tasks (conservative)
1. Document the exact toolchain and flags used to create the existing kernel.elf and BOOTX64.EFI (if known). If these artifacts were built manually, add those commands to BUILDING.md.
2. Add a minimal Makefile that builds only confirmed, reproducible targets (kernel.c -> kernel.elf) — already provided.
3. Disassemble or inspect BOOTX64.EFI to determine its behavior and document its provenance.
4. Improve the allocator incrementally (add alignment and bounds checks) and make the limit configurable via a linker symbol.
5. Add tests that validate non-privileged behaviors (pointer arithmetic and allocator bump properties) on the host.

Appendix: key files and one-line descriptions
- README.md — project overview and status (this file)
- BUILDING.md — step-by-step minimal build instructions (root)
- linker.ld — link origin 0x200000, ENTRY(kernel_main)
- main.c — UEFI stub (efi_main)
- BOOTX64.EFI — prebuilt EFI binary (unverified)
- kernel.c — kernel_main writing to VGA text buffer (0xB8000)
- memory.c / memory.h — trivial bump allocator
- syscall.c / syscall.h — syscall skeleton
- context.asm / switch.asm — context save/restore (NASM)
- irq.asm / isr.asm — IRQ/ISR stubs (NASM)
