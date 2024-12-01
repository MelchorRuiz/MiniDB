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

  Table t;
  t.id = 1;
  strcpy(t.name, "My Table");
  t.records = 0;
  t.columns = 0;
  t.databaseId = d.id;
  insertTable(t);

  Column c;
  c.id = 1;
  strcpy(c.name, "My Column");
  strcpy(c.type, "TEXT");
  c.tableId = t.id;
  insertColumn(c);

  Record r;
  r.id = 1;
  strcpy(r.value, "My Record");
  r.columnId = c.id;
  insertRecord(r);

  c.id = 2;
  strcpy(c.name, "My Column 2");
  insertColumn(c);

  r.id = 2;
  strcpy(r.value, "My Record 2");
  r.columnId = c.id;
  insertRecord(r);


  displayTable(t.id);
  return 0;
}
