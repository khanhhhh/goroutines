all:
	g++ -std=c++17 -I./libgoroutine -L./libgoroutine -lgoroutine ./pingpong.cc
	LD_LIBRARY_PATH=./libgoroutine ./a.out
clean:
	rm -f a.out
