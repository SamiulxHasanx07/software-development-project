#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

//Display ATM Main Menu
void displayMenu (bool isFirst) {
    if(!isFirst){
        printf("\n");
    }
    printf("------Welcome to Bangla Bank------\n");
    printf("\n0. Cancel operation");
    printf("\n1. Register new account");
    printf("\n2. Insert Card");
    printf("\n3. Deposit money with bank account");
    printf("\n4. Reset PIN");
    printf("\n5. Block Card");
    printf("\n6. Admin/Author Login");
    printf("\n7. Seed account(Only for development purpouse)");
    printf("\n");
    if(!isFirst){
        printf("\n");
    }
}

//Display Admin Menu
void displayAdminMenu () {
    printf("------Welcome to Admin Dashboard------\n");
    printf("\n0. Cancel operation");
    printf("\n1. See registered accounts");
    printf("\n2. Block User");
    printf("\n3. Total available balance");
    printf("\n");
}

//Display Card Operations Menu
void displayCardOperationsMenu (bool isFirst, char name[256]) {
    if(!isFirst){
        printf("\n");
    }
    printf("\n------ Hi, %s ------\n", name);
    printf("\n0. Cancel transaction");
    printf("\n1. Balance Query");
    printf("\n2. Balance Withdraw");
    printf("\n3. Add money");
    printf("\n4. Transfer Balance");
    printf("\n5. Transaction History");
    printf("\n6. Reset PIN");
    printf("\n7. Disable Account");
    printf("\n");
    if(!isFirst){
        printf("\n");
    }
}

