/*

  The MIT License (MIT)

  Copyright (c) 2015 VISUEM LTD

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

*/

#include "instruction.h"
#include "register.h"
#include <assert>
using namespace armvm;

Instruction::Instruction()
{

}

Instruction::~Instruction()
{

}

const Instruction::OperationType Instruction::GetOperationType() const
{
    return mOperation->type;
}

const Instruction::Condition Instruction::GetCondition() const
{
    return mOperation->condition;
}

const bool Instruction::ShouldUpdateFlags() const
{
    return mOperation->set_flags;
}

const Instruction::OperandType Instruction::GetOperandType(const unsigned int index) const
{
    assert(index < 4 && "Operand index cannot be greater than 3");
    return mOperands[index].type;
}

const int32_t Instruction::GetOperandValue(const unsigned int index) const
{
    assert(index < 4 && "Operand index cannot be greater than 3");
    return mOperands[index].value;
}

Instruction::OperationMap Instruction::OperationLookup::Init()
{
    const struct
    {
        OperationType type;
        const char* name;
        bool set_flags_variants;
        bool condition_variants;
    } operation_meta[] =
    {
        {OP_MOV,    "MOV",    true,   true},
        {OP_MVN,    "MVN",    true,   true},
        {OP_AND,    "AND",    true,   true},
        {OP_ORR,    "ORR",    true,   true},
        {OP_EOR,    "EOR",    true,   true},
        {OP_BIC,    "BIC",    true,   true},
        {OP_ADD,    "ADD",    true,   true},
        {OP_SUB,    "SUB",    true,   true},
        {OP_RSB,    "RSB",    true,   true},
        {OP_ADC,    "ADC",    true,   true},
        {OP_SBC,    "SBC",    true,   true},
        {OP_RSC,    "RSC",    true,   true},
        {OP_CMP,    "CMP",    false,  true},
        {OP_CMN,    "CMN",    false,  true},
        {OP_TST,    "TST",    false,  true},
        {OP_TEQ,    "TEQ",    false,  true},
        {OP_MUL,    "MUL",    true,   true},
        {OP_MLA,    "MLA",    false,  true},
        {OP_MLA,    "MLA",    false,  true},
        {OP_B,      "B",      false,  true},
        {OP_BL,     "BL",     false,  true},
        {OP_BX,     "BX",     false,  true},
        {OP_LDR,    "LDR",    false,  true},
        {OP_STR,    "STR",    false,  true},
        {OP_NOP,    "NOP",    false,  false}
    };

    const char* cond[] = {"", "EQ", "NE", "CS", "HS", "CC", "LO", "MI", 
                          "PL", "VS", "VC", "HI", "LS", "GE", "LT", "GT",
                          "LE", "AL"};

    int condition_count = sizeof(cond)/ sizeof(const char*);

    OperationMap o_map;

    for (int i = 0; i < int(CONDITION_COUNT); i++)
    {
        for (int j = 0; j < int(OPERATION_TYPE_COUNT); j++)
        {
            if (operation_meta[j].condition_variants || i == 0)
            {
                std::string op = std::string() + operation_meta[j].name + cond[i];
                o_map[op] = std::make_shared<const Operation>(OperationType(j), 
                                                              false, 
                                                              Condition(i));
                if (operation_meta[j].set_flags_variants)
                    o_map[op + "S"] = std::make_shared<const Operation>(OperationType(j), 
                                                                        true,
                                                                        Condition(i));
            }
        }
    }
    return o_map;
}

const Instruction::OperationMap Instruction::OperationLookup::prototypes = Instruction::OperationLookup::Init();
