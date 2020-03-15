/*
 *	Array: 数组类接口
 *	成员变量：
 *				m_array    指向子类的实体数组地址
 *  成员函数：
 *				set        设置数组某一项值
 *				get		   获取数组某一项值
 *				length     纯虚函数
 *				operator[]
*/

#ifndef ARRAY_H
#define ARRAY_H

#include "TopClass.h"
#include "Exception.h"


namespace DSL
{
	template <typename T>
	class Array: public TopClass
	{
		protected:
				T* m_array;
		public:
				virtual bool set(int pos, const T& obj)
				{
					if((pos >= 0) && ( pos < length()))
					{
						m_array[pos] = obj;	
						return 1;
					}
					else
					{
						return false;
					}
				}

				virtual bool get(int pos, T& obj) const
				{
				    if((pos >= 0) && ( pos < length()))
					{
						obj = m_array[pos];	
						return 1;
					}
					else
					{
						return false;
					}
				}

				T& operator[] (int pos)
				{
					if((pos >= 0) && (pos < length()))
					{
						return m_array[pos];
					}
					else
					{
						THROW_EXCEPTION(IdexOutOfBoundException, "error: index is out of bound!");
					}
				}

				T operator[] (int pos) const
				{
					return const_cast<Array<T>&>(*this)[pos];
				}

				T* array() const
				{
					return m_array;
				}
				virtual int length() const = 0 ;
	};

}

#endif
