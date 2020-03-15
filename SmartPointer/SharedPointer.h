/*
*	SharedPointer:	����ָ��ģ��
*	��Ա������
*			m_ref:	����ָ��
*	��Ա������
*			SharedPointer:	�o����ָ������ѿռ䣬��ʼ��m_pointer,m_ptr��������һ��
*			SharedPointer:	����m_ref,m_pointer��������һ��
*			operator =   :  �����ֵ����ĳ�Ա���������¸�ֵ��������һ��
*			clear()		 :  ��������Ա�������жϼ����Ƿ�Ϊ�㡣
*			
*			operator ==
*           operator !=
*/
#ifndef SHAREDPOINTER_H
#define SHAREDPOINTER_H

#include"Pointer.h"
#include"Exception.h"
#include<cstdlib>

namespace DSL
{
	template < typename T >
	class SharedPointer : public Pointer<T>
	{
	protected:
			int* m_ref;
	public:
			SharedPointer(T* ptr = NULL) : m_ref(NULL)
			{
				if(ptr != NULL)
				{
					this->m_ref = static_cast<int*>(std::malloc(sizeof(int)));
					if(this->m_ref != NULL)
					{
						this->m_pointer = ptr;
						*(this->m_ref) = 1;
					}
					else
					{
						THROW_EXCEPTION(NotEnoughMemoryException,"error: no enougth memory to create count reference!");
					}
				}
			}
			
			SharedPointer(const SharedPointer<T>& obj)
			{
				this->m_ref = obj.m_ref;
				this->m_pointer = obj.m_pointer;
				if( this->m_ref != NULL )
				{
					*(this->m_ref)++;
				}
			}

			SharedPointer<T>& operator = (const SharedPointer<T>& obj)
			{
				if(this != &obj)
				{
					clean();
					this->m_pointer = obj.m_pointer;
					this->m_ref = obj.m_ref;
					if(this->m_pointer != NULL)
					{
						*(this->m_ref)++;
					}
				}
				return *this;
			}

			void clean()
			{
				T* temp_pointer = this->m_pointer;
				int* temp_ref = this->m_ref;
				this->m_pointer = NULL;
				this->m_ref = NULL;
				if(temp_ref)
				{
					*temp_ref--;
					if(*temp_ref == 0)
					{
						std::free(temp_ref);
						delete temp_pointer;
					}
				}
			}
	};

template <typename T>
	bool operator == (const SharedPointer<T>& obj1,const SharedPointer<T>& obj2)
	{
		return (obj1.get() == obj2.get());
	}

template <typename T>
	bool operator != (const SharedPointer<T>& obj1,const SharedPointer<T>& obj2)
	{
		return !(obj1 == obj2);
	}

}

#endif
