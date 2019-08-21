
all: kernel.bin

isrs.o:
	as -32 isrs.S -o isrs.o
interrupts.o: isrs.o
	gcc -c interrupts.c -o interrupts.o -std=gnu99 -ffreestanding -O2 -Wextra -m32
kernel_head.o:
	as -32 kernel.S -o kernel_head.o
kernel.o: kernel_head.o interrupts.o
	gcc -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wextra -m32
kernel.bin: kernel.o
	gcc -T kernel.ld -o kernel.bin -ffreestanding -O2 -nostdlib kernel_head.o kernel.o isrs.o interrupts.o -lgcc -m32
debug: kernel.bin
	objdump -lS kernel.bin > kernel.lst
run: kernel.bin
	qemu-system-i386 -kernel kernel.bin
clean:
	rm kernel.o kernel.bin kernel_head.o

