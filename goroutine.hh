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
  void Go(void* function, void* argument) {
    _goroutine(function, argument, m_wg);
  }
  void Join() {
    _goroutine_join_waitgroup(m_wg);
  }
};
#endif