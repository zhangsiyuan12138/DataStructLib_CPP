/*
*	LinkListQueue:	���������
*	��Ա������
*			LinkList<T> m_LinkList:	���ʹ�õ���������ʵ�ֶ���
*	��Ա������
*			LinkListQueue		
*			add()				�ڶ���β��������ݣ�������β����
*			remove()			�ڶ���ͷ��ȡ�����ݣ�������ͷ����
*			front()				ȡ������ͷ�����ݣ�������ͷ����
*			clear()				����������ݣ���յ�����
*			length()			���ض��г��ȣ����ص������ȣ�
*			~LinkListQueue()	��ն��У���յ�����
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
