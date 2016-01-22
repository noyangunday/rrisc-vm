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

#ifndef __NARMVM_REGISTER_H__
#define __NARMVM_REGISTER_H__

#include "instruction.h"

namespace narmvm
{

/**
 * @brief Arm register bank implementation
 */
class RegisterBank
{
    public:

    /**
     * @brief Available registers
     * @Note: LR, SP and PC are available as general purpose
     *        registers. (r13, r14, r15)
     */
    enum Register
    {
        R0 =  0x0,
        R1 =  0x1,
        R2 =  0x2,
        R3 =  0x3,
        R4 =  0x4,
        R5 =  0x5,
        R6 =  0x6,
        R7 =  0x7,
        R8 =  0x8,
        R9 =  0x9,
        R10 = 0xA,
        R11 = 0xB,
        R12 = 0xC,
        R13 = 0xD,
        R14 = 0xE,
        R15 = 0xF,
        LR =  0xD,
        SP =  0xE,
        PC =  0xF
    };

    /**
     * @brief Program state register bitmask values
     */
    enum ConditionFlag
    {
        NEGATIVE = 0x1,
        ZERO =     0x2,
        CARRY =    0x4,
        OVERFLOW = 0x8
    };

    public:

    /**
     * @brief Default constructor
     */
    RegisterBank();

    /**
     * @brief Destructor
     */
    ~RegisterBank();

    /**
     * @brief Subscript operator
     * @param[in] reg Source register
     * @return The value stored in the register
     */
    const int32_t operator[] (const Register reg) const;

    /**
     * @brief Read a value from the specified register
     * @param[in] reg Source register
     * @return The value stored in the register
     */
    const int32_t Load(const Register reg) const;

    /**
     * @brief Stores a value in the specified register
     * @param[in] reg Target register
     * @param[in] value Value to store
     */
    void Store(const Register reg, const int32_t value);

    /**
     * @brief Change PSR flags' states
     * @param[in] set New state of the specified flags.
     * @param[in] mask A bitmask that indicates the flags to change.
     */
    void SetFlags(const bool set, const int32_t mask);

    /**
     * @brief Get current state of the specified condition flag
     * @param[in] flag Flag to check
     * @return Current state of the condition flag
     */
    const bool GetFlag(const ConditionFlag flag) const;

    /**
     * @brief Get the current value of PSR
     * @return Value of program state register
     */
    const int32_t GetFlags() const;

    /**
     * @brief Test if the specified condition passes with the current PSR state
     * @param[in] condition Condition to test
     * @return Test result
     */
    const bool TestCondition(const Instruction::Condition condition) const;

    private:

    int32_t     mPSR;
    int32_t     mRegisters[16];

};

}

#endif
