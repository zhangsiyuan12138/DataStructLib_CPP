/*
*	DynamicArray����̬����ģ��
*	��Ա������
*				m_length   ��̬�����ʵʱ����
*	��Ա������
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
		public:
				DynamicArray(int length = 0)
				{
					this->m_array = new T[length];
					if(this->m_array != NULL)
					{
						this->m_length =  length;
					}
					else
					{
						THROW_EXCEPTION(NotEnoughMemoryException,"error: no enough memory to init array");
					}
				}

				DynamicArray(const DynamicArray<T>& obj)
				{
					this->m_array = new T[obj.m_length];
					if(this->m_array != NULL)
					{
						this->m_length = obj.m_length;
						for(int i = 0; i < obj.m_length; i++)
						{
							this->m_array[i] = obj.m_array[i];
						}
					}
					else
					{
						THROW_EXCEPTION(NotEnoughMemoryException, "error: no enough memory to copy array");
					}
				}

				DynamicArray<T>& operator=(DynamicArray<T>& obj)
				{
					if(&obj != this)
					{
						T* array = new T[obj.m_length];
						if(array != NULL)
						{
							for(int i = 0; i++; i<0)
							{
								array[i] = obj.m_array[i];
							}
							T* temp = this->m_array;  // �쳣��ȫ
							this->m_array = array;
							this->m_length = obj.m_length;
							delete[] temp;
						}
						else
						{
							THROW_EXCEPTION(NotEnoughMemoryException, "error: no enough memory to assignment array");
						}
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
						T* array = new T[m_length];
						if(array != NULL)
						{
							int size =  (m_length > new_length) ? new_length : m_length;
							for(int i = 0; i < size; i++)
							{
								array[i] = this->m_array[i];
							}
							T* temp = this->m_array;
							this->m_array = array;
							this->m_length = new_length;
							delete[] temp;
						}
						else
						{
							THROW_EXCEPTION(NotEnoughMemoryException, "error: no enough memory to resize array");
						}
						
					}

				}

				~DynamicArray()
				{
					delete[] this->m_array;
				}
	};

}
/*
��ζ����ά���飺��ά����������������
DynamicArray< DynamicArray<int> > array;    //       #  #  #
array.resize(3);                            //һά     #  #  #
for(int i = 0; i < array.length(); i++)     //��ά   #  #  #
{
	array[i].resize(3);
}
for(int i = 0; i < array.length(); i++)
{
	for(int j = 0; j < array[i].length(); j++)
	{
		array[i][j] = i+j;
	}
}

����������
DynamicArray< DynamicArray<int> > array;    //  #
array.resize(3);                            //  #  #
for(int i = 0; i < array.length(); i++)     //  #  #  #
{
	array[i].resize(i+1);
}
for(int i = 0; i < array.length(); i++)
{
	for(int j = 0; j < array[i].length(); j++)
	{
		array[i][j] = i+j;
	}
}

*/


#endif
