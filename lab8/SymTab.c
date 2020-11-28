#include "SymTab.h"

SymTab* symTab_init(){
    SymTab* head;
    head = (SymTab*)malloc(sizeof(SymTab));
    head->next = NULL;
    return head;
}

int is_empty(SymTab* head){
    return (head->next == NULL);
}

void push(SymTab* head) {
    SymTab* newTab= (SymTab*)malloc(sizeof(SymTab));
    memset(newTab->dict, 0, sizeof(int) * 26);
    newTab->next = head->next;
    head->next = newTab;
}

int* pop(SymTab* head) {
    int* topData;
    if (is_empty(head)) {
        printf("Can't pop global scope\n");
        return ERROR;
    }
    SymTab* firstCell = head->next;
    head->next = firstCell->next;
    topData = firstCell->dict;
    return topData;
}

int* peek(SymTab* head){
    if(is_empty(head)){
        printf("empty stack\n");
        return NULL;
    }
    SymTab* firstCell = head->next;
    return firstCell->dict;
}

int insert_symbol(SymTab *head, char* key) {
    int i = key[1] - 'a';
    int *table = peek(head);
    if (table[i] == 1) {
        printf("duplicate key: %s\n", key);
        return 0;
    }
    else {
        table[i] = 1;
        return 1;
    }
}