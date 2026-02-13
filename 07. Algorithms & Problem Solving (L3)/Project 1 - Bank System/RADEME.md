Bank Management System (Console-based)
A simple and efficient C++ Console Application to manage bank client records. This project demonstrates core programming concepts including File Handling, Data Structures (Structs), and CRUD operations.

🚀 Features
The system provides a main menu to perform the following operations:

Show Client List: Displays all clients stored in the system in a formatted table.

Add New Client: Allows adding new records with validation to prevent duplicate Account Numbers.

Delete Client: Removes a client record safely based on their Account Number.

Update Client Info: Enables editing existing client details (Pin Code, Name, Phone, Balance).

Find Client: Searches and displays specific client details quickly.

Exit: Safely closes the program.

🛠️ Technical Highlights
File Persistence: Data is stored and retrieved from a text file (myFile.txt) using fstream.

Data Formatting: Uses iomanip (setw, left) for a clean, tabular UI in the console.

Architecture: Utilizes struct for data modeling and vector for dynamic memory management.

Data Parsing: Includes a custom string splitting function to handle delimited data (/#).

📁 Project Structure
main.cpp: Contains the full source code and logic.

myFile.txt: The database file where client records are saved (auto-created upon running).

💻 How to Run
Ensure you have a C++ compiler installed (like GCC/MinGW).

Compile the code:

Bash

g++ main.cpp -o BankSystem
Run the executable:

Bash

./BankSystem