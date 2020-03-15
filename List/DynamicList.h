/*
*	DynamicList：动态顺序存储链表
*	成员变量：m_capacity        顺序存储空间大小
*			
*	成员函数：DynamicList       申请堆空间
*			  capacity     返回堆空间大小m_capacity
*			  resize       重新设置存储空间大小
*			  ~DynamicList 归还空间
*/
#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include"SeqList.h"
#include"Exception.h"

namespace DSL
{
template <typename T>
class DynamicList : public SeqList<T>
{
	protected:
		int m_capacity;
	public:
		DynamicList(int size)
		{
			this->m_array = new T[size];
			if(this->m_array != NULL)
			{
				this->m_capacity = size;
				this->m_length = 0;
			}
			else
			{
				THROW_EXCEPTION(NotEnoughMemoryException,"error: no enough memory!");
			}
		}

		int capacity() const
		{
			return m_capacity;
		}

		void resize(int new_size)
		{
			if(new_size != m_capacity)
			{
				T* array_temp = new T[new_size];  // 如果直接将申请空间地址赋值给this->m_array，将会丢失原来的数据
				if(array_temp != NULL)
				{
					int length_temp = (new_size > this->m_length ? this->m_length : new_size );
					for(int i = 0; i < length_temp; i++)
					{
						 array_temp[i] = this->m_array[i];  // 赋值操作符发重载函数发生异常？
					}
					T* temp_m_array = this->m_array;   //1.便于释放重定义大小前的空间
													   //2.如果直接delete this->m_array时，如果析构函数抛出异常将会直接返回，无法初始化成员变量
					this->m_capacity = new_size;       // 异常安全
					this->m_length = length_temp;
					this->m_array  =array_temp;

					delete[] temp_m_array;
				}
				else
				{
					THROW_EXCEPTION(NotEnoughMemoryException,"error: no enough memory!");
				}
			}

		}

		~DynamicList()
		{
			delete[] this->m_array;
		}
		
};

}

#endif
