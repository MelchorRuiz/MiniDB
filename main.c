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

  displayDatabases();

  Table t;
  t.id = 1;
  strcpy(t.name, "My Table");
  t.records = 0;
  t.columns = 0;
  t.databaseId = d.id;
  insertTable(t);
  displayTables(d.id);

  Column c;
  c.id = 1;
  strcpy(c.name, "My Column");
  strcpy(c.type, "TEXT");
  c.tableId = t.id;
  insertColumn(c);

  c.id = 2;
  strcpy(c.name, "My Column 2");
  insertColumn(c);

  displayColumns(t.id);

  strcpy(c.name, "My Other Column");
  modifyColumn(c);
  displayColumns(t.id);

  deleteColumn(c);
  displayColumns(t.id);

  return 0;
}
