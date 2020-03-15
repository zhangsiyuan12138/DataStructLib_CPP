/* SmartPoniter: ����ָ��ģ��
 * 1.ָ���������ڽ���ʱ�����ͷŶѿռ� --> ��������
 * 2.һ���ѿռ�ֻ��һ��ָ��ָ��        --> �������캯��,���ظ�ֵ������
 * 3.���ɽ���ָ������ -->
 * 4.���ؽ�ָ�����������Ա���ʷ�  --> ����->��*����
 * 5.ָ���ʼ��ΪNULL --> ���캯��
 * 6.�õ�ָ���ַ --> get����
 * 7.�ж�ָ��ǿ� --> isNULL����
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
		SmartPoniter(T* p = NULL) : Pointer<T>(p) // ���ø��๹�캯��
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
				delete temp; // �쳣��ȫ
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
