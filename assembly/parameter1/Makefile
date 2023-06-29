all:
	aarch64-linux-gnu-g++-11 -o test test.cpp add.s --static

clean:
	rm test

run:all
	qemu-aarch64-static ./test
