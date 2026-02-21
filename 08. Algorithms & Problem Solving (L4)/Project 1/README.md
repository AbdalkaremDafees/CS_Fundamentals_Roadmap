Bank Management System - User Control Extension
📋 Overview
This extension adds a comprehensive User Management System to the existing Bank Management System, allowing administrators to control access and permissions for different users of the application.

👥 User Management Features
1. User Authentication
Secure login system with username and password verification

Session management for logged-in users

Protection against unauthorized access

2. Permission-Based Access Control
The system implements a binary permission system where each user can have specific access rights:

Permission	Value	Description
Full Access	-1	All permissions granted
List Clients	1	View client list
Add New Client	2	Create new clients
Delete Client	4	Remove clients
Update Clients	8	Modify client information
Find Client	16	Search for clients
Transactions	32	Perform deposits/withdrawals
Manage Users	64	Access user management
3. User Management Operations
📝 Add New User
Create new system users with customizable permissions

Prevent duplicate usernames

Set granular permissions through interactive prompts

👥 Show Users List
Display all registered users

View usernames and their permission levels

Track total user count

🗑️ Delete User
Remove existing users from the system

Protection against deleting the default "Admin" account

Confirmation prompts before deletion

✏️ Update User Information
Modify existing user credentials

Adjust user permissions dynamically

Update passwords and access levels

🔍 Find User
Search for users by username

Display complete user details including permission levels

🔒 Security Features
Password Protection: All users require password authentication

Access Denied Messages: Clear feedback when users attempt unauthorized actions

Admin Protection: Built-in safeguard prevents deletion of main administrator account

Session Management: Proper logout functionality

💾 Data Storage
Users stored in Users.txt file

Data format: Username/##/Password/##/Permissions

Persistent storage with proper file handling operations

🎯 How It Works
Login: Users must authenticate with valid credentials

Permission Check: System verifies user permissions before each operation

Access Control: Users only see options they have permission to use

Session End: Proper logout returns to login screen

📁 File Structure
text
BankManagementSystem/
├── Project1.cpp        # Main application file
├── Clients.txt         # Client data storage
└── Users.txt          # User credentials and permissions
🚀 Getting Started
Default admin credentials: Username: Admin, Password: Admin (you can modify these in Users.txt)

Login with admin credentials to access all features

Add new users with specific permissions as needed

Regular users will only see menu options they have access to

⚙️ Technical Implementation
Written in C++ with object-oriented principles

Uses file I/O for persistent data storage

Implements binary bitmasking for efficient permission management

Clean separation between client management and user management modules