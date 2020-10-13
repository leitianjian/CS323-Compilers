#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

FILE *out;

char *strcopy(char *str){
    char *dest = (char *)malloc(strlen(str));
    strcpy(dest, str);
    return dest;
}

typedef struct ASTNode
{
    char *value;
    char *type;
    int terminal;
    int row;
    int child_count;
    struct ASTNode *sibling;
    struct ASTNode *child;
} ASTNode;

ASTNode *init()
{
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    node->value = NULL;
    node->type = NULL;
    node->child_count = 0;
    node->terminal = 0;
    node->row = 0;
    node->sibling = NULL;
    node->child = NULL;
    return node;
}

ASTNode *new(char* type, char* value, int terminal, int row)
{
    ASTNode *node = init();
    node->type = type;
    node->value = value;
    node->terminal = terminal;
    node->row = row;
    return node;
}

ASTNode *newValueLeaf(char* type, char* value)
{
    return new(type, strcopy(value), 1, 0);
}

ASTNode *newNode(char* type, int row)
{
    return new(type, NULL, 0, row);
}

ASTNode *newKWLeaf(char* type)
{
    return new(type, NULL, 2, 0);
}

void addChild(ASTNode *parent, int count, ...)
{
    va_list list;
    va_start(list, count);
    ASTNode *node_ptr = parent->child;
    int i = 0;
    while(node_ptr != NULL && 
          node_ptr->sibling != NULL)
        node_ptr = node_ptr->sibling;

    if(node_ptr == NULL) {
        parent->child = va_arg(list, ASTNode *);
        parent->child_count = 1;
        node_ptr = parent->child;
        i = 1;
    }
    for(; i < count; ++ i) {
        node_ptr->sibling = va_arg(list, ASTNode *);
        node_ptr = node_ptr->sibling;
        ++parent->child_count;
    }
}

void printfNode(ASTNode *node, int count)
{
    if(node->type != "NONE"){
        if(node->terminal == 1) {
            // printf("%*s%s: %s\n", count, "", node->type, node->value);
            fprintf(out, "%*s%s: %s\n", count, "", node->type, node->value);
        } else if (node->terminal == 0) {
            // printf("%*s%s (%d)\n", count, "", node->type, node->row);
            fprintf(out, "%*s%s (%d)\n", count, "", node->type, node->row);
        } else {
            // printf("%*s%s\n", count, "", node->type);
            fprintf(out, "%*s%s\n", count, "", node->type);
        }
    }
}

void dfsPrint(ASTNode *node, int count)
{   
    if(node == NULL)
        return;
    printfNode(node, count);
    dfsPrint(node->child, count + 2);
    dfsPrint(node->sibling, count);
}
