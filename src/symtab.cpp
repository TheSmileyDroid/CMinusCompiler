#include "symtab.h"
#include <cstdlib>
#include <cstring>
#include <string>

#define SIZE 211
#define SHIFT 4

static int currentMemLoc = 0; // contador para locais de memória

int getNextMemLoc() { return currentMemLoc++; }

static int hash(char *key) {
  int temp = 0;
  int i = 0;
  while (key[i] != '\0') {
    temp = ((temp << SHIFT) + key[i]) % SIZE;
    ++i;
  }
  return temp;
}

static BucketList hashTable[SIZE];

void st_insert(char *name, char *scope, int lineno, int loc, SymbolKind kind,
               DataType dataType) {
  // Para variável, use "scope:name"; para função, use apenas o nome
  std::string keyStr =
      (kind == VAR_SYM) ? (std::string(scope) + ":" + name) : std::string(name);
  char *key = strdup(keyStr.c_str());

  int h = hash(key);
  BucketList l = hashTable[h];
  while ((l != nullptr) && (strcmp(key, l->name) != 0))
    l = l->next;

  if (l == nullptr) { /* símbolo ainda não está na tabela */
    l = new struct BucketListRec;
    l->name = key; // chave composta já duplicada
    l->lines = new struct LineListRec;
    l->lines->lineno = lineno;
    l->memloc = loc;
    l->kind = kind;
    l->scope = strdup(scope);
    l->dataType = dataType;
    l->lines->next = nullptr;
    l->next = hashTable[h];
    hashTable[h] = l;
  } else { /* símbolo encontrado, apenas adiciona o número da linha */
    LineList t = l->lines;
    while (t->next != nullptr)
      t = t->next;
    t->next = new struct LineListRec;
    t->next->lineno = lineno;
    t->next->next = nullptr;
  }
  // Se for variável e a chave era composta, libere a memória temporária usada
  // para lookup se necessário
}

int st_lookup(char *name, char *scope, SymbolKind kind) {
  std::string keyStr =
      (kind == VAR_SYM) ? (std::string(scope) + ":" + name) : std::string(name);
  char *key = strdup(keyStr.c_str());
  int h = hash(key);
  BucketList l = hashTable[h];
  while ((l != nullptr) && (strcmp(key, l->name) != 0))
    l = l->next;
  free(key);
  if (l == nullptr)
    return -1;
  else
    return l->memloc;
}

void printSymTab(FILE *listing) {
  int i;
  fprintf(listing,
          "Variable Name     Scope      Type   Location   Line Numbers\n");
  fprintf(listing,
          "-------------     -----      ----   --------   ------------\n");
  for (i = 0; i < SIZE; ++i) {
    if (hashTable[i] != nullptr) {
      BucketList l = hashTable[i];
      while (l != nullptr) {
        LineList t = l->lines;
        fprintf(listing, "%-17s ", l->name);
        fprintf(listing, "%-10s ", l->scope);
        fprintf(listing, "%-6s  ", (l->kind == VAR_SYM ? "var" : "fun"));
        fprintf(listing, "%-8d  ", l->memloc);
        while (t != nullptr) {
          fprintf(listing, "%4d ", t->lineno);
          t = t->next;
        }
        fprintf(listing, "\n");
        l = l->next;
      }
    }
  }
}
