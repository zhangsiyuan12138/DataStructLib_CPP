/*
*	���㸸�ࣺSpuperClass,ͳһ new��new[]ʧ��ʱΪ����NULL�����׳��쳣
*/

#ifndef TOPCLASS_H
#define TOPCLASS_H

namespace DSL
{
	class TopClass
	{
	public:
		#define ture 1
		#define false 0
		void* operator new (size_t)throw();  // C++11����дnew ����ֵ������void* ����������size_t
		void  operator delete(void* p);	
		void* operator new[] (size_t)throw();
		void  operator delete[] (void* p);
		bool operator == (const TopClass& obj);  // ������������find���������Զ������ıȽϣ�Ĭ��ʵ��ͨ����ַ�Ƚ�
		bool operator != (const TopClass& obj);
		virtual ~TopClass() = 0;  // ���麯����������Խ��ж�̬ʶ��
	};
}

#endif
