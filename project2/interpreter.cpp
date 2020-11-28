#include <sstream>
#include <iostream>

#include "interpreter.h"
#include "ASTNode.h"
#include "location.hh"

using namespace Compiler;

Interpreter::Interpreter() :
    m_rootNode(nullptr),
    m_scanner(*this),
    m_parser(m_scanner, *this),
    m_location(Compiler::location(nullptr, 1, 1)),
    m_errorMsg(std::string(""))
{}

int Interpreter::parse() {
    m_location.initialize();
    return m_parser.parse();
}

void Interpreter::clear() {
    m_error = 0;
    m_errorMsg.clear();
    m_location.initialize();
    clearTreeByNode(m_rootNode);
    m_rootNode = nullptr;
}

void Interpreter::clearTreeByNode(ASTNode *node) {
    if (node == nullptr) 
        return;
    
    clearTreeByNode(node->m_sibling);
    clearTreeByNode(node->m_child);
    delete node;
    node = nullptr;
    return;
}

std::string Interpreter::str() const {
    std::stringstream s;
    s << strTree(m_rootNode, 0);
    return s.str();
}

std::string Interpreter::strTree(ASTNode *node, int level) const {
    std::stringstream s;
    if (node == nullptr)
        return "";

    s << (node->str(level));    
    s << strTree(node->m_child, level + 2);
    s << strTree(node->m_sibling, level);
    return s.str();
}

void Interpreter::switchInputStream(std::istream *is) {
    m_scanner.switch_streams(is, NULL);
    this->clear();    
}

void Interpreter::switchIOStream(std::istream *is, std::ostream *os) {
    m_scanner.switch_streams(is, os);
    this->clear();
}

void Interpreter::setRoot(ASTNode *root)
{
    m_rootNode = root;
}

void Interpreter::setErrorFlag()
{
    m_error = 1;
}

void Interpreter::appendErrorMsg(int type, const std::string &err_str, int lineno)
{
    std::stringstream ss;
    if (type == 0) {
        ss << "Error type A at Line " << lineno << ": unknown lexeme " << err_str << std::endl;
    } else {
        ss << "Error type B at Line " << lineno << ": " << err_str << std::endl;
    }
    m_errorMsg += ss.str();
}

const std::string &Interpreter::errorMsg() const {
    return m_errorMsg;
}

const int &Interpreter::errorFlag() const {
    return m_error;
}
// void Interpreter::increaseLocation(unsigned int loc) {
//     m_location += loc;
//     cout << "increaseLocation(): " << loc << ", total = " << m_location << endl;
// }

// const location &Interpreter::location() {
//     return m_location;
// }
