#include <stdio.h>
#include "view.h"

void showMenu()
{
  printf("\nMenú de opciones:\n");
  printf("1. Insertar registro\n");
  printf("2. Mostrar todos los registros\n");
  printf("3. Modificar registro\n");
  printf("4. Eliminar registro\n");
  printf("5. Salir\n");
  printf("Seleccione una opción: ");
}

void showMessage(const char *message)
{
  printf("%s\n", message);
}
