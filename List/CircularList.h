/*
*	CirularList: ѭ������ģ��
*	��Ա������
*			
*	��Ա������
*			last_to_first()						������β�ڵ�
*			bool insert(int pos,const T& obj)	�����±�Ϊpos�Ľڵ㡣���������½ڵ���ͷ�ڵ㣬�½ڵ���0�ڵ㣬�½ڵ���β�ڵ�
*			bool remove(int pos)				ɾ���±�Ϊpos�Ľڵ㡣��������ͷ�ڵ���1�ڵ㣬β�ڵ���1�ڵ㣬ɾ��0�ڵ�
*			bool set(int pos, const T& obj)		����pos�±�ֵ
*			bool get(int pos, T& obj) const		��ȥ�±�pos�ڵ��ֵ
*			int find(const T& obj) const		Ѱ��ֵ��ͬ�ĵ�һ���ڵ���±�
*			void clean()						������нڵ�
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
			bool insert(const T& obj) // Ĭ�ϲ���β��
			{
				return (this->insert(this->m_length,obj));
			}

			bool insert(int pos, const T & obj)
			{
				bool ret = 1;
				pos = pos % (this->m_length + 1);
				if(pos == 0) // ��������ͷ��
				{
					ret = LinkList<T>::insert(pos,obj);
					last_to_first();
				}
				else  // ���������в�
				{
					ret = LinkList<T>::insert(pos,obj);
				}
				return ret;
			}

			bool remove(int pos)  
			{
				bool ret = 1;
				pos = (this->m_length == 0 ? 0 : (pos % this->m_length));
				if(pos == 0) // ɾ��0�ڵ�
				{
					Node* toDel = this->m_header.next;
					if(this->m_length > 0)  // �ڵ�0����
					{
						this->m_header.next = toDel->next;  
						this->m_length--;
						if(this->m_length > 0)  // ɾ��0�ڵ���¸��ڵ����
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
				else // ɾ���м�ڵ�
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
					if( this->m_length > 1) // ɾ���м�ڵ�
					{
						remove(1);
					}
					else  // ɾ��ͷ�ڵ�
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
Լɪ��
num:   ������
start: ������ʼλ��
step:  ��������
void Josephus(int num, int start, int step)
{
	CircularList<int> cl;
	for(int i = 1; i <= num; i++)
	{
		cl.insert(i);
	}
	cl.move(start - 1); // ѭ�������±��0��ʼ
	while(cl.length() > 0)
	{
		cl.next(step - 1);
		cout << cl.current() << endl;	
		cl.remove(cl.find(cl.current()));
	}
}


*/

#endif
