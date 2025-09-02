#include "library.h"
#include "libtime.c"

// Define MAX_TIMER with a default value
int MAX_TIMER = 10;  // Default value, can be changed using set_max_timer()

// Function to set MAX_TIMER value
void set_max_timer(int value) {
    if (value > 0) {
        MAX_TIMER = value;
    }
}

//-------------------------------------------------abs machines of books : -------------------------------------------------//
bool allocate_bk (bkptr *cell)
{
    *cell = malloc(sizeof(struct books)); // Allocates memory for a book structure
    return (*cell != NULL) ? 1 : 0;
}
//----------------------------------------//
void ass_id_bk (bkptr cell , int val)
{
    cell->id = val; // Assigns an ID to a book
}
//----------------------------------------//
void ass_title (bkptr cell , char string[64])
{
    strncpy(cell->title, string, sizeof(cell->title) - 1); // Assigns a title to a book
    cell->title[sizeof(cell->title) - 1] = '\0';
}
//----------------------------------------//
void ass_author (bkptr cell , char string[32])
{
    strncpy(cell->author, string, sizeof(cell->author) - 1); // Assigns an author to a book
    cell->author[sizeof(cell->author) - 1] = '\0';
}
//----------------------------------------//
void ass_copies(bkptr cell , int val)
{
    cell->copies = val; // Assigns the number of copies to a book
}
//----------------------------------------//
void ass_next_bk (bkptr p , bkptr q)
{
    p->next = q; // Links the next book in the list
}
//----------------------------------------//
void ass_prev_bk (bkptr p , bkptr q)
{
    p->prev = q; // Links the previous book in the list
}
//----------------------------------------//
bkptr next_bk (bkptr p)
{
    return p->next; // Returns the next book in the list
}
//----------------------------------------//
bkptr prev_bk(bkptr p)
{
    return p->prev; // Returns the previous book in the list
}
//----------------------------------------//
int id_bk(bkptr p)
{
    return p->id; // Returns the ID of a book
}
//----------------------------------------//
char* title(bkptr p)
{
    return p->title; // Returns the title of a book
}
//----------------------------------------//
char* author (bkptr p)
{
    return p->author; // Returns the author of a book
}
//----------------------------------------//
int copies(bkptr p)
{
    return p->copies; // Returns the number of copies of a book
}
//----------------------------------------//
void free_book (bkptr book)
{
    free(book); // Frees the memory allocated for a book
}
//---------------------------------------------------------------------------------------------------------------------------//



//-------------------------------------------------abs machines of borrowers : ----------------------------------------------//
bool allocate_br (brptr *cell)
{
    *cell = malloc(sizeof(struct borrowers)); // Allocates memory for a borrower structure
    return (*cell != NULL) ? 1 : 0;
}
//----------------------------------------//
void ass_id_br (brptr cell, int val)
{
    cell->id = val; // Assigns an ID to a borrower
}
//----------------------------------------//
void ass_name (brptr cell , char string[32])
{
    strncpy(cell->name, string, sizeof(cell->name) - 1); // Assigns a name to a borrower
    cell->name[sizeof(cell->name) - 1] = '\0';
}
//----------------------------------------//
void ass_next_br (brptr p , brptr q)
{
    p->next = q; // Links the next borrower in the list
}
//----------------------------------------//
void ass_prev_br (brptr p , brptr q)
{
    p->prev = q; // Links the previous borrower in the list
}
//----------------------------------------//
brptr next_br (brptr p)
{
    return p->next; // Returns the next borrower in the list
}
//----------------------------------------//
brptr prev_br (brptr p)
{
    return p->prev; // Returns the previous borrower in the list
}
//----------------------------------------//
int id_br(brptr p)
{
    return p->id; // Returns the ID of a borrower
}
//----------------------------------------//
char* name(brptr p)
{
    return p->name; // Returns the name of a borrower
}
//----------------------------------------//
void free_borrower (brptr borrower)
{
    free(borrower); // Frees the memory allocated for a borrower
}
//---------------------------------------------------------------------------------------------------------------------------//



