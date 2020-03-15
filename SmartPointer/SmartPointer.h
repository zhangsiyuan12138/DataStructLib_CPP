/* SmartPoniter: 智能指针模板
 * 1.指针生命周期结束时主动释放堆空间 --> 析构函数
 * 2.一个堆空间只由一个指针指向        --> 拷贝构造函数,重载赋值符函数
 * 3.不可进行指针运算 -->
 * 4.重载解指针操作符，成员访问符  --> 重载->和*函数
 * 5.指针初始化为NULL --> 构造函数
 * 6.得到指针地址 --> get函数
 * 7.判断指针非空 --> isNULL函数
 */
 
#ifndef  SMARTPOINTER_H
#define  SMARTPOINTER_H

#include<iostream>
#include"Pointer.h"


namespace DSL
{
	template <typename T>
	class SmartPoniter : public Pointer<T>
	{
	public:
		SmartPoniter(T* p = NULL) : Pointer<T>(p) // 调用父类构造函数
	    {	}
		
		SmartPoniter(const SmartPoniter<T>& obj) 
		{
			this->m_pointer = obj.m_pointer;
			const_cast<SmartPoniter<T>&>(obj).m_pointer = NULL;
		}
		
		SmartPoniter<T>& operator = (const SmartPoniter<T>& obj)  
		{
	     	if(this != &obj)
	   		{
	   			T* temp = this->m_pointer;
				this->m_pointer = obj.m_pointer;
				const_cast<SmartPoniter<T>&>(obj).m_pointer = NULL;
				delete temp; // 异常安全
			}
			return *this;
		}
		
		~SmartPoniter() 
		{
			delete this->m_pointer;
		}

	};
}

#endif
