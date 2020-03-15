/*
*	StaticLinkList:��̬������
*	��Ա������
*			Snode:		����new��Node�ڵ�
*			m_pool[]:	�̶���С�ڴ��
*			m_flag[]:	���ʹ���˵Ľڵ�
*	��Ա������
*			create()	�ڴ��������ڵ�ռ�
*			destroy()	���ؽڵ�ռ䵽�ڴ��
*
*			StaticLinkList()	��ʼ�����
*			capacity()			��ȡ�ڴ�ش�С
*			
*/

#ifndef STATICLINKLIST_H
#define STATICLINKLIST_H

#include"LinkList.h"

namespace DSL
{
	template < typename T, int N >
	class StaticLinkList : public LinkList<T> 
	{
		protected:
			typedef typename LinkList<T>::Node Node;
			struct Snode : public Node
			{
				void* operator new (size_t size, void* addr)
				{
					return addr;	
				}				
			};
			unsigned char m_pool[sizeof(Node) * N];
			char m_flag[N];
			
			Node* create()
			{
				Snode* addr = NULL;
				for(int i = 0; i < N; i++)
				{
					if(m_flag[i] == 0)
					{
						addr = reinterpret_cast<Snode*>(m_pool + i*sizeof(Snode));
						addr = new(addr) Snode(); // ��m_pool������ڵ�ռ䣬�����ù��캯��
						m_flag[i] = 1;
						break;
					}
				}
				return addr;
			}

			void destroy(Node* addr)
			{
				Snode* toDel = dynamic_cast<Snode*>(addr);
				for(int i = 0; i < N; i++)
				{
					if(toDel ==  reinterpret_cast<Snode*>(&m_pool[i*sizeof(Node)]))
					{
						m_flag[i] == 0;
						toDel->~Node();
						break;
					}
				}
			}

		public:
			StaticLinkList()
			{
				for(int i = 0; i < N; i++)
				{
					m_flag[i] = 0;
				}
			}
			int capacity()
			{
				return N;
			}

			~StaticLinkList()  // ���û��ʵ������������Ĭ�������������ø���LinkList��������������ֱ���ͷ��ڴ�صĿռ�
			{
				this->clean(); // ���ø����clean����������������destroy������
			}				   // ���죬�����������õ��麯���ǵ��õ�ǰ���ʵ�ֵİ汾
		
	};
}

#endif
