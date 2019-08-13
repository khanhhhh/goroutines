# GOROUTINES IN C++

The two features that the most "đáng đồng tiền bát gạo" in Golang is `goroutine` and `channel`.

- `goroutine` is a very lightweight asynchronous call (2KB of stack memory) that has been used in Golang to provide concurrency with its own scheduler (Threads using OS scheduler). Therefore, using `goroutine` can produce a very optimized code with minimum overheads of context switching and memory.

- `channel` is a shared buffer between `goroutine`s.

`Do not communicate by sharing memory; instead, share memory by communicating.`

# FEATURES

- Goroutines: Run a C functions in a goroutine.

- Yeild: Provide a hint to scheduler

- Channel: Channel of void pointer

# CODE

- This code using 2 features of go compiler `cgo` and`export`.

# BUILD

- Create shared library

  - `cd libgoroutine`

  - `make build` : build library and C api
  
- Compile with C++ header

  - `make all`
