# Minitalk

> A small UNIX signal-based communication program developed as part of the 42 School curriculum.

## 📚 Overview

**Minitalk** is a project that demonstrates inter-process communication (IPC) using UNIX signals. The project consists of a **server** and a **client**, where the client sends messages to the server using `SIGUSR1` and `SIGUSR2` signals, encoding the data bit by bit.

This project is a great introduction to low-level signal handling, bitwise operations, and asynchronous programming in C.

## 🛠️ Features

- **Custom Protocol**: Encode and send characters bit by bit using signals.
- **Signal Handling**: Use of `SIGUSR1` and `SIGUSR2` for binary data transmission.
- **Robust Server**: Handles multiple messages and displays them in real-time.
- **Acknowledgment System** *(Bonus)*: Ensures message delivery and synchronization between client and server.

## 📁 Project Structure

### minitalk :
- client.c 	 # Sends messages to the server 
- server.c 	 # Receives and prints messages from clients 
- utils.c 	 # Helper functions (string handling, conversions, etc.) 
- minitalk.h # Header file containing prototypes and includes - 
- Makefile 	 # Build automation

## 🧠 How It Works

1. The **server** starts and prints its **PID**.
2. The **client** sends each character of a string as bits to the server using:
   - `SIGUSR1` for binary `1`
   - `SIGUSR2` for binary `0`
3. The **server** reconstructs each character and prints the full message.

## 🧪 Usage

### 1. Compile

```bash
make
```
### 2. Run Server
```bash
./server
```
Output: Server PID: 12345

### 3. Run Client (in another terminal)
```bash
./client 12345 "Hello, world!"
```
Replace 12345 with the actual server PID displayed.

## 💡 Bonus

- If implemented, the bonus version supports:

- Sending messages with delivery acknowledgment.

- Handling Unicode and longer messages.

- Signal-based synchronization for safer transmission.

## ⚠️ Limitations

- The client must send messages to an existing, running server.

- If the server is not running or the PID is wrong, the message will not be received.

- Message speed depends on system signal handling latency.

## 📌 Project Goals

- Learn low-level communication via signals.

- Understand asynchronous programming and signal safety.

- Practice robust C development with Makefiles and modular design.

## 📝 Author
Developed by **NOUHAILA AZIKI** as part of the 42 curriculum.

