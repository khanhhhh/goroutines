#ifndef _GOROUTINE_HH_
#define _GOROUTINE_HH_
#include"goroutine.h"
void _goroutine_yield();
class WaitGroup {
private:
  GoUintptr m_wg;
public:
  WaitGroup():
    m_wg(_goroutine_new_waitgroup())
  {}
  ~WaitGroup() {
    Join();
    _goroutine_del_waitgroup(m_wg);
  }
public:
  void Go(void (*function)(void*), void* argument) {
    _goroutine((void*)function, argument, m_wg);
  }
  void Join() {
    _goroutine_join_waitgroup(m_wg);
  }
};
template<typename type>
class Channel {
private:
  GoUintptr m_chan;
public:
  Channel(size_t count):
    m_chan(_goroutine_new_channel((GoUintptr)count))
  {}
  ~Channel() {
    _goroutine_del_channel(m_chan);
  }
  void Send(type* item) {
    _goroutine_send_channel(m_chan, (GoUintptr)item);
  }
  type* Recv() {
    return (type*)_goroutine_recv_channel(m_chan);
  }
};
class Defer {
private:
  void (*function)(void*);
  void *argument;
public:
  Defer(void (*function)(void*), void* parameter):
    function(function),
    argument(parameter)
  {}
  ~Defer() {
    function(argument);
  }
};
#endif
