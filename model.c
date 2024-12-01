#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model.h"

void insertDatabase(Database d)
{
  FILE *file = fopen("db/databases.dat", "ab");
  fwrite(&d, sizeof(Database), 1, file);
  fclose(file);
}

Database* getDatabases(int *size)
{
  FILE *file = fopen("db/databases.dat", "rb");
  Database *databases = (Database*)malloc(sizeof(Database));
  Database d;
  int i = 0;
  while (fread(&d, sizeof(Database), 1, file))
  {
    databases = (Database*)realloc(databases, (i+1)*sizeof(Database));
    databases[i] = d;
    i++;
  }
  fclose(file);
  *size = i;
  return databases;
}

Database getDatabase(char *name)
{
  FILE *file = fopen("db/databases.dat", "rb");
  Database d;
  while (fread(&d, sizeof(Database), 1, file))
  {
    if (strcmp(d.name, name) == 0)
    {
      fclose(file);
      return d;
    }
  }
  fclose(file);
  printf("Database not found");
  return d;
}

void modifyDatabase(Database d)
{
  FILE *file = fopen("db/databases.dat", "rb+");
  Database tmp;
  while(fread(&tmp, sizeof(Database), 1, file))
  {
    if (d.id == tmp.id)
    {
      fseek(file, -sizeof(Database), SEEK_CUR);
      fwrite(&d, sizeof(Database), 1, file);
      fclose(file);
      return;
    }
  }
  fclose(file);
  printf("Database not found");
}

void deleteDatabase(Database d)
{
  FILE *file = fopen("db/databases.dat", "rb");
  FILE *tmpFile = fopen("db/tmp.dat", "wb");
  Database tmp;
  while(fread(&tmp, sizeof(Database), 1, file))
  {
    if (d.id != tmp.id)
    {
      fwrite(&tmp, sizeof(Database), 1, tmpFile);
    }
  }
  fclose(file);
  fclose(tmpFile);
  remove("db/databases.dat");
  rename("db/tmp.dat", "db/databases.dat");
}

void insertTable(Table t)
{
  FILE *file = fopen("db/tables.dat", "ab");
  fwrite(&t, sizeof(Table), 1, file);
  fclose(file);
}

Table* getTables(int *size, int databaseId)
{
  FILE *file = fopen("db/tables.dat", "rb");
  Table *tables = (Table*)malloc(sizeof(Table));
  Table t;
  int i = 0;
  while (fread(&t, sizeof(Table), 1, file))
  {
    if (t.databaseId == databaseId)
    {
      tables = (Table*)realloc(tables, (i+1)*sizeof(Table));
      tables[i] = t;
      i++;
    }
  }
  fclose(file);
  *size = i;
  return tables;
}

Table getTable(char *name)
{
  FILE *file = fopen("db/tables.dat", "rb");
  Table t;
  while (fread(&t, sizeof(Table), 1, file))
  {
    if (strcmp(t.name, name) == 0)
    {
      fclose(file);
      return t;
    }
  }
  fclose(file);
  printf("Table not found");
  return t;
}

void modifyTable(Table t)
{
  FILE *file = fopen("db/tables.dat", "rb+");
  Table tmp;
  while(fread(&tmp, sizeof(Table), 1, file))
  {
    if (t.id == tmp.id)
    {
      fseek(file, -sizeof(Table), SEEK_CUR);
      fwrite(&t, sizeof(Table), 1, file);
      fclose(file);
      return;
    }
  }
  fclose(file);
  printf("Table not found");
}

void deleteTable(Table t)
{
  FILE *file = fopen("db/tables.dat", "rb");
  FILE *tmpFile = fopen("db/tmp.dat", "wb");
  Table tmp;
  while(fread(&tmp, sizeof(Table), 1, file))
  {
    if (t.id != tmp.id)
    {
      fwrite(&tmp, sizeof(Table), 1, tmpFile);
    }
  }
  fclose(file);
  fclose(tmpFile);
  remove("db/tables.dat");
  rename("db/tmp.dat", "db/tables.dat");
}

void insertColumn(Column c)
{
  FILE *file = fopen("db/columns.dat", "ab");
  fwrite(&c, sizeof(Column), 1, file);
  fclose(file);
}

Column* getColumns(int *size, int tableId)
{
  FILE *file = fopen("db/columns.dat", "rb");
  Column *columns = (Column*)malloc(sizeof(Column));
  Column c;
  int i = 0;
  while (fread(&c, sizeof(Column), 1, file))
  {
    if (c.tableId == tableId)
    {
      columns = (Column*)realloc(columns, (i+1)*sizeof(Column));
      columns[i] = c;
      i++;
    }
  }
  fclose(file);
  *size = i;
  return columns;
}

Column getColumn(char *name)
{
  FILE *file = fopen("db/columns.dat", "rb");
  Column c;
  while (fread(&c, sizeof(Column), 1, file))
  {
    if (strcmp(c.name, name) == 0)
    {
      fclose(file);
      return c;
    }
  }
  fclose(file);
  printf("Column not found");
  return c;
}

void modifyColumn(Column c)
{
  FILE *file = fopen("db/columns.dat", "rb+");
  Column tmp;
  while(fread(&tmp, sizeof(Column), 1, file))
  {
    if (c.id == tmp.id)
    {
      fseek(file, -sizeof(Column), SEEK_CUR);
      fwrite(&c, sizeof(Column), 1, file);
      fclose(file);
      return;
    }
  }
  fclose(file);
  printf("Column not found");
}

void deleteColumn(Column c)
{
  FILE *file = fopen("db/columns.dat", "rb");
  FILE *tmpFile = fopen("db/tmp.dat", "wb");
  Column tmp;
  while(fread(&tmp, sizeof(Column), 1, file))
  {
    if (c.id != tmp.id)
    {
      fwrite(&tmp, sizeof(Column), 1, tmpFile);
    }
  }
  fclose(file);
  fclose(tmpFile);
  remove("db/columns.dat");
  rename("db/tmp.dat", "db/columns.dat");
}

void displayTable(Table t)
{
  FILE *columnsFile = fopen("db/columns.dat", "rb");
  FILE *recordsFile = fopen("db/records.dat", "rb");

  Column columns[t.columns];
  Record records[t.records*t.columns];

  int i = 0;
  int j = 0;
  Column c;
  while(fread(&c, sizeof(Column), 1, columnsFile))
  {
    if (c.tableId == t.id)
    {
      columns[i] = c;
      i++;
      Record r;
      while(fread(&r, sizeof(Record), 1, recordsFile))
      {
        if (r.columnId == c.id)
        {
          records[j] = r;
          j++;
        }
      }
    }
  }

  printf("+");
  for (int i = 0; i < t.columns; i++)
  {
    printf("---------------+");
  }
  printf("\n|");
  for (int i = 0; i < t.columns; i++)
  {
    printf(" %-13s |", columns[i].name);
  }
  printf("\n+");
  for (int i = 0; i < t.columns; i++)
  {
    printf("---------------+");
  }
  printf("\n");

  for (int i = 0; i < t.records; i++)
  {
    printf("|");
    for (int j = 0; j < t.columns; j++)
    {
      printf(" %-13s |", records[i*t.columns+j].value);
    }
    printf("\n");
  }

  fclose(columnsFile);
  fclose(recordsFile);
}