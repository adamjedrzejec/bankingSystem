#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct account{
  int accountNumber;
  char firstName[30],
    lastName[30],
    pesel[12];
  float balance;
}account;

int main (int argc, char **argv) {

  account newAccount;
  FILE *externFile;

  newAccount.accountNumber = 42;
  strcpy(newAccount.firstName, "Adam");
  strcpy(newAccount.lastName, "Jędrzejec");
  strcpy(newAccount.pesel, "98122908698");
  newAccount.balance = 12.47;

  printf("Account information:\n");
  printf("Account number: %d\n", newAccount.accountNumber);
  printf("First name:     %s\n", newAccount.firstName);
  printf("Last name:      %s\n", newAccount.lastName);
  printf("Pesel:          %s\n", newAccount.pesel);
  printf("Balance:        %f\n", newAccount.balance);

  externFile = fopen("accounts.dat", "a");
  fwrite (&newAccount, sizeof(struct account), 1, externFile);
  fclose(externFile);
  return 0;
}
