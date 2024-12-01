#include <stdio.h>
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