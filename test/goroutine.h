typedef __SIZE_TYPE__ GoUintptr;
#ifdef __cplusplus
extern "C" {
#endif
extern void _goroutine(void* p0, void* p1, GoUintptr p2);
extern GoUintptr _goroutine_new_waitgroup();
extern void _goroutine_del_waitgroup(GoUintptr p0);
extern void _goroutine_join_waitgroup(GoUintptr p0);
extern void _goroutine_yield();
extern GoUintptr _goroutine_new_channel(GoUintptr p0);
extern void _goroutine_del_channel(GoUintptr p0);
extern GoUintptr _goroutine_recv_channel(GoUintptr p0);
extern void _goroutine_send_channel(GoUintptr p0, GoUintptr p1);
#ifdef __cplusplus
}
#endif
