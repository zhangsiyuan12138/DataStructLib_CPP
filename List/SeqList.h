/*
*  	SeqList：线性表抽象类。
*	成员变量：m_array 存储空间指针
*			  m_length 存储空间中的线性表长度
*	成员函数：insert()
*			  remove()
*			  set()
*			  get()
*			  length()   获得线性表长度
*			  clear()    清除线性表
*			  operator[] 重载数组成员访问符
*             capacity() 存储空间大小 
*          
*/

#ifndef SEQLIST_H
#define SEQLIST_H

#include"List.h"
#include"Exception.h"

namespace DSL
{
template <typename T>
class SeqList : public List<T>
{
	protected:
		int m_length;
		T *m_array;
	public:
		bool insert(int pos, const T& obj)
		{
			bool ret = ((pos >= 0) && (pos <= m_length));
			ret = ret && (m_length < capacity());
			if(ret)
				{
					for(int post = m_length - 1; pos <= post; post--)
					{
						m_array[post + 1] = m_array[post];
					}
					m_array[pos] = obj;
					m_length++;
				}
			return ret;
		}

		bool insert(const T& obj)
		{
			return insert(m_length,obj);
		}
		
		bool remove(int pos)
		{
			bool ret = ((0 <= pos) && (pos <= m_length-1));
			if(ret)
				{
					for(int post = pos; post < m_length - 1; post++)
					{
						m_array[post] = m_array[post + 1];
					}
					m_length--;
				}
			return ret;
		}
		
		bool get(int pos, T& obj) const
		{
			bool ret = ((pos >= 0) && (pos <= m_length -1));
			if(ret)
			{
				obj = m_array[pos];
			}
			return ret;
		}
		bool set(int pos,const T& obj)
		{
			bool ret = ((pos >= 0) && (pos <= m_length -1));
			if(ret)
			{
				m_array[pos] = obj;
			}
			return ret;
		}

		int find(const T& obj) const
		{
			int ret = -1;
			for(int i = 0; i < m_length; i++)
			{
				if(m_array[i] == obj)
				{
					ret = i;
					break;
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
			m_length = 0;
		}
		
		T& operator[] (int pos)
		{
			if( pos >= 0 && pos <= m_length -1)
			{
				return m_array[pos];
			}
			else
			{
				THROW_EXCEPTION(IdexOutOfBoundException,"error: index out of bound!");
			}
		}

		T operator[] (int pos) const
		{
			return (const_cast<SeqList<T>&>(*this))[pos];
		}

		virtual int capacity() const = 0; 
};

}

#endif
