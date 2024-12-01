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
  printf("+-----------------------------+\n");
  printf("| Id   | Database Name        |\n");
  printf("+-----------------------------+\n");
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
  printf("+-----------------------------+\n");
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

void displayTables(Database d)
{
  FILE *file = fopen("db/tables.dat", "rb");
  Table t;
  printf("+------+----------------------+---------+\n");
  printf("| Id   | Table Name           | Records |\n");
  printf("+------+----------------------+---------+\n");
  while (fread(&t, sizeof(Table), 1, file))
  {
    if (t.databaseId == d.id)
    {
      printf("| %-4d | %-20s | %-7d |\n", t.id, t.name, t.records);
    }
  }
  printf("+------+----------------------+---------+\n");
  fclose(file);
}

void insertColumn(Column c)
{
  FILE *file = fopen("db/columns.dat", "ab");
  fwrite(&c, sizeof(Column), 1, file);
  fclose(file);
}

void insertRecord(Record r)
{
  FILE *file = fopen("db/records.dat", "ab");
  fwrite(&r, sizeof(Record), 1, file);
  fclose(file);
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