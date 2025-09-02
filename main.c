#include "library.c"
//-----------------------------------------------------------THE MENU--------------------------------------------------------//
void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    }
//-------------------------------------------------------//
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
//-------------------------------------------------------//
void print_colored(const char* text, const char* color) {
    printf("%s%s\033[0m", color, text);
}
//-------------------------------------------------------//
void display_books(bkptr head) {
    clear_screen();
    if (head == NULL) {
        print_colored("+------------------------------------+\n", "\033[1;31m");
        print_colored("|         No books in database!      |\n", "\033[1;31m");
        print_colored("+------------------------------------+\n", "\033[1;31m");
        return;
    }
    print_colored("\n+---------------------------------------------------------------+-------+\n", "\033[1;34m");
    print_colored("|                         Book Catalog                          |       |\n", "\033[1;34m");
    print_colored("+-------+--------------------------------+----------------------+-------+\n", "\033[1;34m");
    printf("| %-5s | %-30s | %-20s | %-5s|\n", "ID", "Title", "Author", "Copies");
    print_colored("+-------+--------------------------------+----------------------+-------+\n", "\033[1;34m");
    bkptr current = head;
    while (current != NULL) {
        printf("| %-5d | %-30.30s | %-20.20s | %-5d |\n", id_bk(current), title(current), author(current), copies(current));
        current = next_bk(current);
    }
    print_colored("+-------+--------------------------------+----------------------+-------+\n", "\033[1;34m");
}
//-------------------------------------------------------//
void display_borrowers(brptr head) {
    clear_screen();
    if (head == NULL) {
        print_colored("+------------------------------------+\n", "\033[1;31m");
        print_colored("|       No borrowers found!          |\n", "\033[1;31m");
        print_colored("+------------------------------------+\n", "\033[1;31m");
        return;
    }
    print_colored("\n+-------------------------------------------------------+\n", "\033[1;34m");
    print_colored("|                     Borrowers List                    |\n", "\033[1;34m");
    print_colored("+-------+-----------------------------------------------+\n", "\033[1;34m");
    printf("| %-5s | %-45s |\n", "ID", "Name");
    print_colored("+-------+-----------------------------------------------+\n", "\033[1;34m");
    brptr current = head;
    while (current != NULL) {
        printf("| %-5d | %-45s |\n", id_br(current), name(current));
        current = next_br(current);
    }
    print_colored("+-------+-----------------------------------------------+\n", "\033[1;34m");
}
//-------------------------------------------------------//
void display_queue(queue q) {
    clear_screen();
    if (empty_queue(q)) {
        print_colored("+------------------------------------+\n", "\033[1;31m");
        print_colored("|       No active loans found!       |\n", "\033[1;31m");
        print_colored("+------------------------------------+\n", "\033[1;31m");
        return;
    }

    // Sort only by priority
    priority_sort(&q);

    print_colored("\n+-------------------------------------------------------------+\n", "\033[1;34m");
    print_colored("|                         Active Loans                        |\n", "\033[1;34m");
    print_colored("+-------+-------+------------+--------------------------------+\n", "\033[1;34m");
    printf("| %-5s | %-5s | %-10s | %-30s |\n", "Book", "User", "Due Date", "Priority");
    print_colored("+-------+-------+------------+--------------------------------+\n", "\033[1;34m");
    loan *current = q.head;
    while (current != NULL) {
        char prio_color[20];
        int prio = priority(current);
        // Color coding based on priority (0-9)
        if (prio >= 0 && prio <= 9) {
            switch(prio) {
                case 0: strcpy(prio_color, "\033[1;30m"); break; // Black for priority 0
                case 1: strcpy(prio_color, "\033[1;31m"); break; // Red for priority 1
                case 2: strcpy(prio_color, "\033[1;33m"); break; // Yellow for priority 2
                case 3: strcpy(prio_color, "\033[1;32m"); break; // Green for priority 3
                case 4: strcpy(prio_color, "\033[1;36m"); break; // Cyan for priority 4
                case 5: strcpy(prio_color, "\033[1;35m"); break; // Magenta for priority 5
                case 6: strcpy(prio_color, "\033[1;34m"); break; // Blue for priority 6
                case 7: strcpy(prio_color, "\033[1;37m"); break; // White for priority 7
                case 8: strcpy(prio_color, "\033[1;90m"); break; // Gray for priority 8
                case 9: strcpy(prio_color, "\033[1;91m"); break; // Bright Red for priority 9
                default: strcpy(prio_color, "\033[0m");
            }
        } else {
            strcpy(prio_color, "\033[0m"); // Default color for invalid priorities
        }
        printf("| %-5d | %-5d | %-10s | %s%-30d\033[0m |\n", 
               idbk_q(current), 
               idbr_q(current), 
               date_q(current), 
               prio_color, 
               prio);
        current = next_q(current);
    }
    print_colored("+-------+-------+------------+--------------------------------+\n", "\033[1;34m");
}
//-------------------------------------------------------//
void display_overdue(queue q) {
    clear_screen();
    if (empty_queue(q)) {
        print_colored("+------------------------------------+\n", "\033[1;31m");
        print_colored("|       No loans in the system.      |\n", "\033[1;31m");
        print_colored("+------------------------------------+\n", "\033[1;31m");
        return;
    }
    print_colored("\n+---------------------------------------------------+\n", "\033[1;31m");
    print_colored("|                     Overdue Books                 |\n", "\033[1;31m");
    print_colored("+-------+-------+------------+------------+--------+\n", "\033[1;31m");
    printf("| %-5s | %-5s | %-10s | %-10s | %-6s |\n", "Book", "User", "Loan Date", "Due Date", "Days");
    print_colored("+-------+-------+------------+------------+--------+\n", "\033[1;31m");
    loan *current = q.head;
    int found = 0;
    char current_date[11];
    current_time(current_date);  // Get current date
    
    while (current) {
        int overdue_days;
        // Check if the book is overdue using our new function
        if (is_overdue(date_q(current), 15, current_date, &overdue_days)) {  // Using 15 days as loan duration
            // Calculate assumed return date using add_days function
            char assumed_return_date[11];
            strcpy(assumed_return_date, date_q(current));
            add_days(assumed_return_date, 15);
            
            // Convert dates to integers for date_difference
            int current_date_int = 0;
            int assumed_return_date_int = 0;
            
            // Convert current_date from YYYY-MM-DD to YYYYMMDD
            int curr_year, curr_month, curr_day;
            sscanf(current_date, "%d-%d-%d", &curr_year, &curr_month, &curr_day);
            current_date_int = curr_year * 10000 + curr_month * 100 + curr_day;
            
            // Convert assumed_return_date from YYYY-MM-DD to YYYYMMDD
            int year, month, day;
            sscanf(assumed_return_date, "%d-%d-%d", &year, &month, &day);
            assumed_return_date_int = year * 10000 + month * 100 + day;
            
            // Calculate overdue days
            overdue_days = date_difference(assumed_return_date_int, current_date_int);
            
            printf("| %-5d | %-5d | %-10s | %-10s | %-6d |\n", 
                   idbk_q(current), 
                   idbr_q(current), 
                   date_q(current),
                   assumed_return_date,
                   overdue_days);
            found = 1;
        }
        current = next_q(current);
    }
    if (!found) {
        print_colored("|               No overdue books found.                    |\n", "\033[1;32m");
    }
    print_colored("+-------+-------+------------+------------+--------+\n", "\033[1;31m");
}
//-------------------------------------------------------//
void display_not_returned(queue loan_q, queue return_q) {
    clear_screen();
    if (empty_queue(loan_q)) {
        print_colored("+------------------------------------+\n", "\033[1;31m");
        print_colored("|       No loans in the system.      |\n", "\033[1;31m");
        print_colored("+------------------------------------+\n", "\033[1;31m");
        return;
    }
    print_colored("\n+---------------------------------------------------+\n", "\033[1;34m");
    print_colored("|                 Not Returned Books                 |\n", "\033[1;34m");
    print_colored("+-------+-------+------------+------------+--------+\n", "\033[1;34m");
    printf("| %-5s | %-5s | %-10s | %-10s | %-6s |\n", "Book", "User", "Loan Date", "Priority", "Status");
    print_colored("+-------+-------+------------+------------+--------+\n", "\033[1;34m");
    
    loan *current = loan_q.head;
    int found = 0;
    
    while (current != NULL) {
        if (not_returned(loan_q, return_q, current)) {
            char prio_color[20];
            int prio = priority(current);
            // Color coding based on priority (0-9)
            if (prio >= 0 && prio <= 9) {
                switch(prio) {
                    case 0: strcpy(prio_color, "\033[1;30m"); break; // Black
                    case 1: strcpy(prio_color, "\033[1;31m"); break; // Red
                    case 2: strcpy(prio_color, "\033[1;33m"); break; // Yellow
                    case 3: strcpy(prio_color, "\033[1;32m"); break; // Green
                    case 4: strcpy(prio_color, "\033[1;36m"); break; // Cyan
                    case 5: strcpy(prio_color, "\033[1;35m"); break; // Magenta
                    case 6: strcpy(prio_color, "\033[1;34m"); break; // Blue
                    case 7: strcpy(prio_color, "\033[1;37m"); break; // White
                    case 8: strcpy(prio_color, "\033[1;90m"); break; // Gray
                    case 9: strcpy(prio_color, "\033[1;91m"); break; // Bright Red
                    default: strcpy(prio_color, "\033[0m");
                }
            } else {
                strcpy(prio_color, "\033[0m");
            }
            
            printf("| %-5d | %-5d | %-10s | %s%-10d\033[0m | %-6s |\n", 
                   idbk_q(current), 
                   idbr_q(current), 
                   date_q(current),
                   prio_color,
                   prio,
                   "Active");
            found = 1;
        }
        current = next_q(current);
    }
    
    if (!found) {
        print_colored("|               No active loans found.                    |\n", "\033[1;32m");
    }
    print_colored("+-------+-------+------------+------------+--------+\n", "\033[1;34m");
}
//-------------------------------------------------------//
void display_menu(bkptr headb, brptr headbr, queue return_q, queue q) {
    int choice;
    while(1) {
        clear_screen();
        print_colored("\n+---------------------------------------+\n", "\033[1;36m");
        print_colored("|           Display Options             |\n", "\033[1;36m");
        print_colored("+---------------------------------------+\n", "\033[1;36m");
        print_colored("|  1. Display All Books                 |\n", "\033[1;37m");
        print_colored("|  2. Display All Borrowers             |\n", "\033[1;37m");
        print_colored("|  3. Display Active Loans              |\n", "\033[1;37m");
        print_colored("|  4. Display Return History            |\n", "\033[1;37m");
        print_colored("|  5. Display Overdue Books             |\n", "\033[1;37m");
        print_colored("|  6. Display Not Returned Books       |\n", "\033[1;37m");
        print_colored("|  0. Back to Main Menu                 |\n", "\033[1;37m");
        print_colored("+---------------------------------------+\n", "\033[1;36m");
        print_colored("\nEnter your choice: ", "\033[1;33m");
        if(scanf("%d", &choice) != 1) {
            print_colored("Invalid input!\n", "\033[1;31m");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();
        switch(choice) {
            case 1:
                display_books(headb);
                break;
            case 2:
                display_borrowers(headbr);
                break;
            case 3:
                display_queue(q);
                break;
            case 4:
                date_sort(&return_q);
                display_queue(return_q);
                break;
            case 5:
                display_overdue(q);
                break;
            case 6:
                display_not_returned(q, return_q);
                break;
            case 0:
                return;
            default:
                print_colored("Invalid choice!\n", "\033[1;31m");
        }
        printf("\nPress Enter to continue...");
        getchar();
    }
}
//-------------------------------------------------------//
void search_book_menu(bkptr head) {
    int choice, id;
    char string[64];
    clear_screen();
    print_colored("\n+---------------------------------------+\n", "\033[1;36m");
    print_colored("|             Search Book               |\n", "\033[1;36m");
    print_colored("+---------------------------------------+\n", "\033[1;36m");
    print_colored("|  1. Search by ID                      |\n", "\033[1;37m");
    print_colored("|  2. Search by Title                   |\n", "\033[1;37m");
    print_colored("+---------------------------------------+\n", "\033[1;36m");
    print_colored("\nEnter your choice: ", "\033[1;33m");
    scanf("%d", &choice);
    clear_input_buffer();
    switch(choice) {
        case 1:
            print_colored("\n+---------------------------------------+\n", "\033[1;34m");
            print_colored("|             Search by ID              |\n", "\033[1;34m");
            print_colored("+---------------------------------------+\n", "\033[1;34m");
            printf("Enter book ID: ");
            scanf("%d", &id);
            clear_input_buffer();
            bkptr result = search_bk_id(head, id);
            if(result) {
                print_colored("\n+---------------------------------------+\n", "\033[1;32m");
                print_colored("|               Book Found              |\n", "\033[1;32m");
                print_colored("+---------------------------------------+\n", "\033[1;32m");
                printf("ID: %d\nTitle: %s\nAuthor: %s\nCopies: %d\n", id_bk(result), title(result), author(result), copies(result));
            } else {
                print_colored("\n+---------------------------------------+\n", "\033[1;31m");
                print_colored("|             Book Not Found            |\n", "\033[1;31m");
                print_colored("+---------------------------------------+\n", "\033[1;31m");
            }
            break;
        case 2:
            print_colored("\n+---------------------------------------+\n", "\033[1;34m");
            print_colored("|            Search by Title            |\n", "\033[1;34m");
            print_colored("+---------------------------------------+\n", "\033[1;34m");
            printf("Enter book title: ");
            fgets(string, sizeof(string), stdin);
            string[strcspn(string, "\n")] = 0;
            result = search_bk_title(head, string);
            if(result) {
                print_colored("\n+---------------------------------------+\n", "\033[1;32m");
                print_colored("|               Book Found              |\n", "\033[1;32m");
                print_colored("+---------------------------------------+\n", "\033[1;32m");
                printf("ID: %d\nTitle: %s\nAuthor: %s\nCopies: %d\n", id_bk(result), title(result), author(result), copies(result));
            } else {
                print_colored("\n+---------------------------------------+\n", "\033[1;31m");
                print_colored("|             Book Not Found            |\n", "\033[1;31m");
                print_colored("+---------------------------------------+\n", "\033[1;31m");
            }
            break;
        default:
            print_colored("\n+---------------------------------------+\n", "\033[1;31m");
            print_colored("|             Invalid Choice            |\n", "\033[1;31m");
            print_colored("+---------------------------------------+\n", "\033[1;31m");
    }
}
//-------------------------------------------------------//
void search_borrower_menu(brptr head) {
    int choice, id;
    char string[32];
    clear_screen();
    print_colored("\n+---------------------------------------+\n", "\033[1;36m");
    print_colored("|           Search Borrower             |\n", "\033[1;36m");
    print_colored("+---------------------------------------+\n", "\033[1;36m");
    print_colored("|  1. Search by ID                      |\n", "\033[1;37m");
    print_colored("|  2. Search by Name                    |\n", "\033[1;37m");
    print_colored("+---------------------------------------+\n", "\033[1;36m");
    print_colored("\nEnter your choice: ", "\033[1;33m");
    scanf("%d", &choice);
    clear_input_buffer();
    switch(choice) {
        case 1:
            print_colored("\n+---------------------------------------+\n", "\033[1;34m");
            print_colored("|           Search by ID                |\n", "\033[1;34m");
            print_colored("+---------------------------------------+\n", "\033[1;34m");
            printf("Enter borrower ID: ");
            scanf("%d", &id);
            clear_input_buffer();
            brptr result = search_br_id(head, id);
            if(result) {
                print_colored("\n+---------------------------------------+\n", "\033[1;32m");
                print_colored("|           Borrower Found              |\n", "\033[1;32m");
                print_colored("+---------------------------------------+\n", "\033[1;32m");
                printf("ID: %d\nName: %s\n", id_br(result), name(result));
            } else {
                print_colored("\n+---------------------------------------+\n", "\033[1;31m");
                print_colored("|         Borrower Not Found            |\n", "\033[1;31m");
                print_colored("+---------------------------------------+\n", "\033[1;31m");
            }
            break;
        case 2:
            print_colored("\n+---------------------------------------+\n", "\033[1;34m");
            print_colored("|          Search by Name               |\n", "\033[1;34m");
            print_colored("+---------------------------------------+\n", "\033[1;34m");
            printf("Enter borrower name: ");
            fgets(string, sizeof(string), stdin);
            string[strcspn(string, "\n")] = 0;
            result = search_br_name(head, string);
            if(result) {
                print_colored("\n+---------------------------------------+\n", "\033[1;32m");
                print_colored("|           Borrower Found              |\n", "\033[1;32m");
                print_colored("+---------------------------------------+\n", "\033[1;32m");
                printf("ID: %d\nName: %s\n", id_br(result), name(result));
            } else {
                print_colored("\n+---------------------------------------+\n", "\033[1;31m");
                print_colored("|         Borrower Not Found            |\n", "\033[1;31m");
                print_colored("+---------------------------------------+\n", "\033[1;31m");
            }
            break;
        default:
            print_colored("\n+---------------------------------------+\n", "\033[1;31m");
            print_colored("|           Invalid Choice              |\n", "\033[1;31m");
            print_colored("+---------------------------------------+\n", "\033[1;31m");
    }
}
//-------------------------------------------------------//
void print_menu() {
    clear_screen();
    print_colored("\n+---------------------------------------+\n", "\033[1;36m");
    print_colored("|       Library Management System       |\n", "\033[1;36m");
    print_colored("+---------------------------------------+\n", "\033[1;36m");
    print_colored("|  1. File Operations                   |\n", "\033[1;37m");
    print_colored("|  2. Book Management                   |\n", "\033[1;37m");
    print_colored("|  3. Borrower Management               |\n", "\033[1;37m");
    print_colored("|  4. Loan Management                   |\n", "\033[1;37m");
    print_colored("|  5. Display Options                   |\n", "\033[1;37m");
    print_colored("|  6. Generate Statistics               |\n", "\033[1;37m");
    print_colored("|  7. Set MAX_TIMER                     |\n", "\033[1;37m");
    print_colored("|  8. About                             |\n", "\033[1;37m");
    print_colored("|  0. Exit                              |\n", "\033[1;37m");
    print_colored("+---------------------------------------+\n", "\033[1;36m");
    print_colored("\nEnter your choice: ", "\033[1;33m");
}
//-------------------------------------------------------//
void file_menu(bkptr *headb, brptr *headbr, queue *q, queue *return_q) {
    while(1)
    {
    clear_screen();
    int choice;
    char filename[100];
    print_colored("+---------------------------------------------+\n", "\033[1;36m");
    print_colored("|               File Operations               |\n", "\033[1;36m");
    print_colored("+---------------------------------------------+\n", "\033[1;36m");
    print_colored("|  1. Read Books from File                    |\n", "\033[1;37m");
    print_colored("|  2. Read Borrowers from File                |\n", "\033[1;37m");
    print_colored("|  3. Read Borrowing Transactions from File   |\n", "\033[1;37m");
    print_colored("|  4. Read Returning Transactions from File   |\n", "\033[1;37m");
    print_colored("|  0. Back to Main Menu                       |\n", "\033[1;37m");
    print_colored("+---------------------------------------------+\n", "\033[1;36m");
    print_colored("\nEnter your choice: ", "\033[1;33m");
    if(scanf("%d", &choice) != 1) {
        print_colored("\nInvalid input! Please enter a valid number.\n", "\033[1;31m");
        clear_input_buffer();
        return;
    }
    clear_input_buffer();
    if(choice >= 1 && choice <= 4) {
        print_colored("\nEnter filename: ", "\033[1;33m");
        if(fgets(filename, sizeof(filename), stdin)) {
            filename[strcspn(filename, "\n")] = 0;
            switch(choice) {
                case 1:
                    if(add_books_file(headb, filename))
                        print_colored("\nBooks loaded successfully!\n", "\033[1;32m");
                    else
                        print_colored("\nFailed to load books from file.\n", "\033[1;31m");
                    break;
                case 2:
                    if(add_borrowers_file(headbr, filename))
                        print_colored("\nBorrowers loaded successfully!\n", "\033[1;32m");
                    else
                        print_colored("\nFailed to load borrowers from file.\n", "\033[1;31m");
                    break;
                case 3:
                    if(borrow_file(q, filename))
                        print_colored("\nLoan transactions loaded successfully!\n", "\033[1;32m");
                    else
                        print_colored("\nFailed to load loan transactions from file.\n", "\033[1;31m");
                    break;
                case 4:
                    if(return_file(return_q, filename))
                        print_colored("\nLoan transactions loaded successfully!\n", "\033[1;32m");
                    else
                        print_colored("\nFailed to load loan transactions from file.\n", "\033[1;31m");
                    break;
                default: print_colored("\nInvalid choice! Please select a valid option.\n", "\033[1;31m");
                    break;
            }
            printf("\nPress Enter to continue...");
            getchar();
        }
    } else if (choice == 0) {
            return;
    } else {
        print_colored("\nInvalid choice! Please select a valid option.\n", "\033[1;31m");
        printf("\nPress Enter to continue...");
        getchar();
    }
    }
    printf("\nPress Enter to continue...");
    getchar();
}
//-------------------------------------------------------//
void generate_statistics(bkptr headb, brptr headbr, queue q) {
    // Count books and total copies
    int book_count = 0, total_copies = 0;
    bkptr temp_book = headb;
    while(temp_book) {
        book_count++;
        total_copies += copies(temp_book);
        temp_book = next_bk(temp_book);
    }

    // Count borrowers
    int borrower_count = 0;
    brptr temp_borr = headbr;
    while(temp_borr) {
        borrower_count++;
        temp_borr = next_br(temp_borr);
    }

    // Count loans by priority (0-9)
    int loan_count = 0;
    int priority_counts[10] = {0}; // Array to store counts for priorities 0-9
    loan *temp_loan = q.head;
    while(temp_loan != NULL) {
        loan_count++;
        int prio = priority(temp_loan);
        if (prio >= 0 && prio <= 9) {
            priority_counts[prio]++;
        }
        temp_loan = next_q(temp_loan);
    }

    // Generate SVG visualization of statistics
    FILE *graph = fopen("library_statistics.svg", "w");
    if (graph == NULL) {
        print_colored("Error creating SVG statistics file!\n", "\033[1;31m");
        fclose(graph);
        return;
    }

    fprintf(graph, "<svg width='2000' height='1600' xmlns='http://www.w3.org/2000/svg'>\n");

    // Write main title
    fprintf(graph, "<text x='850' y='30' font-family='Arial' font-size='30' text-anchor='middle' fill='black'>Library Management System Statistics</text>\n");

    // Graph 1: Books and Borrowers
    fprintf(graph, "<text x='850' y='80' font-family='Arial' font-size='20' text-anchor='middle' fill='black'>1. Books and Borrowers</text>\n");

    // Calculate bar heights (proportional)
    int max_count = (book_count > borrower_count) ? book_count : borrower_count;
    if (max_count == 0) max_count = 1; // Avoid division by zero

    float book_height = ((float)book_count / max_count) * 275;
    float borrower_height = ((float)borrower_count / max_count) * 275;
    book_height = (book_height == 0) ? 5 : book_height;
    borrower_height = (borrower_height == 0) ? 5 : borrower_height;

    // Draw bars
    fprintf(graph, "<rect x='750' y='%.2f' width='50' height='%.2f' fill='blue' />\n", 400 - book_height, book_height);
    fprintf(graph, "<rect x='850' y='%.2f' width='50' height='%.2f' fill='green' />\n", 400 - borrower_height, borrower_height);

    // Add values
    fprintf(graph, "<text x='760' y='%.2f' font-size='18' fill='black'>%d</text>\n", 400 - book_height - 10, book_count);
    fprintf(graph, "<text x='860' y='%.2f' font-size='18' fill='black'>%d</text>\n", 400 - borrower_height - 10, borrower_count);

    // Labels
    fprintf(graph, "<text x='760' y='420' font-size='18' fill='black'>Books</text>\n");
    fprintf(graph, "<text x='860' y='420' font-size='18' fill='black'>Borrowers</text>\n");

    // Graph 2: Loan Priorities
    fprintf(graph, "<text x='850' y='450' font-family='Arial' font-size='20' text-anchor='middle' fill='black'>2. Loan Priority Distribution</text>\n");

    char *colors[10] = {"black", "red", "yellow", "green", "cyan", "magenta", "blue", "white", "gray", "brightred"};
    char *labels[10] = {"P0", "P1", "P2", "P3", "P4", "P5", "P6", "P7", "P8", "P9"};

    for (int i = 0; i < 10; i++) {
        float height = ((float)priority_counts[i] / (loan_count > 0 ? loan_count : 1)) * 300;
        height = (height == 0) ? 5 : height;
        int x = 450 + i * 80;

        fprintf(graph, "<rect x='%d' y='%.2f' width='50' height='%.2f' fill='%s' />\n", x, 800 - height, height, colors[i]);
        fprintf(graph, "<text x='%d' y='%.2f' font-size='18' fill='black'>%d</text>\n", x + 10, 800 - height - 10, priority_counts[i]);
        fprintf(graph, "<text x='%d' y='820' font-size='18' fill='black'>%s</text>\n", x + 10, labels[i]);
    }

    // Graph 3: Copies vs. Loans
    fprintf(graph, "<text x='850' y='850' font-family='Arial' font-size='20' text-anchor='middle' fill='black'>3. Total Copies vs. Active Loans</text>\n");

    max_count = (total_copies > loan_count) ? total_copies : loan_count;
    if (max_count == 0) max_count = 1; // Avoid division by zero

    float copies_height = ((float)total_copies / max_count) * 300;
    float loans_height = ((float)loan_count / max_count) * 300;
    copies_height = (copies_height == 0) ? 5 : copies_height;
    loans_height = (loans_height == 0) ? 5 : loans_height;

    fprintf(graph, "<rect x='750' y='%.2f' width='50' height='%.2f' fill='orange' />\n", 1200 - copies_height, copies_height);
    fprintf(graph, "<rect x='850' y='%.2f' width='50' height='%.2f' fill='purple' />\n", 1200 - loans_height, loans_height);

    fprintf(graph, "<text x='760' y='%.2f' font-size='18' fill='black'>%d</text>\n", 1200 - copies_height - 10, total_copies);
    fprintf(graph, "<text x='860' y='%.2f' font-size='18' fill='black'>%d</text>\n", 1200 - loans_height - 10, loan_count);

    fprintf(graph, "<text x='760' y='1220' font-size='18' fill='black'>Copies</text>\n");
    fprintf(graph, "<text x='860' y='1220' font-size='18' fill='black'>Loans</text>\n");

    fprintf(graph, "</svg>\n");
    fclose(graph);

    // Console output
    clear_screen();
    print_colored("\n+-----------------------------------------------+ \n", "\033[1;32m");
    print_colored("|            Library Statistics                 | \n", "\033[1;32m");
    print_colored("+-----------------------------------------------+ \n", "\033[1;32m");
    printf("|  Total Books: %-30d  |\n", book_count);
    printf("|  Total Copies: %-29d  |\n", total_copies);
    printf("|  Registered Borrowers: %-22d |\n", borrower_count);
    printf("|  Active Loans: %-29d  |\n", loan_count);
    for (int i = 0; i < 10; i++) {
        printf("|  Priority %d Loans: %-28d |\n", i, priority_counts[i]);
    }
    print_colored("+-----------------------------------------------+ \n", "\033[1;32m");
    print_colored("Visual statistics generated in library_statistics.svg\n", "\033[1;32m");
}
//-------------------------------------------------------//
void book_management_menu(bkptr *head) {
    int choice, n, id;
    char title[64];
    while(1) {
        clear_screen();
        print_colored("\n+---------------------------------------+\n", "\033[1;36m");
        print_colored("|           Book Management             |\n", "\033[1;36m");
        print_colored("+---------------------------------------+\n", "\033[1;36m");
        print_colored("|  1. Add Books                         |\n", "\033[1;37m");
        print_colored("|  2. Remove Book by ID                 |\n", "\033[1;37m");
        print_colored("|  3. Remove Book by Title              |\n", "\033[1;37m");
        print_colored("|  4. Search Book                       |\n", "\033[1;37m");
        print_colored("|  5. Display Books                     |\n", "\033[1;37m");
        print_colored("|  0. Back to Main Menu                 |\n", "\033[1;37m");
        print_colored("+---------------------------------------+\n", "\033[1;36m");
        print_colored("\nEnter your choice: ", "\033[1;33m");
        if(scanf("%d", &choice) != 1) {
            print_colored("\nInvalid input! Please enter a valid number.\n", "\033[1;31m");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();
        switch(choice) {
            case 1:
                print_colored("\n+---------------------------------------+\n", "\033[1;34m");
                print_colored("|              Add Books                |\n", "\033[1;34m");
                print_colored("+---------------------------------------+\n", "\033[1;34m");
                printf("How many books to add? ");
                scanf("%d", &n);
                clear_input_buffer();
                if(add_book(head, n))
                    print_colored("\nBooks added successfully!\n", "\033[1;32m");
                break;
            case 2:
                print_colored("\n+---------------------------------------+\n", "\033[1;34m");
                print_colored("|           Remove Book by ID           |\n", "\033[1;34m");
                print_colored("+---------------------------------------+\n", "\033[1;34m");
                printf("Enter book ID to remove: ");
                scanf("%d", &id);
                clear_input_buffer();
                remove_bk_id(head, id);
                print_colored("\nBook removed if found!\n", "\033[1;32m");
                break;
            case 3:
                print_colored("\n+---------------------------------------+\n", "\033[1;34m");
                print_colored("|         Remove Book by Title          |\n", "\033[1;34m");
                print_colored("+---------------------------------------+\n", "\033[1;34m");
                printf("Enter book title to remove: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = 0;
                remove_bk_title(head, title);
                print_colored("\nBook removed if found!\n", "\033[1;32m");
                break;
            case 4:
                print_colored("\n+---------------------------------------+\n", "\033[1;34m");
                print_colored("|             Search Book               |\n", "\033[1;34m");
                print_colored("+---------------------------------------+\n", "\033[1;34m");
                search_book_menu(*head);
                break;
            case 5:
                print_colored("\n+---------------------------------------+\n", "\033[1;34m");
                print_colored("|            Display Books              |\n", "\033[1;34m");
                print_colored("+---------------------------------------+\n", "\033[1;34m");
                display_books(*head);
                break;
            case 0:
                print_colored("\nReturning to main menu...\n", "\033[1;32m");
                return;
            default:
                print_colored("\nInvalid choice! Please select a valid option.\n", "\033[1;31m");
        }
        printf("\nPress Enter to continue...");
        getchar();
    }
}
//-------------------------------------------------------//
void borrower_management_menu(brptr *head) {
    int choice, n, id;
    char name[32];
    while(1) {
        clear_screen();
        print_colored("\n+---------------------------------------+\n", "\033[1;36m");
        print_colored("|         Borrower Management           |\n", "\033[1;36m");
        print_colored("+---------------------------------------+\n", "\033[1;36m");
        print_colored("|  1. Add Borrowers                     |\n", "\033[1;37m");
        print_colored("|  2. Remove Borrower by ID             |\n", "\033[1;37m");
        print_colored("|  3. Remove Borrower by Name           |\n", "\033[1;37m");
        print_colored("|  4. Search Borrower                   |\n", "\033[1;37m");
        print_colored("|  5. Display Borrowers                 |\n", "\033[1;37m");
        print_colored("|  0. Back to Main Menu                 |\n", "\033[1;37m");
        print_colored("+---------------------------------------+\n", "\033[1;36m");
        print_colored("\nEnter your choice: ", "\033[1;33m");
        if(scanf("%d", &choice) != 1) {
            print_colored("\nInvalid input! Please enter a valid number.\n", "\033[1;31m");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();
        switch(choice) {
            case 1:
                print_colored("\n+---------------------------------------+\n", "\033[1;34m");
                print_colored("|              Add Borrowers            |\n", "\033[1;34m");
                print_colored("+---------------------------------------+\n", "\033[1;34m");
                printf("How many borrowers to add? ");
                scanf("%d", &n);
                clear_input_buffer();
                if(add_borrower(head, n))
                    print_colored("\nBorrowers added successfully!\n", "\033[1;32m");
                break;
            case 2:
                print_colored("\n+---------------------------------------+\n", "\033[1;34m");
                print_colored("|          Remove Borrower by ID        |\n", "\033[1;34m");
                print_colored("+---------------------------------------+\n", "\033[1;34m");
                printf("Enter borrower ID to remove: ");
                scanf("%d", &id);
                clear_input_buffer();
                remove_br_id(head, id);
                print_colored("\nBorrower removed if found!\n", "\033[1;32m");
                break;
            case 3:
                print_colored("\n+---------------------------------------+\n", "\033[1;34m");
                print_colored("|        Remove Borrower by Name        |\n", "\033[1;34m");
                print_colored("+---------------------------------------+\n", "\033[1;34m");
                printf("Enter borrower name to remove: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = 0;
                remove_br_name(head, name);
                print_colored("\nBorrower removed if found!\n", "\033[1;32m");
                break;
            case 4:
                print_colored("\n+---------------------------------------+\n", "\033[1;34m");
                print_colored("|            Search Borrower            |\n", "\033[1;34m");
                print_colored("+---------------------------------------+\n", "\033[1;34m");
                search_borrower_menu(*head);
                break;
            case 5:
                print_colored("\n+---------------------------------------+\n", "\033[1;34m");
                print_colored("|           Display Borrowers           |\n", "\033[1;34m");
                print_colored("+---------------------------------------+\n", "\033[1;34m");
                display_borrowers(*head);
                break;
            case 0:
                print_colored("\nReturning to main menu...\n", "\033[1;32m");
                return;
            default:
                print_colored("\nInvalid choice! Please select a valid option.\n", "\033[1;31m");
        }
        printf("\nPress Enter to continue...");
        getchar();
    }
}
//-------------------------------------------------------//
void loan_management_menu(queue *q, queue *return_q, bkptr headb, brptr headbr) {
    int choice;
    while(1) {
        clear_screen();
        print_colored("\n+---------------------------------------+\n", "\033[1;36m");
        print_colored("|           Loan Management             |\n", "\033[1;36m");
        print_colored("+---------------------------------------+\n", "\033[1;36m");
        print_colored("|  1. Borrow Book                       |\n", "\033[1;37m");
        print_colored("|  2. Return Book                       |\n", "\033[1;37m");
        print_colored("|  3. Display Active Loans              |\n", "\033[1;37m");
        print_colored("|  4. Display Overdue Books             |\n", "\033[1;37m");
        print_colored("|  5. Display Not Returned Books        |\n", "\033[1;37m");
        print_colored("|  0. Back to Main Menu                 |\n", "\033[1;37m");
        print_colored("+---------------------------------------+\n", "\033[1;36m");
        print_colored("\nEnter your choice: ", "\033[1;33m");
        if(scanf("%d", &choice) != 1) {
            print_colored("\nInvalid input! Please enter a valid number.\n", "\033[1;31m");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();
        switch(choice) {
            case 1:
                if(borrow_enqueue(q, headb, headbr))
                    print_colored("\nBook borrowed successfully!\n", "\033[1;32m");
                break;
            case 2: {
                if(dequeue_borrow(q, return_q))
                    print_colored("\nBook returned successfully!\n", "\033[1;32m");
                else print_colored("\nNo one has borrowed a book :(","\033[1;31m");
                break;
            }
            case 3:
                display_queue(*q);
                break;
            case 4:
                display_overdue(*q);
                break;
            case 5:
                display_not_returned(*q, *return_q);
                break;
            case 0:
                print_colored("\nReturning to main menu...\n", "\033[1;32m");
                return;
            default:
                print_colored("\nInvalid choice! Please select a valid option.\n", "\033[1;31m");
        }
        printf("\nPress Enter to continue...");
        getchar();
    }
}
//-------------------------------------------------------//
void display_active_loans(queue loan_q, queue return_q, bkptr headbk, brptr headbr) {
    if (empty_queue(loan_q)) {
        printf("\nNo active loans found.\n");
        return;
    }

    // Sort only by priority
    priority_sort(&loan_q);

    printf("\n%-10s %-30s %-20s %-15s %-10s %-10s %-10s\n",
           "Book ID", "Title", "Borrower", "Loan Date", "Priority", "Active Days", "Overdue Days");
    printf("--------------------------------------------------------------------------------------------------------\n");

    loan* current = loan_q.head;
    char current_date[11];
    current_time(current_date);
    int total_active = 0;
    int total_overdue = 0;

    while (current != NULL) {
        int active_days = 0;
        int overdue_days = 0;
        
        // Check if the loan is active using is_active function
        if (is_active(date_q(current), 14, current_date, &active_days, &overdue_days)) {
            bkptr book = search_bk_id(headbk, idbk_q(current));
            brptr borrower = search_br_id(headbr, idbr_q(current));
            
            if (book != NULL && borrower != NULL) {
                printf("%-10d %-30s %-20s %-15s %-10d %-10d %-10d\n",
                       id_bk(book),
                       title(book),
                       name(borrower),
                       date_q(current),
                       priority(current),
                       active_days,
                       overdue_days);
                
                total_active++;
                if (overdue_days > 0) {
                    total_overdue++;
                }
            }
        }
        current = next_q(current);
    }

    printf("\nSummary:\n");
    printf("Total Active Loans: %d\n", total_active);
    printf("Total Overdue Loans: %d\n", total_overdue);
}
//-------------------------------------------------------//
int main() {
    bkptr headb = NULL;
    brptr headbr = NULL;
    queue q, return_q;
    create_queue(&q);
    create_queue(&return_q);
    int choice;
    while(1) {
        print_menu();
        if(scanf("%d", &choice) != 1)
        {
            print_colored("Invalid input!\n", "\033[1;31m");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();
        switch(choice) {
            case 1: // File Operations
                file_menu(&headb, &headbr, &q , &return_q);
                break;
            case 2: // Book Management
                book_management_menu(&headb);
                break;
            case 3: // Borrower Management
                borrower_management_menu(&headbr);
                break;
            case 4: // Loan Management
                loan_management_menu(&q, &return_q, headb, headbr);
                break;
            case 5: // Display Options
                display_menu(headb, headbr, return_q, q);
                break;
            case 6: // Generate Statistics
                generate_statistics(headb, headbr, q);
                printf("\nPress Enter to continue...");
                getchar();
                break;
            case 7: // Set MAX_TIMER
                clear_screen();
                print_colored("\n+---------------------------------------+\n", "\033[1;36m");
                print_colored("|           Set MAX_TIMER               |\n", "\033[1;36m");
                print_colored("+---------------------------------------+\n", "\033[1;36m");
                printf("Current MAX_TIMER value: %d\n", MAX_TIMER);
                printf("Enter new MAX_TIMER value (must be > 0): ");
                int new_timer;
                if (scanf("%d", &new_timer) == 1 && new_timer > 0) {
                    set_max_timer(new_timer);
                    print_colored("\nMAX_TIMER updated successfully!\n", "\033[1;32m");
                } else {
                    print_colored("\nInvalid value! MAX_TIMER must be greater than 0.\n", "\033[1;31m");
                }
                clear_input_buffer();
                printf("\nPress Enter to continue...");
                getchar();
                break;
            case 8: //About
                clear_screen();
                printf("Made by:");
                print_colored("\nSidAli BEGGAR   ", "\033[31m");
                printf("&");
                print_colored("   Souhail EL FRAIHI", "\033[34m");
                printf("\n   1CP G14              1CP G01");
                getchar();
                break;
            case 0: // Exit
                clear_screen();
                print_colored("Thank you for using the Library Management System!\n", "\033[1;32m");
                return 0;
            default:
                print_colored("Invalid choice!\n", "\033[1;31m");
                break;
        }
    }
    return 0;
}
