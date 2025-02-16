#include "symtab.h"
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <string>

#define SIZE 211
#define SHIFT 4

static int currentMemLoc = 0;

int getNextMemLoc() { return currentMemLoc++; }
void skipMemLoc(int n) { currentMemLoc += n; }

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

  std::string keyStr =
      (kind == VAR_SYM) ? (std::string(scope) + ":" + name) : std::string(name);
  char *key = strdup(keyStr.c_str());

  int h = hash(key);
  BucketList l = hashTable[h];
  while ((l != nullptr) && (strcmp(key, l->name) != 0))
    l = l->next;

  if (l == nullptr) {
    l = new struct BucketListRec;
    l->name = key;
    l->lines = new struct LineListRec;
    l->lines->lineno = lineno;
    l->memloc = loc;
    l->kind = kind;
    l->scope = strdup(scope);
    l->dataType = dataType;
    l->paramCount = 0;
    l->lines->next = nullptr;
    l->next = hashTable[h];
    hashTable[h] = l;
  } else {
    LineList t = l->lines;
    while (t->next != nullptr)
      t = t->next;
    t->next = new struct LineListRec;
    t->next->lineno = lineno;
    t->next->next = nullptr;
  }
}

void st_insert_func(char *name, char *scope, int lineno, int loc,
                    SymbolKind kind, DataType dataType, DataType *paramTypes,
                    int paramCount) {
  st_insert(name, scope, lineno, loc, kind, dataType);
  BucketList l = st_retrieve(name, scope, kind);
  l->paramTypes = paramTypes;
  l->paramCount = paramCount;
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
  if (l == nullptr) {
    if (strcmp(scope, "global") != 0)
      return st_lookup(name, const_cast<char *>("global"), kind);
    return -1;
  } else {
    return l->memloc;
  }
}

BucketList st_retrieve(char *name, char *scope, SymbolKind kind) {
  if (!*name)
    return nullptr;
  std::string keyStr =
      (kind == VAR_SYM) ? (std::string(scope) + ":" + name) : std::string(name);
  char *key = strdup(keyStr.c_str());
  int h = hash(key);
  BucketList l = hashTable[h];
  while ((l != nullptr) && (strcmp(key, l->name) != 0))
    l = l->next;
  free(key);
  if (l == nullptr) {
    if (strcmp(scope, "global") != 0)
      return st_retrieve(name, const_cast<char *>("global"), kind);
    return nullptr;
  } else {
    return l;
  }
  return l;
}

void printSymTab(FILE *listing) {
  // Atualiza cabeçalho para incluir coluna de parâmetros
  fprintf(listing, "Variable Name     Scope      Type   DataType   Location   "
                   "Param Types      Line Numbers\n");
  fprintf(listing, "-------------     -----      ----   --------   --------   "
                   "-----------      ------------\n");
  for (int i = 0; i < SIZE; ++i) {
    if (hashTable[i] != nullptr) {
      BucketList l = hashTable[i];
      while (l != nullptr) {
        LineList t = l->lines;
        fprintf(listing, "%-17s ", l->name);
        fprintf(listing, "%-10s ", l->scope);
        fprintf(listing, "%-6s  ", (l->kind == VAR_SYM ? "var" : "fun"));
        const char *dt = "";
        switch (l->dataType) {
        case INT_TYPE:
          dt = "int";
          break;
        case VOID_TYPE:
          dt = "void";
          break;
        default:
          dt = "unknown";
          break;
        }
        fprintf(listing, "%-8s  ", dt);
        fprintf(listing, "%-8d  ", l->memloc);
        // Adiciona impressão dos parâmetros para funções
        if (l->kind != VAR_SYM) { // Função
          std::string params = "(";
          for (int i = 0; i < l->paramCount; i++) {
            if (l->paramTypes[i] == INT_TYPE)
              params += "int";
            else if (l->paramTypes[i] == VOID_TYPE)
              params += "void";
            else
              params += "unknown";
            if (i < l->paramCount - 1)
              params += ", ";
          }
          params += ")";
          fprintf(listing, "%-15s  ", params.c_str());
        } else {
          fprintf(listing, "%-15s  ", "");
        }
        // Imprime números de linha
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
