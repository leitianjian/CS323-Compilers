#ifndef SYMTAB_H
#define SYMTAB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR NULL

typedef struct SymTab {
    int dict[26];
    struct SymTab* next;
}SymTab;

SymTab* symTab_init();

int is_empty(SymTab*);

void push(SymTab*);

int* pop(SymTab*);

int* peek(SymTab*);

int insert_symbol(SymTab *head, char* key);

#endif