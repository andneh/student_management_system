#include "./user.hpp"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEP "|"

typedef struct {
  int cap;
  user *users;
  int size;
} database;

database user_database = {-1, NULL, 0};

void add_user(user_status status, char *login, char *pass_hash,
              char *first_name, char *last_name, char *phone, char *email) {

  if (user_database.cap == -1) {
    user_database.cap = 0;
    add_user(root.status, root.login, root.pass_hash, root.first_name,
             root.last_name, root.phone, root.email);
  }

  user_database.cap += 1;

  user_database.users = realloc(
      user_database.users, (user_database.cap * sizeof(*user_database.users)));
  if (user_database.users == NULL) {
    fprintf(stderr, "ADDING USER TO DATABASE ERROR: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  // TODO LOGIN CHECK @nehalch
  user_init(&user_database.users[user_database.cap - 1], user_database.cap - 1,
            status, login, pass_hash, first_name, last_name, phone, email);
}

void import_users() {
  FILE *dump = fopen("./data/users.hex", "rb");
  if (dump == NULL) {
    // fprintf(stderr, "DUMP FILE ERROR: %s\n", strerror(errno));
    // exit(EXIT_FAILURE);
    return;
  } else {
    char buffer[100];
    while (fgets(buffer, 150, dump)) {
      user_status status = atoi(strtok(buffer, SEP));
      char *login = strtok(NULL, SEP);
      char *pass_hash = strtok(NULL, SEP);
      char *first_name = strtok(NULL, SEP);
      char *last_name = strtok(NULL, SEP);
      char *phone = strtok(NULL, SEP);
      char *email = strtok(NULL, "\n");

      add_user(status, login, pass_hash, first_name, last_name, phone, email);
    }
    fclose(dump);
  }
}

void delete_user(char *login_del) {
  if (user_database.users == NULL) {
    printf("DATABASE EMPTY!\n");
  } else {
    for (int i = 0; i != user_database.cap; i++) {
      // TODO LOGIN IF CHECK @nehalch
      if (user_database.users[i].login == login_del) {
        user_destruction(&user_database.users[i]);
        return;
      }
    }
    printf("USER NOT FOUND!\n");
  }
}

void export_users() {
  FILE *dump = fopen("./data/users.hex", "wb+");
  if (dump == NULL) {
    fprintf(stderr, "DUMP FILE ERROR: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i != user_database.cap; i++) {
    if (user_database.users[i].id != 0) {
      fprintf(dump, "%u%s", user_database.users[i].status, SEP);
      fprintf(dump, "%s%s", user_database.users[i].login, SEP);
      fprintf(dump, "%s%s", user_database.users[i].pass_hash, SEP);
      fprintf(dump, "%s%s", user_database.users[i].first_name, SEP);
      fprintf(dump, "%s%s", user_database.users[i].last_name, SEP);
      fprintf(dump, "%s%s", user_database.users[i].phone, SEP);
      fprintf(dump, "%s\n", user_database.users[i].email);
    }
    user_destruction(&user_database.users[i]);
  }
  fclose(dump);

  free(user_database.users);
}

void show_users() {
  if (user_database.users == NULL) {
    printf("NO USERS\n");
  } else {
    for (int i = 0; i != user_database.cap; i++) {
      if (user_database.users[i].id != 0) {
        user_show(&user_database.users[i]);
        printf("\n");
      }
    }
  }
}

int login(char *login, char *pass_hash) { return 0; }

int logout() { return 0; }

int update_user() { return 0; }