/*
*	StackToQueue:	
*	��Ա������
*			m_stack_in
*			m_stack_out
*	��Ա������
*			move()           	��inջ��ȫ����Ա�������outջ��
*			StackToQueue()		
*			add()				�Ƚ����ݷ���inջ
*			remove()			���outջ�����Ѿ���ȫ��pop,�ٵ�inջ��ȡ���ݣ���ɾ��
*			front()				���outջ�����Ѿ���ȫ��pop,�ٵ�inջ��ȡ���ݣ��ٶ�ȡ
*			length()			inջ��outջ��Ա������
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
