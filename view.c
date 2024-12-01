#include <stdio.h>
#include <stdlib.h>
#include "view.h"
#include "model.h"

void displayDatabases()
{
  printf("+-----------------------------+\n");
  printf("| Id   | Database Name        |\n");
  printf("+-----------------------------+\n");
  int size;
  Database *databases = getDatabases(&size);
  for (int i = 0; i < size; i++)
  {
    printf("| %-4d | %-20s |\n", databases[i].id, databases[i].name);
  }
  printf("+-----------------------------+\n");
}

void displayTables(int databaseId)
{
  printf("+------+----------------------+---------+\n");
  printf("| Id   | Table Name           | Records |\n");
  printf("+------+----------------------+---------+\n");
  int size;
  Table *tables = getTables(&size, databaseId);
  for (int i = 0; i < size; i++)
  {
    printf("| %-4d | %-20s | %-7d |\n", tables[i].id, tables[i].name, tables[i].records);
  }
  printf("+------+----------------------+---------+\n");
}

void displayColumns(int tableId)
{
  printf("+------+----------------------+---------+\n");
  printf("| Id   | Column Name          | Type    |\n");
  printf("+------+----------------------+---------+\n");
  int size;
  Column *columns = getColumns(&size, tableId);
  for (int i = 0; i < size; i++)
  {
    printf("| %-4d | %-20s | %-7s |\n", columns[i].id, columns[i].name, columns[i].type);
  }
  printf("+------+----------------------+---------+\n");
}

void displayRecords(int columnId)
{
  printf("+------+----------------------+\n");
  printf("| Id   | Record Value         |\n");
  printf("+------+----------------------+\n");
  int size;
  Record *records = getRecords(&size, columnId);
  for (int i = 0; i < size; i++)
  {
    printf("| %-4d | %-20s |\n", records[i].id, records[i].value);
  }
  printf("+------+----------------------+\n");
}

void displayTable(int tableId)
{
  Table t;
  t.id = tableId;
  Column *columns = getColumns(&t.columns, t.id);
  
  Record **records = (Record**)malloc(t.columns*sizeof(Record*));
  for (int i = 0; i < t.columns; i++)
  {
    records[i] = getRecords(&t.records, columns[i].id);
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
      printf(" %-13s |", records[j][i].value);
    }
    printf("\n");
  }

  printf("+");
  for (int i = 0; i < t.columns; i++)
  {
    printf("---------------+");
  }
  printf("\n");

}