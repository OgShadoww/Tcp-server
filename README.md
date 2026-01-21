# Simple Multi-Threaded TCP Server (C)

A lightweight multi-threaded TCP client–server application written in pure C using POSIX sockets and pthreads.

This project demonstrates:

* Low-level socket programming (IPv4, TCP)
* Thread-per-connection server design
* Basic network I/O
* Running services persistently on a VPS

---

## 📦 Features

* Multi-client support using `pthread`
* Listens on all network interfaces (`INADDR_ANY`)
* Simple echo-style request/response logic
* Graceful connection handling
* Ready for deployment on a public VPS

---

## 🗂 Project Structure

```
.
├── server.c     # TCP server implementation
├── client.c     # TCP client implementation
└── README.md    # Project documentation
```

---

## ⚙️ Requirements

* Linux / macOS
* GCC or Clang
* POSIX threads (pthreads)

---

## 🛠 Build

Compile both server and client:

```bash
gcc -Wall -Wextra -O2 server.c -o server -lpthread
gcc -Wall -Wextra -O2 client.c -o client
```

---

## 🚀 Run Locally

### Start the server

```bash
./server
```

You should see:

```
Listening...
```

---

### Run the client

Edit `client.c` and replace:

```c
inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
```

With:

```c
inet_pton(AF_INET, "YOUR_SERVER_IP", &addr.sin_addr);
```

Then:

```bash
./client
```

Type messages and see echoed responses from the server.


---

## 📈 Future Improvements

* Switch to epoll instead of thread-per-client
* Add TLS (OpenSSL)
* Add authentication
* Implement a simple protocol
* Add logging
* Dockerize for CI/CD

---

## 🧠 Learning Goals

This project helps you practice:

* TCP/IP networking
* POSIX threads
* System-level debugging
* VPS deployment
* Linux process management
* DevOps basics

---

## 📜 License

MIT License

---

## ✨ Author

Orest

Built as part of a low-level networking & DevOps learning journey.

