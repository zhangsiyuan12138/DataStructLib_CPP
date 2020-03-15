/*
*	StaticStack: 静态栈模板
*	成员变量：
*			m_space[N]:	栈的存储空间。
*			m_top:		栈顶标识符。栈空时m_top=-1。栈满时m_top=capacity-1。
*			m_size:		当前栈的大小。
*	成员函数：
*			StaticStack()	构造函数初始化成员变量
*			push()			入栈
*			pop()			出栈
*			top()			获取栈顶元素
*			capacity()		获取栈空间大小
*			size()			获取栈的大小
*			clean()			清空栈
*			~StaticStack()	清空栈	
*/

#ifndef STATICSTACK_H
#define STATICSTACK_H

#include"Exception.h"
#include"Stack.h"

namespace DSL
{
	template <typename T, int N>
	class StaticStack : public Stack<T>
	{
	protected:
		T m_space[N];
		int m_top;
		int m_size;
	public:
		StaticStack()
		{
			m_top = -1;
			m_size = 0;
		}

		void push(const T& obj)
		{
			if(m_size < N)
			{
				m_space[m_top + 1] = obj;
				m_top++;
				m_size++;
			}
			else
			{
				THROW_EXCEPTION(InvalidOperationException,"error: no space to push!");
			}
		}

		void pop()
		{
			if(m_size > 0)
			{
				m_size--;
				m_top--;
			}
			else
			{
				THROW_EXCEPTION(InvalidOperationException,"error: no element to pop!");
			}
		}

		T top() const 
		{
			if(m_size > 0)
			{
				return m_space[m_top];
			}
			else
			{
				THROW_EXCEPTION(InvalidOperationException,"error: no element to top!");
			}
		}

		int capacity()
		{
			return N;
		}

		int size() const
		{
			return m_size;
		}

		void clean()
		{
			m_size = 0;
			m_top = -1;
		}

		~StaticStack()
		{
			clean();
		}

	};

}

#endif
