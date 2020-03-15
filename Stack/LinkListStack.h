/*
*	LinkListStack: ����ջģ��
*	��Ա������
*			LinkList<T> m_statcklinklist:	ʹ��������
*	��Ա������
*			LinkListStack(): 	����Ҫ���캯�����������ʱ���Զ����������캯������ģ��Ҳ��ʹ��stackģ��ĳ�Ա������
*			push():				����ͷ����Ϊջ��,������ͷ��ѹ��Ԫ��
*			pop():				ɾ������ͷ����Ԫ��
*			top():				��������ͷ����Ԫ��
*			clean():			�������
*			size():				����������
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
