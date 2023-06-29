all:
	aarch64-linux-gnu-gcc -c add.c -o add.o
	aarch64-linux-gnu-as -o demo.o demo.s
	aarch64-linux-gnu-gcc add.o demo.o -o executable

clean:
	rm -f executable

run: all
	qemu-aarch64-static ./executable
