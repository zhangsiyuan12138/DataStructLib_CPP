/*
*	LinkListStack: 链表栈模板
*	成员变量：
*			LinkList<T> m_statcklinklist:	使用链表来
*	成员函数：
*			LinkListStack(): 	不需要构造函数。定义对象时就自动调用链表构造函数。本模板也不使用stack模板的成员变量。
*			push():				链表头部作为栈顶,在链表头部压入元素
*			pop():				删除链表头部的元素
*			top():				返回链表头部的元素
*			clean():			清空链表
*			size():				返回链表长度
*/

#ifndef LINKLISTSTACK_H
#define LINKLISTSTACK_H

#include"Stack.h"
#include"LinkList.h"

namespace DSL
{
	template <typename T>
	class LinkListStack : public Stack<T>
	{
	protected:
		LinkList<T> m_liststack;
	public:
		void push(const T& obj)
		{
			m_liststack.insert(0,obj);
		}

		void pop()
		{
			if(m_liststack.length() > 0)
			{
				m_liststack.remove(0);
			}
			else
			{
				THROW_EXCEPTION(InvalidOperationException,"error: no element to pop!");
			}
		}

		T top() const
		{
			if(m_liststack.length() > 0)
			{
				return  m_liststack.get(0);
			}
			else
			{
				THROW_EXCEPTION(InvalidOperationException,"error: no element to top!");
			}
		}

		void clean()
		{
			m_liststack.clean();
		}

		int size() const 
		{
			return m_liststack.length();
		}
		
	};
}

#endif
