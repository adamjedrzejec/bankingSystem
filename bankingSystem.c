#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_FIRST_LAST_NAME_LENGTH 30
#define MAX_ADDRESS_LENGTH 50
#define PESEL_LENGTH 11


typedef struct account{
  int accountNumber;
  char firstName[MAX_FIRST_LAST_NAME_LENGTH + 1],
        lastName[MAX_FIRST_LAST_NAME_LENGTH + 1],
        address[MAX_ADDRESS_LENGTH + 1],
        pesel[PESEL_LENGTH + 1];
  float balance;
}account;



void menu(void);
void newAccount(void);
int getNameOrLastname(char *, size_t);
void safeInput(char *, size_t);
void clearBuffer(void);
int howManyAccountsExist(void);
void listAllAccounts(void);
int getAddress(char *, size_t);
int getPesel(char *, size_t);
void moneyOperation(char *); // possible variables: "withdraw" and "deposit"
void shortListAllAccounts(void);
void clearDatabase(void);
void transferOperation(int, int);
bool isAccount(int);


int main (int argc, char **argv) {
  printf("\e[2J\e[H"); // clear terminal
  menu();
  return 0;
}


void menu(){
  int choice;
  //printf("\e[2J\e[H"); // clear terminal
  printf("\n\n===BANKING SYSTEM==============================================\n");
  printf("===MENU========================================================\n\n");
  printf("Choose one of options:\n");
  printf("1.Create an account\n2.List all accounts\n3.Withdraw\n4.Deposit\n5.Transfer\n6.Clear database\n7.Exit");
  printf("\n===============================================================\n");
  fflush(stdin);
  if(!scanf("%d", &choice)){
    while ((getchar()) != '\n');
    printf("\nINVALID INPUT\n");
    menu();
  }
  clearBuffer();

  printf("\e[2J\e[H"); // clear terminal

  if(choice == 1){
    newAccount();
  }else if(choice == 2){
    if(howManyAccountsExist() > 0)
      listAllAccounts();
      else{
        printf("\e[2J\e[H"); // clear terminal
        printf("There are no accounts here");
        menu();
      }
  }else if(choice == 3){
    if(howManyAccountsExist() > 0)
      moneyOperation("withdraw");
    else{
      printf("\e[2J\e[H"); // clear terminal
      printf("There are no accounts here");
      menu();
    }
  }else if(choice == 4){
    if(howManyAccountsExist() > 0)
      moneyOperation("deposit");
    else{
      printf("\e[2J\e[H"); // clear terminal
      printf("There are no accounts here");
      menu();
    }
  }else if(choice == 5){

    if(howManyAccountsExist() < 2){
      printf("\e[2J\e[H"); // clear terminal
      printf("Operation not possible, too few accounts.");
      menu();
    }

    int transferFrom, transferTo;
    printf("\e[2J\e[H"); // clear terminal
    shortListAllAccounts();
    printf("\n\nTransfer from: ");
    if(!scanf("%d", &transferFrom)){
      while ((getchar()) != '\n');
      printf("\nINVALID INPUT\n");
      menu();
    }
    clearBuffer();

    printf("\e[2J\e[H"); // clear terminal
    shortListAllAccounts();
    printf("\n\nTransfer from: %d\n", transferFrom);
    printf("Transfer to:   ");
    if(!scanf("%d", &transferTo)){
      while ((getchar()) != '\n');
      printf("\nINVALID INPUT\n");
      menu();
    }
    clearBuffer();

    if(isAccount(transferFrom) && isAccount(transferTo)){
      transferOperation(transferFrom, transferTo);
    }else{
      printf("\e[2J\e[H"); // clear terminal
      printf("Operation not possible, such accounts doesn't exist!");
      menu();
    }

  }else if(choice == 6){
    clearDatabase();

  }else if(choice == 7){
    exit(1);
  }else{
    printf("\nINVALID INPUT\n");
    menu();
  }
}

