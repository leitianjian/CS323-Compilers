#include <string>
#include <iostream>
#include <cstring>
#include <cstdarg>
#include <fstream>
#include <sstream>
#include <variant>

#include "SymTab.h"

using namespace Compiler;

/**
 * Variable node implement section
*/
Variable::Variable ()
{}

Variable::Variable (std::string &name, DataType::Type type):
    m_type ( type ),
    m_name ( name ),
    m_dimension ( 0 ),
    m_eleType ( type ),
    m_size ( ),
    m_structName ( )
{}

Variable::Variable (std::string &name, std::string &structName):
    m_type ( DataType::STRUCTURE ),
    m_name ( name ),
    m_structName ( structName ),
    m_dimension ( 0 ),
    m_eleType ( DataType::STRUCTURE ),
    m_size ( )
{}

Variable::Variable (int dimension, std::vector<int> &size, std::string &name, DataType::Type eleType):
    m_dimension ( dimension ),
    m_size ( size ),
    m_name ( name ),
    m_eleType ( eleType ),
    m_structName ( )
{
    if (dimension != 0) {
        m_type = DataType::ARRAY;
    } else {
        m_type = eleType;
    }
}

Variable::Variable (int dimension, std::vector<int> &size, std::string &name, std::string &structName):
    m_dimension ( dimension ),
    m_size ( size ),
    m_name ( name ),
    m_structName ( structName ),
    m_eleType ( DataType::STRUCTURE )
{
    if (dimension != 0) {
        m_type = DataType::ARRAY;
    } else {
        m_type = DataType::STRUCTURE;
    }
}

Variable::~Variable ()
{}

/**
 * Function node implement section
*/
Function::Function ()
{}

Function::Function (std::string &name, DataType::Type retType, std::string &structName, std::vector<Variable> &params):
    m_name ( name ),
    m_retType ( retType ),
    m_structName ( structName ),
    m_params ( params )
{}

Function::~Function ()
{}

/**
 * Structure node implement section
*/
Structure::Structure ()
{}

Structure::Structure(std::string &name): 
    m_name ( name ),
    m_symTab ( nullptr )
    // m_decList ( )
{}

Structure::Structure(std::string &name, SymTab *selfSymTab):
    m_name ( name ),
    m_symTab ( selfSymTab )
{}

Structure::~Structure ()
{}

/**
 * Array node implement section
*/
Array::Array ()
{}

Array::Array(std::string &name, DataType::Type ele_type, int len):
    m_name ( name ),
    m_elementType ( ele_type ),
    m_len ( len )
{}

Array::~Array ()
{}

/**
 * Symbol Table entry implement section
*/
VAL_T::VAL_T ()
{}

VAL_T::VAL_T (EntryType::Type valType, std::variant<Structure, Variable, Function> &val):
    m_valType ( valType ),
    m_val ( val )
{}

VAL_T::VAL_T(EntryType::Type valType, Structure &s):
    m_valType ( valType ),
    m_val ( s )
{}

VAL_T::VAL_T(EntryType::Type valType, Variable &v):
    m_valType ( valType ),
    m_val ( v )
{}

VAL_T::VAL_T(EntryType::Type valType, Function &f):
    m_valType ( valType ),
    m_val ( f )
{}

int VAL_T::compare (VAL_T &val)
{
    if (m_valType == val.m_valType && m_val.index() == val.m_val.index()) {
        return 0;
    } else {
        return 1;
    }
}

DataType::Type VAL_T::getType()
{
    if (m_valType == EntryType::VARIABLE) {
        Variable v = std::get<Variable>(m_val);
        return v.m_type;
    } else if (m_valType == EntryType::STRUCTURE) {
        return DataType::STRUCTURE;
    }
}

VAL_T::~VAL_T ()
{}


/**
 * Symbol table implement section
*/
SymTab::SymTab ():
    m_table( ),
    m_scope_level( 0 ),
    m_scope_name( "" ),
    m_enclosing_scope( nullptr )
{}

SymTab::SymTab (int scope_level):
    m_table( ),
    m_scope_level( scope_level ),
    m_scope_name( "" ),
    m_enclosing_scope( nullptr )
{}

SymTab::SymTab (std::string &scope_name, int scope_level):
    m_table( ),
    m_scope_level( scope_level ),
    m_scope_name( scope_name ),
    m_enclosing_scope( nullptr )
{}

SymTab::SymTab (std::string &scope_name, int scope_level, SymTab *enclosing_scope):
    m_table( ),
    m_scope_level( scope_level ),
    m_scope_name( scope_name ),
    m_enclosing_scope( enclosing_scope )
{}

int SymTab::insert (std::string &key, VAL_T &val)
{
    std::cout << "trying to insert key=" << key << " to symbol table" << std::endl;
    m_table.insert_or_assign(key, val);
    return 1;
}

VAL_T *SymTab::lookup (std::string &key, int current_scope_only)
{
    if (m_table.find(key) != m_table.end()){
        return &m_table[key];
    } 

    if (current_scope_only == 1) {
        return nullptr;
    }
    
    if (m_enclosing_scope != nullptr) {
        return m_enclosing_scope->lookup(key, 0);
    }

    return nullptr;
}

int SymTab::remove (std::string &key)
{
    return m_table.erase(key);
}

int SymTab::registerVariables (std::vector<std::string> &keys, std::vector<Variable> &vals)
{
    int len = keys.size();
    for (int i = 0; i < len; ++ i) {
        std::cout << "register variable with key: " << keys[i] << " with type: " << vals[i].m_type << " at scope: " << m_scope_name << std::endl;
        VAL_T v(EntryType::VARIABLE, vals[i]);
        insert(keys[i], v);
    }
    return 1;
}

int SymTab::registerFunction (std::string &funcName, DataType::Type retType, std::string &structName, std::vector<Variable> &params)
{
    Function f(funcName, retType, structName, params);
    VAL_T v(EntryType::FUNCTION, f);
    std::string key = funcName;
    insert(key, v);
    return 1;
}

SymTab::~SymTab ()
{}
