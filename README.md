# 📚 Library Management System

A simple, console-based **Library Management System** built in **C++**, designed to manage books, users, and admin operations with file persistence. The system supports Admin/User roles, book issue tracking, and dynamic user management, all through a clear CLI interface.

---

## ✅ Features

### 👤 Admin Access
- Login with **admin ID and password**
- Add books and new admins
- Issue or return books
- Search books by title or ID
- Search users by ID
- View all books or users
- View issued books with corresponding users
- View books issued by a specific user
- Automatically removes users who return all books

### 👥 User Access
- Search books by title
- Issue books (user is automatically added if new)
- Return books (user is deleted if all books returned)
- View all available books

### 📂 File I/O
- All data is persisted across sessions using text files:
  - `books.txt` → list of books
  - `admins.txt` → list of admin credentials
  - `users.txt` → active users who have issued books
  - `issued.txt` → book-user issue mapping

### 🧠 Smart User Management
- Users are **created only when they issue a book**
- Users are **deleted automatically** once they return all their books

### 🗂️ Efficient Data Structures
- `unordered_map` for fast lookups (by ID)
- `map` for sorted display (by title/name)
- `bookIssuedByUser` map to track which user issued which book

---

## 🛠️ How to Run

1. **Compile the project** using any C++ compiler:
   ```bash
   g++ main.cpp src/*.cpp -o LibrarySystem
2. *Ensure* the following files exist (can be empty initially):
  - `books.txt`
  - `admins.txt`
  - `users.txt`
  - `issued.txt`
3. **Run the executable:**
    `./LibrarySystem`
