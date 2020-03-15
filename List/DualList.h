/*
*	DualLinkList:	˫��������ģ��
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

#ifndef DUALLIST_H
#define DUALLIST_H

#include"List.h"
#include"Exception.h"

namespace DSL
{
	template <typename T>
	class DualList : public List<T>
	{
		protected:
			struct Node : public TopClass
			{
				T value;
				Node* next;
				Node* pre;
			};

			mutable struct : public TopClass
			{
				char reserve[sizeof(T)];
				Node* next;
				Node* pre;
			}m_header;

			int m_length;
			int m_step;
			Node* m_current;

			virtual Node* create(const T& value)
			{
				Node* node = new Node();
				node->value = value;
				if(node == NULL)
				{
					THROW_EXCEPTION(NotEnoughMemoryException,"error: no enough memory to create node!");
				}
				return node;
			}

			virtual void destroy(Node* toDel)
			{
				delete toDel;
			}	
		public:
			DualList()
			{
				m_length = 0;
				m_step = 1;
				m_current = NULL;
				m_header.next = NULL;
				m_header.pre = NULL;
			}

			bool insert(const T& obj)
			{
				return insert(m_length,obj);
			}
			
			bool insert(int pos, const T& obj)
			{
				bool ret = ((0 <= pos) && (pos <= m_length));
				if(ret)
				{
					Node* new_node = create(obj);
					Node* slider_node = reinterpret_cast<Node*>(&m_header);
					Node* head_node = reinterpret_cast<Node*>(&m_header);
					for(int i = 0; i < m_length; i++)
					{
						slider_node = slider_node->next;					
					}
					Node* pre_node = slider_node;
					Node* next_node = slider_node->next;

					new_node->next = next_node; // pre�ڵ�ָ��new�ڵ㣬new�ڵ�ָ��next�ڵ� ���κ�������ǰ�ȫ����
					pre_node->next = new_node;
					if(pre_node == head_node) // ��������ͷ��
					{
						new_node->pre = NULL;
					}
					if(pre_node != head_node) //���������м�
					{
						new_node->pre = pre_node;
					}
					if(next_node == NULL)	 //��������ĩβ
					{
						;
					}
					if(next_node != NULL)	 //���������м�
					{
						next_node->pre = new_node;
					}
					m_length++;
				}
				return ret;
			}

			bool remove(int pos)
			{
				bool ret = ((pos >= 0) && (pos < m_length));
				if(ret)
				{
					Node* slider_node = reinterpret_cast<Node*>(&m_header);
					for(int i = 0; i < pos; i++)
					{
						slider_node = slider_node->next;
					}
					Node* pre_node = slider_node;
					Node* toDel =slider_node->next;
					Node* next_node = toDel->next;
					Node* head_node = reinterpret_cast<Node*>(&m_header);

					pre_node->next = next_node;  // pre�ڵ�ָ��next�ڵ� ���κ�������ǰ�ȫ����
					if(next_node == NULL) // ɾ��β�ڵ�
					{
						;
					}
					if(next_node != NULL)  // ɾ���м�ڵ��ͷ�ڵ�
					{
						next_node->pre = toDel->pre;
					}
					m_length--;

					if(m_current == toDel)  // �α괦��
					{
						m_current = next_node;
					}
					destroy(toDel);
				}
				return ret;
			}

			bool set(int pos, const T& obj)
			{
				bool ret = ((0 <= pos) && (pos < m_length));
				if(ret)
				{
					Node* slider_node = reinterpret_cast<Node*>(&m_header);
					for(int i = 0; i < pos; i++)
					{
						slider_node = slider_node->next;
					}
					slider_node->next->value = obj;					
				}
				return ret;
			}

			T get(int pos) const
			{
				T ret;
				get(pos,ret);
				return ret;
			}
			
			bool get(int pos, T& obj) const 
			{
				bool ret = ((0 <= pos) && (pos < m_length));
				if(ret)
				{
					Node* slider_node = reinterpret_cast<Node*>(&m_header);
					for(int i = 0; i < pos; i++)
					{
						slider_node = slider_node->next;
					}
					obj = slider_node->next->value;
				}
				return ret;
			}

			int find(const T& obj) const
			{
				int ret = -1;
				Node* head_node = reinterpret_cast<Node*>(&m_header);
				Node* slider_node = head_node->next;
				for(int i = 0; i < m_length; i++)
				{
					if(slider_node->value == obj)
					{
						ret = i;
						break;
					}
					else
					{
						slider_node = slider_node->next;
					}
				}
				return ret;
			}

			int length() const
			{
				return m_length;
			}

			void clean()
			{
				while(m_length > 0)
				{
					remove(0);
				}
			}

			bool move(int pos)
			{
				bool ret = ((0 <= pos) && (pos < m_length));
				if(ret)
				{
					Node* slider_node = reinterpret_cast<Node*>(&m_header);
					for(int i = 0; i < pos; i++)
					{
						slider_node = slider_node->next;
					}
					m_current = slider_node->next;
				}
				return ret;
			}

			bool end()
			{
				return (m_current == NULL);
			}

			T current()
			{
				if(m_current != NULL)
				{
					return m_current->value;
				}
				else
				{
					THROW_EXCEPTION(IdexOutOfBoundException,"error: operat a no exit node!");
				}
			}

			bool next(int step = 1)
			{
				bool ret = (step > 0);
				if(ret)
				{
					for(int i = 0; (i < step) && (m_current != NULL); i++)
					{
						m_current = m_current->next;
					}
				}
				return ret;
			}

			bool pre(int step = 1)
			{
				bool ret = (step > 0);
				if(ret)
				{
					for(int i = 0; (i < step) && (m_current != NULL); i++)
					{
						m_current = m_current->pre;
					}
				}
				return ret;
			}
			~DualList()
			{
				clean();
			}
	};
}

#endif
