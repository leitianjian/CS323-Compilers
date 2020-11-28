#include<string>
#include<iostream>
#include<cstring>
#include<cstdarg>
#include<fstream>

std::ofstream fout;

char *strcopy(char *str){
    char *dest = (char *)malloc(strlen(str));
    strcpy(dest, str);
    return dest;
}

struct ASTNode
{
    char *value;
    char *type;
    // std::string type;
    // std::string value;
    int terminal;
    int row;
    int child_count;
    ASTNode *sibling;
    ASTNode *child;

    ASTNode::ASTNode(char* type, char* value, int terminal, int row) {
        this->type = type;
        this->value = value;
        this->terminal = terminal;
        this->row = row;
    }

    ASTNode *newValueLeaf(char* type, char* value) {
        return &ASTNode(type, value, 1, 0);
    }
};