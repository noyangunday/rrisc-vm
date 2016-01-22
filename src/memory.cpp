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

#include "memory.h"
using namespace armvm;

namespace
{
    static const int32_t DEFAULT_STACK_SIZE(1024);
}

Memory::Memory()
{
    mStack = new int32_t[DEFAULT_STACK_SIZE];
}

Memory::~Memory()
{
    delete[] stack;
    mHeap.clear();
}

const int32_t Memory::operator[] (const int32_t location) const
{
    return Load(location);
}

const Instruction* Memory::operator[] (const int32_t location) const
{
    return Load(location);
}

const int32_t Memory::Load(const int32_t location) const
{
    it = mHeap.find(location);
    if (it != mHeap.end())
    {
        return it->second.value.integer;
    }
    return 0;
}

const Instruction* Memory::Load(const int32_t location) const
{
    it = mHeap.find(location);
    if (it != mHeap.end())
    {
        Word& word = it->second;
        if (word.type != INSTRUCTION) 
          return NULL;
        return word.value.instruction;        
    }
    return NULL;
}

void Memory::Store(const int32_t location, const int32_t value)
{
    it = mHeap.find(location);
    if (it != mHeap.end())
      mHeap.erase(it);
    mHeap.insert(std::pair<int32_t, Word>(location, Word(value)));
}

void Memory::Store(const int32_t location, const Instruction* instruction)
{
    it = mHeap.find(location);
    if (it != mHeap.end())
      mHeap.erase(it);
    mHeap.insert(std::pair<int32_t, Word>(location, Word(instruction)));
}

void Memory::Push(const int32_t value, const int32_t sp)
{

}

const int32_t Memory::Pop(const int32_t sp) const
{

}

void Memory::Reset()
{
    mHeap.clear();
}

Memory::Word::Word(int32_t integer)
: type(INTEGER)
{
    value.integer = integer;
}

Memory::Word::Word(Instruction* instruction)
: type(INTRUCTION)
{
    value.instruction = instruction;
}

Memory::Word::~Word()
{
    if (type == INSTRUCTION)
        delete value.instruction;
}
