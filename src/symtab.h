#ifndef SYMTAB_H
#define SYMTAB_H

#include <stdio.h>

#define SIZE 211

typedef enum { VAR_SYM, FUN_SYM } SymbolKind;
typedef enum { INT_TYPE, VOID_TYPE, UNKNOWN_TYPE } DataType;

inline const char *dataTypeToString(DataType dt) {
  switch (dt) {
  case INT_TYPE:
    return "int";
  case VOID_TYPE:
    return "void";
  default:
    return "unknown";
  }
}

inline int isUnknown(DataType dt) { return dt != INT_TYPE && dt != VOID_TYPE; }

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
  DataType *paramTypes;
  int paramCount;
  DataType dataType;

  struct BucketListRec *next;
} *BucketList;

void st_insert(char *name, char *scope, int lineno, int loc, SymbolKind kind,
               DataType dataType);

void st_insert_func(char *name, char *scope, int lineno, int loc,
                    SymbolKind kind, DataType dataType, DataType *paramTypes,
                    int paramCount);

int st_lookup(char *name, char *scope, SymbolKind kind);

BucketList st_retrieve(char *name, char *scope, SymbolKind kind);

void printSymTab(FILE *listing);
int getNextMemLoc();
void skipMemLoc(int n);

#endif
