#include <stdio.h>

#define MAX_CUSTOMERS 80
#define BALANCE_THRESHOLD 1000

// Structure to represent customer data
struct Customer {
    int accountNumber;
    char name[50];
    float balance;
};

// Function to print details of customers with balance less than 1000
void printCustomersWithLowBalance(struct Customer customers[MAX_CUSTOMERS]) {
    printf("Customers with balance less than 1000:\n");
    for (int i = 0; i < MAX_CUSTOMERS; ++i) {
        if (customers[i].balance < BALANCE_THRESHOLD) {
            printf("Name: %s, Account Number: %d\n", customers[i].name, customers[i].accountNumber);
        }
    }
    printf("\n");
}

// Function to handle deposit or withdrawal
void performTransaction(struct Customer *customer, float amount, int code) {
    if (code == 1) {  // Withdrawal
        if (customer->balance - amount < 0) {
            printf("Insufficient balance for withdrawal.\n");
        } else {
            customer->balance -= amount;
            printf("Withdrawal of %.2f successful. New balance: %.2f\n", amount, customer->balance);
        }
    } else if (code == 0) {  // Deposit
        customer->balance += amount;
        printf("Deposit of %.2f successful. New balance: %.2f\n", amount, customer->balance);
    }
}

int main() {
    struct Customer customers[MAX_CUSTOMERS];

    // Read customer data from a file
    FILE *file = fopen("bank.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    for (int i = 0; i < MAX_CUSTOMERS; ++i){
        fscanf(file, "%d %s %f", &customers[i].accountNumber, customers[i].name, &customers[i].balance);
           
        
    }

    fclose(file);

    // Print customers with balance less than 1000
    printCustomersWithLowBalance(customers);

    // Demonstrate a transaction (withdrawal for the first customer)
    int accountToModify = 1001;
    float amountToModify = 200;
    int transactionCode = 1;  // 1 for withdrawal, 0 for deposit

    for (int i = 0; i < MAX_CUSTOMERS; ++i) {
        if (customers[i].accountNumber == accountToModify) {
            performTransaction(&customers[i], amountToModify, transactionCode);
            break;
        }
    }

    return 0;
}
