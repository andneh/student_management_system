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
  char *login;
  char *pass_hash;
  char *first_name;
  char *last_name;
  user_status status;
  char phone[9];
  char *email;
} user;

char *set_string(char *string) {
  char *ptr = malloc(sizeof(string));
  if (ptr == NULL) {
    fprintf(stderr, "SETTING UP STRING ERROR: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  strcpy(ptr, string);
  return ptr;
}

void init_user(user *self, int id, char *login, char *pass_hash,
               char *first_name, char *last_name, user_status status,
               char *phone, char *email) {
  self->id = id;
  self->status = status;

  self->login = set_string(login);
  self->pass_hash = set_string(pass_hash);
  self->first_name = set_string(first_name);
  self->last_name = set_string(last_name);
  self->email = set_string(email);

  // strcpy(self->phone, phone); //ERROR
  for (int i = 0; i != 9; i++) {
    self->phone[i] = phone[i];
  }
}

void user_destruction(user *self) {
  free(self->login);
  free(self->pass_hash);
  free(self->first_name);
  free(self->last_name);
  free(self->email);
}