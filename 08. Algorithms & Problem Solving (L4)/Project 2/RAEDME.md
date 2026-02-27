# ATM Management System

A robust, console-based ATM management system developed in C++ to demonstrate the fundamentals of functional programming, file handling, and data structures.

## 📋 Overview

This project simulates a real-world ATM interface. It allows users to authenticate themselves via a secure login screen and perform standard banking operations such as withdrawing, depositing, and checking account balances. Data persistence is handled through an external flat-file database (`Clients.txt`).

## ✨ Features

* **Secure Authentication**: Validates user credentials (Account Number and PIN) against the data file.
* **Quick Withdraw**: Provides pre-defined denominations for faster transactions.
* **Normal Withdraw**: Allows custom amounts that are verified for specific business rules (multiples of 5).
* **Deposit System**: Enables real-time balance updates.
* **Persistent Data Storage**: All transactions and balance changes are saved to `Clients.txt` immediately using file streams.
* **User-Friendly Navigation**: A clean, modularized main menu interface.

## 🛠 Technical Implementation

* **Language**: C++
* **Programming Paradigm**: Functional Programming (Modular design using specific functions for each task).
* **Data Management**:
* **Structs**: Used `sClient` to represent user data effectively.
* **Vectors**: Managed client data in memory using the Standard Template Library (`vector`).
* **File I/O**: Leveraged `<fstream>` for reading from and writing to the database file.


* **Code Organization**: Logic is split into clear segments (Authentication, Withdrawals, Deposits, and Data Parsing).

## 📁 File Structure

* `Project 2_Course 8.cpp`: The primary source code containing all system logic.
* `Clients.txt`: The flat-file database using `/##/` as a delimiter to store client records.

## 🚀 Getting Started

1. **Prerequisites**: Ensure you have a C++ compiler (like GCC or MSVC) installed.
2. **Clone/Download**: Save the files to your local machine.
3. **Setup**: Make sure `Clients.txt` is in the same directory as your compiled executable.
4. **Compile**: Use your preferred IDE or command line:
```bash
g++ -o ATM_System "Project 2_Course 8.cpp"

```


5. **Run**:
```bash
./ATM_System

```



## 📈 Future Roadmap

* Implementing multi-threading for handling concurrent transactions.
* Adding a dedicated transaction history log for each account.
* Enhancing security with encrypted PIN storage.