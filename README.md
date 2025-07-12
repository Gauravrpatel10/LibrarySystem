# 📚 Library Management System

A simple, console-based **Library Management System** built in **C++**, designed to manage books, users, and admin operations with file persistence. This system is menu-driven, supports role-based access (Admin/User), and maintains book records efficiently using STL containers.

---

## ✅ Features

### 👤 Admin Access
- Login with **admin ID and password**
- Add books, users, or new admins
- Issue or return books
- Search books by title
- Search users by ID
- View all books or users
- Automatically deletes users who return all books

### 👥 User Access
- Search books by title
- Issue books (enter user info if not already registered)
- Return books
- View all available books

### 📂 File I/O
- Books and admins are saved to text files (`books.txt`, `admins.txt`)
- Data is automatically loaded on startup and saved on exit
- File format:
  - Books: `id,title,author,issued`
  - Admins: `id,name,password`

### 🧠 Smart User Management
- Users are **created only when they issue a book**
- Users are **deleted automatically** once they return all books

### 🗂️ Efficient Data Structures
- `unordered_map` for fast ID-based lookups
- `map` for sorted title/name display
- `bookIssuedToUser` map to track who has issued which book

---

## 🛠️ How to Run

1. **Compile the project** using any C++ compiler (e.g., g++, Code::Blocks, Visual Studio)
2. Make sure `books.txt` and `admins.txt` are in the **same folder** as your `.exe` or executable
3. Run the program and follow the menu options

---

## 📁 File Structure