//------------------------------------------------PROCEDURES OF BOOKS : -----------------------------------------------------//
bkptr get_tail_bk(bkptr head)
{
    bkptr q = head;
    while (next_bk(q) != NULL) // Traverses to the last book in the list
    {
        q = next_bk(q);
    }
    return q; // Returns the last book in the list
}
//-------------------------------------------------------//
int idbk_exist(bkptr head , int id)
{
    if (head == NULL) return 0; // Checks if the list is empty
    bkptr p = head;
    while (p != NULL) // Traverses the list to check if a book ID exists
    {
        if (id == id_bk(p))
        {
            return 1; // Returns 1 if the ID exists
        }
        p = next_bk(p);
    }
    return 0; // Returns 0 if the ID does not exist
}
//-------------------------------------------------------//
int add_book (bkptr *head , int n)
{
    if (n <= 0) return 0; // Checks if the number of books to add is valid
    bkptr p , q;
    if (allocate_bk(&p)) // Allocates memory for a new book
    {
        int id;
        int copies;
        char ch , title[64] , author[32];
        do
        {
            printf("ENTER THE BOOK'S ID : ");
            while(scanf("%d",&id) != 1) // Validates the book ID input
            {
                printf("INVALID INPUT , YOU MUST ENTER AN INTEGER.\n");
                while ((ch = getchar()) != '\n' && ch != EOF);
                printf("ENTER THE BOOK'S ID : ");
            }
            if(idbk_exist(*head,id) == 1) printf("ID CANNOT BE REPEATED.\n");
            if(id < 0) printf("ENTER A POSITIVE VALUE.\n");
        } while (idbk_exist(*head,id) == 1 || id < 0);
        getchar();
        do
        {
            printf("ENTER THE TITLE OF THE BOOK: ");
            fgets(title, sizeof(title), stdin); // Reads the book title
            title[strcspn(title, "\n")] = '\0';
            if (strcmp(title, "") == 0) {printf("TITLE CANNOT BE EMPTY\n");}
        } while (strcmp(title, "") == 0);
        do
        {
            printf("ENTER THE AUTHOR OF THE BOOK: ");
            fgets(author, sizeof(author), stdin); // Reads the book author
            author[strcspn(author, "\n")] = '\0';
            if (strcmp(author, "") == 0) {printf("ENTER A VALID NAME.\n");}
        } while (strcmp(author, "") == 0);
        printf("HOW MANY COPIES THERE ARE : ");
        while(scanf("%d",&copies) != 1) // Validates the number of copies input
        {
            printf("INVALID INPUT , YOU MUST ENTER AN INTEGER.\n");
            while ((ch = getchar()) != '\n' && ch != EOF);
            printf("HOW MANY COPIES THERE ARE : ");
        }
        getchar();
        if(copies < 0) copies = abs(copies); // Ensures the number of copies is non-negative
        ass_title(p,title);
        ass_author(p,author);
        ass_id_bk(p,id);
        ass_copies(p,copies);
        if (*head == NULL) // Adds the book as the head if the list is empty
        {
            *head = p;
            ass_prev_bk(*head,NULL);
            ass_next_bk(*head,NULL);
        }
        else
        {
            q = *head;
            while((q != NULL) && (id_bk(q) < id)) // Finds the correct position to insert the book
            {
                q = next_bk(q);
            }
            if (q == NULL) // Adds the book at the end of the list
            {
                bkptr k = get_tail_bk(*head);
                ass_next_bk(k,p);
                ass_prev_bk(p,k);
                ass_next_bk(p,NULL);
            }
            else
            {
                if (q == *head) // Adds the book at the beginning of the list
                {
                    ass_prev_bk(*head,p);
                    ass_next_bk(p,*head);
                    *head = p;
                }
                else // Adds the book in the middle of the list
                {
                    ass_prev_bk(p,prev_bk(q));
                    ass_next_bk(prev_bk(q),p);
                    ass_next_bk(p,q);
                }
            }
        }
        for (int i = 2 ; i<= n ; i++) // Repeats the process for additional books
        {
            if (allocate_bk(&p))
            {
                do
                {
                    printf("ENTER THE BOOK'S ID : ");
                    while(scanf("%d",&id) != 1)
                    {
                        printf("INVALID INPUT , YOU MUST ENTER AN INTEGER.\n");
                        while ((ch = getchar()) != '\n' && ch != EOF);
                        printf("ENTER THE BOOK'S ID : ");
                    }
                    if(idbk_exist(*head,id) == 1) printf("ID CANNOT BE REPEATED.\n");
                    if(id < 0) printf("ENTER A POSITIVE VALUE.\n");
                } while (idbk_exist(*head,id) == 1 || id < 0);
                getchar();
                if(id < 0) id = abs(id);
                do
                {
                    printf("ENTER THE TITLE OF THE BOOK: ");
                    fgets(title, sizeof(title), stdin);
                    title[strcspn(title, "\n")] = '\0';
                    if (strcmp(title, "") == 0) {printf("TITLE CANNOT BE EMPTY\n");}
                } while (strcmp(title, "") == 0);
                do
                {
                    printf("ENTER THE AUTHOR OF THE BOOK: ");
                    fgets(author, sizeof(author), stdin);
                    author[strcspn(author, "\n")] = '\0';
                    if (strcmp(author, "") == 0) {printf("ENTER A VALID NAME.\n");}
                } while (strcmp(author, "") == 0);
                printf("HOW MANY COPIES THERE ARE : ");
                while(scanf("%d",&copies) != 1)
                {
                    printf("INVALID INPUT , YOU MUST ENTER AN INTEGER.\n");
                    while ((ch = getchar()) != '\n' && ch != EOF);
                    printf("HOW MANY COPIES THERE ARE : ");
                }
                getchar();
                if(copies < 0) copies = abs(copies);
                ass_copies(p,copies);
                ass_title(p, title);
                ass_id_bk(p,id);
                q = *head;
                while((q != NULL) && (id_bk(q) < id))
                {
                    q = next_bk(q);
                }
                if (q == NULL)
                {
                    bkptr k = get_tail_bk(*head);
                    ass_next_bk(k,p);
                    ass_prev_bk(p,k);
                    ass_next_bk(p,NULL);
                }
                else
                {
                    if (q == *head)
                    {
                        ass_prev_bk(*head,p);
                        ass_next_bk(p,*head);
                        *head = p;
                    }
                    else
                    {
                        ass_prev_bk(p,prev_bk(q));
                        ass_next_bk(prev_bk(q),p);
                        ass_next_bk(p,q);
                    }
                }
            }
            else return 0;
        }
        printf("-------------------------------");
        printf("Book has been added succefully!");
        printf("-------------------------------");
        return 1;
    }
    else
    {
        free_book(p); // Frees memory if allocation fails
        return 0;
    }
}
//-------------------------------------------------------//
int add_books_file (bkptr *head , const char filename[] )
{
    FILE *file = fopen(filename,"r");
    if(file == NULL) // Checks if the file can be opened
    {
        printf("CANNOT OPEN AN EMPTY FILE .\n");
        return 0;
    }
    int id , copies;
    char title[64],author[32];
    char command[10];
    char line[255];
    while(fgets(line, sizeof(line), file)) // Reads the file line by line
    {
        if (sscanf(line,"%9s %d \"%63[^\"]\" \"%31[^\"]\" %d\n",command,&id,title,author,&copies) == 5)
        {
            if(strcmp(command,"ADD_BOOK") == 0) // Checks if the command is to add a book
            {
                bkptr p;
                if(!allocate_bk(&p)) // Allocates memory for a new book
                {
                    fclose(file);
                    return 0;
                }
                if(idbk_exist(*head,id)) // Checks if the book ID already exists
                {
                    printf("ERROR ID : %d ALREADY EXISTS IN THE LIST .\n", id);
                }
                else
                {
                    ass_id_bk(p,id);
                    ass_title(p,title);
                    ass_copies(p,copies);
                    ass_author(p,author);
                    ass_next_bk(p,NULL);
                    ass_prev_bk(p,NULL);
                    if (*head == NULL || id_bk(*head) > id) // Adds the book to the head of the list if appropriate
                    {
                        ass_next_bk(p,*head);
                        if (*head != NULL)
                        {
                            ass_prev_bk(*head,p);
                        }
                        *head = p;
                    }
                    else
                    {
                        bkptr q = *head;
                        while (next_bk(q) != NULL && id_bk(next_bk(q)) < id) // Finds the correct position to insert the book
                        {
                            q = next_bk(q);
                        }
                        ass_next_bk(p, next_bk(q));
                        ass_prev_bk(p, q);
                        if (next_bk(q) != NULL)
                        {
                            ass_prev_bk(next_bk(q), p);
                        }
                        ass_next_bk(q, p);
                    }
                }
            }
        }
    }
    fclose(file); // Closes the file after reading
    return 1;
}
//-------------------------------------------------------//
void swap_books (bkptr p , bkptr q) // Swaps the details of two books
{
    char titletemp[64];
    strcpy(titletemp, title(p));
    int idtemp = id_bk(p);
    int tempcopy = copies(p);
    ass_id_bk(p,id_bk(q));
    ass_title(p,title(q));
    ass_copies(p,copies(q));
    ass_id_bk(q,idtemp);
    ass_title(q,titletemp);
    ass_copies(q,tempcopy);
}
//-------------------------------------------------------//
void bubble_sort_bk (bkptr *head) // Sorts the books list by ID using bubble sort
{
    if (*head == NULL) return;
    else
    {
        int swapped = 1 ;
        bkptr p , q;
        while (swapped) // Repeats until no swaps are needed
        {
            swapped = 0;
            p = *head ;
            while(p != NULL && next_bk(p) != NULL ) // Traverses the list to compare adjacent books
            {
                q = next_bk(p);
                if(id_bk(q) < id_bk(p)) // Swaps if the next book's ID is smaller
                {
                    swap_books(p,q);
                    swapped = 1;
                }
                p = next_bk(p);
            }
        }
    }
}
//-------------------------------------------------------//
bkptr search_bk_id(bkptr head , int id) // Searches for a book by its ID
{
    if(head == NULL) return NULL;
    bkptr p = head;
    while(p != NULL && id_bk(p) != id) // Traverses the list to find the book with the given ID
    {
        p = next_bk(p);
    }
    if (p == NULL) return NULL; // Returns NULL if not found
    return p;
}
//-------------------------------------------------------//
bkptr search_bk_title(bkptr head , char string[]) // Searches for a book by its title
{
    if(head == NULL) return NULL;
    bkptr p = head;
    while (p != NULL) // Traverses the list to find the book with the given title
    {
        char* book = title(p);
        if (strcmp(string, book) == 0) // Compares the title with the given string
        {
            return p;
        }
        p = next_bk(p);
    }
    return NULL; // Returns NULL if not found
}
//-------------------------------------------------------//
void remove_bk_id(bkptr *head , int id) // Removes a book by its ID
{
    bkptr p = search_bk_id(*head,id) ;
    if (p == NULL) return; // Does nothing if the book is not found
    if(p == *head) // Removes the head book
    {
        if(next_bk(*head) != NULL)
        {
            *head = next_bk(*head);
            ass_prev_bk(*head,NULL);
        }
        free_book(p);
    }
    else if (p == get_tail_bk(*head)) // Removes the tail book
    {
        bkptr q = prev_bk(p);
        ass_next_bk(q,NULL);
        free_book(p);
    }
    else // Removes a book in the middle of the list
    {
        bkptr q = prev_bk(p) , r = next_bk(p);
        ass_next_bk(q,r);
        ass_prev_bk(r,q);
        free_book(p);
    }
}
//-------------------------------------------------------//
void remove_bk_title(bkptr *head , char string[]) // Removes a book by its title
{
    bkptr p = search_bk_title(*head,string) ;
    if (p == NULL) return; // Does nothing if the book is not found
    if(p == *head) // Removes the head book
    {
        if(next_bk(*head) != NULL)
        {
            *head = next_bk(*head);
            ass_prev_bk(*head,NULL);
        }
        free(p);
    }
    else if (p == get_tail_bk(*head)) // Removes the tail book
    {
        bkptr q = prev_bk(p);
        ass_next_bk(q,NULL);
        free_book(p);
    }
    else // Removes a book in the middle of the list
    {
        bkptr q = prev_bk(p) , r = next_bk(p);
        ass_next_bk(q,r);
        ass_prev_bk(r,q);
        free_book(p);
    }
}
//---------------------------------------------------------------------------------------------------------------------------//



