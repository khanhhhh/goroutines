#include"goroutine.h"
void _ccall(void (*function)(void*), void* argument) {
	function(argument);
}