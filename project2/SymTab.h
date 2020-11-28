#ifndef SYMTAB_H
#define SYMTAB_H
#include <unordered_map>
#include <vector>
#include <variant>

namespace Compiler 
{
class VAL_T;
class SymTab;

struct DataType {
    typedef enum {
        INT, FLOAT, CHAR, ARRAY, STRUCTURE, UNKNOW 
    } Type;
};
struct EntryType {
    typedef enum {
        VARIABLE, STRUCTURE, FUNCTION
    } Type;
};
// enum DataType { INT, FLOAT, CHAR, ARRAY, STRUCTURE, UNKNOW };
// enum EntryType { VARIABLE, STRUCTURE, FUNCTION };

struct Variable 
{
    DataType::Type m_type;
    std::string m_structName;
    std::string m_name;
    int m_dimension;
    std::vector<int> m_size;
    DataType::Type m_eleType;

    Variable();
    ~Variable();
    Variable(std::string &name, DataType::Type type); // variable
    Variable(std::string &name, std::string &structName); // struct variable
    Variable(int dimension, std::vector<int> &size, std::string &name, DataType::Type eleType); // array
    Variable(int dimension, std::vector<int> &size, std::string &name, std::string &structName);
};

struct Function
{
    std::string m_name;
    DataType::Type m_retType;
    std::string m_structName;

    std::vector<Variable> m_params;

    Function();
    ~Function();
    Function(std::string &name, DataType::Type retType, std::string &structName, std::vector<Variable> &params);
};

struct Structure
{
    std::string m_name;

    SymTab *m_symTab;

    Structure();
    ~Structure();
    Structure(std::string &name);
    Structure(std::string &name, SymTab *selfSymTab);
};

struct Array
{
    std::string m_name;
    DataType::Type m_elementType;
    int m_len;

    Array();
    ~Array();
    Array(std::string &name, DataType::Type ele_type, int len);
};

class VAL_T
{
public:
    EntryType::Type m_valType;
    std::variant<Structure, Variable, Function> m_val;

    VAL_T();
    ~VAL_T();
    VAL_T(EntryType::Type valType, std::variant<Structure, Variable, Function> &val);
    VAL_T(EntryType::Type valType, Structure &s);
    VAL_T(EntryType::Type valType, Variable &v);
    VAL_T(EntryType::Type valType, Function &f);
    int compare(VAL_T &val);
    DataType::Type getType();
};

class SymTab 
{
public:
    std::unordered_map<std::string, VAL_T> m_table;
    std::string m_scope_name;
    int m_scope_level;
    SymTab *m_enclosing_scope;

    SymTab();
    ~SymTab();
    SymTab(int scope_level);
    SymTab(std::string &scope_name, int scope_level);
    SymTab(std::string &scope_name, int scope_level, SymTab *enclosing_scope);

    int insert(std::string &key, VAL_T &val);
    VAL_T *lookup(std::string &key, int current_scope_only);
    int remove(std::string &key);

    int registerVariables(std::vector<std::string> &keys, std::vector<Variable> &vals);
    int registerFunction(std::string &funcName, DataType::Type retType, std::string &structName, std::vector<Variable> &params);
};
}
#endif