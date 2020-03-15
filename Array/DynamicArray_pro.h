/*
*	DynamicArray����̬����ģ��
*	��Ա������
*				m_length   ��̬�����ʵʱ����
*	��Ա������
*				init()      ��ʼ����Ա����,�׳��쳣
*				copy()      ����ѿռ䣬��ʼ���ѿռ�
*				update()    ��ʼ����Ա�������ͷŶѿռ�
*
*				DynamicArray()   ����ѿռ�,��ʼ����Ա����    
*				DynamicArray()   ����ѿռ�,��ʼ���ѿռ�,��ʼ����Ա����  
*				operator=()      ����ѿռ�,��ʼ���ѿռ�,��ʼ����Ա����,�ͷ�ԭʼ�ѿռ�  
*				length()         ���ض�̬���鳤��
*				resize()         ����ѿռ�,��ʼ���ѿռ�,��ʼ����Ա����,�ͷ�ԭʼ�ѿռ�
*				~DynamicArray()  �ͷŶѿռ�
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
