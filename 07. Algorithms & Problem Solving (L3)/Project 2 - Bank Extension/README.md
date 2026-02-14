Bank Management System (C++) - Project 2
A robust, console-based Bank Management System designed to handle client records and financial transactions using C++. This project focuses on CRUD operations and file-based data persistence, utilizing a structured approach with std::vector and custom data types.

🚀 Features
1. Client Management (CRUD)
Show Client List: Displays all registered clients in a formatted table.

Add New Client: Validates and adds unique account numbers to the system.

Update/Delete: Allows for modification or removal of client records with confirmation prompts.

Find Client: Quick search functionality by Account Number.

2. Transaction Module
Deposit: Increase account balance for a specific client.

Withdraw: Secure withdrawal with balance sufficiency checks.

Total Balances: View a summary of all accounts and the bank's total liquidity.

3. Data Persistence
Uses a flat-file database (myFile.txt) with custom delimiters (/##/) to ensure data is saved across sessions.

🛠️ Technical Overview
Language: C++

Data Structures: struct for record modeling and std::vector for in-memory data manipulation.

File I/O: fstream for reading and writing client records.

Formatting: iomanip for clean, professional console output tables.

📖 How to Run
Ensure you have a C++ compiler installed (e.g., GCC, Clang, or MSVC).

Clone the repository and navigate to the directory.

Compile the file:

Bash

g++ "Project 2 - Extension Fro Project 1.cpp" -o BankSystem
Run the executable:

Bash

./BankSystem