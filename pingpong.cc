#include"goroutine.hh"
#include<cstdio>
#include<tuple>

void paddle(void* rawparam) {
  auto [ch, id] = *(std::tuple<Channel*, int>*)rawparam;
  if (0 == id) {
    ch->Send((void*)0);
  }
  _goroutine_yield();
  for (int i=0; i<10000; i++) {
    void* ptr = ch->Recv();
    std::printf("Routine %d: received: %d\n", id, (size_t)ptr);
    ptr = (void*)((size_t)ptr + id);
    ch->Send(ptr);
    _goroutine_yield();
  }
}
int main() {
  auto ch = Channel(1);
  auto wg = WaitGroup();
  { // Routine -1
    std::tuple<Channel*, int> param = {&ch, 0};
    wg.Go(paddle, &param);
  }
  { // Routine +1
    std::tuple<Channel*, int> param = {&ch, +1};
    wg.Go(paddle, &param);
  }
  wg.Join();
}
