/*
*	StaticQueue:	静态循环数组实现队列
*	成员变量：
*			m_space[]	队列存储空间，T是数组成员变量类型，N是数组长度
*			m_front		队头标识符
*			m_rear		队尾标识符，指向真实队尾的下一个元素，方便于判断队列是否满或空
*			m_length	队列实时长度
*	成员函数：
*			StaticQueue()	初始化成员变量
*			add()			插入元素到队尾
*			remove()		删除队头元素
*			front()			返回队头元素
*			clear()			清空成员变量
*			length()		返回实时队列长度
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
		T m_space[N];  //数组元素为类类型是，创建StaticQueue对象时，会多次调用元素类型的构造函数。
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
