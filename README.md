# Systems & Low-Level Engineering Suite

A comprehensive collection of core computer science implementations, systems-level utilities, operating system synchronization mechanisms, and fundamental data structures implemented from scratch in modern C++ and C.

---

## 📂 Repository Structure

### 1. [`os-and-system-programming/`](./os-and-system-programming)
Operating system mechanisms and concurrency primitives exploring thread safety, synchronization, and low-level networking:
* **Classic Concurrency Problems:** Implementations of Dining Philosophers, Sleeping Barber, Readers-Writers, and Producer-Consumer models.
* **Synchronization Primitives:** Native WinAPI / POSIX mutexes, condition variables, semaphores, and critical sections.
* **Network Sockets:** Custom TCP/UDP client-server implementations built upon native socket APIs (`sys/socket.h` / `WinSock2`).

### 2. [`cpp-algorithms/`](./cpp-algorithms)
Zero-dependency, cache-friendly implementations of abstract data types:
* **Binary Heap & Priority Queue:** Array-backed binary heap with `O(log n)` insertion and extraction.
* **Custom Dynamic Array:** Contiguous memory vector with manual reallocation strategies and amortized `O(1)` appending.
* **Linear Containers:** Singly and doubly linked lists, stacks, and circular queues.

### 3. [`cpp-core-oop/`](./cpp-core-oop)
Modular C++ architecture emphasizing clean code and systems design:
* **OOP & Patterns:** Extensive application of RAII, encapsulation, and the Observer pattern (`Subject.cpp`).
* **Database Integration:** Direct integration with embedded SQLite engine (`sqlite3.c`) for deterministic data persistence.

### 4. [`assembly-routines/`](./assembly-routines)
Low-level x86 subroutines and hardware-interfacing programs focusing on CPU architecture, register management, and instruction-level execution:
* **Arithmetic & Carry Flags:** Signed/unsigned multi-byte arithmetic handling carry/borrow flags (`ADC`, `SBB`, `CWD`, `IDIV`).
* **Fixed-Point & BCD Computation:** Software implementation of fractional calculations via fixed-point representations and binary-coded decimal arithmetic utilizing hardware CPU correction (`DAA`, `DAS`).
* **x87 FPU Coprocessor:** Direct IEEE 754 floating-point operations utilizing the x87 coprocessor register stack (`FLD`, `FADD`, `FMUL`, `FDIV`, `FIST`).
* **Calling Conventions & Memory Alignment:** Stack frame construction (`EBP`/`ESP`), manual parameter passing via stack, and raw contiguous memory array operations.
  
---

## Build & Compilation

The project uses CMake for cross-platform compilation.

```bash
# Clone repository
git clone [https://github.com/OrukamiTensey/systems-and-low-level-programming.git](https://github.com/OrukamiTensey/systems-and-low-level-programming.git)
cd systems-and-low-level-programming

# Configure build
cmake -B build -S .

# Build all targets
cmake --build build --config Release

