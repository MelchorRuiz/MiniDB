#ifndef MODEL_H
#define MODEL_H

typedef struct
{
  int id;
  char name[100];
  int age;
} Person;

void insertRecord(const char *filename, Person p);
void displayRecords(const char *filename);
void modifyRecord(const char *filename, int id, Person newRecord);
void deleteRecord(const char *filename, int id);

#endif
