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

#include "register.h"
using namespace armvm;

RegisterBank::RegisterBank()
: mPSR(0)
{
}

RegisterBank::~RegisterBank()
{
}

const int32_t RegisterBank::operator[] (const RegisterBank::Register reg) const
{
    return mRegisters[reg];
}

const int32_t RegisterBank::Load(const RegisterBank::Register reg) const
{
    return mRegisters[reg];
}

void RegisterBank::Store(const RegisterBank::Register reg, const int32_t value)
{
    mRegisters[reg] = value;
}

void RegisterBank::SetFlags(const bool set, const int32_t mask)
{
    mPSR = value?(mPSR & ~mask):(mPSR | mask);
}

const bool RegisterBank::GetFlag(const RegisterBank::ConditionFlag flag) const
{
    return (mPSR & flag);
}

const int32_t RegisterBank::GetFlags() const
{
    return mPSR & 0xF;
}

const bool RegisterBank::TestCondition(const Instruction::Condition condition) const
{
    switch (condition)
    {
        case CD_NONE:
        case CD_AL:
            return true;
        case CD_EQ:
            return mPSR & ZERO;
        case CD_NE:
            return !(mPSR & ZERO);
        case CD_CS:
        case CD_HS:
            return mPSR & CARRY;
        case CD_CC:
        case CD_LO:
            return !(mPSR & CARRY);
        case CD_MI:
            return mPSR & NEGATIVE;
        case CD_PL:
            return !(mPSR & NEGATIVE);
        case CD_VS:
            return mPSR & OVERFLOW;
        case CD_VC:
            return !(mPSR & OVERFLOW);
        case CD_HI:
            return (mPSR & CARRY) && !(mPSR & ZERO);
        case CD_LS:
            return !(mPSR & CARRY) && (mPSR & ZERO);
        case CD_GE:
            return (mPSR & NEGATIVE > 0) == (mPSR & OVERFLOW > 0);
        case CD_LT:
            return (mPSR & NEGATIVE > 0) != (mPSR & OVERFLOW > 0);
        case CD_GT:
            return !(mPSR & ZERO) && ((mPSR & NEGATIVE > 0) == (mPSR & OVERFLOW > 0));
        case CD_LE:
            return (mPSR & ZERO) && ((mPSR & NEGATIVE > 0) != (mPSR & OVERFLOW > 0));
        default:
            return false;
    }
}
