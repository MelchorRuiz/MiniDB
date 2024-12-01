#include <stdio.h>
#include "model.h"
#include "view.h"
#include <string.h>
#include <ctype.h>

void createDatabase(char *name)
{
  Database d;
  FILE *file = fopen("db/databases.dat", "rb");
  if (file == NULL)
  {
    d.id = 1;
  }
  else
  {
    Database temp;
    int maxId = 0;
    while (fread(&temp, sizeof(Database), 1, file))
    {
      if (strcmp(temp.name, name) == 0)
      {
        printf("Error: Database already exists.\n");
        fclose(file);
        return;
      }
      if (temp.id > maxId)
      {
        maxId = temp.id;
      }
    }
    d.id = maxId + 1;
    fclose(file);
  }
  strcpy(d.name, name);
  insertDatabase(d);
}

void createTable(char *name, char *databaseName, char *columns)
{
  Database d = getDatabase(databaseName);

  Table t;
  FILE *fileTables = fopen("db/tables.dat", "rb");
  if (fileTables == NULL)
  {
    t.id = 1;
  }
  else
  {
    Table temp;
    int maxId = 0;
    while (fread(&temp, sizeof(Table), 1, fileTables))
    {
      if (strcmp(temp.name, name) == 0 && temp.databaseId == d.id)
      {
        printf("Error: Table already exists.\n");
        fclose(fileTables);
        return;
      }
      if (temp.id > maxId)
      {
        maxId = temp.id;
      }
    }
    t.id = maxId + 1;
    fclose(fileTables);
  }
  strcpy(t.name, name);
  t.databaseId = d.id;
  t.records = 0;
  t.columns = 0;
  char *token = strtok(columns, ",");

  FILE *fileColumns = fopen("db/columns.dat", "rb");
  int maxId = 0;
  if (fileColumns != NULL)
  {
    Column temp;
    while (fread(&temp, sizeof(Column), 1, fileColumns))
    {
      if (temp.id > maxId)
      {
        maxId = temp.id;
      }
    }
    fclose(fileColumns);
  }
  while (token != NULL)
  {
    Column c;
    c.id = maxId + t.columns + 1;
    strcpy(c.name, token);
    strcpy(c.type, "string");
    c.tableId = t.id;
    insertColumn(c);
    t.columns++;
    token = strtok(NULL, ",");
  }

  insertTable(t);
}

void createRecord(char *tableName, char *databaseName, char *values)
{
  Database d = getDatabase(databaseName);
  Table t = getTable(tableName, d.id);
  Column *columns = getColumns(&t.columns, t.id);

  FILE *file = fopen("db/records.dat", "rb");
  int maxId = 0;
  if (file != NULL)
  {
    Record temp;
    while (fread(&temp, sizeof(Record), 1, file))
    {
      if (temp.id > maxId)
      {
        maxId = temp.id;
      }
    }
    fclose(file);
  }
  char *token = strtok(values, ",");
  int i = 0;
  while (token != NULL)
  {
    Record r;
    r.id = maxId + i;
    strcpy(r.value, token);
    r.columnId = columns[i].id;
    insertRecord(r);
    token = strtok(NULL, ",");
    i++;
  }

  t.records++;
  modifyTable(t);
}

void handleRequest(char* request)
{
  char requestCopy[strlen(request) + 1];
  strcpy(requestCopy, request);

  char *token = strtok(requestCopy, " ");
  if (strcmp(token, "CREATE") == 0)
  {
    token = strtok(NULL, " ");
    if (strcmp(token, "DATABASE") == 0)
    {
      token = strtok(NULL, " ");
      createDatabase(token);
    }
    else if (strcmp(token, "TABLE") == 0)
    {
      token = strtok(NULL, ".");
      char *databaseName = token;
      token = strtok(NULL, " ");
      char *tableName = token;
      token = strtok(NULL, "");
      char *columns = token;

      int len = strlen(columns);
      memmove(columns, columns + 1, len - 1);
      columns[len - 2] = '\0';

      createTable(tableName, databaseName, columns);
    }
  }
  else if (strcmp(token, "INSERT") == 0)
  {
    token = strtok(NULL, " ");
    token = strtok(NULL, ".");
    char *databaseName = token;
    token = strtok(NULL, " ");
    char *tableName = token;
    token = strtok(NULL, " ");
    token = strtok(NULL, "");
    char *values = token;

    int len = strlen(values);
    memmove(values, values + 1, len - 1);
    values[len - 2] = '\0';

    createRecord(tableName, databaseName, values);
  }
  else if (strcmp(token, "SELECT") == 0)
  {
    token = strtok(NULL, " ");
    if (token == NULL || strcmp(token, "*") != 0) {
      printf("Error: Invalid SELECT format.\n");
      return;
    }

    token = strtok(NULL, " ");
    if (token == NULL || strcmp(token, "FROM") != 0) {
      printf("Error: Missing FROM keyword.\n");
      return;
    }

    char *databaseName = strtok(NULL, ".");
    char *tableName = strtok(NULL, " ");

    Database d = getDatabase(databaseName);
    Table t = getTable(tableName, d.id);
    displayTable(t.id);
  }
}