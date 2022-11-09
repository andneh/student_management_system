#include "./marks.h"
#include "./users/database.h"
#include <stdio.h>
// #include <openssl/rsa.h>

char *pass_hash(char *pass) {
  // rsa.h
  return pass;
}

int main() {
  import_users();
  // add_user(student, "andrew", "12345", "Andrii", "Stoilaky", "000111333",
  //          "adnsrii@h.h");
  // add_user(student, "sabi", "12345", "Sabina", "Stoilaky", "000111333",
  //          "sabi@h.h");
  // add_user(teacher, "kolia", "12345", "Kolia", "Stoilaky", "000111333",
  //          "kolia@h.h");

  delete_user("andrew");
  // delete_user(4);
  // delete_user(20);
  show_users();
  export_users();
  return 0;
}