struct Account {
    char name[256], phone[256], address[500];
    int nidNumber, cardNumber, accountNumber, cardPin;
    double balance;
    bool isCardBlocked, isCardDisabled;
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

void insertCard(struct Account *accountsArr, int totalAccounts, bool *isCardInserted, int *insertedCard, char *userName){
    if(totalAccounts == 0){
        printf("There is no account records available, Please Register account first\n");
    }else{
        printf("Enter card number: ");
        int providedCardNumber;
        scanf("%d", &providedCardNumber);

        //authenticate card number and pin check
        for(int i=0; i<totalAccounts; i++){
            if(accountsArr[i].cardNumber == providedCardNumber){
                printf("Enter PIN Number: ");
                int providedPin;
                scanf("%d", &providedPin);
                if(providedPin==accountsArr[i].cardPin){
                    *isCardInserted = true;
                    *insertedCard = accountsArr[i].cardNumber;
                    strcpy(userName, accountsArr[i].name);
                }else{
                    printf("Incorrect PIN number.\n");
                    int insertAttempt=1;
                    do{
                        printf("Enter PIN Number, you have %d attempt remaining: ", 3-insertAttempt);
                        scanf("%d", &providedPin);
                        if(providedPin==accountsArr[i].cardPin){
                            *isCardInserted = true;
                            *insertedCard = accountsArr[i].cardNumber;
                            strcpy(userName, accountsArr[i].name);
                            break;
                        }

                        insertAttempt ++;
                        if(insertAttempt == 3){
                            printf("Your card is blocked!! To unblock visit our bank or call us\n");
                        }
                    }while(insertAttempt < 3);

                }
                break;
            }else{
              printf("Enter valid card number!! Your provided card number is not authorized to our bank!\n");
            }
        }
    }
}

int loggedinId (int id){
    return id;
}

//Balance query
void balanceQuery(struct Account *accountsArr, int totalAccounts, int insertedCard) {
    for(int i = 0; i<totalAccounts; i++){
        if(accountsArr[i].cardNumber == insertedCard ){
            printf("Current Balance is: %.2f Taka\n", accountsArr[i].balance);
            break;
        }
    }
}

//this function is for minimize add/deposit balance function
void addBalance(struct Account *account){
    double getAmount;
    printf("Enter amount to deposit: ");
    scanf("%lf", &getAmount);
    if(getAmount >= 500){
        account->balance += getAmount;
        printf("%.2lf Taka added successfully!!\n", getAmount);
        printf("New balance is %.2lf taka.!!\n", account->balance);

    }else{
      printf("Minimum deposit 500tk, try again!!\n");
    }
}

//Deposit cash
void dipositMoney(struct Account *accountsArr, int totalAccounts,bool isCardInserted, int insertedCard ){
    if(!isCardInserted){
        int getAccount;
        printf("Enter bank account number: ");
        scanf("%d", &getAccount);
        bool isAccountExists = false;
        for(int i = 0; i < totalAccounts; i++){
            if(accountsArr[i].accountNumber == getAccount){
                isAccountExists = true;
                addBalance(&accountsArr[i]);
                break;
            }
        }
        if(!isAccountExists){
          printf("Account not exists!! try again thanks!! \n");
        }
    }

    //deposit with card number
    if(isCardInserted){
        for(int i = 0; i < totalAccounts; i++){
            if(accountsArr[i].cardNumber == insertedCard){
                addBalance(&accountsArr[i]);
                break;
            }
        }
    }
}

//Withdraw balance
void withdrawBalance(struct Account *accountsArr, int totalAccounts, int insertedCard){
    int withdrawAmount;
    printf("Enter withdraw amount: ");
    scanf("%d", &withdrawAmount);

    if(withdrawAmount % 500 != 0){
        do{
            printf("Invalid amount, mount should be 500*NumberOfNote or 1000*NumberOfNote: \n");
            scanf("%d", &withdrawAmount);
        }while(withdrawAmount % 500 != 0);
    }

    for(int i = 0; i<totalAccounts; i++){
        if(accountsArr[i].cardNumber == insertedCard ){
            if(accountsArr[i].balance>1000 && withdrawAmount<=(accountsArr[i].balance-500)){
                double newBalance = accountsArr[i].balance - withdrawAmount;
                accountsArr[i].balance = newBalance;
                printf("\nTransaction successful!\n");
                printf("Your new balance is: %2lf taka\n\n\n", newBalance);
            }else if(accountsArr[i].balance==500){
                printf("Balance is low, you can not withdraw money!!\n");
            }else{
                printf("Insufficient Balance, Current Balance is: %2lf taka\n\n", accountsArr[i].balance);
            }
            break;
        }
    }
}

//Transfer Balance
void transferBalance(){
    printf("Transfer balance\n");
}

//Transaction History
void transactionHistory(){
    printf("Transaction history\n");
}

//Forgot password
void resetPin(){
    printf("Forgot PIN Number\n");
};

//Block card
void blockCard(){
    printf("Block card\n");
};

//Card disable request
void requestDisableATMCard(){
    printf("Request disable atm card\n");
};

//show all saved accounts
void showAccounts(){
    FILE *file = fopen("accounts.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char line[256];
    int accountNumber;
    char name[100];
    char phone[20];
    double balance;

    printf("\n");
    while (fgets(line, sizeof(line), file) != NULL) {
        if (sscanf(line, "Account Number: %d", &accountNumber) == 1) {
            printf("Account Number: %d\n", accountNumber);
        } else if (sscanf(line, "Name: %[^\n]", name) == 1) {
            printf("Name: %s\n", name);
        } else if (sscanf(line, "Phone: %[^\n]", phone) == 1) {
            printf("Phone: %s\n", phone);
        } else if (sscanf(line, "Balance: %lf", &balance) == 1) {
            printf("Balance: %.2lf\n", balance);
        }
    }
    printf("\n");

    fclose(file);
}
//show Available balance of all accounts
void totalAvailableBalance(){
    FILE *file = fopen("accounts.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    double balance, totalBalance = 0.0;
    char line[256];

    printf("\n");
    while (fgets(line, sizeof(line), file) != NULL) {
        if (sscanf(line, "Balance: %lf", &balance) == 1) {
            totalBalance += balance;
        }
    }

    printf("Total Available Balance: %.2lf\n", totalBalance);
    printf("\n");

    fclose(file);
}
//Admin login
void adminLogin(){
    int pass;
    int loginAttempts = 0;
    int adminPass = 2222;
    bool isAdminLogin = false;
    do{
        printf("\nEnter admin password: ");
        scanf("%d", &pass);

        if(pass == adminPass){
            isAdminLogin=true;
            printf("login successfull");
            break;
        }else{
            printf("Enter correct password!!");
            loginAttempts++;
        }
    }while(loginAttempts<3);

    if(isAdminLogin){
        printf("\n");
        displayAdminMenu();
        int selectAdminMenu;
        printf("\nSelect menu: ");
        scanf("%d", &selectAdminMenu);

        switch (selectAdminMenu){
            case 0:
                printf("You are loggedout!");
                exit(0);
                break;
            case 1:
                showAccounts();
                break;
            case 2:
                printf("Block user");
                break;
            case 3:
                totalAvailableBalance();
                break;
            default:
                printf("Menu dosen't exists! Please select correct menu!! \n");
                break;
        }
    }


};

//exit program
void exitProgram(){
    printf("Are you sure want to exit program?(Y/N): ");
    char confirmation[2];
    scanf("%s", confirmation);

    if(strcmp(confirmation, "Y") == 0 || strcmp(confirmation, "y") == 0){
        printf("Program exited!! Thanks for being with us!!\n");
        exit(0);
    } else if(strcmp(confirmation, "N") == 0 || strcmp(confirmation, "n") == 0){
        displayMenu(false);
        return;
    } else {
        printf("Invalid input! Returning to menu.\n");
        return;
    }
}

//store accounts to txt file
void saveAccountToFile(struct Account account) {
    FILE *file = fopen("accounts.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(file, "Account Number: %d\n", account.accountNumber);
    fprintf(file, "Card Number: %d\n", account.cardNumber);
    fprintf(file, "Name: %s\n", account.name);
    fprintf(file, "Phone: %s\n", account.phone);
    fprintf(file, "Address: %s\n", account.address);
    fprintf(file, "NID Number: %d\n", account.nidNumber);
    fprintf(file, "Balance: %.2lf\n", account.balance);
    fprintf(file, "Card PIN: %d\n", account.cardPin);
    fprintf(file, "--------------------------\n");
    fclose(file);
}

int main(){
    displayMenu(true);
    int selectMenu;
    char name[256];
    srand(time(NULL));

    struct Account *accounts = NULL;
    int currentAccount = 0;

    bool isCardInserted = false;
    int insertedCard = 0;
    char userName[256];

    do {
        printf("\nSelect menu: ");
        scanf("%d", &selectMenu);

        switch(selectMenu){
            case 0:
                exitProgram();
                break;
            case 1:
                accounts = realloc(accounts, (currentAccount + 1) * sizeof(struct Account));
                //8 digit account number generate
                accounts[currentAccount].accountNumber = rand() % 90000000 + 10000000;
                //7 digit account number generate
                accounts[currentAccount].cardNumber = rand() % 9000000 + 1000000;

                //old code for backup [manually added data]
                //account1.accountNumber = rand() % 90000000 + 10000000;
                //account1.cardNumber = rand() % 9000000 + 1000000;
                accounts[currentAccount].isCardBlocked = false;
                accounts[currentAccount].isCardDisabled = false;

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
                    printf("\n");

                    //Registerd account display
                    printf("Account registered!!\n");
                    printf("Name: %s\n", accounts[currentAccount].name);
                    printf("Phone: %s\n", accounts[currentAccount].phone);
                    printf("Address: %s\n", accounts[currentAccount].address);
                    printf("NID Number: %d\n", accounts[currentAccount].nidNumber);
                    printf("Card Number: %d\n", accounts[currentAccount].cardNumber);
                    printf("Account Number: %d\n", accounts[currentAccount].accountNumber);
                    printf("Balance: %2lf\n", accounts[currentAccount].balance);

                    //save created account in txt file
                    saveAccountToFile(accounts[currentAccount]);

                    //this line is for update current total account number
                    currentAccount++;


                    break;
                }else{
                    break;
                }
            case 2:
                insertCard(accounts, currentAccount, &isCardInserted, &insertedCard, &userName);
                if(isCardInserted){
                    do{
                        displayCardOperationsMenu(true, userName);
                        int cardOperation;
                        printf("\nSelect transaction menu: ");
                        scanf("%d", &cardOperation);
                        switch (cardOperation){
                            case 0:
                                printf("Collect your card! Thanks for being with us!");
                                exit(0);
                                break;
                            case 1:
                                balanceQuery(accounts, currentAccount, insertedCard);
                                break;
                            case 2:
                                withdrawBalance(accounts, currentAccount, insertedCard);
                                break;
                            case 3:
                                dipositMoney(accounts, currentAccount, isCardInserted, insertedCard);
                                break;
                            case 4:
                                transferBalance();
                                break;
                            case 5:
                                transactionHistory();
                                break;
                            case 6:
                                resetPin();
                                break;
                            case 7:
                                requestDisableATMCard();
                                break;
                            default:
                                printf("Menu dosen't exists! Please select correct menu!! \n");
                                break;
                        }
                    }while(true);
                }else{
                    printf("Card is not inserted!! Something went wrong!!\n");
                    break;
                }
            case 3:
                dipositMoney(accounts, currentAccount, isCardInserted, insertedCard);
                break;
            case 4:
                resetPin();
                break;
            case 5:
                blockCard();
                break;
            case 6:
                adminLogin();
                break;
            case 7:
                //Seed dummy data for development purpose

                accounts = realloc(accounts, (currentAccount + 1) * sizeof(struct Account));
                //8 digit account number generate
                accounts[currentAccount].accountNumber = rand() % 90000000 + 10000000;
                //7 digit account number generate
                accounts[currentAccount].cardNumber = 1234567;
                //rand() % 9000000 + 1000000;
                strcpy(accounts[currentAccount].name, "Samiul");
                strcpy(accounts[currentAccount].phone, "01788058690");
                strcpy(accounts[currentAccount].address, "Rajshahi, Bangladesh");;
                accounts[currentAccount].nidNumber = 330434242;
                accounts[currentAccount].cardPin = 1234;
                accounts[currentAccount].balance = 50000;

                //print seed data

                printf("Account seeded with:\n");
                printf("Name: %s\n", accounts[currentAccount].name);
                printf("Card Number: %d\n", accounts[currentAccount].cardNumber);
                printf("Account Number: %d\n", accounts[currentAccount].accountNumber);
                printf("Account Balance: %.2lf\n", accounts[currentAccount].balance);
                printf("Phone: %s\n", accounts[currentAccount].phone);
                printf("Address: %s\n", accounts[currentAccount].address);
                printf("NID Number: %d\n", accounts[currentAccount].nidNumber);
                printf("Card Pin: %d\n", accounts[currentAccount].cardPin);
                currentAccount ++;
                break;
            default:
                printf("Menu dosen't exists! Please select correct menu!! \n");
                break;
        }
        if(selectMenu != 0) {
            displayMenu(false);
        }
    } while (true);

    //this line for free memory allocation
    free(accounts);
}
