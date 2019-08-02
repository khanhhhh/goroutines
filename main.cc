#include"goroutine.hh"
#include<cstdio>
#include<tuple>
void adder(void* void_param) {
  auto [ch, num] = *(std::tuple<Channel*, int>*)void_param;
  while (true) {
    size_t i = (size_t)ch->Recv();
    i = i + num;
    ch->Send((void*)i);
  }
}
int main() {
  auto ch = new Channel(1);
  ch->Send((void*)1);

  auto wg = WaitGroup();
  {
    std::tuple<Channel*, int> param {ch, +1};
    wg.Go(adder, &param);
  }
  {
    std::tuple<Channel*, int> param {ch, -1};
    wg.Go(adder, &param);
  }

  while (true) {
    size_t i = (size_t)ch->Recv();
    std::printf("%d\n", i);
    ch->Send((void*)i);
  }
  delete ch;
}
