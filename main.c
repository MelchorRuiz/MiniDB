#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "controller.h"
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
  
  char command[256];
  
  printf("Bienvenido al gestor de base de datos.\n");
  printf("--------------------------------------\n");
  printf("Escriba 'exit' para salir.\n");
  printf("--------------------------------------\n");
  printf("Ejemplo de comandos:\n");
  printf("CREATE DATABASE database_name\n");
  printf("CREATE TABLE database_name.table_name (column1_name,column2_name,...)\n");
  printf("INSERT INTO database_name.table_name VALUES (value1,value2,...)\n");
  printf("SELECT * FROM database_name.table_name\n");
  printf("--------------------------------------\n");
  
  while (1)
  {
    printf("db> ");
    if (fgets(command, sizeof(command), stdin) == NULL)
    {
      break;
    }
    
    command[strcspn(command, "\n")] = 0;
    
    if (strcmp(command, "exit") == 0)
    {
      break;
    }
    
    handleRequest(command);
  }
  
  return 0;
}