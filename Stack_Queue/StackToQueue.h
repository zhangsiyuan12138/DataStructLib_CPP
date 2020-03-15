/*
*	StackToQueue:	
*	成员变量：
*			m_stack_in
*			m_stack_out
*	成员函数：
*			move()           	将in栈的全部成员逆序放入out栈中
*			StackToQueue()		
*			add()				先将数据放入in栈
*			remove()			如果out栈数据已经被全部pop,再到in栈读取数据，再删除
*			front()				如果out栈数据已经被全部pop,再到in栈读取数据，再读取
*			length()			in栈和out栈成员数量和
*			clear()				
*			~StackToQueue()		
*/

#ifndef STACKTOQUEUE
#define STACKTOQUEUE

#include"LinkListQueue.h"
#include"LinkListStack.h"

namespace DSL
{
	template <typename T>
	class StackToQueue : Queue<T>
	{
	protected:
		mutable LinkListStack<T> m_stack_in;
		mutable LinkListStack<T> m_stack_out;
		void move()  const
		{
			if(m_stack_out.size() == 0)
			{
				while(m_stack_in.size() > 0)
				{
					m_stack_out.push(m_stack_in.top());
					m_stack_in.pop();
				}
			}
		}
	public:
		StackToQueue()
		{
		}
	
		void add(const T& obj)
		{
			m_stack_in.push(obj);
		}
	
		void remove()
		{
			move();
			if(m_stack_out.size() > 0)
			{
				m_stack_out.pop();
			}
			else
			{
				THROW_EXCEPTION(InvalidOperationException,"error: no member pop!");
			}
		}
		
		T front() const
		{
			move();
			if(m_stack_out.size() > 0)
			{
				m_stack_out.top();
			}
			else
			{
				THROW_EXCEPTION(InvalidOperationException,"error: no member top!");
			}
		}

		int length() const
		{
			return (m_stack_in.size() + m_stack_out.size());
		}

		void clear()
		{
			m_stack_in.clean();
			m_stack_out.clean();
		}

		~StackToQueue()
		{
			clear();
		}

	};
}
#endif
