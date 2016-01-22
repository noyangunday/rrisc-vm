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

#ifndef __NARMVM_MEMORY_H__
#define __NARMVM_MEMORY_H__

#include <map>

namespace narmvm
{

/**
 * @brief System memory implementation
 */
class Memory
{
    public:

    /**
     * @brief Default constructor
     */
    Memory();

    /**
     * @brief Destructor
     */
    ~Memory();

    /**
     * @brief Subscript operator
     * @param[in] location Memory location
     * @return The value stored in the memory location
     */
    const int32_t operator[] (const int32_t location) const;

    /**
     * @brief Subscript operator
     * @param[in] location Memory location
     * @return Returns the instruction stored in the memory location if it exists
     *         Returns NULL if the value stored is not an instruction.
     */
    const Instruction* operator[] (const int32_t location) const;

    /**
     * @brief Read a value from the specified memory location
     * @param[in] location Memory location
     * @return The value stored in the memory location
     */
    const int32_t Load(const int32_t location) const;

    /**
     * @brief Subscript operator
     * @param[in] location Memory location
     * @return Returns the instruction stored in the memory location if it exists
     *         Returns NULL if the value stored is not an instruction.
     */
    const Instruction* Load(const int32_t location) const;

    /**
     * @brief Stores an integer in the specified memory location
     * @param[in] location Target memory location
     * @param[in] value Value to store
     */
    void Store(const int32_t location, const int32_t value);

    /**
     * @brief Stores a value in the specified memory location
     * @param[in] location Target memory location
     * @param[in] instruction Instruction to store
     * @Note Memory takes the ownership of the instructions.
     */
    void Store(const int32_t location, const Instruction* instruction);

    /**
     * @brief Pushes a value on top of the stack
     * @param[in] value Value to push
     * @param[in] sp stack pointer
     */
    void Push(const int32_t value, const int32_t sp);

    /**
     * @brief Pop a value from the top of the stack
     * @param[in] sp stack pointer
     * @return The value read from the stack
     */
    const int32_t Pop(const int32_t sp) const;

    /**
     * @brief Clears the heap (deallocating all the instructions)
     */
    void Reset();

    private:

    /**
     * @brief Type of content stored in memory address
     */
    enum AddressContent
    {
        INTEGER,
        INSTRUCTION
    };

    /**
     * @brief 32-bit (assumed) memory storage
     */
    struct Word 
    {
        AddressType type;
        union
        {
          int32_t               integer;
          const Instruction*    intruction;
        } value;

        /**
         * @brief Integer constructor
         * @param[in] Integer to store
         */
        Word(int32_t integer);

        /**
         * @brief Instruction constructor
         * @param[in] Instruction to store
         */
        Word(Instruction* instruction);

        /**
         * @brief Destructor
         */
        ~Word();
    };

    std::map<int32_t, Word>          mHeap;
    int32_t                         *mStack;
};

}

#endif
