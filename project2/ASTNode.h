#ifndef ASTNODE_H
#define ASTNODE_H
#include <string>
#include <cstring>
#include <cstdarg>
#include <fstream>

// std::ofstream out;
// FILE *out;

namespace Compiler {

class ASTNode
{
public:
    // char *value;
    // char *type;
    std::string m_type;
    std::string m_value;
    int m_terminal;
    int m_row;
    int m_childCount = 0;
    ASTNode *m_sibling = nullptr;
    ASTNode *m_child = nullptr;

    ASTNode(const std::string &type, const std::string &value, int terminal, int row);
    ASTNode(const std::string &type, const std::string &value);
    ASTNode(const std::string &type, int row);
    ASTNode(const std::string &type);
    ASTNode();
    ~ASTNode();

    void addChild(int count...);
    std::string str(int level);
    // static void dfsPrint(ASTNode *root, int level);
};

}
#endif