/*
*	DualLinkList:	双向链表类模板
*	成员变量：
*			Node:		节点实体
*			m_header:	头节点
*			m_length	链表长度
*			m_step		步进长度
*			m_current	当前节点前一个节点	
*	成员函数：
*			create()	申请一个新节点		
*			destroy()	删除一个新节点
*			
*			DualLinList()		构造函数初始化成员变量
*			insert()			参数判断，申请新节点，寻找节点，插入节点。分四步：
*			remove()			参数判断，寻找节点，删除节点。							  分三步：
*			set()				参数判断，寻找节点，设置节点值
*			get()				参数判断，寻找节点，获取节点值
*			length() 			获取链表长度
*			clean()				释放所有节点空间
*			find()      		返回对应值得节点下标
*			position()		 	返回下标pos节点的上一个的节点指针
*			~LinkList()			释放所有节点空间
*
*			bool move() 		移动游标到指定位置
*			bool end()			判断游标是否到最后
*			T current()			回去当前游标节点值
*			bool next()			移动步长的节点数
*			bool pre()			移动步长的节点数

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

					new_node->next = next_node; // pre节点指向new节点，new节点指向next节点 在任何情况下是安全操作
					pre_node->next = new_node;
					if(pre_node == head_node) // 插入链表头部
					{
						new_node->pre = NULL;
					}
					if(pre_node != head_node) //插入链表中间
					{
						new_node->pre = pre_node;
					}
					if(next_node == NULL)	 //插入链表末尾
					{
						;
					}
					if(next_node != NULL)	 //插入链表中间
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

					pre_node->next = next_node;  // pre节点指向next节点 在任何情况下是安全操作
					if(next_node == NULL) // 删除尾节点
					{
						;
					}
					if(next_node != NULL)  // 删除中间节点和头节点
					{
						next_node->pre = toDel->pre;
					}
					m_length--;

					if(m_current == toDel)  // 游标处理
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
