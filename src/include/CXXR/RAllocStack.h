/*CXXR $Id$
 *CXXR
 *CXXR This file is part of CXXR, a project to refactor the R interpreter
 *CXXR into C++.  It may consist in whole or in part of program code and
 *CXXR documentation taken from the R project itself, incorporated into
 *CXXR CXXR (and possibly MODIFIED) under the terms of the GNU General Public
 *CXXR Licence.
 *CXXR 
 *CXXR CXXR is Copyright (C) 2008-10 Andrew R. Runnalls, subject to such other
 *CXXR copyrights and copyright restrictions as may be stated below.
 *CXXR 
 *CXXR CXXR is not part of the R project, and bugs and other issues should
 *CXXR not be reported via r-bugs or other R project channels; instead refer
 *CXXR to the CXXR website.
 *CXXR */

/*
 *  R : A Computer Language for Statistical Data Analysis
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2.1 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, a copy is available at
 *  http://www.r-project.org/Licenses/
 */

/** @file RAllocStack.h
 * @brief Function R_alloc() and kin.
 *
 * Defines functions R_alloc() and related functions, and the class
 * CXXR::RAllocStack which is used to implement them.
 */

#ifndef RALLOCSTACK_H
#define RALLOCSTACK_H 1

#ifdef __cplusplus

#include <stack>
#include <vector>

namespace CXXR {
    /** @brief Class for implementing R_alloc() and kindred functions.
     *
     * This class has only static members.  It implements a stack of
     * pointers to blocks of memory.
     */
    class RAllocStack {
    public:
	/** @brief Allocate a new block of memory.
	 *
	 * The block will be aligned on a multiple of
	 * <tt>sizeof(double)</tt> .
	 * @param sz The required size in bytes (strictly, as a
	 *           multiple of <tt>sizeof(char)</tt>), of the memory block.
	 * @return Pointer to the start of the memory block.
	 */
	static void* allocate(size_t sz);

	/** @brief Restore stack to a previous size.
	 *
	 * Restore the stack to a previous size by popping elements
	 * off the top.
	 * @param new_size The size to which the stack is to be
	 *          restored.  Must not be greater than the current
	 *          size.
	 * @note In future this method will probably cease to be
	 * public, and be accessible only by a class encapsulating R
	 * contexts.
	 */
	static void restoreSize(size_t new_size);

	/** @brief Current size of stack.
	 *
	 * @return the current size of the stack.
	 *
	 * @note This method is intended for use in conjunction with
	 * restoreSize(), and like it may cease to be public in
	 * future.
	 */
	static size_t size()
	{
	    return s_stack.size();
	}
    private:
	typedef std::pair<size_t, void*> Pair;
	typedef std::stack<Pair, std::vector<Pair> > Stack;
	static Stack s_stack;

	// Not implemented.  Declared to stop the compiler generating
	// a constructor.
	RAllocStack();
    };
}  // namespace CXXR

extern "C" {
#endif /* __cplusplus */

    /* ***** C interface ***** */

    /** @brief Allocate a block of memory.
     *
     * This function is provided primarily for the use of code called
     * from the R <tt>.C</tt> function.  It will allocate a block of
     * memory that will automatically be reclaimed by R at the end of
     * the <tt>.C</tt> call.
     *
     * @param num_elts Number of data items to be accommodated in the
     *          block.
     *
     * @param elt_size Size in bytes (strictly, as a multiple of
     *          <tt>sizeof(char)</tt>) of each data item.  Must be
     *          non-negative.
     *
     * @return Pointer to the start of the memory block.
     *
     * @note The signed type of \a elt_size is anomalous, but is part
     * of the R API.
     */
    char* R_alloc(size_t num_elts, int elt_size);

#ifdef __cplusplus
    /** @brief Allocate a block of memory.
     *
     * This is a wrapper round R_alloc() for the use of former CR code
     * that is now treated as C++.  It differs from R_alloc() in
     * returning void* rather than char*, thus allowing conversion to
     * the required pointer type to be achieved by static_cast rather
     * than reinterpret_cast.
     *
     * @param num_elts Number of data items to be accommodated in the
     *          block.
     *
     * @param elt_size Size in bytes (strictly, as a multiple of
     *          <tt>sizeof(char)</tt>) of each data item.  Must be
     *          non-negative.
     *
     * @return Pointer to the start of the memory block.
     *
     * @deprecated For use only as described above.  The function is
     * not accessible from C, and new C++ code should use C++ memory
     * allocation mechanisms (i.e. new/delete).
     */
    inline void* CXXR_alloc(size_t num_elts, int elt_size)
    {
	return static_cast<void*>(R_alloc(num_elts, elt_size));
    }
#endif

    /** @brief Allocate a block of memory, and initialize it to zero.
     *
     * This is part of the S compatibility interface.  It does the
     * same thing as R_alloc(), except that the memory block is
     * guaranteed to be initialized to zero.
     * @param num_elts Number of data items to be accommodated in the
     *          block.  Must be non-negative.
     * @param elt_size Size in bytes (strictly, as a multiple of
     *          <tt>sizeof(char)</tt>) of each data item.  Must be
     *          non-negative.
     * @return Pointer to the start of the memory block.
     */
    char* S_alloc(long num_elts, int elt_size);

    /** @brief Reallocate a block of memory.
     *
     * This is part of the S compatibility interface, and is used when
     * it is decided that a block of memory previously allocated by 
     * S_alloc() or S_realloc() needs to be expanded.  It allocates a
     * new block of memory, copies across the previous contents, and
     * zeroes any additional elements.
     * @param prev_block Pointer to a block of memory previously
     *          allocated by S_alloc() or S_realloc().
     * @param new_sz New number of elements (>= 0) to be
     *          accommodated.
     * @param old_sz Number of elements contained in prev_block.
     * @param elt_size Size in bytes (strictly, as a multiple of
     *          sizeof(char)) of each data item.  Must be
     *          non-negative.
     * @return Pointer to the start of the newly allocated memory
     *         block.  If \a new_sz \c <= \a old_sz, the function does
     *         not allocate a new block, and simply returns \a
     *         prev_block.
     */
    char* S_realloc(char *prev_block, long new_sz, long old_sz, int elt_size);

    /** @brief Number of memory blocks allocated.
     *
     * @return The current number of blocks allocated via R_alloc(),
     *         S_alloc() and S_realloc(), coerced into a char* for
     *         compatibility with CR.  (This function and vmaxset()
     *         are declared in the R.h API.)
     *
     * @note C++ code should preferably use CXXR::RAllocStack::size() directly.
     */
#ifndef __cplusplus
    void* vmaxget(void);
#else
    inline void* vmaxget(void)
    {
	return static_cast<char*>(0) + CXXR::RAllocStack::size();
    }
#endif

    /** @brief Reclaims memory blocks.
     *
     * @param stack_sizep A value previously returned by a call to
     *          vmaxget().  vmaxset() will reclaim the memory
     *          from all blocks allocated via R_alloc(),
     *          S_alloc() and S_realloc() subsequent to that call of
     *          vmaxget().
     *
     * @deprecated For expert use only.  C++ code should preferably
     * use CXXR::RAllocStack::restoreSize() directly.
     */
#ifndef __cplusplus
    void vmaxset(const void* stack_sizep);
#else
    inline void vmaxset(const void* stack_sizep)
    {
	size_t stack_size = static_cast<const char*>(stack_sizep)
	                    - static_cast<const char*>(0);
	CXXR::RAllocStack::restoreSize(stack_size);
    }
#endif

#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif  // RALLOCSTACK_H
