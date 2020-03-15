/*
*   LinkList: ��������
*	��Ա������
*			Node       	�ڵ�
*			m_handler  	ͷ�������ڵ�
*			m_length	�ڵ���
*	��Ա������
*			create()	
*			destroy()	
*			
*			LinkList()	���캯����ʼ��Ա����
*			insert()	�����жϣ������½ڵ㣬Ѱ�ҽڵ㣬����ڵ㡣��������ǰ�ڵ����½ڵ㣬��ڵ����½ڵ�
*			remove()	�����жϣ�Ѱ�ҽڵ㣬ɾ���ڵ㡣							  ��������ǰ�ڵ����½ڵ㣬��ڵ����½ڵ�
*			set()		�����жϣ�Ѱ�ҽڵ㣬���ýڵ�ֵ
*			get()		�����жϣ�Ѱ�ҽڵ㣬��ȡ�ڵ�ֵ
*			length()	��ȡ������
*			clean()		�ͷ����нڵ�ռ�
*			find(const T& obj) const    ���ض�Ӧֵ�ýڵ��±�
*			position(int pos) 		 	�����±�pos�ڵ����һ���Ľڵ�ָ��
*			~LinkList()	�ͷ����нڵ�ռ�
*
*			move(int addr) 		�ƶ��α굽ָ��λ��
*			end()				�ж��α��Ƿ����
*			current()			��ȥ��ǰ�α�ڵ�ֵ
*			next(int step = 1)	�ƶ������Ľڵ���
*/

#ifndef LINKLIST_H
#define LINKLIST_H

#include"List.h"
#include"Exception.h"

namespace DSL
{
	template <typename T>
	class LinkList : public List<T>
	{
		protected:
				struct Node : public TopClass
				{
					T value;
					Node* next;
				};
				//mutable Node m_header; // ͷ�ڵ��а����������򣬵���ָ�����й��캯���׳��쳣ʱ���˴�����ù��캯�������쳣			
				mutable struct : public TopClass // �̳ж��㸸��ʹ���ڴ沼����ͬ
				{
					char reserved[sizeof(T)];
					Node* next;
				}m_header;
				int m_length;    // ������ 
				int m_step;      // �α�ÿ���ƶ���Ŀ
				Node* m_current; // �α�λ��

				virtual Node* create(const T& value)
				{
					Node* node = new Node();
					node->value = value;
					return node;
				}
				virtual void destroy(Node* node)
				{
					delete node;
				}
		public:	
				LinkList()
				{
					m_header.next = NULL;
					m_length = 0;
					m_step = 1;
					m_current = NULL;
				}

				virtual bool insert(const T& obj)
				{
					return insert(m_length,obj);
				}

				virtual bool insert(int pos, const T& obj)
				{
					bool ret = ((pos >= 0) && (pos <= m_length));
					if(ret)
					{
						Node* node =create(obj);
						if(node != NULL)
						{
							Node* current = reinterpret_cast<Node*>(&m_header);
							for(int i = 0; i < pos; i++)
							{
								current = current->next;
							}
							node->next = current->next;
							current->next = node;
							m_length++;
						}
						else
						{
							THROW_EXCEPTION(NotEnoughMemoryException,"error: no enough memory to create node!");
						}
					}
					return ret;
				}

				virtual bool remove(int pos)
				{
					bool ret = ((pos >= 0) && (pos < m_length));
					if(ret)
					{
						Node* current = reinterpret_cast<Node*>(&m_header);
						for(int i = 0; i < pos; i++)
						{
							current = current->next;
						}
						Node* toDel = current->next;
						if(m_current == toDel)  // ���α�ǰ��һλ
						{
							m_current = toDel->next;
						}
						current->next = toDel->next;
						m_length--;
						destroy(toDel);
					}
					else
					{
						THROW_EXCEPTION(IdexOutOfBoundException,"error: index out of bound!");
					}
					return ret;
				}
				
				virtual bool set(int pos,const T& obj)
				{
					bool ret = ((0 <= pos) && (pos < m_length));
					if(ret)
					{
						Node* current = reinterpret_cast<Node*>(&m_header);
						for(int i = 0; i < pos; i++)
						{
							current = current->next;
						}
						current->next->value = obj;
					}
					else
					{
						THROW_EXCEPTION(IdexOutOfBoundException,"error: index out of bound!");
					}
					return ret;
				}

				virtual T get(int pos) const
				{
					T ret;
					get(pos, ret);
					return ret;
				}

				virtual bool get(int pos, T& obj) const
				{
					bool ret = ((0 <= pos) && (pos < m_length));
					if(ret)
					{
						Node* current = reinterpret_cast<Node*>(&m_header);   //const��Ա�����������޸ĳ�Ա������ֵ
						for(int i = 0; i < pos; i++)
						{
							current = current->next;
						}
						obj = current->next->value;
					}
					else
					{
						THROW_EXCEPTION(IdexOutOfBoundException,"error: index out of bound!");
					}
					return ret;
				}

				int find(const T& obj) const   
				{
					int ret = -1;
					Node* current = reinterpret_cast<Node*>(&m_header);
					current = current->next;
					for(int i = 0; i <= m_length; i++)
					{
						if( current->value == obj)  // ����ָ����Ϊ����ʱ���޷��Ƚϣ�Ҫ��TopClass������==������
						{
							ret = i;
							break;
						}
						else
						{
							current = current->next;
						}
					}
					return ret;
				}

				Node* position(int pos) // �����±�pos����һ���Ľڵ�ָ��
				{
					Node* current = reinterpret_cast<Node*>(&m_header);   
					for(int i = 0; i < pos; i++)
					{
						current = current->next;
					}
					return current;
				}

				int length() const
				{
					return m_length;
				}

				void clean()
				{
					while(m_header.next)
					{
						Node* toDel = m_header.next;
						m_header.next = toDel->next;
						m_length--;
						destroy(toDel);
					}
				}

				virtual bool move(int pos) // �ƶ���pos�ڵ�
				{
					bool ret = ((0 <= pos) && (pos < m_length));
					if(ret)
					{
						Node* current = reinterpret_cast<Node*>(&m_header);
						for(int i = 0; i < pos; i++)
						{
							current = current->next;
						}
						m_current = current->next;
					}
					return ret;
				}

				virtual bool end() // �ж��α��Ƿ�������β��
				{
					return (m_current == NULL);
				}

				virtual T current() //�����α����ڽڵ��ֵ
				{
					if(m_current != NULL)
					{
						return m_current->value;
					}
					else
					{
						THROW_EXCEPTION(InvalidOperationException,"error: operation a no exit node!");
					}
				}

				virtual bool next(int step = 1) // һ���ƶ�����Ϊm_step�Ľڵ�
				{
					bool ret = (0 < step);
					if(ret)
					{
						int i = 0;
						while((i < step) && (m_current != NULL))
						{
							m_current = m_current->next;
							i++;
						}
						return (i == step);
					}
					else
					{
						THROW_EXCEPTION(InvalidOperationException,"error: operation node over max node number!");
					}
				}
				
				~LinkList()
				{
					clean();
				}
	};

}

#endif
