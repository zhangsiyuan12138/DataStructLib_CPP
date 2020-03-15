/*
*	LinuxQueue: 使用内核双向链表实现队列
*	成员变量：
*			Node
*			m_length
*			m_header
*	成员函数：
*			LinuxQueue()
*			add()
*			remove()
*			front()
*			length()
*			clear()
*			~LinuxQueue()
*/

#ifndef LINUXQUEUE_H		
#define LINUXQUEUE_H	

#include"LinuxList.h"
#include"Exception.h"
#include"Queue.h"

namespace DSL
{
	template <typename T>
	class LinuxQueue : public Queue<T>
	{
	protected:
		struct Node : public TopClass
		{
			list_head head;
			T value;
		};
		int m_length;
		list_head *m_header;
	public:
		LinuxQueue()
		{
			m_length = 0;
			Node *m_list = new Node();
			m_header = &m_list->head;
			INIT_LIST_HEAD(m_header);
		}
		
		void add(const T& obj)
		{
			Node *toadd = new Node();
			if(toadd != NULL)
			{
				toadd->value = obj;
				list_add_tail(&toadd->head,m_header);
				m_length++;
			}
			else
			{
				THROW_EXCEPTION(NullPointerException,"error: no enough memory to malloc!");
			}
		}

		void remove()
		{
			if(m_length > 0)
			{
				list_head *temp = m_header->next;
				list_del(temp);
				m_length--;
				delete list_entry(temp, Node, head);
			}
			else
			{
				THROW_EXCEPTION(InvalidOperationException,"error: no member to remove!");
			}
		}

		T front() const
		{
			if(m_length > 0)
			{		
				return  ((Node *)list_entry(m_header->next, Node, head))->value;  
			}															
			else														
			{
				THROW_EXCEPTION(InvalidOperationException,"error: no member to get!");
			}
			return 0;
		}

		int length() const
		{
			return m_length;
		}

		void clear()
		{
			while(m_length > 0)
			{
				remove();
			}
		}

		~LinuxQueue()
		{
			clear();
		}
	};
}
#endif
