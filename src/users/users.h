#include <errno.h>
#include <openssl/rsa.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int id;
  char *login;
  char *pass_hash;

  char *first_name;
  char *last_name;

  enum {
    student,
    parent,
    teacher,
    admin,
  } status;

  int phone[9];
  char *email;
} user;

int create_profile() {}

int load() {}

int login(char *login, char *password) {

  FILE *file = fopen("./accounts.csv", "wb");
  if (file == NULL) {
    fprintf(stderr, "ERROR: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  printf("file opened\n");
}

int logout() {}

int registr() {}