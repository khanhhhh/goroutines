#include"goroutine.h"
#include<stdio.h>

typedef struct {
  size_t channel;
  int id;
} param_t;
void paddle(void* rawparam) {
  param_t param = *(param_t*)rawparam;
  printf("ID: %d\n", param.id);
  _goroutine_yield();
  for (int i=0; i<10; i++) {
    size_t item = _goroutine_recv_channel(param.channel);
    printf("Routine (%d): received: %zu\n", param.id, item); fflush(stdout);
    item += param.id;
    _goroutine_send_channel(param.channel, item);
    _goroutine_yield();
  }
}

int main() {
size_t item = -1;
{
  size_t ch = _goroutine_new_channel(1);
  _goroutine_send_channel(ch, 0);
  {
    size_t wg = _goroutine_new_waitgroup();
    {
      param_t argument = {ch, -1};
      _goroutine(paddle, &argument, wg);
    }
    {
      param_t argument = {ch, +1};
      _goroutine(paddle, &argument, wg);
    }
    _goroutine_join_waitgroup(wg);
    _goroutine_del_waitgroup(wg);
  }
  item = _goroutine_recv_channel(ch);
  _goroutine_del_channel(ch);
}
  printf("Main: received: %zu\n", item);
  return 0;
}
