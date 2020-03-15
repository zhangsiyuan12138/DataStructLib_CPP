/*
*	CirularList: 循环链表模板
*	成员变量：
*			
*	成员函数：
*			last_to_first()						连接首尾节点
*			bool insert(int pos,const T& obj)	插入下标为pos的节点。分三步：新节点与头节点，新节点与0节点，新节点与尾节点
*			bool remove(int pos)				删除下标为pos的节点。分三步：头节点与1节点，尾节点与1节点，删除0节点
*			bool set(int pos, const T& obj)		设置pos下标值
*			bool get(int pos, T& obj) const		过去下标pos节点的值
*			int find(const T& obj) const		寻找值相同的第一个节点的下标
*			void clean()						清空所有节点
*/

#ifndef CIRCULARLIST_H
#define CIRCULARLIST_H

#include"LinkList.h"

namespace DSL
{
	template <typename T>
	class CircularList : public LinkList<T>
	{
		protected:
			typedef typename LinkList<T>::Node Node;
			void last_to_first()
			{
				Node* current = reinterpret_cast<Node*>(&this->m_header);
				for(int i = 0; i < this->m_length; i++)
				{
					current = current->next;
				}
				current->next = this->m_header.next;
			}

		public:
			bool insert(const T& obj) // 默认插入尾部
			{
				return (this->insert(this->m_length,obj));
			}

			bool insert(int pos, const T & obj)
			{
				bool ret = 1;
				pos = pos % (this->m_length + 1);
				if(pos == 0) // 插入链表头部
				{
					ret = LinkList<T>::insert(pos,obj);
					last_to_first();
				}
				else  // 插入链表中部
				{
					ret = LinkList<T>::insert(pos,obj);
				}
				return ret;
			}

			bool remove(int pos)  
			{
				bool ret = 1;
				pos = (this->m_length == 0 ? 0 : (pos % this->m_length));
				if(pos == 0) // 删除0节点
				{
					Node* toDel = this->m_header.next;
					if(this->m_length > 0)  // 节点0存在
					{
						this->m_header.next = toDel->next;  
						this->m_length--;
						if(this->m_length > 0)  // 删除0节点后下个节点存在
						{
							last_to_first();
							if(this->m_current == toDel)
							{
								this->m_current = toDel->next;
							}
						}
						else
						{
							this->m_header.next == NULL;
							this->m_current = NULL;
						}
						this->destroy(toDel);
					}
					else
					{
						this->m_header.next == NULL;
						this->m_current = NULL;
					}
					
				}
				else // 删除中间节点
				{
					ret = LinkList<T>::remove(pos);
				}
				return ret;
			}

			bool set(int pos, const T& obj)
			{
				pos = (this->m_length == 0 ? 0 : (pos % this->m_length));
				return LinkList<T>::set(pos,obj);
			}

			T get(int pos)
			{
				pos = (this->m_length == 0 ? 0 : (pos % this->m_length));
				return LinkList<T>::get(pos);
			}
		
			bool get(int pos, T& obj) const
			{
				pos = (this->m_length == 0 ? 0 : (pos % this->m_length));
				return LinkList<T>::get(pos,obj);
			}

			int find(const T& obj) const
			{
				int ret = -1;
				Node* slider = this->m_header.next;
				for(int i = 0; i < this->m_length; i++)
				{
					if(slider->value == obj)
					{
						ret = i;
						break;
					}
					slider = slider->next;
				}
			}

			void clean()
			{
				for(int i = this->m_length; i > 0; i--)
				{
					if( this->m_length > 1) // 删除中间节点
					{
						remove(1);
					}
					else  // 删除头节点
					{
						Node* toDel = this->m_header.next;
						this->m_header.next = NULL;
						this->m_current = NULL;
						this->m_length = 0;
						this->destroy(toDel);
					}
				}
			}

			bool move(int pos)
			{
				pos = (this->m_length == 0 ? 0 : (pos % this->m_length));
				return LinkList<T>::move(pos);
			}

			bool end()
			{
				return ((this->m_length == 0) || (this->m_current == NULL));
			}

			~CircularList()
			{
				clean();
			}

	};
}

/*
约瑟夫环
num:   总人数
start: 报数起始位置
step:  报数个数
void Josephus(int num, int start, int step)
{
	CircularList<int> cl;
	for(int i = 1; i <= num; i++)
	{
		cl.insert(i);
	}
	cl.move(start - 1); // 循环链表下标从0开始
	while(cl.length() > 0)
	{
		cl.next(step - 1);
		cout << cl.current() << endl;	
		cl.remove(cl.find(cl.current()));
	}
}


*/

#endif
