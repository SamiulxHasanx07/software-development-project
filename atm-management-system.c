#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Display ATM Menu
void displayMenu () {
    printf("------Welcome to Bangla Bank------");
    printf("\n0. Cancel operation");
    printf("\n1. Register new account");
    printf("\n2. Balance query");
    printf("\n3. Deposit Cash");
    printf("\n4. Withdraw Balance");
    printf("\n5. Forgot Password");
    printf("\n6. Block Card");
    printf("\n7. Request Disable ATM Card");
}

struct Account {
    char name[256], phone[256], address[500];
    int nidNumber, cardNumber, accountNumber;
    double balance;
};

//generate account number
void generateRandomNumber(char *number, size_t length) {
    const char digits[] = "0123456789";
    for (size_t i = 0; i < length; i++) {
        number[i] = digits[rand() % 10];
    }
}

//Register new account
void registerNewAccount(struct Account *account){
    account->accountNumber = rand() % 90000000 + 10000000;
    account->cardNumber = rand() % 9000000 + 1000000;
    printf("\nEnter your name: ");
    scanf("%s", account->name);
    printf("\nEnter phone number: ");
    scanf("%s",account->phone);
    printf("\nEnter NID number: ");
    scanf("%d",account->nidNumber);
}

//Balance query
void balanceQuery(){
    printf("Balance query\n");
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

int main(){
    displayMenu();
    int selectMenu;
    char name[256];

    struct Account account1, account2;
    do {
        printf("\nSelect menu: ");
        scanf("%d", &selectMenu);

        switch(selectMenu){
            case 1:
                registerNewAccount(&account1);
                printf("account number %d", account1.accountNumber);
                printf("Card number %d", account1.cardNumber);
                break;
            case 2:
                balanceQuery();
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
                printf("Operation canceled! Collect your card! \n");
                break;
        }
    } while (selectMenu != 0);
}
