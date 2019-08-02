#include"goroutine.hh"
#include<cstdio>
void foo(void*) {
  for (int i=0; i<10; i++) {
    std::printf("world\n");
  }
}
int main() {
  auto wg = WaitGroup();
  wg.Go((void*)foo, nullptr);
  wg.Join();
  std::printf("Done!\n");
}