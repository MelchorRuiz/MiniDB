#ifndef MODEL_H
#define MODEL_H

typedef struct
{
  int id;
  char name[100];
} Database;

typedef struct
{
  int id;
  char name[100];
  int records;
  int columns;
  int databaseId;
} Table;

typedef struct
{
  int id;
  char name[100];
  char type[100];
  int tableId;
} Column;

typedef struct
{
  int id;
  char value[100];
  int columnId;
} Record;

void insertDatabase(Database d);
void displayDatabases();

void insertTable(Table t);
void displayTables(Database d);

void insertColumn(Column c);
void insertRecord(Record r);

void displayTable(Table t);

#endif
