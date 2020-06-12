/*
*   LinkList: 单链表类
*	成员变量：
*			Node       	节点
*			m_handler  	头部辅助节点
*			m_length	节点数
*	成员函数：
*			create()	
*			destroy()	
*			
*			LinkList()	构造函数初始成员变量
*			insert()	参数判断，申请新节点，寻找节点，插入节点。分两步：前节点与新节点，后节点与新节点
*			remove()	参数判断，寻找节点，删除节点。							  分两步：前节点与新节点，后节点与新节点
*			set()		参数判断，寻找节点，设置节点值
*			get()		参数判断，寻找节点，获取节点值
*			length()	获取链表长度
*			clean()		释放所有节点空间
*			find(const T& obj) const    返回对应值得节点下标
*			position(int pos) 		 	返回下标pos节点的上一个的节点指针
*			~LinkList()	释放所有节点空间
*
*			move(int addr) 		移动游标到指定位置
*			end()				判断游标是否到最后
*			current()			回去当前游标节点值
*			next(int step = 1)	移动步长的节点数
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
				//mutable Node m_header; // 头节点中包含了数据域，当泛指类型中构造函数抛出异常时，此处会调用构造函数发生异常			
				mutable struct : public TopClass // 继承顶层父类使得内存布局相同
				{
					char reserved[sizeof(T)];
					Node* next;
				}m_header;
				int m_length;    // 链表长度 
				int m_step;      // 游标每次移动数目
				Node* m_current; // 游标位置

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
						if(m_current == toDel)  // 将游标前进一位
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
						Node* current = reinterpret_cast<Node*>(&m_header);   //const成员函数不可以修改成员变量的值
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
					Node* current = this->m_header.next;
					for(int i = 0; i < this->m_length; i++)
					{
						if( current->value == obj)  // 当泛指类型为对象时，无法比较，要在TopClass中重载==操作符
						{
							ret = i;
							break;
						}
						current = current->next;
					}
					return ret;
				}

				Node* position(int pos) // 返回下pos的上一个的节点指针
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

				virtual bool move(int pos) // 移动到pos节点
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

				virtual bool end() // 判断游标是否在链表尾部
				{
					return (m_current == NULL);
				}

				virtual T current() //返回游标所在节点的值
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

				virtual bool next(int step = 1) // 一次移动步长为m_step的节点
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