void newAccount(){

  FILE *externFile;
  account accStruct;
  char accept;

  printf("\n\n===============================================================\n");
  printf("=NEW ACCOUNT CREATOR===========================================\n\n");

  accStruct.accountNumber = howManyAccountsExist() + 1;

  do{
    printf("Input your first name. Maximum 30 chars, letters only:\n");
  }while(!getNameOrLastname(accStruct.firstName, sizeof(accStruct.firstName)));
  do{
    printf("Input your last name. Maximum 30 chars, letters only:\n");
  }while(!getNameOrLastname(accStruct.lastName, sizeof(accStruct.lastName)));
  do{
    printf("Input your PESEL. 11 digits, digits only:\n");
  }while(!getPesel(accStruct.pesel, sizeof(accStruct.pesel)));
  do{
    printf("Input your address. Maximum 50 chars:\n");
  }while(!getAddress(accStruct.address, sizeof(accStruct.address)));


  printf("Do you approve these data?\n\n");
  printf("Account number:  %d\n", accStruct.accountNumber);
  printf("First name:      %s\n", accStruct.firstName);
  printf("Last name:       %s\n", accStruct.lastName);
  printf("PESEL:           %s\n", accStruct.pesel);
  printf("Address:         %s\n\n", accStruct.address);

  do{
    printf("Input y to accept, n to refuse\n");
    accept = getchar();
    clearBuffer();
  }while(!(accept == 'y' || accept == 'n'));


  printf("\e[2J\e[H"); // clear terminal


  if(accept == 'y'){
    externFile = fopen("accounts.dat", "a");
    if(externFile == NULL){
      printf("Cannot create/open file.");
      exit(1);
    }
    fwrite (&accStruct, sizeof(struct account), 1, externFile);
    fclose(externFile);
    printf("Account was created succesfully!");
  }else if(accept == 'n'){
    printf("Account was not created.\n");
  }

  menu();
}


int getNameOrLastname(char * reference, size_t size){
  char user[MAX_FIRST_LAST_NAME_LENGTH + 1];
  int onlyLetters = 1;

  safeInput(user, size);

  for(int i = 0; i < strlen(user); i++)
  {
    if(!isalpha(user[i]))
      onlyLetters = 0;
  }

  if(onlyLetters && strlen(user) != 0){
    if(!isupper(user[0]))
      user[0] -= 32;
    for(int i = 1; i < strlen(user); i++){
      if(!islower(user[i]))
        user[i] += 32;

    }
    strcpy(reference, user);
    return 1;
  }
  else{
    printf("Wrong input, try again\n");
    return 0;
  }
}


int getAddress(char * reference, size_t size){
  char user[MAX_ADDRESS_LENGTH + 1];
  int onlyAlphaNumerical = 1;

  safeInput(user, size);

  for(int i = 0; i < strlen(user); i++)
  {
    if(!isalnum(user[i]))
      onlyAlphaNumerical = 0;
  }

  if(onlyAlphaNumerical && strlen(user) != 0){
    if(!isupper(user[0]))
      user[0] -= 32;
    strcpy(reference, user);
    return 1;
  }
  else{
    printf("Wrong input, try again\n");
    return 0;
  }
}


int getPesel(char * reference, size_t size){
  char user[PESEL_LENGTH + 1];
  int onlyDigits = 1;

  safeInput(user, size);

  for(int i = 0; i < strlen(user); i++)
  {
    if(!(user[i] >= '0' && user[i] <= '9'))
      onlyDigits = 0;
  }

  if(onlyDigits && strlen(user) == PESEL_LENGTH){
    strcpy(reference, user);
    return 1;
  }
  else
  {
    printf("Wrong input, try again\n");
    return 0;
  }
}


int howManyAccountsExist(void){
  account accounts;
  int cnt_accounts = 0;
  FILE *externFile;
  externFile = fopen("accounts.dat", "r");
  if(externFile == NULL)
    return cnt_accounts;
  else{
    while(fread(&accounts, sizeof(struct account), 1, externFile)){
      cnt_accounts++;
    }
    fclose (externFile);
    return cnt_accounts;
  }
}


