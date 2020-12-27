#include "CodeOptimizer.hpp"

using namespace Compiler;

CodeOptimizer::CodeOptimizer()
{}

CodeOptimizer::~CodeOptimizer()
{}

CodeOptimizer::CodeOptimizer(std::vector<Instruction> &codes) :
    m_codes ( codes ),
    m_blocks (),
    m_entry ( nullptr )
{
    m_entry = new Instruction();
    m_entry->m_prev_ins = nullptr;
    divide_code_to_blocks(codes);
}

void CodeOptimizer::divide_code_to_blocks(std::vector<Instruction> &codes)
{
    int len = codes.size();
    // int block_start = -1;

    m_entry->m_next_ins = &codes[0];
    for (int i = 1; i < len; ++ i) {
        Instruction *ins_ptr = &codes[i];

        codes[i].m_prev_ins = &codes[i - 1];
        codes[i].m_next_ins = (i < len - 1) ? &codes[i + 1] : nullptr;
    }
    codes[0].m_prev_ins = m_entry;
    codes[0].m_next_ins = (len > 1) ? &codes[1] : nullptr;

    Instruction *block_start = m_entry->m_next_ins;
    Instruction *block_end;

    while (block_start != nullptr) {
        block_end = block_start->m_next_ins;

        while(true) {
            std::cout << block_end << std::endl;
            if (block_end->m_opType == OpType::FUNC || block_end->m_opType == OpType::LABEL)
            {
                break;
            } 
            else if (block_end->m_opType == OpType::J_RELOP || block_end->m_opType == OpType::JUMP || block_end->m_opType == OpType::RET)
            {
                block_end = block_end->m_next_ins;
                break;
            }
            block_end = block_end->m_next_ins;
        }
        m_blocks.push_back(std::make_pair(block_start, block_end));
        block_start = block_end;
    }
}

int CodeOptimizer::check_var_reassign(Instruction *ins, V target)
{
    int reassign = 0;
    switch (ins->m_opType)
    {
        case OpType::ASSI :
        case OpType::MUL :
        case OpType::DIV :
        case OpType::PLUS :
        case OpType::MINUS :
        case OpType::READ :
        case OpType::PARAM :
        {
            if (ins->m_result.index() == 1 && std::get<V>(ins->m_result) == target)
            {
                reassign = 1;
            }
            break;
        }
    }
    return reassign;
}

int CodeOptimizer::check_var_in_instruction(Instruction *ins, V v)
{
    int used = 0;
    switch (ins->m_opType)
    {
        case OpType::ASSI :
        {
            if (ins->m_arg1.index() == 1 && std::get<V>(ins->m_arg1) == v)
            {
                used = 1;
            }
            break;
        }
        case OpType::MUL :
        case OpType::DIV :
        case OpType::PLUS :
        case OpType::MINUS :
        case OpType::J_RELOP :
        {
            if (ins->m_arg1.index() == 1 && std::get<V>(ins->m_arg1) == v)
            {
                used = 1;
            }

            if (ins->m_arg2.index() == 1 && std::get<V>(ins->m_arg2) == v)
            {
                used = 1;
            }
            break;
        }
        case OpType::WRITE :
        case OpType::ARG :
        case OpType::RET :
        {
            if (ins->m_result.index() == 1 && std::get<V>(ins->m_result) == v)
            {
                used = 1;
            }
            break;
        }
    }
    return used;
}

int CodeOptimizer::check_var_is_used(Instruction *ins, V target) 
{
    Instruction *ptr = ins;
    int used = 0;
    while (ptr != nullptr) {
        if (check_var_reassign(ptr, target) == 1) 
        {
            if (check_var_in_instruction(ptr, target) == 1) {
                used = 1;
                break;
            }
            break;
        }

        if (check_var_in_instruction(ptr, target) == 1) {
            used = 1;
            break;
        }
        ptr = ptr->m_next_ins;
    }
    if (used == 0) {
        ptr = m_entry->m_next_ins;
        while (ptr != ins) {
            // if (check_var_reassign(ptr, target) == 1) 
            // {
            //     if (check_var_in_instruction(ptr, target) == 1) {
            //         used = 1;
            //         break;
            //     }
            //     break;
            // }

            if (check_var_in_instruction(ptr, target) == 1) {
                used = 1;
                break;
            }
            ptr = ptr->m_next_ins;
        }
    }
    return used;
}

