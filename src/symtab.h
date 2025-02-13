#ifndef SYMTAB_H
#define SYMTAB_H

#include <stdio.h>

#define SIZE 211

typedef enum { VAR_SYM, FUN_SYM } SymbolKind;
typedef enum { INT_TYPE, FLOAT_TYPE, VOID_TYPE } DataType;

typedef struct LineListRec {
  int lineno;
  struct LineListRec *next;
} *LineList;

typedef struct BucketListRec {
  char *name;
  LineList lines;
  int memloc;
  SymbolKind kind;
  char *scope;
  DataType dataType;

  struct BucketListRec *next;
} *BucketList;

void st_insert(char *name, char *scope, int lineno, int loc, SymbolKind kind,
               DataType dataType);

int st_lookup(char *name, char *scope, SymbolKind kind);

void printSymTab(FILE *listing);
int getNextMemLoc();

#endif
