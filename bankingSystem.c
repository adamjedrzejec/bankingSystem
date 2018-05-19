#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_FIRST_LAST_NAME_LENGTH 30

typedef struct account{
  int accountNumber;
  char firstName[MAX_FIRST_LAST_NAME_LENGTH + 1],
        lastName[MAX_FIRST_LAST_NAME_LENGTH + 1],
        pesel[12];
  float balance;
}account;



void menu(void);
void newAccount(void);
int getNameOrLastname(char *, size_t);
void safeInput(char *, size_t);
void clearBuffer(void);
int accountNumberCreator(void);


int main (int argc, char **argv) {
  menu();
  return 0;
}


void menu(){
  int choice;

  printf("\n\n===BANKING SYSTEM==============================================\n");
  printf("===MENU========================================================\n");
  printf("Choose one of options:\n");
  printf("1.Create an account\n2.Exit\n");
  fflush(stdin);
  if(!scanf("%d", &choice)){
    while ((getchar()) != '\n');
    printf("\nINVALID INPUT\n");
    menu();
  }

  clearBuffer();

  if(choice == 1){
    newAccount();
  }else if(choice == 2){
    exit(1);
  }else if(choice == 3){

  }else{
    printf("\nINVALID INPUT\n");
    menu();
  }
}

void newAccount(){

  FILE *externFile;
  account accStruct;

  printf("\n\n===============================================================\n");
  printf("=NEW ACCOUNT CREATOR===========================================\n\n");

  accStruct.accountNumber = accountNumberCreator() + 1;

  do{
    printf("Input your first name. Maximum 30 chars, letters only:\n");
  }while(!getNameOrLastname(accStruct.firstName, sizeof(accStruct.firstName)));
  do{
    printf("Input your last name. Maximum 30 chars, letters only:\n");
  }while(!getNameOrLastname(accStruct.lastName, sizeof(accStruct.lastName)));

  printf("First name: %s\n", accStruct.firstName);
  printf("Last name: %s\n", accStruct.lastName);
  printf("Account number: %d\n", accStruct.accountNumber);

  externFile = fopen("accounts.dat", "a");
  fwrite (&newAccount, sizeof(struct account), 1, externFile);
  fclose(externFile);

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

  if(onlyLetters){
    if(!isupper(user[0]))
      user[0] -= 32;
    for(int i = 1; i < strlen(user); i++)
      if(!islower(user[i]))
        user[i] += 32;
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
  FILE *fptr;
  fptr = fopen("accounts.dat", "r");
  if(fptr == NULL)
    return cnt_accounts;
  else{
    while(fread(&accounts, sizeof(struct account), 1, fptr)){
      cnt_accounts++;
    }
    fclose (fptr);
    return cnt_accounts;
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
