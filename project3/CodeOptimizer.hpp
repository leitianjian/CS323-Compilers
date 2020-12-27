#ifndef CODE_OPTIMIZER_H
#define CODE_OPTIMIZER_H

#include <vector>
#include <iostream>
// #include

#include "instruction.h"

namespace Compiler
{
class CodeOptimizer
{
public:
    std::vector<Instruction> m_codes;
    std::vector<std::pair<Instruction *,Instruction *>> m_blocks;
    Instruction *m_entry;
    
    CodeOptimizer();
    ~CodeOptimizer();
    CodeOptimizer(std::vector<Instruction> &codes);
    void divide_code_to_blocks(std::vector<Instruction> &codes);
    void optimize();
    void optimize_block(Instruction *block_start, Instruction *block_end);
    Instruction *find_copy(Instruction *block_start, Instruction *block_end);
    Instruction *get_v_scope(V variable, Instruction *start, Instruction *end);
    void copy_propagation(Instruction *start, Instruction *end, V variable, std::variant<Label, V, std::string, int> target);
    void global_optimize(Instruction *head);
    void dead_code_elimination(Instruction *head);
    int check_var_is_used(Instruction *ins, V v);
    int check_var_reassign(Instruction *ins, V v);
    int check_var_in_instruction(Instruction *ins, V v);
    void redundant_label_elimination(Instruction *head);
    void replace_label(Instruction *head, Label ori, Label target);

    void print_blocks();
};
}

#endif