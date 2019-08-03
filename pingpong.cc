#include"goroutine.hh"
#include<cstdio>
#include<tuple>

void paddle(void* rawparam) {
  auto [ch, id] = *(std::tuple<Channel<void>*, int>*)rawparam;
  std::printf("ID: %d\n", id);
  _goroutine_yield();
  for (int i=0; i<10; i++) {
    void* ptr = ch->Recv();
    std::printf("Routine (%d): received: %d\n", id, (size_t)ptr);
    ptr = (void*)((size_t)ptr + id);
    ch->Send(ptr);
    _goroutine_yield();
  }
}
int main() {
  auto ch = Channel<void>(1);
  ch.Send((void*)0);
  auto wg = WaitGroup();
  { // Routine -1
    std::tuple<Channel<void>*, int> args = {&ch, -1};
    wg.Go(paddle, &args);
  }
  { // Routine +1
    std::tuple<Channel<void>*, int> args = {&ch, +1};
    wg.Go(paddle, &args);
  }
  wg.Join();
}
