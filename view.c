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