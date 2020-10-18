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

symtab *symtab_init(){
    return init_node_entry(NULL);
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

VAL_T symtab_lookup(symtab *self, char *key){
    symtab *node = tree_lookup(self, key);
    if (!node)
        return -1;
    else
        return node->entry->value;
}

symtab *find_left_most(symtab *self) {
    symtab *node = self;
    while (node->left != NULL)
        node = node->left;
    return node;
}

int node_remove(symtab *node) {
    if (node->left == NULL && node->right == NULL) {
        // symtab *child = (node->left) ? node->left : node->right;
        if (node->parent == NULL){
            node->entry = NULL;
            return 1;    
        } else {
            if (node->parent->left == node){
                node->parent->left = NULL;
            } else {
                node->parent->right = NULL;
            }
            node->parent = NULL;
            return 1;
        }
    } else if (node->left != NULL && node->right != NULL) {
        symtab *left_most = find_left_most(node->right);
        entry *temp = node->entry;
        node->entry = left_most->entry;
        left_most->entry = temp;
        return node_remove(left_most);
        // symtab *new_node = node_remove(left_most);
    } else {
        if (node->left == NULL) { // 只有右孩子
            // printf("node parent: %d\n", node->parent);
            if (node->parent == NULL) {
                node->entry = node->right->entry;
                node->left = node->right->left;
                node->right = node->right->right;
                return 1;
            } else {
                if (node->parent->left == node){
                    node->parent->left = node->right;
                    node->right->parent = node->parent;
                    return 1;
                } else {
                    node->parent->right = node->right;
                    node->right->parent = node->parent;
                    return 1;
                }
            }
        } else {
            if (node->parent == NULL) {
                node->entry = node->left->entry;
                node->left = node->left->left;
                node->right = node->left->right;
                return 1;
            } else {
                if (node->parent->left == node){
                    node->parent->left = node->left;
                    node->left->parent = node->parent;
                    return 1;
                } else {
                    node->parent->right = node->left;
                    node->left->parent = node->parent;
                    return 1;
                }
            }
        }
    }
}

int symtab_remove(symtab *self, char *key){
    symtab *node = tree_lookup(self, key);
    if (!node){
        // printTree(self);
        // printf("lookup failed, %s\n", key);
        return 0;
    }

    if (!node_remove(node)){
        return 0;
    } else {
        return 1;
    }
}
