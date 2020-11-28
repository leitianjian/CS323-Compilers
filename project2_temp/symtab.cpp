#include <iostream>
#include <string>
#include <unordered_map>

class ScopedSymbolTable {
 public:
    std::unordered_map<std::string, std::string> symTab;
    int scope_depth;
    ScopedSymbolTable *enclosing_scope;
    
    ScopedSymbolTable(int depth, ScopedSymbolTable *enclosing_scope) : 
        scope_depth(depth), enclosing_scope(enclosing_scope) {}
    // void insert
};