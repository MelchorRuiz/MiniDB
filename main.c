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
  strcpy(d.name, "My Database 2");
  insertDatabase(d);

  displayDatabases();

  Table t;
  t.id = 1;
  strcpy(t.name, "My Table");
  t.records = 0;
  t.columns = 0;
  t.databaseId = d.id;
  insertTable(t);
  displayTables(d.id);

  strcpy(t.name, "My Table 2");
  modifyTable(t);
  displayTables(d.id);

  deleteTable(t);
  displayTables(d.id);


  return 0;
}
