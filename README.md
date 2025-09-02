Project Title: Advanced Digital Library Management System
A comprehensive, menu-driven C application for managing a library's core operations. This system efficiently handles book and borrower catalogs, loan transactions, and real-time statistics through a custom-built data structure ecosystem of doubly-linked lists and priority queues.

🌟 Key Features
Dual Catalog Management:

Books: Maintain a sorted list of books with details like ID, title, author, and available copies.

Borrowers: Manage a list of library members with unique IDs and names.

Features: Add, remove, search (by ID/name/title), and display all entries.

Intelligent Loan & Return System:

Process book borrowings and returns with date tracking.

Implements a priority-based queue system to manage loan requests.

Configurable Processing Timer (MAX_TIMER): Automatically processes the oldest loan request after a user-defined number of new requests are made, simulating real-world batch processing.

Dynamic Priority Assignment: Loans are automatically assigned a priority level (0-9), which is used to sort and visualize active loans, providing insights into loan urgency or status.

Advanced Date & Time Management: Includes a custom date-handling module (libtime.c) for:

Calculating due dates by adding days to a loan date.

Identifying overdue books and calculating overdue days.

Determining active loan periods.

Data Persistence: Import initial data from text files for books, borrowers, and loan/return transactions, making the system scalable and easy to bootstrap.

Rich Terminal Interface:

Color-coded menus and outputs for improved readability and user experience.

Cross-platform screen clearing for a clean interface.

Comprehensive Reporting & Statistics:

View active loans, return history, and overdue books.

Generate detailed visual statistics exported to an SVG file (library_statistics.svg), creating bar charts for:

Total Books vs. Borrowers

Loan Priority Distribution

Total Copies vs. Active Loans

🛠️ Technical Implementation
Language: C

Data Structures:

Doubly-Linked Lists: For efficient management and traversal of books and borrowers.

Queue (Linked List Implementation): To handle the FIFO (First-In, First-Out) nature of loan requests.

Priority Sorting: Loans are sorted and displayed based on a dynamically assigned priority value.

Memory Management: Manual memory allocation and deallocation (malloc, free) ensuring no leaks.

Modular Architecture: Code is separated into logical modules (library.c, libtime.c, main.c) with clear header files for better maintainability.

📁 Project Structure
text
digital-library-system/
├── main.c          # Core application & menu interface
├── library.h       # Header file for core data structures and functions
├── library.c       # Implementation of book, borrower, and loan logic
├── libtime.h       # Header for date-time utilities
├── libtime.c       # Implementation of date calculations and manipulations
└── README.md       # Project description and instructions
🚀 How to Run
Compile: Use a C compiler (e.g., gcc) to compile all .c files.

bash
gcc -o library_system main.c library.c libtime.c
Execute: Run the generated executable.

bash
./library_system
📊 Sample Data Files
The system can read from structured text files:

Books: ADD_BOOK <id> "<title>" "<author>" <copies>

Borrowers: ADD_BORROWER <id> <name>

Loans/Returns: BORROW_BOOK/RETURN_BOOK <book_id> <borrower_id> <YYYY-MM-DD>
