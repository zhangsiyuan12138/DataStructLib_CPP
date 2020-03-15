/*
*	StaticStack: ��̬ջģ��
*	��Ա������
*			m_space[N]:	ջ�Ĵ洢�ռ䡣
*			m_top:		ջ����ʶ����ջ��ʱm_top=-1��ջ��ʱm_top=capacity-1��
*			m_size:		��ǰջ�Ĵ�С��
*	��Ա������
*			StaticStack()	���캯����ʼ����Ա����
*			push()			��ջ
*			pop()			��ջ
*			top()			��ȡջ��Ԫ��
*			capacity()		��ȡջ�ռ��С
*			size()			��ȡջ�Ĵ�С
*			clean()			���ջ
*			~StaticStack()	���ջ	
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
