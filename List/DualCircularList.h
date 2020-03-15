/*
*	DualLinkList:	˫��ѭ������
*	��Ա������
*			Node:		�ڵ�ʵ��
*			m_header:	ͷ�ڵ�
*			m_length	������
*			m_step		��������
*			m_current	��ǰ�ڵ�ǰһ���ڵ�	
*	��Ա������
*			create()	����һ���½ڵ�		
*			destroy()	ɾ��һ���½ڵ�
*			
*			DualLinList()		���캯����ʼ����Ա����
*			insert()			�����жϣ������½ڵ㣬Ѱ�ҽڵ㣬����ڵ㡣���Ĳ���
*			remove()			�����жϣ�Ѱ�ҽڵ㣬ɾ���ڵ㡣							  ��������
*			set()				�����жϣ�Ѱ�ҽڵ㣬���ýڵ�ֵ
*			get()				�����жϣ�Ѱ�ҽڵ㣬��ȡ�ڵ�ֵ
*			length() 			��ȡ������
*			clean()				�ͷ����нڵ�ռ�
*			find()      		���ض�Ӧֵ�ýڵ��±�
*			position()		 	�����±�pos�ڵ����һ���Ľڵ�ָ��
*			~LinkList()			�ͷ����нڵ�ռ�
*
*			bool move() 		�ƶ��α굽ָ��λ��
*			bool end()			�ж��α��Ƿ����
*			T current()			��ȥ��ǰ�α�ڵ�ֵ
*			bool next()			�ƶ������Ľڵ���
*			bool pre()			�ƶ������Ľڵ���	
*/

#ifndef DUALLINKLIST_H
#define DUALLINKLIST_H

#include"DualList.h"

namespace DSL
{
	template<typename T>
	class DualCircularList : public DualList<T>
	{
	protected:
		typedef typename DualList<T>::Node Node;
	public:
		DualCircularList()
		{
			this->m_length = 0;
			this->m_step = 1;
			this->m_current = NULL;
			this->m_header.next = NULL;
		}
		
		bool insert(const T& obj)
		{
			insert(this->m_length,obj);
		}

		bool insert(int pos, const T& obj)
		{
			bool ret  = ((pos >= 0) && (pos <= this->m_length));
			if(ret)
			{
				

			}
			return ret;
		}


	};
	
}

#endif
