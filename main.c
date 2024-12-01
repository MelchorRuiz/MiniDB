#include <stdio.h>
#include "model.h"
#include "view.h"
#include "controller.h"

int main()
{
  const char *filename = "database.dat";
  int option;

  while (1)
  {
    showMenu();
    scanf("%d", &option);

    switch (option)
    {
    case 1:
      handleInsert(filename);
      break;
    case 2:
      handleDisplay(filename);
      break;
    case 3:
      handleModify(filename);
      break;
    case 4:
      handleDelete(filename);
      break;
    case 5:
      showMessage("Saliendo del programa.");
      return 0;
    default:
      showMessage("Opción no válida.");
    }
  }
}
