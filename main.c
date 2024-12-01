#include <stdio.h>
#include <string.h>
#include "model.h"
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

  Database d;
  d.id = 1;
  strcpy(d.name, "My Database");
  insertDatabase(d);
  d.id = 2;
  insertDatabase(d);
  displayDatabases();

  strcpy(d.name, "My New Database");
  modifyDatabase(d);
  displayDatabases();
  
  d = getDatabase("My Database");
  deleteDatabase(d);
  displayDatabases();
  return 0;
}
