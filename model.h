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
Database* getDatabases(int *size);
Database getDatabase(char *name);
void modifyDatabase(Database d);
void deleteDatabase(Database d);

void insertTable(Table t);
Table* getTables(int *size, int databaseId);
Table getTable(char *name);
void modifyTable(Table t);
void deleteTable(Table t);

void insertColumn(Column c);
Column* getColumns(int *size, int tableId);
Column getColumn(char *name);
void modifyColumn(Column c);
void deleteColumn(Column c);

// void insertRecord(Record r);


#endif
