#ifdef _WIN32
#include <windows.h>
#else
#include <stdio.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

// Remove the #define MAX_TIMER
// Instead, add it as an external variable
extern int MAX_TIMER;  // Will be defined in library.c

typedef struct books
{
    int id;
    int copies;
    char title[64];
    char author[32];
    struct books* next;
    struct books* prev;
} *bkptr;
typedef struct borrowers
{
    int id;
    char name[32];
    struct borrowers* next;
    struct borrowers* prev;
} *brptr;
typedef struct loan
{
    int id_bk;
    int id_br;
    char date[11];
    int priority;
    struct loan* next;
} loan;
typedef struct
{
    struct loan* head;
    struct loan* tail;
    int request_count;  // Counter for tracking number of requests
} queue;

// Abstract machines of books
bool allocate_bk (bkptr *cell);             // Allocates memory for a new book node
void ass_id_bk (bkptr cell , int val);      // Sets book ID
void ass_title (bkptr cell , char string[64]); // Sets book title
void ass_author (bkptr cell , char string[32]); // Sets book author
void ass_copies(bkptr cell , int val);      // Sets number of book copies
void ass_next_bk (bkptr p , bkptr q);       // Links to next book in list
void ass_prev_bk (bkptr p , bkptr q);       // Links to previous book in list
bkptr next_bk (bkptr p);                    // Gets next book pointer
bkptr prev_bk(bkptr p);                     // Gets previous book pointer
int id_bk(bkptr p);                         // Gets book ID
char* title(bkptr p);                       // Gets book title
char* author (bkptr p);                     // Gets book author
int copies(bkptr p);                        // Gets number of copies
void free_book (bkptr book);                // Deallocates book memory

// Abstract machines of borrowers
bool allocate_br (brptr *cell);             // Allocates memory for new borrower
void ass_id_br (brptr cell, int val);       // Sets borrower ID
void ass_name (brptr cell , char string[32]); // Sets borrower name
void ass_next_br (brptr p , brptr q);       // Links to next borrower
void ass_prev_br (brptr p , brptr q);       // Links to previous borrower
brptr next_br (brptr p);                    // Gets next borrower pointer
brptr prev_br (brptr p);                    // Gets previous borrower pointer
int id_br(brptr p);                         // Gets borrower ID
char* name(brptr p);                        // Gets borrower name
void free_borrower (brptr borrower);        // Deallocates borrower memory

// Abstract machines of loans
void create_queue (queue *q);               // Initializes empty loan queue
int full_queue (queue q);                   // Checks if queue is full
bool empty_queue (queue q);                 // Checks if queue is empty
int idbk_q(loan * p);                       // Gets book ID from loan
int idbr_q(loan * p);                       // Gets borrower ID from loan
loan * next_q(loan * p);                    // Gets next loan in queue
char* date_q(loan * p);                     // Gets loan date
void ass_next_q(loan * p, loan * q);        // Sets next loan pointer
void ass_idbk_q(loan * p, int idbk);        // Sets book ID in loan
void ass_idbr_q(loan * p, int idbr);        // Sets borrower ID in loan
int enqueue(queue *q , bkptr headbk , brptr headbr); // Adds new loan to queue
void ass_prio(loan * p, int prio);        // Sets loan priority
int priority(loan * p);                     // Gets loan priority

// Book list operations
bkptr get_tail_bk(bkptr head);              // Gets last book in list
int idbk_exist(bkptr head , int id);        // Checks if book ID exists
int add_book (bkptr *head , int n);         // Adds n new books
int add_books_file(bkptr *head , const char filename[]); // Loads books from file
void swap_books (bkptr p , bkptr q);        // Swaps two books in list
void bubble_sort_bk (bkptr *head);          // Sorts books by ID
bkptr search_bk_id(bkptr head , int id);    // Finds book by ID
bkptr search_bk_title(bkptr head , char string[]); // Finds book by title
void remove_bk_id(bkptr *head , int id);    // Removes book by ID
void remove_bk_title(bkptr *head , char string[]); // Removes book by title

// Borrower list operations
brptr get_tail_br(brptr head);              // Gets last borrower in list
int idbr_exist(brptr head , int id);        // Checks if borrower exists
int add_borrower (brptr *head , int n);     // Adds n new borrowers
int add_borrowers_file(brptr *head , const char filename[]); // Loads borrowers from file
void swap_borrowers (brptr p , brptr q);    // Swaps two borrowers
void bubble_sort_br (brptr *head);          // Sorts borrowers by ID
brptr search_br_id(brptr head , int id);    // Finds borrower by ID
brptr search_br_name(brptr head , char string[]); // Finds borrower by name
void remove_br_id(brptr *head , int id);    // Removes borrower by ID
void remove_br_name(brptr *head , char string[]); // Removes borrower by name

// Loan queue operations
void set_max_timer(int value);              // Sets the MAX_TIMER value
void define_prio(loan * p);                 // Sets loan priority based on date
int idbr_exist_q(queue q, int idbr);        // Checks for active loans by borrower
int idbk_exist_q(queue q, int idbk);        // Checks for loans of a book
int borrow_enqueue(queue *q, bkptr headbk, brptr headbr); // Processes new loan
int borrow_file(queue *q , const char filename[]); // Loads loans from file
int return_file(queue *q , const char filename[]); // Loads returns from file
int date_sort(queue *q);                    // Sorts loans by date
int priority_sort(queue *q);                 // Sorts the queue by priority
int dequeue_borrow(queue *q, queue *return_q); // Moves loan to return queue
int dequeue_return(queue *return_q , loan **x , bkptr headbk); // Processes book return
bool not_returned(queue loan_q, queue return_q, loan* current_loan); // Checks if a book is not returned
