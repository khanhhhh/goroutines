all:
	g++ -std=c++17 -I./goroutine -L./goroutine -lgoroutine ./main.cc
	LD_LIBRARY_PATH=./goroutine ./a.out
clean:
	rm -f a.out
