# **Computer Networks Lab Experiments**

**Repository Name:** `computer-networks`  
**Description:** A collection of networking protocols, algorithms, and simulations implemented in C for educational purposes. This repository includes implementations of key computer networking concepts such as TCP, UDP, routing algorithms, and error-control protocols.

---

## **📌 Repository Structure**
| File/Folder | Description |
|-------------|-------------|
| **`ftp/`** | File Transfer Protocol (FTP) implementation for client-server file exchange. |
| **`go_back_N/`** | Implementation of the Go-Back-N ARQ protocol for reliable data transfer. |
| **`multi-user-chat/`** | A multi-user chat application demonstrating socket programming. |
| **`selective_repeat/`** | Selective Repeat ARQ protocol for efficient error recovery in data transmission. |
| **`tcp/`** | TCP socket programming examples (e.g., connection setup, data transfer). |
| **`udp/`** | UDP socket programming examples (e.g., datagram transmission). |
| **`DistanceVectorRouting.c`** | Distance Vector Routing algorithm implementation (e.g., RIP). |
| **`LinkStateRouting.c`** | Link-State Routing algorithm implementation (e.g., Dijkstra’s algorithm). |
| **`leaky.c`** | Leaky Bucket algorithm for traffic shaping and congestion control. |
| **`.gitignore`** | Specifies files to be ignored by Git (e.g., executables, object files). |

---

## **🚀 How to Use**
1. **Clone the Repository**:
   ```sh
   git clone https://github.com/your-username/computer-networks.git
   cd computer-networks
   ```

2. **Compile and Run**:
   - For C files (e.g., routing algorithms):
     ```sh
     gcc DistanceVectorRouting.c -o dvr
     ./dvr
     ```
   - For protocol implementations (e.g., TCP/UDP), refer to the respective subfolder’s `README`.

---

## **🛠️ Dependencies**
- **GCC** (for compiling C programs)
- **Linux/Unix environment** (recommended for socket programming)
- **Wireshark** (optional, for packet analysis)

---

## **📜 License**
This project is open-source under the **MIT License**. Feel free to use, modify, and distribute the code for educational purposes.

---

## **📌 Key Features**
✅ **Error-Control Protocols**:  
   - Go-Back-N (`go_back_N/`)  
   - Selective Repeat (`selective_repeat/`)  

✅ **Routing Algorithms**:  
   - Distance Vector (`DistanceVectorRouting.c`)  
   - Link-State (`LinkStateRouting.c`)  

✅ **Traffic Management**:  
   - Leaky Bucket (`leaky.c`)  

✅ **Socket Programming**:  
   - TCP (`tcp/`)  
   - UDP (`udp/`)  

✅ **Applications**:  
   - FTP (`ftp/`)  
   - Multi-User Chat (`multi-user-chat/`)  

---

## **🤝 Contributing**
Contributions are welcome! If you’d like to improve the code or add new networking implementations:
1. Fork the repository.  
2. Create a new branch (`git checkout -b feature/new-protocol`).  
3. Commit your changes (`git commit -m "Add new feature"`).  
4. Push to the branch (`git push origin feature/new-protocol`).  
5. Open a **Pull Request**.  

---

## **📧 Contact**
For questions or suggestions, feel free to reach out:  
📩 **Email**: nehaelizabeththomas0@gmail.com
