#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

//Display ATM Menu
void displayMenu (bool isFirst) {
    if(!isFirst){
        printf("\n");
    }
    printf("------Welcome to Bangla Bank------\n");
    printf("\n0. Cancel operation");
    printf("\n1. Register new account");
    printf("\n2. Balance query");
    printf("\n3. Deposit Cash");
    printf("\n4. Withdraw Balance");
    printf("\n5. Forgot Password");
    printf("\n6. Block Card");
    printf("\n7. Request Disable ATM Card");
    printf("\n8. Admin/Author Login");
    printf("\n");
    if(!isFirst){
        printf("\n");
    }
}

struct Account {
    char name[256], phone[256], address[500];
    int nidNumber, cardNumber, accountNumber, cardPin;
    double balance;
    bool data;
};

//generate account number
void generateRandomNumber(char *number, size_t length) {
    const char digits[] = "0123456789";
    for (size_t i = 0; i < length; i++) {
        number[i] = digits[rand() % 10];
    }
}

//Register new account
void registerNewAccount(){
}

//Balance query
void balanceQuery(struct Account *acc) {
    printf("Enter PIN: ");
    int pin;
    scanf("%d", &pin);

    if (pin == acc->cardPin) {
        printf("Balance is %lf\n", acc->balance);
    } else {
        printf("Incorrect PIN\n");
    }
}

//Deposit cash
void depositCash(){
    printf("Deposit cash\n");
}
//Withdraw balance
void withdrawBalance(){
    printf("Withdraw balance\n");
}

//Forgot password
void forgotPassword(){
    printf("Forgot password\n");
};

//Block card
void blockCard(){
    printf("Block card\n");
};

//Card disable request
void requestDisableATMCard(){
    printf("Request disable atm card\n");
};

void exitProgram(){
    printf("Are you sure want to exit program?(Y/N): ");
    char confirmation[2];
    scanf("%s", confirmation);

    if(strcmp(confirmation, "Y") == 0 || strcmp(confirmation, "y") == 0){
        printf("Program exited!! Thanks for being with us!!\n");
        exit(0);
    } else if(strcmp(confirmation, "N") == 0 || strcmp(confirmation, "n") == 0){
        return;
    } else {
        printf("Invalid input! Returning to menu.\n");
        return;
    }
}

int main(){
    displayMenu(true);
    int selectMenu;
    char name[256];
    srand(time(NULL));

    struct Account *accounts = NULL;
    int currentAccount = 0;

    do {
        printf("\nSelect menu: ");
        scanf("%d", &selectMenu);

        switch(selectMenu){
            case 0:
                exitProgram();
                break;
            case 1:
                accounts = realloc(accounts, (currentAccount + 1) * sizeof(struct Account));
                accounts[currentAccount].accountNumber = rand() % 90000000 + 10000000;
                accounts[currentAccount].cardNumber = rand() % 9000000 + 1000000;

                //old code for backup [manually added data]
                //account1.accountNumber = rand() % 90000000 + 10000000;
                //account1.cardNumber = rand() % 9000000 + 1000000;

                printf("\nEnter your name: ");
                scanf("%s", accounts[currentAccount].name);

                printf("\nEnter phone number: ");
                scanf("%s", accounts[currentAccount].phone);

                printf("\nEnter address: ");
                scanf("%s", accounts[currentAccount].address);

                printf("\nEnter NID number: ");
                scanf("%d", &accounts[currentAccount].nidNumber);

                double tk;
                int attempts = 0;
                int maxAttempts = 3;

                while (attempts < maxAttempts) {
                    printf("\nEnter account opening minimum deposit 500tk: ");
                    scanf("%lf", &tk);
                    if(tk == 500 || tk >= 500) {
                        accounts[currentAccount].balance = tk;
                        break;
                    } else {
                        attempts++;
                        if (attempts < maxAttempts) {
                            printf("Deposit must be at least 500tk. Please try again.\n");
                        } else {
                            printf("Too many invalid attempts. Exiting the program.\n");
                            break;
                        }
                    }
                }

                if (tk >= 500) {
                    printf("\nEnter card PIN number: ");
                    scanf("%d", &accounts[currentAccount].cardPin);

                    //Registerd account display
                    printf("Account registered!!\n");
                    printf("Name: %s\n", accounts[currentAccount].name);
                    printf("Phone: %s\n", accounts[currentAccount].phone);
                    printf("Address: %s\n", accounts[currentAccount].address);
                    printf("NID Number: %d\n", accounts[currentAccount].nidNumber);
                    printf("Card Number: %d\n", accounts[currentAccount].cardNumber);
                    printf("Account Number: %d\n", accounts[currentAccount].accountNumber);
                    printf("Balance: %lf\n", accounts[currentAccount].balance);

                    //this line is for update current total account number
                    currentAccount++;

                    //this line for free memory allocation
                    free(accounts);
                    break;
                }else{
                    break;
                }
            case 2:
                //update this function for multiple user update here

                //update this function
                //balanceQuery(&account1);
                break;
            case 3:
                depositCash();
                break;
            case 4:
                withdrawBalance();
                break;
            case 5:
                forgotPassword();
                break;
            case 6:
                blockCard();
                break;
            case 7:
                requestDisableATMCard();
                break;
            default:
                printf("Menu dosen't exists! Please select correct menu!! \n");
                break;
        }
        if(selectMenu != 0) {
            displayMenu(false);
        }
    } while (true);
}
