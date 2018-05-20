#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
int accountNumberCreator(void);
void listAllAccounts(void);
int getAddress(char *, size_t);
int getPesel(char *, size_t);


int main (int argc, char **argv) {
  menu();
  return 0;
}


void menu(){
  int choice;
  //printf("\e[2J\e[H"); // clear terminal
  printf("\n\n===BANKING SYSTEM==============================================\n");
  printf("===MENU========================================================\n\n");
  printf("Choose one of options:\n");
  printf("1.Create an account\n2.List all accounts\n3.Exit");
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
    listAllAccounts();
  }else if(choice == 3){
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

  accStruct.accountNumber = accountNumberCreator() + 1;

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

  if(accept == 'y'){
    externFile = fopen("accounts.dat", "a");
    if(externFile == NULL){
      printf("Cannot create/open file.");
      exit(1);
    }
    fwrite (&accStruct, sizeof(struct account), 1, externFile);
    fclose(externFile);
    printf("Account was created succesfully!\n");
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



int accountNumberCreator(){
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
  struct account tempAccount;

  FILE *externFile;
  externFile = fopen("accounts.dat", "r");
  if(externFile == NULL){
    printf("\nThere is no account here!");
    menu();
  }

  printf("===LIST OF ALL ACCOUNTS===========================================\n\n");

  while(fread(&tempAccount, sizeof(struct account), 1, externFile)){
    printf("Account number:  %d\n", tempAccount.accountNumber);
    printf("First name:      %s\n", tempAccount.firstName);
    printf("Last name:       %s\n", tempAccount.lastName);
    printf("PESEL:           %s\n", tempAccount.pesel);
    printf("Address:         %s\n\n\n", tempAccount.address);
  }
  fclose(externFile);
  printf("==================================================================\n\n");
  menu();
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
