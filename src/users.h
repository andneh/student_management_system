#include "user.h"
// #include <openssl/rsa.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int size;
  user *users;
  int cap;
} database;

const char sep[] = "|";
const char endl[] = ";";
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
  user_init(&user_database.users[0], 0, "root", pass_hash("root"), "ro", "ot",
            admin, "111000333", "root@example.com");
}

void add_user(char *login, char *pass_hash, char *first_name, char *last_name,
              user_status status, char *phone, char *email) {
  user_database.cap += 1;
  user_database.users = realloc(
      user_database.users, (user_database.cap * sizeof(*user_database.users)));
  if (user_database.users == NULL) {
    fprintf(stderr, "ADDING USER TO DATABASE ERROR: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  user_init(&user_database.users[user_database.cap - 1],
            user_database.users[user_database.cap - 2].id + 1, login, pass_hash,
            first_name, last_name, status, phone, email);
}

void import_users() {
  FILE *dump = fopen("./data/users.hex", "rb");
  if (dump == NULL) {
    fprintf(stderr, "DUMP FILE ERROR: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  // printf("file opened\n");
  // fread(&user_database, sizeof(user_database), 1, dump);
  char buffer[150];
  while (fgets(buffer, 150, dump)) {
    user_status status = atoi(strtok(buffer, sep));
    char *login = strtok(NULL, sep);
    char *pass_hash = strtok(NULL, sep);
    char *first_name = strtok(NULL, sep);
    char *last_name = strtok(NULL, sep);
    char *phone = strtok(NULL, sep);
    char *email = strtok(NULL, endl);

    add_user(login, pass_hash, first_name, last_name, status, phone, email);
  }
  fclose(dump);
}

void export_users() {
  FILE *dump = fopen("./data/users.hex", "wb+");
  if (dump == NULL) {
    fprintf(stderr, "DUMP FILE ERROR: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  // printf("file opened\n");
  for (int i = 1; i != user_database.cap; i++) {
    fprintf(dump, "%u|%s|%s|%s|%s|%s|%s;", user_database.users[i].status,
            user_database.users[i].login, user_database.users[i].pass_hash,
            user_database.users[i].first_name, user_database.users[i].last_name,
            user_database.users[i].phone, user_database.users[i].email);
    // fwrite(&user_database.users[i], sizeof(user_database.users[i]), 1,
    // dump);
  }

  fclose(dump);

  for (int i = 0; i != user_database.cap; i++) {
    user_destruction(&user_database.users[i]);
  }
  free(user_database.users);
}

void show_users() {
  for (int i = 0; i != user_database.cap; i++) {
    user_show(&user_database.users[i]);
  }
}

int login(char *login, char *password) { return 0; }

int logout() { return 0; }

int update_user() { return 0; }