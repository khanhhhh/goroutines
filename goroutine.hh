#ifndef _GOROUTINE_HH_
#define _GOROUTINE_HH_
#include"libgoroutine.h"
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
  void Send(void* item) {
    _goroutine_send_channel(m_chan, (GoUintptr)item);
  }
  void* Recv() {
    return (void*)_goroutine_recv_channel(m_chan);
  }
};
#endif
