package main

/*
#cgo CFLAGS: -I.
#cgo LDFLAGS: -L.
#include"goroutine.h"
*/
import "C"
import (
	"sync"
	"unsafe"
)

func _ccall(function unsafe.Pointer, argument unsafe.Pointer, wg *sync.WaitGroup) {
	if wg != nil {
		defer wg.Done()
	}
	C._ccall((*[0]byte)(function), argument)
}

//export _goroutine
func _goroutine(function unsafe.Pointer, argument unsafe.Pointer, wg uintptr) {
	wgptr := wgPool[wg]
	wgptr.Add(1)
	go _ccall(function, argument, wgptr)
}

// wgPool
var wgPool = map[uintptr]*sync.WaitGroup{}

//export _goroutine_new_waitgroup
func _goroutine_new_waitgroup() uintptr {
	wg := sync.WaitGroup{}
	ptr := uintptr(unsafe.Pointer(&wg))
	wgPool[ptr] = &wg
	return ptr
}

//export _goroutine_del_waitgroup
func _goroutine_del_waitgroup(wg uintptr) {
	delete(wgPool, wg)
}

//export _goroutine_join_waitgroup
func _goroutine_join_waitgroup(wg uintptr) {
	wgPool[wg].Wait()
}

func main() {}
