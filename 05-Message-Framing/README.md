# Message Framing (FrameClient)

## Overview
TCP is a stream of bytes and does not keep message boundaries. If a client sends `one`, `two` and `three` one after another, the server may receive them joined together or split in a different way. This program solves that with **length-prefixed messages**: every message is sent with its size in front of it.

## Files
| File | Description |
|------|-------------|
| `frame_client.cpp` | Client that sends several framed messages and prints the replies |
| `Screenshots/` | Screenshots of the client and server output |

The client uses `send_msg` and `recv_msg` from the shared `net.hpp` (section "Length-prefixed messages"). It is tested against `frame_server.cpp`.

## How the framing works
1. **Sending (`send_msg`):** the message length is converted to network byte order with `htonl` and sent as 4 bytes, followed by the message itself.
2. **Receiving (`recv_msg`):** the receiver reads exactly 4 bytes to get the length, converts it with `ntohl`, then reads exactly that many bytes.
3. **Safety limit:** `MAX_MSG` is 1 MB. A larger length is rejected so a bad sender cannot force a huge memory allocation.

## What FrameClient does
1. Connects to the server using the host and port given on the command line.
2. Sends each remaining argument as a separate framed message.
3. Reads one framed reply for each message and prints it.

## Build (g++)
```
g++ -std=c++17 -Wall -Wextra frame_client.cpp -o frame_client.exe -lws2_32
g++ -std=c++17 -Wall -Wextra frame_server.cpp -o frame_server.exe -lws2_32
```

## Run
Terminal 1 (server):
```
.\frame_server.exe 5001
```
Terminal 2 (client):
```
.\frame_client.exe 127.0.0.1 5001 one two three
```

## Expected output
Client:
```
Reply: ONE
Reply: TWO
Reply: THREE
```
Server:
```
Got 3 bytes
Got 3 bytes
Got 5 bytes
```
The server received each message separately with the correct size and sent it back in uppercase.

## Screenshots
See the `Screenshots` folder for the client and server windows.
