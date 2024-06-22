#include <stdio.h>

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
//Register new account
void registerNewAccount(){
    printf("Register account\n");
}
//Balance query
void balanceQuery(){
    printf("Balance query\n");
}
//Deposit cash
void depositCash(){
    printf("Deposit cash\n");
}
void withdrawBalance(){
    printf("Withdraw balance\n");
}
void forgotPassword(){
    printf("Forgot password\n");};
void blockCard(){printf("Block card\n");};
void requestDisableATMCard(){printf("Request disable atm card\n");};

int main(){
    displayMenu();
    int selectMenu;

    do {
        printf("\nSelect menu: ");
        scanf("%d", &selectMenu);

        switch(selectMenu){
            case 1:
                registerNewAccount();
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
                printf("C.\n");
                break;
        }
    } while (selectMenu != 0);
}
