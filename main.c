#include <stdio.h>
#include "controller.h"
#include "view.h"
#include <sys/stat.h>

void ensureDbDirectoryExists()
{
  struct stat st = {0};
  if (stat("db", &st) == -1)
  {
    mkdir("db", 0700);
  }
}

int main()
{
  ensureDbDirectoryExists();
  handleRequest("CREATE DATABASE test");
  handleRequest("CREATE TABLE test.users (name,age)");
  handleRequest("INSERT INTO test.users VALUES (John Doe,30)");
  handleRequest("INSERT INTO test.users VALUES (Jane Doe,25)");
  handleRequest("SELECT * FROM test.users");
  
  return 0;
}
