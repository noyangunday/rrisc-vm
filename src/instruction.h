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

/*
 *    author:    noyan gunday
 *    date:      01/08/2015
 */

#ifndef __NARMVM_INSTRUCTION_H__
#define __NARMVM_INSTRUCTION_H__

#include <string>
#include <shared_ptr>
#include <unordered_map>

namespace narmvm
{

/**
 * @brief ARM instruction implementation
 */
class Instruction
{
    public:

    /**
     * @brief Supported operations
     */
    enum OperationType
    {
        MOV,               /* Move register or constant */
        MVN,               /* Move negative register */
        AND,               /* Logical AND */
        ORR,               /* Negative or */
        EOR,               /* Exclusive OR */
        BIC,               /* Bit clear */
        ADD,               /* Add */
        SUB,               /* Subtract */
        RSB,               /* Reverse subtract */
        ADC,               /* Add with carry */
        SBC,               /* Subtract with carry */
        RSC,               /* Reverse subtract with carry */
        CMP,               /* Compare */
        CMN,               /* Compare negative */
        TST,               /* Test bits */
        TEQ,               /* Test bitwise equality */
        MUL,               /* Multiply */
        MLA,               /* Multiply accumulate */
        MLS,               /* Multiply with subtract */
        B,                 /* Branch */
        BL,                /* Branch with link */
        BX,                /* Branch and exchange */
        LDR,               /* Load register from memory */
        STR,               /* Store register to memory */
        NOP,               /* No operation */
        OPERATION_TYPE_COUNT
    };

    /**
     * @brief Conditional execution suffixes
     */
    enum Condition
    {
        NONE,               /* no condition suffix */
        EQ,                 /* Equal */
        NE,                 /* Not Equal */
        CS,                 /* Carry set */
        HS,                 /* Unsigned higher or same */
        CC,                 /* Carry clear */
        LO,                 /* Unsigned lower */
        MI,                 /* Negative */
        PL,                 /* Positive or zero */
        VS,                 /* Overflow */
        VC,                 /* No overflow */
        HI,                 /* Unsigned higher */
        LS,                 /* Unsigned lower or same */
        GE,                 /* Signed grater than or equal */
        LT,                 /* Signed less than */
        GT,                 /* Signed greater than */
        LE,                 /* Signed less than or equal */
        AL,                 /* Always */
        CONDITION_COUNT
    };

    /**
     * @brief Types of operands
     */
    enum OperandType
    {
        REGISTER,          /* Read value from a register */
        IMMEDIATE,         /* Immediate valie */
        MEMORY,            /* Read value from a memory location */
        LABEL              /* Decode memory location from label */
    };

    public:

    /**
     * @brief Default constructor
     */
    Instruction();
    
    /**
     * @brief Destructor
     */
    ~Instruction();

    /**
     * @brief Get the type of operation
     * @return Operation type
     */
    const OperationType GetOperationType() const;

    /**
     * @brief Get the conditional execution suffix of this instruction
     * @return Conditional execution suffix
     */
    const Condition GetCondition() const;

    /**
     * @brief Should this instruction update PSR flags
     * @return Update flag
     */
    const bool ShouldUpdateFlags() const;

    /**
     * @brief Get the type of an operand
     * @param[in] index Index of the operand
     * @return Type of the operand stored in the given index
     */
    const OperandType GetOperandType(const int index) const;

    /**
     * @brief Get the value of an operand
     * @param[in] index Index of the operand
     * @return Value of the operand stored in the given index
     */
    const int32_t GetOperandValue(const int index) const;

    private:

    /**
     * @brief Operation paramters
     */
    struct Operation
    {
        OperationType   type;
        Condition       condition;
        bool            set_flags;
    };

    typedef std::unordered_map<std::string, std::shared_ptr<const Operation> > OperationMap;

    /**
     * @brief A lookup table for supported instruction prototypes 
     *        (including set flags and condition combinations)
     */
    struct OperationLookup
    {
        static const OperationMap prototypes;

        /**
         * @brief Initializes prototypes
         */
        static OperationMap Init();
    };

    /**
     * @brief Operands of instruction
     */
    struct Operand
    {
        OperandType     type;
        int32_t         value;
    }                                   mOperands[4];
    std::shared_ptr<const Operation>    mOperation;
};

}

#endif
