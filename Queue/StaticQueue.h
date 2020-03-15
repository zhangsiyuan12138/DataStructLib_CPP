/*
*	StaticQueue:	��̬ѭ������ʵ�ֶ���
*	��Ա������
*			m_space[]	���д洢�ռ䣬T�������Ա�������ͣ�N�����鳤��
*			m_front		��ͷ��ʶ��
*			m_rear		��β��ʶ����ָ����ʵ��β����һ��Ԫ�أ��������ж϶����Ƿ������
*			m_length	����ʵʱ����
*	��Ա������
*			StaticQueue()	��ʼ����Ա����
*			add()			����Ԫ�ص���β
*			remove()		ɾ����ͷԪ��
*			front()			���ض�ͷԪ��
*			clear()			��ճ�Ա����
*			length()		����ʵʱ���г���
*			~StaticQueue()	
*/

#ifndef STATICQUEUE_H
#define STATICQUEUE_H

#include"Queue.h"
#include"Exception.h"

namespace DSL
{
	template <typename T, int N>
	class StaticQueue : public Queue<T>
	{
	protected:
		T m_space[N];  //����Ԫ��Ϊ�������ǣ�����StaticQueue����ʱ�����ε���Ԫ�����͵Ĺ��캯����
		int m_front;
		int m_rear;
		int m_length;
	public:
		StaticQueue()
		{
			m_front = 0;
			m_rear = 0;
			m_length = 0;
		}

		void add(const T& obj)
		{
			if(m_length < N)
			{
				m_space[m_rear] = obj;
				m_rear = (m_rear + 1) % N;
				m_length++;
			}
			else
			{
				THROW_EXCEPTION(InvalidOperationException,"no space in current queue!");
			}
		}
		
		void remove()
		{
			if(m_length > 0)
			{
				m_front = (m_front + 1) % N;
				m_length--;
			}
			else
			{
				THROW_EXCEPTION(InvalidOperationException,"no element to remove from the queue!");
			}
		}

		T front() const
		{
			if(m_length > 0 && m_length <= N)
			{
				return m_space[m_front];
			}
			else
			{
				THROW_EXCEPTION(InvalidOperationException,"no element to get from the queue!");
			}
		}

		int length() const
		{
			return m_length;
		}

		void clear()
		{
			m_length = 0;
			m_front = 0;
			m_rear = 0;
		}

		~StaticQueue()	
		{
			clear();
		}
		
		
	};
}

#endif
/* Test 
int main(void)
{
	StaticQueue<int,5> queue;
	for(int i = 0; i < 5; i++)
	{
		queue.add(i);
	}

	while(queue.length() > 0)
	{
		cout << queue.front() << endl;
		queue.remove();
	}
	return 0;
} 

*/
