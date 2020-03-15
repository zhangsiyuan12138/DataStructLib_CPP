/*
*	Stack:	栈接口
*	成员变量：
*			push()		
*			pop()		
*			top()		
*			size()		
*			clean()		
*/

#ifndef STACK_H
#define STACK_H

#include"TopClass.h"

namespace DSL
{
	template <typename T>
	class Stack : public TopClass
	{
	public:
		virtual void push(const T& obj) = 0;
		virtual void pop() = 0;
		virtual T top() const = 0;
		virtual int size() const = 0;
		virtual void clean() = 0;
	};
}

#endif