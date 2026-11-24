# Network Programming – Tutorials 1 & 2

This repository contains my work for the first two tutorials of the Network Programming lab.

The goal was to understand how a server and client communicate using TCP sockets in C++.

## Files

- `Daytime_server.cpp` – Creates a server that listens on port 1313 and sends the current date and time.
- `Daytime_client.cpp` – Connects to the server, receives the date and time, and displays it.

## How to Run

First, compile and run the server:

powershell
g++ -std=c++17 Daytime_server.cpp -o daytime_server.exe -lws2_32
.\daytime_server.exe


Open another terminal and compile and run the client:

powershell
g++ -std=c++17 -o daytime_client.exe Daytime_client.cpp -lws2_32
.\daytime_client.exe 127.0.0.1 1313


## Problems Faced

- **Wrong directory:** Initially, we were running commands from the parent folder instead of the `netlab` folder where the source files were saved. This caused the compiler to report that it couldn't find the files.

  We fixed this by navigating to the correct folder using:
   powershell
  cd "C:\Users\Al MAJEED\Documents\C++ Basics\netlab"
  

- **Ncat not recognized:** We tried using Ncat to test the server, but PowerShell didn't recognize the command because it wasn't installed or available in PATH.

  Instead, we created our own daytime client and used it to test the server.

- **Client compilation:** We used the following command to compile the client successfully:

  ```powershell
  g++ -std=c++17 -o daytime_client.exe Daytime_client.cpp -lws2_32
  ```

## Testing

- Connected the client to `127.0.0.1` on port `1313`.
- Received and displayed the date and time successfully.
- Tested the connection using `localhost`.
- Tested the client's response when the server was stopped.

## What I Learned

Got a better understanding of TCP sockets, client-server communication, IP addresses, ports, and how data is sent and received between two programs.