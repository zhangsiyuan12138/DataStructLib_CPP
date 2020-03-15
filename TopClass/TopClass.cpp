#include<cstdlib>
#include"TopClass.h"

using namespace std;

namespace DSL
{
	void* TopClass::operator new (size_t size) throw() // C++11��дnew������ ����ֵ������void* �������ͱ�����size_t
	{
		return malloc(size);
	}
	void TopClass::operator delete (void *p)
	{
		free(p);
	}
	void* TopClass::operator new[] (size_t size) throw()
	{
		return malloc(size);
	}
	void TopClass::operator delete[] (void *p)
	{
		free(p);
	}
	bool TopClass::operator == (const TopClass& obj)
	{
		return (this == &obj);
	}
	bool TopClass::operator != (const TopClass& obj)
	{
		return (this != &obj);
	}
	TopClass::~TopClass() 
	{
	}
	
}