void CodeOptimizer::dead_code_elimination(Instruction *ins)
{
    Instruction *ptr = ins;
    while (ptr != nullptr) {
        Instruction *i = find_copy(ptr, nullptr);
        if (i == nullptr) {
            return;
        }
        V v = std::get<V>(i->m_result);
        int used = check_var_is_used(i->m_next_ins, v);
        if (used == 0) {
            i->m_prev_ins->m_next_ins = i->m_next_ins;
            if (i->m_next_ins != nullptr) {
                i->m_next_ins->m_prev_ins = i->m_prev_ins;
            }
        }
        ptr = i->m_next_ins;
    }
}

void CodeOptimizer::replace_label(Instruction *head, Label ori, Label target)
{
    Instruction *ptr = head;
    while (ptr != nullptr) {
        if (ptr->m_opType == OpType::JUMP || ptr->m_opType == OpType::J_RELOP) 
        {
            std::cout << "ori " << ori.m_labelName << " " << std::get<Label>(ptr->m_result).m_labelName << std::endl;
            if (std::get<Label>(ptr->m_result) == ori) {
                std::cout << "  target to replace " << target.m_labelName << " " << target.m_count << std::endl;
                ptr->m_result = std::variant<Label, V, std::string, int>(target);
                ptr->m_instruction = ptr->to_string();
            }
        }
        ptr = ptr->m_next_ins;
    }
}

void CodeOptimizer::redundant_label_elimination(Instruction *ins) 
{
    Instruction *ptr = ins;
    while (ptr != nullptr) {
        int redundant = 0;
        Label l1;
        std::vector<Instruction *> redundant_labels_ins;
        std::vector<Label> redundant_labels;
        if (ptr->m_opType == OpType::LABEL) {
            l1 = Label(std::get<std::string>(ptr->m_result));
            redundant_labels.push_back(l1);
            redundant_labels_ins.push_back(ptr);
            ptr = ptr->m_next_ins;
            while (ptr != nullptr && ptr->m_opType == OpType::LABEL) {
                redundant_labels_ins.push_back(ptr);
                redundant_labels.push_back(Label(std::get<std::string>(ptr->m_result)));
                ptr = ptr->m_next_ins;
            }

            if (redundant_labels.size() != 1) {
                for (int i = 1; i < redundant_labels.size(); ++ i) {
                    Instruction *p = redundant_labels_ins[i];
                    replace_label(m_entry->m_next_ins, redundant_labels[i], l1);
                    p->m_prev_ins->m_next_ins = p->m_next_ins;
                    if (p->m_next_ins != nullptr) {
                        p->m_next_ins->m_prev_ins = p->m_prev_ins;
                    }
                }
            }
        }
        if (ptr != nullptr)
            ptr = ptr->m_next_ins;
    }
}

void CodeOptimizer::optimize_block(Instruction *start, Instruction *end) 
{
    Instruction *ptr = start;
    Instruction *copy_ins = find_copy(ptr, end);;
    while (copy_ins != nullptr && copy_ins != end) {
        // std::cout << "ASSI to be propagate " << copy_ins->m_instruction <<std::endl;
        V v = std::get<V>(copy_ins->m_result);
        std::variant<Label, V, std::string, int> v_target = variant_cast(copy_ins->m_arg1);
        Instruction *v_end = get_v_scope(v, copy_ins->m_next_ins, end);
        // std::cout << "  start: " << copy_ins->m_next_ins->m_instruction << std::endl;
        // std::cout << "  end: " << v_end->m_instruction << std::endl;
        copy_propagation(copy_ins->m_next_ins, v_end, v, v_target);
        ptr = copy_ins->m_next_ins;
        copy_ins = find_copy(ptr, end);
    }
}

void CodeOptimizer::optimize()
{
    int len = m_blocks.size();
    for (int i = 0; i < len; ++ i) {
        auto pair = m_blocks[i];
        Instruction *start = pair.first;
        Instruction *end = pair.second;
        Instruction *ptr = start;
        std::cout << "block " << i << " original code " << std::endl;
        while (ptr != end) {
            std::cout << ptr->m_instruction << std::endl;
            ptr = ptr->m_next_ins;
        }
        std::cout << std::endl;
        ptr = start;
        optimize_block(ptr, end);
        std::cout << "block " << i << " after copy propagate" << std::endl;
        while (ptr != end) {
            std::cout << ptr->m_instruction << std::endl;
            ptr = ptr->m_next_ins;
        }
        std::cout << std::endl;

    }
    Instruction *ptr = m_entry->m_next_ins;
    dead_code_elimination(ptr);
    std::cout << " after dead code eliminate" << std::endl;
    while (ptr != nullptr) {
        std::cout << ptr->m_instruction << std::endl;
        ptr = ptr->m_next_ins;
    }
    std::cout << std::endl;
    ptr = m_entry->m_next_ins;
    redundant_label_elimination(ptr);
    // std::cout << " after dead code eliminate" << std::endl;
    // while (ptr != nullptr) {
    //     std::cout << ptr->m_instruction << std::endl;
    //     ptr = ptr->m_next_ins;
    // }
    // std::cout << std::endl;
}