//----------------------------------------------PROCEDURES OF BORROWERS : ---------------------------------------------------//
brptr get_tail_br(brptr head) // Returns the last borrower in the list
{
    brptr q = head;
    while (next_br(q) != NULL) // Traverses to the end of the list
    {
        q = next_br(q);
    }
    return q;
}
//-------------------------------------------------------//
int idbr_exist(brptr head , int id) // Checks if a borrower ID exists in the list
{
    if (head == NULL) return 0;
    brptr p = head;
    while (p != NULL) // Traverses the list to find the borrower with the given ID
    {
        if (id == id_br(p))
        {
            return 1; // Returns 1 if the ID exists
        }
        p = next_br(p);
    }
    return 0; // Returns 0 if the ID does not exist
}
//-------------------------------------------------------//
int add_borrower (brptr *head , int n) // Adds one or more borrowers to the list
{
    if (n <= 0) return 0;
    brptr p , q;
    if (allocate_br(&p)) // Allocates memory for a new borrower
    {
        int id;
        char ch , name[32];
        do
        {
            printf("ENTER THE BORROWER'S ID : ");
            while(scanf("%d",&id) != 1) // Validates the borrower ID input
            {
                printf("INVALID INPUT , YOU MUST ENTER AN INTEGER.\n");
                while ((ch = getchar()) != '\n' && ch != EOF);
            }
            if(idbr_exist(*head,id) == 1) printf("ID CANNOT BE REPEATED.\n");
            if(id < 0) printf("ENTER A POSITIVE VALUE.\n");
        } while (idbr_exist(*head,id) == 1 || id < 0);
        getchar();
        do
        {
            printf("ENTER THE NAME OF THE BORROWER: ");
            fgets(name, sizeof(name), stdin); // Reads the borrower's name
            name[strcspn(name, "\n")] = '\0';
            if (strcmp(name, "") == 0) {printf("NAME CANNOT BE EMPTY\n");}
        } while (strcmp(name, "") == 0);
        ass_name(p,name);
        ass_id_br(p,id);
        if (*head == NULL) // Adds the borrower as the head if the list is empty
        {
            *head = p;
            ass_prev_br(*head,NULL);
            ass_next_br(*head,NULL);
        }
        else
        {
            q = *head;
            while((q != NULL) && (id_br(q) < id)) // Finds the correct position to insert the borrower
            {
                q = next_br(q);
            }
            if (q == NULL) // Adds the borrower at the end of the list
            {
                brptr k = get_tail_br(*head);
                ass_next_br(k,p);
                ass_prev_br(p,k);
                ass_next_br(p,NULL);
            }
            else
            {
                if (q == *head) // Adds the borrower at the beginning of the list
                {
                    ass_prev_br(*head,p);
                    ass_next_br(p,*head);
                    *head = p;
                }
                else // Adds the borrower in the middle of the list
                {
                    ass_prev_br(p,prev_br(q));
                    ass_next_br(prev_br(q),p);
                    ass_next_br(p,q);
                }
            }
        }
        for (int i = 2 ; i<= n ; i++) // Repeats the process for additional borrowers
        {
            if (allocate_br(&p))
            {
                do
                {
                    printf("ENTER THE BORROWER'S ID : ");
                    while(scanf("%d",&id) != 1)
                    {
                        printf("INVALID INPUT , YOU MUST ENTER AN INTEGER.\n");
                        while ((ch = getchar()) != '\n' && ch != EOF);
                    }
                    if(idbr_exist(*head,id) == 1) printf("ID CANNOT BE REPEATED.\n");
                    if(id < 0) printf("ENTER A POSITIVE VALUE.\n");
                } while (idbr_exist(*head,id) == 1 || id < 0);
                getchar();
                do
                {
                    printf("ENTER THE NAME OF THE BORROWER: ");
                    fgets(name, sizeof(name), stdin);
                    name[strcspn(name, "\n")] = '\0';
                    if (strcmp(name, "") == 0) {printf("NAME CANNOT BE EMPTY\n");}
                } while (strcmp(name, "") == 0);
                ass_name(p, name);
                ass_id_br(p,id);
                q = *head;
                while((q != NULL) && (id_br(q) < id))
                {
                    q = next_br(q);
                }
                if (q == NULL)
                {
                    brptr k = get_tail_br(*head);
                    ass_next_br(k,p);
                    ass_prev_br(p,k);
                    ass_next_br(p,NULL);
                }
                else
                {
                    if (q == *head)
                    {
                        ass_prev_br(*head,p);
                        ass_next_br(p,*head);
                        *head = p;
                    }
                    else
                    {
                        ass_prev_br(p,prev_br(q));
                        ass_next_br(prev_br(q),p);
                        ass_next_br(p,q);
                    }
                }
            }
            else return 0;
        }
        return 1;
        printf("-------------------------------");
        printf("Borrower has been added succefully!");
        printf("-------------------------------");
    }
    else
    {
        free_borrower(p); // Frees memory if allocation fails
        return 0;
    }
}
//-------------------------------------------------------//
int add_borrowers_file (brptr *head , const char filename[] ) // Adds borrowers from a file
{
    FILE *file = fopen(filename,"r");
    if(file == NULL)
    {
        printf("CANNOT OPEN AN EMPTY FILE .\n");
        return 0;
    }
    int id;
    char name[32];
    char command[13];
    char line[255];

    while (fgets(line, sizeof(line), file)) // Reads the file line by line
    {
        if (sscanf(line,"%12s %d %30[^\n]\n",command,&id,name) == 3)
        {
            if(strcmp(command,"ADD_BORROWER") == 0) // Checks if the command is to add a borrower
            {
                brptr p;
                if(!allocate_br(&p))
                {
                    fclose(file);
                    return 0;
                }
                if (idbr_exist(*head,id)) // Checks if the borrower ID already exists
                {
                    printf("ERROR ID : %d ALREADY EXISTS IN THE LIST .\n", id);
                }
                else
                {
                    ass_id_br(p,id);
                    ass_name(p,name);
                    ass_next_br(p,NULL);
                    ass_prev_br(p,NULL);
                    if (*head == NULL || id_br(*head) > id) // Adds the borrower to the head of the list if appropriate
                    {
                        ass_next_br(p,*head);
                        if (*head != NULL)
                        {
                            ass_prev_br(*head,p);
                        }
                        *head = p;
                    }
                    else
                    {
                        brptr q = *head;
                        while (next_br(q) != NULL && id_br(next_br(q)) < id) // Finds the correct position to insert the borrower
                        {
                            q = next_br(q);
                        }
                        ass_next_br(p, next_br(q));
                        ass_prev_br(p, q);
                        if (next_br(q) != NULL) ass_prev_br(next_br(q), p);
                        ass_next_br(q, p);
                    }
                }
            }
        }
    }
    fclose(file); // Closes the file after reading
    return 1;
}
//-------------------------------------------------------//
void swap_borrowers (brptr p , brptr q) // Swaps the details of two borrowers
{
    char nametemp[64];
    strcpy(nametemp, name(p));
    int idtemp = id_br(p);
    ass_id_br(p,id_br(q));
    ass_name(p,name(q));
    ass_id_br(q,idtemp);
    ass_name(q,nametemp);
}
//-------------------------------------------------------//
void bubble_sort_br (brptr *head) // Sorts the borrowers list by ID using bubble sort
{
    if (*head == NULL) return;
    else
    {
        int swapped = 1 ;
        brptr p , q;
        while (swapped) // Repeats until no swaps are needed
        {
            swapped = 0;
            p = *head ;
            while(p != NULL && next_br(p) != NULL ) // Traverses the list to compare adjacent borrowers
            {
                q = next_br(p);
                if(id_br(q) < id_br(p)) // Swaps if the next borrower's ID is smaller
                {
                    swap_borrowers(p,q);
                    swapped = 1;
                }
                p = next_br(p);
            }
        }
    }
}
//-------------------------------------------------------//
brptr search_br_id(brptr head , int id) // Searches for a borrower by their ID
{
    if(head == NULL) return NULL;
    brptr p = head;
    while(p != NULL && id_br(p) != id) // Traverses the list to find the borrower with the given ID
    {
        p = next_br(p);
    }
    if (p == NULL) return NULL; // Returns NULL if not found
    return p;
}
//-------------------------------------------------------//
brptr search_br_name(brptr head , char string[]) // Searches for a borrower by their name
{
    if(head == NULL) return NULL;
    brptr p = head;
    while (p != NULL) // Traverses the list to find the borrower with the given name
    {
        char* book = name(p);
        if (strcmp(string, book) == 0) // Compares the name with the given string
        {
            return p;
        }
        p = next_br(p);
    }
    return NULL; // Returns NULL if not found
}
//-------------------------------------------------------//
void remove_br_id(brptr *head , int id) // Removes a borrower by their ID
{
    brptr p = search_br_id(*head,id) ; // Searches for the borrower with the given ID
    if (p == NULL) return; // Does nothing if the borrower is not found
    if(p == *head) // Removes the head borrower
    {
        if(next_br(*head) != NULL)
        {
            *head = next_br(*head); // Updates the head to the next borrower
            ass_prev_br(*head,NULL); // Sets the previous pointer of the new head to NULL
        }
        free(p); // Frees the memory of the removed borrower
    }
    else if (p == get_tail_br(*head)) // Removes the tail borrower
    {
        brptr q = prev_br(p); // Gets the previous borrower
        ass_next_br(q,NULL); // Sets the next pointer of the previous borrower to NULL
        free_borrower(p); // Frees the memory of the removed borrower
    }
    else
    {
        brptr q = prev_br(p) , r = next_br(p); // Gets the previous and next borrowers
        ass_next_br(q,r); // Links the previous borrower to the next borrower
        ass_prev_br(r,q); // Links the next borrower to the previous borrower
        free_borrower(p); // Frees the memory of the removed borrower
    }
}
//-------------------------------------------------------//
void remove_br_name(brptr *head , char string[]) // Removes a borrower by their name
{
    brptr p = search_br_name(*head,string) ; // Searches for the borrower with the given name
    if (p == NULL) return; // Does nothing if the borrower is not found
    if(p == *head) // Removes the head borrower
    {
        if(next_br(*head) != NULL)
        {
            *head = next_br(*head); // Updates the head to the next borrower
            ass_prev_br(*head,NULL); // Sets the previous pointer of the new head to NULL
        }
        free(p); // Frees the memory of the removed borrower
    }
    else if (p == get_tail_br(*head)) // Removes the tail borrower
    {
        brptr q = prev_br(p); // Gets the previous borrower
        ass_next_br(q,NULL); // Sets the next pointer of the previous borrower to NULL
        free_borrower(p); // Frees the memory of the removed borrower
    }
    else
    {
        brptr q = prev_br(p) , r = next_br(p); // Gets the previous and next borrowers
        ass_next_br(q,r); // Links the previous borrower to the next borrower
        ass_prev_br(r,q); // Links the next borrower to the previous borrower
        free_borrower(p); // Frees the memory of the removed borrower
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------//




//-------------------------------------------------abs machines of loans : -------------------------------------------------//
void create_queue(queue *q) {
    q->head = NULL;
    q->tail = NULL;
    q->request_count = 0;  // Initialize request counter
}
//----------------------------------------//
int full_queue (queue q) // Checks if the queue is full (always returns 0 as the queue is dynamic)
{
    return 0;
}
//----------------------------------------//
bool empty_queue (queue q) // Checks if the queue is empty
{
    return ((q.head == NULL) && (q.tail == NULL));
}
//----------------------------------------//
void ass_next_q(loan* p, loan* q) // Assigns the next pointer of a loan
{
    p->next = q;
}
//----------------------------------------//
void ass_idbk_q(loan* p, int idbk) // Assigns the book ID to a loan
{
    p->id_bk = idbk;
}
//----------------------------------------//
void ass_idbr_q(loan* p, int idbr) // Assigns the borrower ID to a loan
{
    p->id_br = idbr;
}
//----------------------------------------//
void ass_date(loan* p,char string[11]) // Assigns the date to a loan
{
    strncpy(p->date, string, sizeof(p->date) - 1);
    p->date[sizeof(p->date) - 1] = '\0';
}
//----------------------------------------//
int idbk_q(loan* p) // Returns the book ID of a loan
{
    return p->id_bk;
}
//----------------------------------------//
int idbr_q(loan* p) // Returns the borrower ID of a loan
{
    return p->id_br;
}
//----------------------------------------//
loan* next_q(loan* p) // Returns the next loan in the queue
{
    return p->next;
}
//----------------------------------------//
char* date_q(loan* p) // Returns the date of a loan
{
    if (p == NULL)
    {
        return NULL;
    }
    return p->date;
}
//----------------------------------------//
int priority(loan* p) // Returns the priority of a loan
{
    if (p == NULL) return 0;
    return p->priority;
}
//----------------------------------------//



//------------------------------------------PROCEDURES OF LOAN TRANSACTIONS : -----------------------------------------------//
void ass_prio(loan* p, int prio) // Sets the priority of a loan
{
    p->priority = prio;
}
//-------------------------------------------------------//
int idbr_exist_q(queue q, int idbr) // Checks if a borrower ID exists in the queue
{
    if (empty_queue(q)) return 0; // Returns 0 if the queue is empty
    loan * L = q.head;
    while(L != NULL) // Traverses the queue to find the borrower ID
    {
        if (idbr_q(L) == idbr) return 1; // Returns 1 if the borrower ID exists
        L = next_q(L);
    }
    return 0; // Returns 0 if the borrower ID does not exist
}
//-------------------------------------------------------//
int idbk_exist_q(queue q, int idbk) // Checks if a book ID exists in the queue
{
    if (empty_queue(q)) return 0; // Returns 0 if the queue is empty
    loan * L = q.head;
    while(L != NULL) // Traverses the queue to find the book ID
    {
        if (idbk_q(L) == idbk) return 1; // Returns 1 if the book ID exists
        L = next_q(L);
    }
    return 0; // Returns 0 if the book ID does not exist
}
//-------------------------------------------------------//
int borrow_enqueue(queue *q, bkptr headbk, brptr headbr) {
    if (full_queue(*q)) return 0; // Returns 0 if the queue is full
    int idbk , idbr;
    char date[11];
    loan* p;
    bkptr r;
    p = malloc(sizeof(loan)); // Allocates memory for a new loan
    if (p == NULL) return 0; // Returns 0 if memory allocation fails
    do
    {
        printf("INSERT THE ID OF THE BOOK : ");
        scanf("%d", &idbk);
        r = search_bk_id(headbk,idbk); // Searches for the book by ID
        if (r != NULL && copies(r) > 0) // Checks if the book exists and has available copies
        {
            ass_copies(r,copies(r)-1); // Decreases the number of available copies
            ass_idbk_q(p, idbk); // Assigns the book ID to the loan
        }
        else
        {
            printf("THIS BOOK DOES NOT EXIST IN THE BOOKS LIST\n");
        }
    } while (r == NULL || copies(r) < 0); // Repeats until a valid book ID is entered

    do
    {
        printf("INSERT THE ID OF THE BORROWER : ");
        scanf("%d", &idbr);
        if (idbr_exist(headbr, idbr)) // Checks if the borrower ID exists
        {
            ass_idbr_q(p, idbr); // Assigns the borrower ID to the loan
        }
        else
        {
            printf("ID DOES NOT EXIST IN THE BORROWERS LIST\n");
        }
    }while (!idbr_exist(headbr, idbr)); // Repeats until a valid borrower ID is entered

    invaliddate: getchar();
    invaliddate1: printf("ENTER THE BORROWING DATE (YYYY-MM-DD): ");
    if (fgets(date, sizeof(date), stdin) == NULL) // Reads the borrowing date
    {
        printf("ERROR READING DATE.\n");
        free(p); // Frees the allocated memory if reading fails
        return 0;
    }
    date[strcspn(date, "\n")] = '\0'; // Removes the newline character
    if (strlen(date) != 10 || date[4] != '-' || date[7] != '-') // Validates the date format
    {
        printf("INVALID DATE FORMAT. USE YYYY-MM-DD\n");
        goto invaliddate1;
    }
    int year, month, day;
    if (sscanf(date, "%d-%d-%d", &year, &month, &day) != 3) // Parses the date
    {
        printf("INVALID DATE FORMAT\n");
        goto invaliddate;
    }
    if (year < 1900 || year > 9999 || month < 1 || month > 12 || day < 1 || day > 31) // Validates the date values
    {
        printf("INVALID DATE VALUES\n");
        goto invaliddate;
    }
    char currenttime[11];
    current_time(currenttime); // Gets the current date
    int date1, date2;
    date1 = (year * 10000) + (month * 100) + day; // Converts the borrowing date to an integer
    sscanf(currenttime, "%d-%d-%d", &year, &month, &day);
    date2 = (year * 10000) + (month * 100) + day; // Converts the current date to an integer
    if (date1 > date2) // Checks if the borrowing date is in the future
    {
        printf("INVALID DATE - CANNOT BE IN THE FUTURE\n");
        goto invaliddate;
    }
    strncpy(p->date, date, sizeof(p->date) - 1); // Assigns the borrowing date to the loan
    p->date[sizeof(p->date) - 1] = '\0';
    printf("HOW MANY DAYS UNTIL RETURNING THE BOOK ?");
    int days;
    if (scanf("%d", &days) != 1 || days < 1) // Reads and validates the number of days until returning
    {
        printf("Invalid number of days\n");
        free(p); // Frees the allocated memory if input is invalid
        return 0;
    }
    add_days(p->date, days); // Adds the number of days to the borrowing date
    if (!empty_queue(*q)) // Adds the loan to the queue
    {
        ass_next_q(q->tail, p);
        q->tail = p;
        ass_next_q(q->tail, NULL);
    }
    else
    {
        q->head = p;
        q->tail = p;
        ass_next_q(q->tail, NULL);
    }

    // Increment request counter
    q->request_count++;

    // Check if we need to process a loan based on MAX_TIMER
    if (q->request_count >= MAX_TIMER) {
        // Find the first loan in the queue
        loan* first_loan = q->head;
        if (first_loan != NULL) {
            // Get book details
            bkptr book = search_bk_id(headbk, idbk_q(first_loan));
            if (book != NULL) {
                printf("\nProcessing loan after %d requests:\n", MAX_TIMER);
                printf("Book ID: %d\n", id_bk(book));
                printf("Book Title: %s\n", title(book));
                printf("Borrower ID: %d\n", idbr_q(first_loan));
                printf("Loan Date: %s\n", date_q(first_loan));
                
                // Process the loan by moving it to the return queue
                queue return_q;
                create_queue(&return_q);
                if (dequeue_borrow(q, &return_q)) {
                    printf("Loan processed successfully!\n");
                } else {
                    printf("Failed to process loan.\n");
                }
            }
        }
        // Reset request counter after processing
        q->request_count = 0;
    }

    return 1; // Returns 1 if the loan is successfully added
}
//-------------------------------------------------------//
int borrow_file(queue *q , const char filename[]) // Reads loan data from a file and adds it to the queue
{
    if (full_queue(*q)) return 0; // Checks if the queue is full
    FILE *file = fopen(filename,"r");
    if(file == NULL) // Checks if the file can be opened
    {
        printf("CANNOT OPEN THE FILE .");
        return 0;
    }
    int idbk , idbr, priority;
    char date[11] , command[12];
    char line[255];
    while (fgets(line,sizeof(line),file)) // Reads the file line by line
    {
        if(sscanf(line,"%11s %d %d %10s %d\n",command,&idbk,&idbr,date,&priority) == 5) // Parses the line for loan data
        {
            loan* p;
            p = malloc(sizeof(loan)); // Allocates memory for a new loan
            if (p == NULL)
            {
                fclose(file);
                return 0;
            }
            if(strcmp(command,"BORROW_BOOK") == 0) // Checks if the command is to borrow a book
            {
                ass_idbk_q(p,idbk); // Assigns the book ID to the loan
                ass_idbr_q(p,idbr); // Assigns the borrower ID to the loan
                ass_date(p,date); // Assigns the date to the loan
                ass_prio(p, priority); // Assigns the priority from file
                if (empty_queue(*q)) // Adds the loan to the queue if it is empty
                {
                    q->head = p;
                    q->tail = p;
                }
                else // Adds the loan to the end of the queue
                {
                    ass_next_q(q->tail,p);
                    q->tail = p;
                }
                ass_next_q(q->tail,NULL); // Sets the next pointer of the tail to NULL
            }
        }
    }
    fclose(file); // Closes the file
    return 1; // Returns success
}
//-------------------------------------------------------//
int return_file(queue *q , const char filename[]) // Reads return data from a file and adds it to the queue
{
    if (full_queue(*q)) return 0; // Checks if the queue is full
    FILE *file = fopen(filename,"r");
    if(file == NULL) // Checks if the file can be opened
    {
        printf("CANNOT OPEN THE FILE .");
        return 0;
    }
    int idbk , idbr;
    char date[11] , command[12];
    char line[255];
    while (fgets(line,sizeof(line),file)) // Reads the file line by line
    {
        if(sscanf(line,"%11s %d %d %10s\n",command,&idbk,&idbr,date) == 4) // Parses the line for return data
        {
            loan* p;
            p = malloc(sizeof(loan)); // Allocates memory for a new loan
            if (p == NULL)
            {
                fclose(file);
                return 0;
            }
            if(strcmp(command,"RETURN_BOOK") == 0) // Checks if the command is to return a book
            {
                ass_idbk_q(p,idbk); // Assigns the book ID to the loan
                ass_idbr_q(p,idbr); // Assigns the borrower ID to the loan
                ass_date(p,date); // Assigns the date to the loan
                if (empty_queue(*q)) // Adds the loan to the queue if it is empty
                {
                    q->head = p;
                    q->tail = p;
                }
                else // Adds the loan to the end of the queue
                {
                    ass_next_q(q->tail,p);
                    q->tail = p;
                }
                ass_next_q(q->tail,NULL); // Sets the next pointer of the tail to NULL
            }
        }
    }
    fclose(file); // Closes the file
    return 1; // Returns success
}
//-------------------------------------------------------//
int date_sort(queue *q) // Sorts the loans in the queue by date
{
    if(empty_queue(*q)) return 0; // Returns 0 if the queue is empty
    if (next_q(q->head) == NULL) return 1; // Returns 1 if there is only one loan
    int swapped;
    loan *prevp = NULL;
    loan *p;
    do
    {
        swapped = 0; // Resets the swapped flag
        p = q->head;
        prevp = NULL;
        while(p != NULL && next_q(p) != NULL) // Traverses the queue to compare adjacent loans
        {
            loan *next = next_q(p);
            int date1, date2, year, month, day;
            sscanf(p->date, "%d-%d-%d", &year, &month, &day); // Parses the date of the current loan
            date1 = (year * 10000) + (month * 100) + day;
            sscanf(next->date, "%d-%d-%d", &year, &month, &day); // Parses the date of the next loan
            date2 = (year * 10000) + (month * 100) + day;
            if (date2 < date1) // Swaps the loans if the next loan's date is earlier
            {
                loan *next_next = next_q(next);
                if (p == q->head) {
                    q->head = next; // Updates the head if the first loan is swapped
                } else {
                    ass_next_q(prevp, next); // Updates the previous loan's next pointer
                }
                ass_next_q(p, next_q(next)); // Updates the current loan's next pointer
                ass_next_q(next, p); // Updates the next loan's next pointer
                if (next_next == NULL)
                {
                    q->tail = p; // Updates the tail if the last loan is swapped
                }
                swapped = 1; // Sets the swapped flag
                prevp = next; // Updates the previous pointer
            }
            else
            {
                prevp = p; // Moves to the next loan
                p = next;
            }
        }
    } while(swapped); // Repeats until no swaps are needed
    return 1; // Returns success
}
//-------------------------------------------------------//
int dequeue_borrow(queue *q, queue *return_q) // Moves a loan from the borrow queue to the return queue
{
    if(empty_queue(*q)) return 0; // Returns 0 if the borrow queue is empty
    loan * x = q->head;
    if (next_q(q->head) != NULL)
    {
        q->head = next_q(q->head); // Updates the head of the borrow queue
    }
    else
    {
        q->head = NULL; // Empties the borrow queue
        q->tail = NULL;
    }
    int date,year,month,day;
    sscanf(x->date,"%d-%d-%d", &year, &month, &day); // Parses the date of the loan
    date = (year * 10000) + (month * 100) + day;
    if (!empty_queue(*return_q)) // Inserts the loan into the return queue in sorted order
    {
        loan * r = return_q->head;
        loan * prev = NULL;
        while (r != NULL) // Traverses the return queue to find the correct position
        {
            int date_r;
            sscanf(r->date,"%d-%d-%d", &year, &month, &day); // Parses the date of the current return loan
            date_r = (year * 10000) + (month * 100) + day;
            if (date > date_r) break; // Stops if the current return loan's date is earlier
            prev = r;
            r = next_q(r);
        }
        if (prev == NULL) // Inserts the loan at the head of the return queue
        {
            ass_next_q(x,return_q->head);
            return_q->head = x;
        }
        else // Inserts the loan in the middle or at the end of the return queue
        {
            ass_next_q(prev,x);
            ass_next_q(x,r);
            if (r == NULL)
            {
                return_q->tail = x; // Updates the tail if the loan is added at the end
            }
        }
    }
    else // Adds the loan as the first element in the return queue
    {
        create_queue(return_q);
        return_q->head = x;
        return_q->tail = x;
        ass_next_q(x,NULL);
    }
    return 1; // Returns success
}
//-------------------------------------------------------//
int dequeue_return(queue *return_q , loan **x , bkptr headbk) // Processes a returned loan and updates the book's copies
{
    if(empty_queue(*return_q)) return 0; // Returns 0 if the return queue is empty
    *x = return_q->head;
    bkptr r = search_bk_id(headbk,(**x).id_bk); // Finds the book in the list
    ass_copies(r,copies(r)+1); // Increments the number of available copies
    loan * p = return_q->head;
    if (next_q(return_q->head) != NULL)
    {
        return_q->head = next_q(return_q->head); // Updates the head of the return queue
    }
    else
    {
        return_q->tail = NULL; // Empties the return queue
    }
    free(p); // Frees the memory of the processed loan
    return 1; // Returns success
}
//---------------------------------------------------------------------------------------------------------------------------//
bool is_active(char loan_date[11], int loan_duration, char current_date[11], int *active_days, int *overdue_days) {
    // Parse dates into integers for comparison
    int loan_year, loan_month, loan_day;
    int current_year, current_month, current_day;
    
    // Parse loan date
    if (sscanf(loan_date, "%d-%d-%d", &loan_year, &loan_month, &loan_day) != 3) {
        return false;
    }
    
    // Parse current date
    if (sscanf(current_date, "%d-%d-%d", &current_year, &current_month, &current_day) != 3) {
        return false;
    }
    
    // Convert dates to integers for easier comparison (YYYYMMDD format)
    int loan_date_int = (loan_year * 10000) + (loan_month * 100) + loan_day;
    int current_date_int = (current_year * 10000) + (current_month * 100) + current_day;
    
    // Calculate assumed return date by adding loan_duration to loan_date
    char assumed_return_date[11];
    strcpy(assumed_return_date, loan_date);
    add_days(assumed_return_date, loan_duration);
    
    // Parse assumed return date
    int return_year, return_month, return_day;
    if (sscanf(assumed_return_date, "%d-%d-%d", &return_year, &return_month, &return_day) != 3) {
        return false;
    }
    int assumed_return_date_int = (return_year * 10000) + (return_month * 100) + return_day;
    
    // Case 1: Book is overdue (current_date > assumed_return_date)
    if (current_date_int > assumed_return_date_int && loan_date_int < assumed_return_date_int) {
        *overdue_days = date_difference(current_date_int, assumed_return_date_int);
        *active_days = date_difference(assumed_return_date_int, loan_date_int);
        return true;
    }
    
    // Case 2: Book is still within return period (current_date < assumed_return_date)
    if (current_date_int < assumed_return_date_int && loan_date_int < current_date_int) {
        *active_days = date_difference(assumed_return_date_int, current_date_int);
        *overdue_days = 0;
        return true;
    }
    
    // Case 3: Book was borrowed after current date (invalid case)
    if (loan_date_int > current_date_int) {
        return false;
    }
    
    // All other cases (book already returned or invalid dates)
    return false;
}
//-------------------------------------------------------//
bool is_overdue(char loan_date[11], int loan_duration, char current_date[11], int *overdue_days) {
    // Parse dates into integers for comparison
    int loan_year, loan_month, loan_day;
    int current_year, current_month, current_day;
    
    // Parse loan date
    if (sscanf(loan_date, "%d-%d-%d", &loan_year, &loan_month, &loan_day) != 3) {
        return false;
    }
    
    // Parse current date
    if (sscanf(current_date, "%d-%d-%d", &current_year, &current_month, &current_day) != 3) {
        return false;
    }
    
    // Convert dates to integers for easier comparison (YYYYMMDD format)
    int loan_date_int = (loan_year * 10000) + (loan_month * 100) + loan_day;
    int current_date_int = (current_year * 10000) + (current_month * 100) + current_day;
    
    // Calculate assumed return date by adding loan_duration to loan_date
    char assumed_return_date[11];
    strcpy(assumed_return_date, loan_date);
    add_days(assumed_return_date, loan_duration);
    
    // Parse assumed return date
    int return_year, return_month, return_day;
    if (sscanf(assumed_return_date, "%d-%d-%d", &return_year, &return_month, &return_day) != 3) {
        return false;
    }
    int assumed_return_date_int = (return_year * 10000) + (return_month * 100) + return_day;
    
    // Case 1: Book has been returned late (current_date > assumed_return_date)
    if (current_date_int > assumed_return_date_int && loan_date_int < current_date_int) {
        *overdue_days = date_difference(current_date_int, assumed_return_date_int);
        return true;
    }
    
    // Case 2: Book is still out and overdue (current_date > assumed_return_date)
    if (current_date_int > assumed_return_date_int && loan_date_int < assumed_return_date_int) {
        *overdue_days = date_difference(current_date_int, assumed_return_date_int);
        return true;
    }
    
    // Case 3: Book was borrowed after current date (invalid case)
    if (loan_date_int > current_date_int) {
        return false;
    }
    
    // All other cases (book returned early or still within return period)
    return false;
}

bool not_returned(queue loan_q, queue return_q, loan* current_loan) {
    if (current_loan == NULL) {
        return false;
    }

    // Get the book and borrower IDs from the current loan
    int book_id = idbk_q(current_loan);
    int borrower_id = idbr_q(current_loan);
    
    // Check if the book exists in the return queue
    loan* current_return = return_q.head;
    while (current_return != NULL) {
        if (idbk_q(current_return) == book_id && idbr_q(current_return) == borrower_id) {
            // Book is found in return queue, so it has been returned
            return false;
        }
        current_return = next_q(current_return);
    }
    
    // Book is not found in return queue, so it hasn't been returned
    return true;
}

int priority_sort(queue *q) {
    if(empty_queue(*q)) return 0;
    if (next_q(q->head) == NULL) return 1;
    
    int swapped;
    do {
        swapped = 0;
        loan *current = q->head;
        loan *prev = NULL;
        
        while (current != NULL && next_q(current) != NULL) {
            loan *next = next_q(current);
            
            if (priority(current) < priority(next)) {
                // Swap the nodes
                if (prev == NULL) {
                    // If we're at the head
                    q->head = next;
                } else {
                    ass_next_q(prev, next);
                }
                
                ass_next_q(current, next_q(next));
                ass_next_q(next, current);
                
                // Update tail if necessary
                if (next_q(current) == NULL) {
                    q->tail = current;
                }
                
                swapped = 1;
                prev = next;
            } else {
                prev = current;
                current = next;
            }
        }
    } while (swapped);
    
    return 1;
}