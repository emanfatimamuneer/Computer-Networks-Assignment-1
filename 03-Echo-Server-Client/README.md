# Echo Server and Client (EchoClient)

## Overview
An echo server sends back exactly what it receives. The **EchoClient** reads lines typed by the user, sends each one to the server, and prints the echoed reply.

## Files
| File | Description |
|------|-------------|
| `echo_client.cpp` | Client that sends typed lines and prints the echo |
| `Screenshots/` | Screenshots of the output |

The client uses `tcp_connect`, `send_all` and `recv_all` from the shared `net.hpp`. It works with the echo server and also with the multithreaded `thread_server.cpp` (folder `06-Multithreaded-Server`).

## How it works
1. Connects to the server using the host and port (defaults: `127.0.0.1` and `5000`).
2. Reads one line from the keyboard and adds a newline.
3. Sends the line with `send_all`.
4. Reads back the same number of bytes with `recv_all` and prints `Echo: ...`.
5. Repeats until the user presses Ctrl+Z then Enter.

## Build (g++)
```
g++ -std=c++17 -Wall -Wextra echo_client.cpp -o echo_client.exe -lws2_32
```

## Run
Start a server first, for example:
```
.\thread_server.exe 5000
```
Then start the client:
```
.\echo_client.exe 127.0.0.1 5000
```

## Example
```
Connected. Type text. Press Ctrl+Z then Enter to stop.
hello
Echo: hello
```

## Screenshots
See the `Screenshots` folder.
