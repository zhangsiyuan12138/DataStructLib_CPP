/*
*	DynamicList����̬˳��洢����
*	��Ա������m_capacity        ˳��洢�ռ��С
*			
*	��Ա������DynamicList       ����ѿռ�
*			  capacity     ���ضѿռ��Сm_capacity
*			  resize       �������ô洢�ռ��С
*			  ~DynamicList �黹�ռ�
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
				T* array_temp = new T[new_size];  // ���ֱ�ӽ�����ռ��ַ��ֵ��this->m_array�����ᶪʧԭ��������
				if(array_temp != NULL)
				{
					int length_temp = (new_size > this->m_length ? this->m_length : new_size );
					for(int i = 0; i < length_temp; i++)
					{
						 array_temp[i] = this->m_array[i];  // ��ֵ�����������غ��������쳣��
					}
					T* temp_m_array = this->m_array;   //1.�����ͷ��ض����Сǰ�Ŀռ�
													   //2.���ֱ��delete this->m_arrayʱ��������������׳��쳣����ֱ�ӷ��أ��޷���ʼ����Ա����
					this->m_capacity = new_size;       // �쳣��ȫ
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
