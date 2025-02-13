#ifndef SYMTAB_H
#define SYMTAB_H

#include <stdio.h>

#define SIZE 211

// Novos enums para identificar símbolo e tipo de dado
typedef enum { VAR_SYM, FUN_SYM } SymbolKind;
typedef enum { INT_TYPE, FLOAT_TYPE, VOID_TYPE } DataType;

typedef struct LineListRec {
  int lineno;
  struct LineListRec *next;
} *LineList;

typedef struct BucketListRec {
  // Chave de identificação baseada no nome (para função) ou scope+name (para
  // variável)
  char *name;
  LineList lines;
  int memloc;        /* local na memória para variável */
  SymbolKind kind;   // var ou fun
  char *scope;       // escopo do símbolo ("global" ou nome da função)
  DataType dataType; // int, float ou void

  struct BucketListRec *next;
} *BucketList;

// Altere a assinatura para receber scope, kind e dataType
void st_insert(char *name, char *scope, int lineno, int loc, SymbolKind kind,
               DataType dataType);

// Altere lookup para considerar o scope quando for variável
int st_lookup(char *name, char *scope, SymbolKind kind);

void printSymTab(FILE *listing);
int getNextMemLoc();

#endif
