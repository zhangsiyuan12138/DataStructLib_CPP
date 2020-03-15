/*
*	QueueToStack:	ʹ����������ʵ��ջ
*	��Ա������
*			m_queue_1		����һ��ѭ��ʹ��
*			m_queue_2		���ж�
*			m_queue_in*		ָ�����������ݵ��Ǹ�ջ
*			m_queue_out*	ָ������������Ǹ�ջ	
*	��Ա������
*			move()			��m_queue_inָ���queue��N-1�����ݱ��浽m_queue_out   
*			swap()			����m_queue_in/outָ��Ķ���
*			QueueToStack()	
*			pop()			��������1.��m_queue_inָ���queue��N-1�����ݱ��浽m_queue_out   ��2.��ɾ����N�����ݡ�         3.����m_queue_in/outָ��Ķ���
*			top()			��������1.��m_queue_inָ���queue��N-1�����ݱ��浽m_queue_out   ��2.���ص�N�����ݡ�
*			push()			�����ݱ��浽m_queue_inָ���queue
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
