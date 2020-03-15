/*
*	DynamicArray：动态数组模板
*	成员变量：
*				m_length   动态数组的实时长度
*	成员函数：
*				init()      初始化成员变量,抛出异常
*				copy()      申请堆空间，初始化堆空间
*				update()    初始化成员变量，释放堆空间
*
*				DynamicArray()   申请堆空间,初始化成员变量    
*				DynamicArray()   申请堆空间,初始化堆空间,初始化成员变量  
*				operator=()      申请堆空间,初始化堆空间,初始化成员变量,释放原始堆空间  
*				length()         返回动态数组长度
*				resize()         申请堆空间,初始化堆空间,初始化成员变量,释放原始堆空间
*				~DynamicArray()  释放堆空间
*/

#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include"Array.h"
#include"Exception.h"

namespace DSL
{
	template <typename T>
	class DynamicArray: public Array<T>
	{
		protected:
				int m_length;

				void init(T* array, int length)
				{
					if(array != NULL)
					{
						this->m_array = array;
						this->m_length = length;
					}
					else
					{
						THROW_EXCEPTION(NotEnoughMemoryException, "error: no enough memory ");
					}
				}
				
				T* copy(T* array, int length, int new_length)
				{
					T* ret = new T[new_length];
					if(ret != NULL)
					{
						int size = (new_length > length ? length : new_length);
						for(int i = 0; i < size; i++)
						{
							ret[i] = array[i];
						}
					}
					return ret;
				}

				void update(T* array, int length)
				{
					if(array != NULL)
					{
						T* temp = this->m_array;
						this->m_array = array;
						this->m_length = length;
						delete[] temp;
					}
				}
				
		public:
				DynamicArray(int length)
				{
					init(new T[length],length);
				}

				DynamicArray(const DynamicArray<T>& obj)
				{
					init(copy(obj.m_array,obj.m_length,obj.m_length), obj.m_length);
				}

				DynamicArray<T>& operator=(DynamicArray<T>& obj)
				{
					if(&obj != this)
					{
						init(copy(obj.m_array,obj.m_length,obj.m_length), obj.m_length);
					}
					return *this;
				}

				int length() const
				{
					return m_length;
				}

				void resize(int new_length)
				{
					if(new_length != m_length)
					{
						update(copy(this->m_array, m_length, new_length), new_length);	
					}
				}

				~DynamicArray()
				{
					delete this->m_array;
				}
	};

}

#endif
