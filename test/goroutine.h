typedef __SIZE_TYPE__ GoUintptr;
typedef __SIZE_TYPE__ size_t;
#ifdef __cplusplus
extern "C" {
#endif
extern void _goroutine(void* function, void* parameter, GoUintptr waitgroup);
extern GoUintptr _goroutine_new_waitgroup();
extern void _goroutine_del_waitgroup(GoUintptr waitgroup);
extern void _goroutine_join_waitgroup(GoUintptr waitgroup);
extern void _goroutine_yield();
extern GoUintptr _goroutine_new_channel(GoUintptr count);
extern void _goroutine_del_channel(GoUintptr channel);
extern GoUintptr _goroutine_recv_channel(GoUintptr channel);
extern void _goroutine_send_channel(GoUintptr channel, GoUintptr item);
#ifdef __cplusplus
}
#endif
