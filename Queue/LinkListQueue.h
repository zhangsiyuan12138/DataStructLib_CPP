/*
*	LinkListQueue:	单链表队列
*	成员变量：
*			LinkList<T> m_LinkList:	组合使用单链表类来实现队列
*	成员函数：
*			LinkListQueue		
*			add()				在队列尾部添加数据（单链表尾部）
*			remove()			在队列头部取出数据（单链表头部）
*			front()				取出队列头部数据（单链表头部）
*			clear()				清除所有数据（清空单链表）
*			length()			返回队列长度（返回单链表长度）
*			~LinkListQueue()	清空队列（清空单链表）
*/

#ifndef LINKLISTQUEUE_H
#define LINKLISTQUEUE_H

#include"LinkList.h"
#include"Queue.h"

namespace DSL
{
	template <typename T>
	class LinkListQueue : public Queue<T>
	{
	protected:
		LinkList<T> m_LinkList;
	public:
		LinkListQueue()
		{

		}

		void add(const T& obj)
		{
			m_LinkList.insert(obj);
		}

		void remove()
		{
			if(m_LinkList.length() > 0)
			{
				m_LinkList.remove(0);
			}
			else
			{
				THROW_EXCEPTION(InvalidOperationException,"error: no element to remove!");
			}
		}

		T front() const
		{
			if(m_LinkList.length() > 0)
			{
				return m_LinkList.get(0);
			}
			else
			{
				THROW_EXCEPTION(InvalidOperationException,"error: no element to get!");
			}
		}

		int length() const
		{
			return m_LinkList.length();
		}

		void clear()
		{
			m_LinkList.clean();
		}

		~LinkListQueue()
		{
			clear();
		}

	};
}

#endif
