#include "user.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEP "|"

typedef struct {
  int size;
  user *users;
  int cap;
} database;

database user_database = {0, &root, 1};

// void init_database() {
//   user_database.cap = 1;
//   user_database.users =
//       calloc(1, user_database.cap * sizeof(*user_database.users));
//   if (user_database.users == NULL) {
//     fprintf(stderr, "INITIALIZING USER DATABASE ERROR: %s\n",
//     strerror(errno)); exit(EXIT_FAILURE);
//   }
//   user_init(&user_database.users[0], 0, "root", pass_hash("root"), "ro",
//   "ot",
//             admin, "111000333", "root@example.com");
// }

void add_user(user_status status, char *login, char *pass_hash,
              char *first_name, char *last_name, char *phone, char *email) {
  user_database.cap += 1;
  user_database.users = realloc(
      user_database.users, (user_database.cap * sizeof(*user_database.users)));
  if (user_database.users == NULL) {
    fprintf(stderr, "ADDING USER TO DATABASE ERROR: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  user_init(&user_database.users[user_database.cap - 1],
            (user_database.users[user_database.cap - 2].id + 1), status, login,
            pass_hash, first_name, last_name, phone, email);
}

void show_users() {
  for (int i = 0; i != user_database.cap; i++) {
    user_show(&user_database.users[i]);
  }
}

void import_users() {
  FILE *dump = fopen("./data/users.hex", "rb");
  if (dump == NULL) {
    fprintf(stderr, "DUMP FILE ERROR: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  char buffer[100];
  while (fgets(buffer, 150, dump)) {
    user_status status = atoi(strtok(buffer, SEP));
    char *login = strtok(NULL, SEP);
    char *pass_hash = strtok(NULL, SEP);
    char *first_name = strtok(NULL, SEP);
    char *last_name = strtok(NULL, SEP);
    char *phone = strtok(NULL, SEP);
    char *email = strtok(NULL, "\n");

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

  for (int i = 1; i != user_database.cap; i++) {
    fprintf(dump, "%u%s", user_database.users[i].status, SEP);
    fprintf(dump, "%s%s", user_database.users[i].login, SEP);
    fprintf(dump, "%s%s", user_database.users[i].pass_hash, SEP);
    fprintf(dump, "%s%s", user_database.users[i].first_name, SEP);
    fprintf(dump, "%s%s", user_database.users[i].last_name, SEP);
    fprintf(dump, "%s%s", user_database.users[i].phone, SEP);
    fprintf(dump, "%s\n", user_database.users[i].email);
  }
  fclose(dump);

  for (int i = 0; i != user_database.cap; i++) {
    user_destruction(&user_database.users[i]);
  }
  free(user_database.users);
}

int login(char *login, char *password) { return 0; }

int logout() { return 0; }

int update_user() { return 0; }