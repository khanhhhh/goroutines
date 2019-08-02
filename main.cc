#include"goroutine.hh"
#include<cstdio>
#include<tuple>

void paddle(void* rawparam) {
  auto [ch, id] = *(std::tuple<Channel*, int>*)rawparam;
  if (0 == id) {
    ch->Send(nullptr);
  }
  WaitGroup::Yield();
  for (int i=0; i<5; i++) {
    void* ptr = ch->Recv();
    std::printf("Routine %d: received!\n", id);
    ch->Send(ptr);
    WaitGroup::Yield();
  }
}
int main() {
  auto ch = Channel(1);
  auto wg = WaitGroup();
  { // Routine 0
    std::tuple<Channel*, int> param = {&ch, 0};
    wg.Go(paddle, &param);
  }
  { // Routine 1
    std::tuple<Channel*, int> param = {&ch, 1};
    wg.Go(paddle, &param);
  }
  wg.Join();
}
