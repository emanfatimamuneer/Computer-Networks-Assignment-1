# Multithreaded Server (ThreadServer)

## Overview
A basic server handles one client at a time, so a second client has to wait. **ThreadServer** creates one thread for every connected client, so many clients are served at the same time. Each thread echoes back whatever its client sends.

## Files
| File | Description |
|------|-------------|
| `thread_server.cpp` | Echo server that uses one thread per client |
| `echo_client.cpp` | Client used to test the server |
| `Screenshots/` | Screenshots of the server with two active clients and both client windows |

Both programs use the shared `net.hpp`.

## How it works
- `accept()` returns a new socket for each client.
- `std::move` hands that socket to a new thread running `serve_client`.
- `detach()` lets the thread clean itself up when the client leaves, so the main loop goes straight back to `accept()`.
- `std::mutex` (`g_log`) stops two threads from mixing their `cout` lines.
- `std::atomic<int>` (`g_active`) keeps the active client counter correct when several threads change it at once.

## Build (g++)
```
g++ -std=c++17 -Wall -Wextra thread_server.cpp -o thread_server.exe -lws2_32
g++ -std=c++17 -Wall -Wextra echo_client.cpp -o echo_client.exe -lws2_32
```

## Run
Terminal 1 (server):
```
.\thread_server.exe 5000
```
Terminal 2 and 3 (two clients):
```
.\echo_client.exe 127.0.0.1 5000
```
Type text in both clients. Each one gets its own echo. Press Ctrl+Z then Enter to quit a client.

## Expected server output
```
Thread server on port 5000
127.0.0.1:50114 connected. Active clients: 1
127.0.0.1:52434 connected. Active clients: 2
127.0.0.1:52434 disconnected. Active clients: 1
127.0.0.1:50114 disconnected. Active clients: 0
```
Port numbers will differ on each run.

## Trade-off
One thread per client is simple and works well for a small number of clients. With thousands of clients it uses a lot of memory and spends time switching between threads.

## Screenshots
See the `Screenshots` folder for the server with 2 active clients and both client windows.