Instruction *CodeOptimizer::find_copy(Instruction *start, Instruction *end) 
{
    while (start != end) {
        if (start->m_opType == OpType::ASSI) {
            return start;
        }
        start = start->m_next_ins;
    }
    return end;
}

Instruction *CodeOptimizer::get_v_scope(V variable, Instruction *start, Instruction *end)
{
    while (start != end) {
        if (start->m_opType == OpType::MINUS || 
            start->m_opType == OpType::PLUS ||
            start->m_opType == OpType::MUL ||
            start->m_opType == OpType::DIV ||
            start->m_opType == OpType::ASSI)
        {
            if (start->m_result.index() == 1 && std::get<V>(start->m_result) == variable) {
                return start;
            }
        }
        start = start->m_next_ins;
    }
    return end;
}

// end should before the variable being changed : ASSI READ
void CodeOptimizer::copy_propagation(Instruction *start, Instruction *end, V variable, std::variant<Label, V, std::string, int> target)
{
    int target_is_V;
    target_is_V = (target.index() == 1) ? 1 : 0;
    int t_value;
    V t_v;
    if (target_is_V) {
        t_v = std::get<V>(target);
    } else {
        t_value = std::get<int>(target);
    }

    while (start != end) {
        // std::cout << start->m_instruction << std::endl;


        if (start->m_opType == OpType::RET || 
            start->m_opType == OpType::ARG || 
            start->m_opType == OpType::WRITE)
        {
            if (start->m_result.index() == 1 && std::get<V>(start->m_result) == variable) 
            {
                // std::cout << "writeRetArg " << target_is_V << std::endl;
                if (target_is_V) {
                    start->m_result = std::variant<Label, V, std::string, int>(t_v);
                    // std::cout << "  " << std::variant<Label, V, std::string, int>(t_v).index() << std::endl;
                } else {
                    start->m_result = std::variant<Label, V, std::string, int>(t_value);
                    // std::cout << "  " << std::variant<Label, V, std::string, int>(t_value).index() << std::endl;
                }
                start->m_instruction = start->to_string();
            }
        }

        if (start->m_opType == OpType::ASSI)
        {
            if (start->m_arg1.index() == 1 && std::get<V>(start->m_arg1) == variable) 
            {
                if (target_is_V) {
                    start->m_arg1 = std::variant<int, V>(t_v);
                } else {
                    start->m_arg1 = std::variant<int, V>(t_value);
                }
                start->m_instruction = start->to_string();
            }
        }
        if (start->m_opType == OpType::MINUS || 
            start->m_opType == OpType::PLUS ||
            start->m_opType == OpType::MUL ||
            start->m_opType == OpType::DIV ||
            start->m_opType == OpType::J_RELOP)
        {
            if (start->m_arg1.index() == 1 && std::get<V>(start->m_arg1) == variable) 
            {
                if (target_is_V) {
                    start->m_arg1 = std::variant<int, V>(t_v);
                } else {
                    start->m_arg1 = std::variant<int, V>(t_value);
                }
                start->m_instruction = start->to_string();
            }

            if (start->m_arg2.index() == 1 && std::get<V>(start->m_arg2) == variable) 
            {
                if (target_is_V) {
                    start->m_arg2 = std::variant<int, V>(t_v);
                } else {
                    start->m_arg2 = std::variant<int, V>(t_value);
                }
                start->m_instruction = start->to_string();
            }
        }

        if (check_var_reassign(start, variable) == 1) 
        {
            std::cout << "variable (lvalue) has been changed, stop propagate" << std::endl;
            break;
        }
        if (target_is_V && check_var_reassign(start, t_v)) 
        {
            std::cout << "rvalue has been changed, stop propagate" << std::endl;
            break;
        }
        start = start->m_next_ins;
    }
}

void CodeOptimizer::print_blocks() {
    int len = m_blocks.size();
    for (int i = 0; i < len; ++ i) {
        auto pair = m_blocks[i];
        Instruction *start = pair.first;
        Instruction *end = pair.second;
        std::cout << "block" << std::endl;
        while (start != end) {
            std::cout << start->m_instruction << std::endl;
            start = start->m_next_ins;
        }
        std::cout << std::endl;
    }
}