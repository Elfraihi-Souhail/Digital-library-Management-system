# Digital Library Management System

A streamlined C application for managing library operations using custom data structures and a terminal-based interface.

## ✨ Features

### Core Management
- **Book Catalog**: Manage titles, authors, and copies in a sorted list
- **Borrower Records**: Handle member IDs and names efficiently
- **Loan System**: Process borrow/return transactions with date tracking

### Advanced Functionality
- **Priority Queue**: Automatic loan sorting and processing
- **Configurable Timer**: Set `MAX_TIMER` for batch processing control
- **Smart Date Handling**: Due date calculations and overdue detection
- **Data Import**: Load initial data from text files

### Visualization & UI
- **Color-Coded Interface**: Enhanced terminal experience
- **SVG Reports**: Generate visual statistics (books, loans, priorities)
- **Interactive Menus**: Easy navigation through all functions

## 🏗️ Technical Stack

- **Language**: C
- **Data Structures**: Doubly-linked lists, Queues
- **Architecture**: Modular design with separate components
- **Compatibility**: Windows & Linux/Unix systems

## 🚀 Quick Start

```bash
# Compile
gcc -o main.c library.c libtime.c

# Run
./main
```

## 📋 Menu Options

1. **File Operations** - Import data
2. **Book Management** - Add/remove/search books
3. **Borrower Management** - Handle members
4. **Loan Management** - Process transactions
5. **Display Options** - View catalogs and reports
6. **Generate Statistics** - Create visual reports
7. **Configure Settings** - Adjust system parameters
