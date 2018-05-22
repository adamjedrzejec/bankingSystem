#ifndef OPERATIONSONDATABASE_H
#define OPERATIONSONDATABASE_H


#define MAX_FIRST_LAST_NAME_LENGTH 30
#define MAX_ADDRESS_LENGTH 50
#define PESEL_LENGTH 11
#define MAX_VALUE_INPUT 13
#define MAX_SEARCH_FOR_INPUT 30


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
float getFloat(char *); // char * is a message
void searchFor(void);

#endif
