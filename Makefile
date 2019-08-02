all:
	g++ main.cc -I./goroutine -L./goroutine -lgoroutine
	LD_LIBRARY_PATH=./goroutine ./a.out
clean:
	rm -f a.out
