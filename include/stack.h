/*******************************************************************************
 * DANIEL'S ALGORITHM IMPLEMENTAIONS
 *
 *  /\  |  _   _  ._ o _|_ |_  ._ _   _ 
 * /--\ | (_| (_) |  |  |_ | | | | | _> 
 *         _|                      
 *
 * STACK
 *
 * Features:
 * 1. Stack with capcity 
 * 
 * http://en.wikipedia.org/wiki/Stack_(abstract_data_type)
 *
 ******************************************************************************/

#ifndef __STACK_H__
#define __STACK_H__

#include <stdint.h>
#include <stdbool.h>

/** 
 * Stack has three properties. capacity stands for the maximum number of
 * elements stack can hold. Size stands for the current size of the stack and elements 
 * is the array of elements 
 */
template<typename T=uintptr_t>
class Stack
{
private:
	uint32_t m_capacity;		// the total capacity
	uint32_t m_size;			// current stack size
	T * m_elements;		// the elements

public:
	/**
	 * capcity is the maximum elements the stack can hold.
	 */
	Stack(uint32_t capacity) {
		this->m_capacity = capacity;
		this->m_size = 0;
		this->m_elements = new T[capacity];
	}

	virtual ~Stack() {
		delete [] m_elements;
	}

private:
	Stack(const Stack&);
	Stack& operator=(const Stack&);

public:
	/**
	 * test whether the stack is empty
	 */
	inline bool is_empty() const { return m_size==0?true:false; } 

	/**
	 * pop stack
	 */
	inline void pop() {
		if(m_size!=0) m_size--;
		return;
	}

	/**
	 * get the top element, test is_empty() before top()
	*/
	inline const T& top() const { return m_elements[m_size-1]; };

	/**
	 * push an element into the stack
	 * returns false when stack is full.
	 */
	inline bool push(const T & value) 
	{
		if(m_size==m_capacity) { return false; }
		else {
			m_elements[m_size++] = value;
			return true;
		}
	}

	/**
	 * return the stack size count.
	 */
	inline uint32_t count() const { return m_size; }

	inline const T& operator[] (int idx) const { return m_elements[m_size-1-idx]; }
};

#endif //
