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

#include "processor.h"
#include <assert>
using namespace armvm;

Processor::Processor()
{
}

Processor::~Processor()
{
}

void Processor::ExecuteInstruction(const Instruction* instruction)
{
    assert(instruction && "Not a valid instruction.");

    const OperationPtr op = instruction->GetOperation();

    if (op->type == OP_NOP || !register_bank->TestCondition(op->condition))
      return;

    switch (op->type)
    {
        case MOV:
          
          break;
        case MVN:
          
          break;
        case AND:
          
          break;
        case ORR:
          
          break;
        case EOR:
          
          break;
        case BIC:
          
          break;
        case ADD:
          
          break;
        case SUB:
          
          break;
        case RSB:
          
          break;
        case ADC:
          
          break;
        case SBC:
          
          break;
        case RSC:
          
          break;
        case CMP:
          
          break;
        case CMN:
          
          break;
        case TST:
          
          break;
        case TEQ:
          
          break;
        case MUL:
          
          break;
        case MLA:
          
          break;
        case MLS:
          
          break;
        case B:
          
          break;
        case BL:
          
          break;
        case BX:
          
          break;
        case LDR:
          
          break;
        case STR:
          
          break;
        default:
          break;
    }
}

const Instruction* Processor::FetchInstruction()
{
    return global_memory.Load(register_bank.Load(RegisterBank::PC));
}
