all:
	g++ -std=c++17 ./libgoroutine.so ./pingpong.cc
clean:
	rm -f libgoroutine.*
	rm -f a.out
