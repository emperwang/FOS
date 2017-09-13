C_SOURCES = $(shell find . -name "*.c")
C_OBJECTS = $(patsubst %.c,%.o,$(C_SOUCES))
S_SOURCES = $(shell find . -name "*.c")
S_OBJECTS = $(patsubst %.s,%.o,$(S_SOURCES))

CC = gcc 
LD = ld
ASM= nasm

C_FLAGS  = -c -Wall -m32 -ggdb -gstabs+ -nostdinc -fno-builtin -fno-stack-protect -I include 
LD_FLAGS = -T sctipts/kernel.ld -m elf_i386 -nostdlib
ASM_FLAGS= -f elf -g -f stabs

all:$(S_OBJECTS) $(C_OBJECTS) link update_image

.c.o:
	@compile file
	$(CC) $(C_FLAGS) $< -o $@
.s.o:
	@compile assmble file
	$(ASM) $(ASM_FLAGS) $<
link:
	$(LD) $(LD_FLAGS) $(S_OBJECTS) $(C_OBJECTS) -o hx_kernel

.PHONY:clean
	$(RM) $(S_OBJECTS) $(C_OBJECTS) hx_kernel

.PHONY:update_image
update_image:
	sudo mount floppy.img /mnt
	sudo cp hx_kernel /mnt/
	sleep 1
	sudo umount /mnt

.PHONY:mount_image
mount_imgae:
	sudo mount floppy.img /mnt

.PHONY:umount_image
umount_image:
	sudo umount /mnt

.PHONT:qemu
qemu:
	qemu-system-i386 -fda floppy.img -boot a
.PHONY:bochs
bochs:
	bochs -f scripts/bochsrc.txt

.PHONY:debug
debug:
	qemu-system-i386 -S -s -fda floppy.img -boot a&
	sleep 1
	cgdb -x scripts/gdbinit

