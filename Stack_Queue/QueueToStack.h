/*
*	QueueToStack:	使用两个队列实现栈
*	成员变量：
*			m_queue_1		队列一，循环使用
*			m_queue_2		队列二
*			m_queue_in*		指向存放输入数据的那个栈
*			m_queue_out*	指向数据输出的那个栈	
*	成员函数：
*			move()			将m_queue_in指向的queue的N-1个数据保存到m_queue_out   
*			swap()			交换m_queue_in/out指向的对象
*			QueueToStack()	
*			pop()			分三步：1.将m_queue_in指向的queue的N-1个数据保存到m_queue_out   。2.再删除第N个数据。         3.交换m_queue_in/out指向的对象
*			top()			分三步：1.将m_queue_in指向的queue的N-1个数据保存到m_queue_out   。2.返回第N个数据。
*			push()			将数据保存到m_queue_in指向的queue
*			size()			
*			clean()			
*			~QueueToStack()	
*/

#ifndef QUEUETOSTACK_H
#define QUEUETOSTACK_H

#include"LinkListQueue.h"
#include"LinkListStack.h"

using namespace std;

namespace DSL
{
	template <typename T>
	class QueueToStack : public Stack<T>
	{
	protected:
		LinkListQueue<T> m_queue_1;
		LinkListQueue<T> m_queue_2;
		mutable LinkListQueue<T> *m_queue_in;
		mutable LinkListQueue<T> *m_queue_out;
		void move() const 
		{
			int count = (m_queue_in->length() - 1);
			for(int i = 0; i < count; i++)
			{
				m_queue_out->add(m_queue_in->front());
				m_queue_in->remove();
			}
		}
		void swap() const 
		{
			LinkListQueue<T> *temp = m_queue_in;
			m_queue_in = m_queue_out; 
			m_queue_out = temp;
		}
	public:
		QueueToStack()
		{
			m_queue_in = &m_queue_1;
			m_queue_out = &m_queue_2;
		}
		
		void push(const T& obj)
		{
			m_queue_in->add(obj);
		}

		void pop()
		{
			if(m_queue_in->length() > 0)
			{
				move();
				m_queue_in->remove();
				swap();
			}
			else
			{
				THROW_EXCEPTION(InvalidOperationException,"error: no member to pop!");
			}
		}

		T top() const
		{
			if(m_queue_in->length() > 0)
			{
				move();
				return m_queue_in->front();
			}
			else
			{
				THROW_EXCEPTION(InvalidOperationException,"error: no member to top!");
			}
		}

		int size() const
		{
			return (m_queue_in->length() + m_queue_out->length());		
		}
		
		void clean()
		{
			m_queue_in->clear();
			m_queue_out->clear();
		}

		~QueueToStack()
		{
			clean();
		}

	};
}
#endif
