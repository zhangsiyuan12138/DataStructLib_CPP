/*
*	StaticLinkList:静态单链表
*	成员变量：
*			Snode:		重载new的Node节点
*			m_pool[]:	固定大小内存池
*			m_flag[]:	标记使用了的节点
*	成员函数：
*			create()	内存池中申请节点空间
*			destroy()	返回节点空间到内存池
*
*			StaticLinkList()	初始化标记
*			capacity()			获取内存池大小
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
						addr = new(addr) Snode(); // 从m_pool中申请节点空间，并调用构造函数
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

			~StaticLinkList()  // 如果没有实现析构函数，默认析构函数调用父类LinkList的析构函数，会直接释放内存池的空间
			{
				this->clean(); // 调用父类的clean函数，会调用子类的destroy函数。
			}				   // 构造，析构函数调用的虚函数是调用当前类的实现的版本
		
	};
}

#endif
