#include "./marks.h"
#include "./users.h"
#include <stdio.h>

int main() {
  init_database();
  import_users();

  // add_user("andrew", "12345", "Andrii", "Stoilaky", student, "000111333",
  //          "adnsrii@h.h");
  // add_user("sabi", "12345", "Sabina", "Stoilaky", student, "000111333",
  //           "sabi@h.h");

  // user_destruction(&user_database.users[0]);
  show_users();

  export_users();
  return 0;
}