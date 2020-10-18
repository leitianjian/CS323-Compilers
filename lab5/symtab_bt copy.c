#include "symtab.h"
#include<stdlib.h>
#include<string.h>

/*
 * symbol table type, binary tree impl
 */
struct symtab {
    entry *entry;
    struct symtab *parent, *left, *right;
};

// ************************************************************
//    Your implementation goes here
// ************************************************************

symtab *symtab_init(){
    return init_node_entry(NULL);
}

void printTree (symtab *self){
    if (self == NULL) {
        return;
    }
    printTree(self->left);
    printf(" %s,", self->entry->key);
    printTree(self->right);
}

int symtab_insert(symtab *self, char *key, VAL_T value){
    if (self->entry == NULL) { // root only initiate case
        self->entry = (entry *)malloc(sizeof(entry));
        strcpy(self->entry->key, key);
        self->entry->value = value;
        self->left = NULL; self->right = NULL; self->parent = NULL;
        return 1;
    } else { // normal case
        int cmp_res = strcmp(self->entry->key, key);
        if(cmp_res > 0) {
            if (self->left) {
                return symtab_insert(self->left, key, value);
            } else {
                symtab *node = init_node_kvpair(key, value);
                self->left = node; node->parent = self;
                return 1;
            }
        } else if (cmp_res < 0) {
            if (self->right) {
                return symtab_insert(self->right, key, value);
            } else {
                symtab *node = init_node_kvpair(key, value);
                self->right = node; node->parent = self;
                return 1;
            }
        } else { // same character then update value
            return 0;
        }
    }
}

VAL_T symtab_lookup(symtab *self, char *key){
    symtab *node = tree_lookup(self, key);
    if (!node)
        return -1;
    else
        return node->entry->value;
}

symtab *tree_lookup(symtab *self, char *key) {
    if (!self)
        return NULL;
    int cmp_res = strcmp(self->entry->key, key);
    if (cmp_res > 0)
        return tree_lookup(self->left, key);
    else if (cmp_res < 0)
        return tree_lookup(self->right, key);
    else {
        return self;
    }
}

symtab *find_left_most(symtab *self) {
    symtab *node = self;
    while (node->left != NULL)
        node = node->left;
    return node;
}

symtab *node_remove(symtab *node) {
    if (node->left == NULL && node->right == NULL) {
        if (!node->parent) {// root node
            node->entry = NULL;
            return node;
        } 
        if (node->parent->left == node) {
            node->parent->left = NULL;
            node->parent = NULL;
            return node;
        } else {
            node->parent->right = NULL;
            node->parent = NULL;
            return node;
        }
    } else if (node->left != NULL && node->right != NULL) {
        symtab *left_most = find_left_most(node->right);
        symtab *new_node = node_remove(left_most);
        if (node->parent == NULL){
            node->entry = new_node->entry;
            return node;
        }
        new_node->left = node->left;
        new_node->right = node->right;
        new_node->parent = node->parent;
        node->left = node->right = node->parent = NULL;
        return node;
    } else {
        symtab *child = (node->left != NULL) ? node->left : node->right;
        if (node->parent == NULL){
            node->entry = child->entry;
            node->left = child->left;
            node->right = child->right;
            child->parent = child->left = child->right = NULL;
            child->entry = NULL;
            return child;
        }
        if (node->parent->left == node) {
            node->parent->left = child;
            child->parent = node->parent;
        } else {
            node->parent->right = child;
            child->parent = node->parent;
        }
        node->left = NULL;
        node->right = NULL;
        node->parent = NULL;
        return node;
    }
}

int symtab_remove(symtab *self, char *key){
    symtab *node = tree_lookup(self, key);
    if (!node){
        printTree(self);
        printf("lookup failed, %s\n", key);
        return 0;
    }

    printf("node and key %s, %s\n", key, node->entry->key);
    if (!node_remove(node)){
        return 0;
    } else {
        return 1;
    }
}

symtab *init_node_entry(entry *entry) {
    symtab *node = (symtab *)malloc(sizeof(symtab));
    node->entry = entry;
    node->left = NULL; node->right = NULL; node->parent = NULL;
    return node;
}

symtab *init_node_kvpair(char *key, VAL_T val) {
    symtab *node = (symtab *)malloc(sizeof(symtab));
    node->entry = (entry *)malloc(sizeof(entry));
    node->left = NULL; node->right = NULL; node->parent = NULL;
    strcpy(node->entry->key, key);
    node->entry->value = val;
    return node;
}