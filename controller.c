#include <stdio.h>
#include "model.h"
#include "view.h"

void handleInsert(const char *filename)
{
  Person p;
  printf("Ingrese el ID: ");
  scanf("%d", &p.id);
  printf("Ingrese el nombre: ");
  getchar();
  fgets(p.name, 100, stdin);
  p.name[strcspn(p.name, "\n")] = '\0';
  printf("Ingrese la edad: ");
  scanf("%d", &p.age);
  insertRecord(filename, p);
  showMessage("Registro insertado.");
}

void handleDisplay(const char *filename)
{
  displayRecords(filename);
}

void handleModify(const char *filename)
{
  int id;
  printf("Ingrese el ID del registro a modificar: ");
  scanf("%d", &id);
  Person p;
  printf("Ingrese el nuevo nombre: ");
  getchar();
  fgets(p.name, 100, stdin);
  p.name[strcspn(p.name, "\n")] = '\0';
  printf("Ingrese la nueva edad: ");
  scanf("%d", &p.age);
  p.id = id;
  modifyRecord(filename, id, p);
  showMessage("Registro modificado.");
}

void handleDelete(const char *filename)
{
  int id;
  printf("Ingrese el ID del registro a eliminar: ");
  scanf("%d", &id);
  deleteRecord(filename, id);
  showMessage("Registro eliminado.");
}
