#include "user.h"
#include <errno.h>
// #include <openssl/rsa.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int size;
  user *users;
  int cap;
} database;

database user_database;

char *pass_hash(char *pass) {
  // rsa.h
  return pass;
}

void init_database() {
  user_database.cap = 1;
  user_database.users =
      calloc(1, user_database.cap * sizeof(*user_database.users));
  if (user_database.users == NULL) {
    fprintf(stderr, "INITIALIZING USER DATABASE ERROR: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  init_user(&user_database.users[0], 0, "root", pass_hash("root"), "ro", "ot",
            admin, "111000333", "root@example.com");
}

void add_user(char *login, char *pass, char *first_name, char *last_name,
              user_status status, char *phone, char *email) {
  user_database.cap += 1;
  user_database.users = realloc(
      user_database.users, (user_database.cap * sizeof(*user_database.users)));
  if (user_database.users == NULL) {
    fprintf(stderr, "ADDING USER TO DATABASE ERROR: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  init_user(&user_database.users[user_database.cap - 1],
            user_database.users[user_database.cap - 2].id + 1, login,
            pass_hash(pass), first_name, last_name, status, phone, email);
}

void import_users() {
  FILE *dump = fopen("./accounts.csv", "rb");
  if (dump == NULL) {
    fprintf(stderr, "DUMP FILE ERROR: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  printf("file opened\n");
  fclose(dump);
}

void export_users() {
  FILE *dump = fopen("./accounts.csv", "wb");
  if (dump == NULL) {
    fprintf(stderr, "DUMP FILE ERROR: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  printf("file opened\n");

  fclose(dump);

  for (int i = 0; i != user_database.cap; i++) {
    user_destruction(&user_database.users[i]);
  }
  free(user_database.users);
}

int login(char *login, char *password) { return 0; }

int logout() { return 0; }

int update_user() { return 0; }