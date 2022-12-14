#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  student,
  parent,
  teacher,
  admin,
} user_status;

typedef struct {
  int id;
  user_status status;
  char *login;
  char *pass_hash;
  char *first_name;
  char *last_name;
  char phone[9];
  char *email;
} user;

user root = {0,    admin, "root",      "root",
             "Ro", "Ot",  "xxxxxxxxx", "root@root.root"};

char *user_set_string(char *string) {
  char *ptr = malloc(sizeof(string));
  if (ptr == NULL) {
    fprintf(stderr, "SETTING UP STRING ERROR: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  strcpy(ptr, string);
  return ptr;
}

void user_init(user *self, int id, user_status status, char *login,
               char *pass_hash, char *first_name, char *last_name, char *phone,
               char *email) {
  self->id = id;
  self->status = status;

  self->login = user_set_string(login);
  self->pass_hash = user_set_string(pass_hash);
  self->first_name = user_set_string(first_name);
  self->last_name = user_set_string(last_name);
  self->email = user_set_string(email);

  // strcpy(self->phone, phone); //ERROR
  for (int i = 0; i != 9; i++) {
    self->phone[i] = phone[i];
  }
}

void user_show(user *self) {
  printf("id:\t%u\n", self->id);
  printf("status:\t%u\n", self->status);
  printf("login:\t%s\n", self->login);
  printf("hash:\t%s\n", self->pass_hash);
  printf("first:\t%s\n", self->first_name);
  printf("last:\t%s\n", self->last_name);
  printf("phone:\t%s\n", self->phone);
  printf("email:\t%s\n", self->email);
}

void user_destruction(user *self) {
  self->id = 0;
  self->status = student;
  free(self->login);
  free(self->pass_hash);
  free(self->first_name);
  free(self->last_name);
  free(self->email);
  for (int i = 0; i != 9; i++) {
    self->phone[i] = 'x';
  }
}