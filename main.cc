#include"goroutine.hh"
#include<cstdio>
#include<mutex>
int i = 0;
using mutex = std::mutex;
using lock = std::unique_lock<std::mutex>;
mutex m;
void foo(void*) {
  for (;;) {
    {
      auto l = lock(m);
      i++;
    }
    WaitGroup::Yield();
  }
}
void bar(void*) {
  for (;;) {
    {
      auto l = lock(m);
      i--;
    }
    WaitGroup::Yield();
  }
}
int main() {
  auto wg = WaitGroup();
  wg.Go(foo, nullptr);
  wg.Go(bar, nullptr);
  for (;;) {
    {
      auto l = lock(m);
      std::printf("%d\n", i);
    }
  }
}
