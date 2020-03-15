/*
*	Pointer: ����ָ��
*	ģ���Ա��
*			pointer
*	ģ�庯����
*			Pointer()	���캯����ʼ��ָ��
*			operator ->	
*			operator *	
*			isNull()	ָ��ǿ�
*			get()		��ȡָ�����ֵ
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
				
				const T* operator -> () const // const����
				{
					return m_pointer;
				}
				
				const T& operator * () const // const����
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
