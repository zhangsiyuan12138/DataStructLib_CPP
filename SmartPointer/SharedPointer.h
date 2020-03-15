/*
*	SharedPointer:	共享指针模板
*	成员变量：
*			m_ref:	计数指针
*	成员函数：
*			SharedPointer:	給计数指针申请堆空间，初始化m_pointer,m_ptr。计数加一。
*			SharedPointer:	设置m_ref,m_pointer。计数加一。
*			operator =   :  清除左值对象的成员变量，重新赋值。计数加一。
*			clear()		 :  清除对象成员变量，判断计数是否为零。
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
