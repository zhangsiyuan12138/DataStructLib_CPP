/*
*	Pointer: 智能指针
*	模板成员：
*			pointer
*	模板函数：
*			Pointer()	构造函数初始化指针
*			operator ->	
*			operator *	
*			isNull()	指针非空
*			get()		获取指针变量值
*/

#ifndef POINTER_H
#define POINTER_H

#include"TopClass.h"

namespace DSL
{
	template <typename T>
	class Pointer : public TopClass
	{
		protected:
				T* m_pointer;
		public:
				Pointer(T* ptr = NULL)
				{
					m_pointer = ptr;
				}
				
				T* operator -> ()
				{
					return m_pointer;
				}
				
				T& operator * ()
				{
					return *m_pointer;
				}
				
				const T* operator -> () const // const重载
				{
					return m_pointer;
				}
				
				const T& operator * () const // const重载
				{
					return *m_pointer;
				}
				
				bool isNull() const
				{
					return m_pointer == NULL;
				}
				
				T* get() const
				{
					return m_pointer;
				}
				
	};

}

#endif
