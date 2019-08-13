#include"goroutine.hh"
#include<cstdio>
#include<tuple>

void paddle(void* rawparam) {
  auto [ch, id] = *(std::tuple<Channel<void>*, int>*)rawparam;
  std::printf("ID: %d\n", id);
  _goroutine_yield();
  for (int i=0; i<10; i++) {
    void* ptr = ch->Recv();
    std::printf("Routine (%d): received: %zu\n", id, (size_t)ptr); std::fflush(stdout);
    ptr = (void*)((size_t)ptr + id);
    ch->Send(ptr);
    _goroutine_yield();
  }
}

void defer_test(void*) {
  std::printf("Hello from Defer!\n");
}
int main() {
  auto h = Defer(defer_test, nullptr);
  size_t item;
{
  auto ch = Channel<void>(1);
  ch.Send((void*)0);
  {
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
  item = reinterpret_cast<size_t>(ch.Recv());
}
  std::printf("Main: received: %zu\n", item); std::fflush(stdout);
  return 0;
}
