/*
*	StaticArray: 静态数组
*	成员变量：
*				m_space  定义数组实体
*			
*	成员函数：
*				StaticArray 构造函数
*				StaticArray 拷贝构造函数
*				operator=   赋值重载函数
*				length()    长度函数
*/
#ifndef STATICARRAY_H
#define STATICARRAY_H

#include"Array.h"

namespace DSL
{
	template <typename T, int N>
	class StaticArray : public Array<T>
	{
		protected:
				T m_space[N];    // 使用C++的原生数组
		public:
				StaticArray()
				{
					this->m_array = m_space;
				}
				
				StaticArray(const StaticArray<T,N>& obj)
				{
					this->m_array = m_space;
					for(int i = 0; i<N; i++)
					{
						m_space[i] = obj.m_space[i];
					}
				}

				StaticArray<T,N>& operator= (const StaticArray<T,N>& obj)
				{
					if(this != &obj)
					{
						for(int i = 0; i < N; i++)
						{
							m_space[i] = obj.m_space[i];	
						}
					}
					else
					{
						return *this;
					}
				}

				int length() const
				{
					return N;
				}
	};
}
#endif
