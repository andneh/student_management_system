#include "./marks.h"
#include "./users.h"
#include <stdio.h>

int main() {
  init_database();
  add_user("1111", "char *pass", "char *first_name", "char *last_name", admin,
           "123123123", "char *email");
  add_user("22222", "char *pass", "char *first_name", "char *last_name", admin,
           "123123123", "char *email");
  printf("%s\n", user_database.users[0].login);
  printf("%s\n", user_database.users[1].login);
  printf("%s\n", user_database.users[2].login);

  export_users();
  return 0;
}