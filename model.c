#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model.h"

// Implementación de las funciones de acceso a datos

void insertRecord(const char *filename, Person p)
{
  FILE *file = fopen(filename, "ab");
  if (file == NULL)
  {
    printf("Error abriendo el archivo para insertar.\n");
    return;
  }
  fwrite(&p, sizeof(Person), 1, file);
  fclose(file);
}

void displayRecords(const char *filename)
{
  FILE *file = fopen(filename, "rb");
  if (file == NULL)
  {
    printf("Error abriendo el archivo para leer.\n");
    return;
  }
  Person p;
  while (fread(&p, sizeof(Person), 1, file))
  {
    printf("ID: %d, Nombre: %s, Edad: %d\n", p.id, p.name, p.age);
  }
  fclose(file);
}

void modifyRecord(const char *filename, int id, Person newRecord)
{
  FILE *file = fopen(filename, "rb+");
  if (file == NULL)
  {
    printf("Error abriendo el archivo para modificar.\n");
    return;
  }
  Person p;
  while (fread(&p, sizeof(Person), 1, file))
  {
    if (p.id == id)
    {
      fseek(file, -sizeof(Person), SEEK_CUR);
      fwrite(&newRecord, sizeof(Person), 1, file);
      fclose(file);
      return;
    }
  }
  fclose(file);
  printf("Registro no encontrado.\n");
}

void deleteRecord(const char *filename, int id)
{
  FILE *file = fopen(filename, "rb");
  if (file == NULL)
  {
    printf("Error abriendo el archivo para eliminar.\n");
    return;
  }
  FILE *tempFile = fopen("temp.dat", "wb");
  if (tempFile == NULL)
  {
    printf("Error creando el archivo temporal.\n");
    fclose(file);
    return;
  }
  Person p;
  while (fread(&p, sizeof(Person), 1, file))
  {
    if (p.id != id)
    {
      fwrite(&p, sizeof(Person), 1, tempFile);
    }
  }
  fclose(file);
  fclose(tempFile);
  remove(filename);
  rename("temp.dat", filename);
}
