/*
*	StaticArray: ��̬����
*	��Ա������
*				m_space  ��������ʵ��
*			
*	��Ա������
*				StaticArray ���캯��
*				StaticArray �������캯��
*				operator=   ��ֵ���غ���
*				length()    ���Ⱥ���
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
				T m_space[N];    // ʹ��C++��ԭ������
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
