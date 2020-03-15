/*
*	顶层父类：SpuperClass,统一 new，new[]失败时为返回NULL，不抛出异常
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
		void* operator new (size_t)throw();  // C++11中重写new 返回值必须是void* 参数必须是size_t
		void  operator delete(void* p);	
		void* operator new[] (size_t)throw();
		void  operator delete[] (void* p);
		bool operator == (const TopClass& obj);  // 用于链表类中find函数进行自定义对象的比较，默认实现通过地址比较
		bool operator != (const TopClass& obj);
		virtual ~TopClass() = 0;  // 纯虚函数，子类可以进行动态识别
	};
}

#endif
