#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 1000
#define FILENAME "library.txt"

// Structure to represent book information
struct Library {
    int accessionNumber;
    char title[50];
    char author[50];
    float price;
    int isIssued; // 0: Not issued, 1: Issued
};

// Function to add book information
void addBook(struct Library books[], int *count) {
    if (*count < MAX_BOOKS) {
        printf("Enter book information:\n");

        printf("Accession Number: ");
        scanf("%d", &books[*count].accessionNumber);
        getchar(); // Consume the newline character

        printf("Title: ");
        fgets(books[*count].title, sizeof(books[*count].title), stdin);
        strtok(books[*count].title, "\n"); // Remove the newline character

        printf("Author: ");
        fgets(books[*count].author, sizeof(books[*count].author), stdin);
        strtok(books[*count].author, "\n"); // Remove the newline character

        printf("Price: ");
        scanf("%f", &books[*count].price);
        books[*count].isIssued = 0; // Initially, the book is not issued

        (*count)++;
        printf("Book added successfully!\n");
    } else {
        printf("Library is full. Cannot add more books.\n");
    }
}

// Function to display book information
void displayBooks(struct Library books[], int count) {
    if (count > 0) {
        printf("Book Information:\n");
        for (int i = 0; i < count; i++) {
            printf("Accession Number: %d\n", books[i].accessionNumber);
            printf("Title: %s\n", books[i].title);
            printf("Author: %s\n", books[i].author);
            printf("Price: %.2f\n", books[i].price);
            printf("Status: %s\n", (books[i].isIssued == 1) ? "Issued" : "Not Issued");
            printf("------------------------\n");
        }
    } else {
        printf("No books available in the library.\n");
    }
}

// Function to list all books of a given author
void listBooksByAuthor(struct Library books[], int count) {
    char authorName[50];
    int found = 0;

    printf("Enter the author's name: ");
    getchar(); // Consume the newline character
    fgets(authorName, sizeof(authorName), stdin);
    strtok(authorName, "\n"); // Remove the newline character

    printf("Books by %s:\n", authorName);
    for (int i = 0; i < count; i++) {
        if (strcmp(books[i].author, authorName) == 0) {
            printf("Title: %s\n", books[i].title);
            found = 1;
        }
    }

    if (!found) {
        printf("No books found for the specified author.\n");
    }
}

// Function to list the title of a specified book
void listTitle(struct Library books[], int count) {
    int accessionNumber;
    int found = 0;

    printf("Enter the accession number: ");
    scanf("%d", &accessionNumber);

    for (int i = 0; i < count; i++) {
        if (books[i].accessionNumber == accessionNumber) {
            printf("Title: %s\n", books[i].title);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Book with the specified accession number not found.\n");
    }
}

// Function to list the count of books in the library
void listBookCount(int count) {
    printf("Number of books in the library: %d\n", count);
}

// Function to list the books in the order of accession number
void listBooksByAccession(struct Library books[], int count) {
    if (count > 0) {
        // Sorting books by accession number (bubble sort)
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (books[j].accessionNumber > books[j + 1].accessionNumber) {
                    // Swap
                    struct Library temp = books[j];
                    books[j] = books[j + 1];
                    books[j + 1] = temp;
                }
            }
        }

        // Displaying sorted books
        printf("Books sorted by accession number:\n");
        for (int i = 0; i < count; i++) {
            printf("Accession Number: %d\n", books[i].accessionNumber);
            printf("Title: %s\n", books[i].title);
            printf("Author: %s\n", books[i].author);
            printf("Price: %.2f\n", books[i].price);
            printf("Status: %s\n", (books[i].isIssued == 1) ? "Issued" : "Not Issued");
            printf("------------------------\n");
        }
    } else {
        printf("No books available in the library.\n");
    }
}

// Function to load book information from a file
void loadBooksFromFile(struct Library books[], int *count) {
    FILE *file = fopen(FILENAME, "r");

    if (file == NULL) {
        printf("Error opening file %s. Starting with an empty library.\n", FILENAME);
        return;
    }

    while (*count < MAX_BOOKS) {
        fscanf(file, "%d %s %s %f %d",
                                        &books[*count].accessionNumber,
                                        books[*count].title,
                                        books[*count].author,
                                        &books[*count].price,
                                        &books[*count].isIssued);
        (*count)++;
    }

    fclose(file);
    printf("Library data loaded from %s.\n", FILENAME);
}


void saveBooksToFile(struct Library books[], int count) {
    FILE *file = fopen(FILENAME, "w");

    if (file == NULL) {
        printf("Error opening file %s for writing.\n", FILENAME);
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d %s %s %.2f %d\n",
                books[i].accessionNumber,
                books[i].title,
                books[i].author,
                books[i].price,
                books[i].isIssued);
    }

    fclose(file);
    printf("Library data saved to %s.\n", FILENAME);
}

int main() {
    struct Library books[MAX_BOOKS];
    int bookCount = 0;
    int choice;

    loadBooksFromFile(books, &bookCount);

    do {
        printf("\nLibrary Management System Menu:\n");
        printf("a) Add book information\n");
        printf("b) Display book information\n");
        printf("c) List all books of given author\n");
        printf("d) List the title of specified book\n");
        printf("e) List the count of books in the library\n");
        printf("f) List the books in the order of accession number\n");
        printf("g) Exit\n");
        printf("Enter your choice (a-g): ");
        scanf(" %c", &choice);

        switch (choice) {
            case 'a':
                addBook(books, &bookCount);
                break;
            case 'b':
                displayBooks(books, bookCount);
                break;
            case 'c':
                listBooksByAuthor(books, bookCount);
                break;
            case 'd':
                listTitle(books, bookCount);
                break;
            case 'e':
                listBookCount(bookCount);
                break;
            case 'f':
                listBooksByAccession(books, bookCount);
                break;
            case 'g':
                saveBooksToFile(books, bookCount);
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option (a-g).\n");
        }
    } while (choice != 'g');

    return 0;
}