void listAllAccounts(){
  account tempAccount;

  FILE *externFile;
  externFile = fopen("accounts.dat", "r");
  if(externFile == NULL){
    printf("\nThere is no account here!");
    menu();
  }

  printf("===LIST OF ALL ACCOUNTS========================================\n\n");

  while(fread(&tempAccount, sizeof(struct account), 1, externFile)){
    printf("Account number:  %d\n", tempAccount.accountNumber);
    printf("First name:      %s\n", tempAccount.firstName);
    printf("Last name:       %s\n", tempAccount.lastName);
    printf("PESEL:           %s\n", tempAccount.pesel);
    printf("Address:         %s\n", tempAccount.address);
    printf("Balance:         %.2f\n\n\n", tempAccount.balance);
  }
  fclose(externFile);
  printf("===============================================================");
  menu();
}


void shortListAllAccounts(){
  account tempAccount;

  FILE *externFile;
  externFile = fopen("accounts.dat", "r");
  if(externFile == NULL){
    printf("\e[2J\e[H"); // clear terminal
    printf("\nThere are no accounts!");
    menu();
  }

  printf("===LIST OF ALL ACCOUNTS========================================\n\n");

  while(fread(&tempAccount, sizeof(struct account), 1, externFile)){
    printf("Account number:  %d\n", tempAccount.accountNumber);
    printf("Account owner:   %s %s\n", tempAccount.firstName, tempAccount.lastName);
    printf("Balance:         %.2f\n\n", tempAccount.balance);
  }
  fclose(externFile);
  printf("===============================================================");
}


void moneyOperation(char *operation){

  account tempAccount;
  int operationOn;
  FILE *externFile;
  bool done = false;
  float howMuchMoney;
  int whichOperation;

  if(strcmp(operation, "withdraw") == 0)
    whichOperation = -1;
  else if(strcmp(operation, "deposit") == 0)
    whichOperation = 1;
  else{
    printf("\e[2J\e[H"); // clear terminal
    printf("Invalid operation!\n");
    menu();
  }

  shortListAllAccounts();
  printf("\n\nChoose account for a %s: ", operation);

  if(!scanf("%d", &operationOn)){
    while ((getchar()) != '\n');
    printf("\nINVALID INPUT\n");
    menu();
  }
  clearBuffer();


  printf("\nEnter how much money to %s: ", operation);

  if(!scanf("%f", &howMuchMoney)){
    while ((getchar()) != '\n');
    printf("\nINVALID INPUT\n");
    printf("\n\n--> %s was not done!", operation);
    menu();
  }
  clearBuffer();


  externFile = fopen("accounts.dat", "r+");
  if(externFile == NULL)
    printf("\nProblem with opening the file.\n");
  else{
    while(!done && fread(&tempAccount, sizeof(struct account), 1, externFile)){
      if(tempAccount.accountNumber == operationOn){
        tempAccount.balance += whichOperation * howMuchMoney;
        fseek(externFile, -sizeof(struct account), 1);
        fwrite(&tempAccount, sizeof(struct account), 1, externFile);
        done = true;
      }
    }
    fclose (externFile);
    printf("\e[2J\e[H"); // clear terminal

    shortListAllAccounts();

    if(done)
      printf("\n\n--> %s done properly.", operation);
    else
      printf("\n\n--> %s was not done!", operation);

    menu();
  }
}


void clearBuffer(void)
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF){}
}


void safeInput(char * reference, size_t size)
{
  int c;
  if(fgets(reference, size, stdin));
  if(strlen(reference) == size - 1)
  {
    while((c = getchar()) != '\n' && c != EOF);
  }
  reference[strcspn(reference, "\n")] = '\0';
  fflush(stdin);
}


void clearDatabase(void){
  fclose(fopen("accounts.dat", "w"));
  printf("\e[2J\e[H"); // clear terminal
  printf("Database is clear");
  menu();
}


void transferOperation(int transferFrom, int transferTo){
  printf("\nOK\n");
  menu();
}

bool isAccount(int accountNumber){
  account tempAccount;
  FILE *externFile;
  externFile = fopen("accounts.dat", "r");
  if(externFile == NULL){
    return false;
  }
  else{
    while(fread(&tempAccount, sizeof(struct account), 1, externFile)){
      if(tempAccount.accountNumber == accountNumber){
        fclose (externFile);
        return true;
      }
    }
    return false;
  }
}
