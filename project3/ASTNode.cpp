#include <string>
#include <iostream>
#include <cstring>
#include <cstdarg>
#include <fstream>
#include <sstream>

#include "ASTNode.h"

using namespace Compiler;

ASTNode::ASTNode(const std::string &type, const std::string &value, int terminal, int row) :
    m_type ( type ),
    m_value ( value ),
    m_terminal ( terminal ),
    m_row ( row )
{}

ASTNode::ASTNode(const std::string &type, const std::string &value) :
    m_type ( type ),
    m_value ( value ),
    m_terminal ( 1 ),
    m_row ( 0 )
{ 
    std::cout << "Initial terminal node with type=[" << type << "] value=[" << value << "\n"; 
}

ASTNode::ASTNode(const std::string &type, int row) :
    m_type ( type ),
    m_value ( "" ),
    m_terminal ( 0 ),
    m_row ( row )
{
    std::cout << "Initial non-terminal node with type=[" << type << "] at row: " << row << "\n";
}

ASTNode::ASTNode(const std::string &type) :
    m_type ( type ),
    m_value ( "" ),
    m_terminal ( 2 ),
    m_row ( 0 )
{
    std::cout << "Initial terminal node with type=[" << type << "]" << std::endl;
}

ASTNode::ASTNode() :
    m_type ( "" ),
    m_value ( "" ),
    m_terminal ( 2 ),
    m_row ( 0 )
{}

ASTNode::~ASTNode()
{}

void ASTNode::addChild(int count, ...)
{
    if (m_terminal == 1) {
        std::cout << "terminal node with type=[" << m_type << "], value=[" << m_value << "]" << std::endl;
    } else {
        std::cout << count;
        std::cout << "non-terminal node with type=[" << m_type << "] at row: " << m_row << std::endl;
    }
    va_list list;
    va_start(list, count);
    ASTNode *node_ptr = this->m_child;
    int i = 0;
    while(node_ptr != nullptr && node_ptr->m_sibling != nullptr)
        node_ptr = node_ptr->m_sibling;

    if(node_ptr == nullptr) {
        this->m_child = va_arg(list, ASTNode *);
        this->m_childCount = 1;
        node_ptr = this->m_child;
        i = 1;
    }
    for(; i < count; ++ i) {
        node_ptr->m_sibling = va_arg(list, ASTNode *);
        node_ptr = node_ptr->m_sibling;
        ++this->m_childCount;
    }
}

std::string ASTNode::str(int level)
{
    std::stringstream s;
    // TODO: 这里好像有问题
    if(this->m_type != "NONE"){
        if(this->m_terminal == 1) {
            // printf("%*s%s: %s\n", count, "", node->type, node->value);
            // fprintf(out, "%*s%s: %s\n", level, "", node.m_type, node.m_value);
            s << std::string(level, ' ') << this->m_type << ": " << this->m_value << "\n";
        } else if (this->m_terminal == 0) {
            // printf("%*s%s (%d)\n", count, "", node->type, node->row);
            if (this->m_childCount != 0) {
                s << std::string(level, ' ') << this->m_type << " (" << this->m_row << ")\n";
            }
            // fprintf(out, "%*s%s (%d)\n", level, "", node.m_type, node.m_row);
        } else {
            // printf("%*s%s\n", count, "", node->type);
            // fprintf(out, "%*s%s\n", level, "", node.m_type);
            s << std::string(level, ' ') << this->m_type << "\n";
        }
    }
    return s.str();
}

std::string dfsPrint(ASTNode *root, int level)
{   
    std::stringstream s;
    if(root == nullptr)
        return "";
    s << root->str(level);
    s << dfsPrint(root->m_child, level + 2);
    s << dfsPrint(root->m_sibling, level);
    return s.str();
}

// int test_function (ASTNode* n1, ASTNode* n2) {

// }
// int main() {
    // ASTNode root("INT", 10);
    // ASTNode n1("INT", "hello1");
    // ASTNode n2("INT", "hello2");
    // ASTNode n3("INT", 11);
    // ASTNode n4("INT", "hello4");
    // root.addChild(4, &n1, &n2, &n3, &n4);
    // ASTNode n5("INT", "hello5");
    // ASTNode n6("INT", "hello6");
    // ASTNode n7("INT", "hello7");
    // ASTNode n8("INT", "hello8");
    // n3.addChild(4, &n5, &n6, &n7, &n8);
    // std::cout << dfsPrint(&root, 0);
    // std::cout << dfsPrint(&n1, 0);
    // std::cout << dfsPrint(&n2, 0);
    // std::cout << dfsPrint(&n3, 0);
    // std::cout << dfsPrint(&n4, 0);
    // std::cout << dfsPrint(&n5, 0);
    // std::cout << dfsPrint(&n6, 0);
    // std::cout << dfsPrint(&n7, 0);

    // ASTNode *root = new ASTNode("INT", 0);
    // test_function(root, new ASTNode("Int", 10));
// }

