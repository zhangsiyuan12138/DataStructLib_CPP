/*
*  	Exception：  顶层异常抽象类   
*	ArithmeticException：       计算异常（除零）
*	NullPointerException：      空指针异常（）
*	IdexOutOfBoundException：   越界异常（数组越界）
*	NotEnoughMemoryException： 内存不足异常（ ）
*	InvalidParameterException：参数错误异常（参数是否合法）
*	InvalidOperationException: 成员函数被调用时，其状态不正确则调用操作异常
*
*	Exception类：
*	功能：打印异常信息，打印异常地址
*	构造函数，析构函数，拷贝构造函数，赋值重载函数，信息打印函数，地址打印函数。
*	地址，信息
*
*/


#ifndef EXCEPTION_H	
#define EXCEPTION_H

#include<cstdlib>
#include"TopClass.h"

namespace DSL
{
#define THROW_EXCEPTION(obj,msg) (throw obj(msg,__FILE__,__LINE__)) // obj抛出异常的类型，msg抛出的异常信息
	class Exception : public TopClass 
	{
	protected:
		char* pt_location;
		char* pt_message;
		void init(const char* message,const char* file,int line);
	public:
		Exception(const char* message);
		Exception(const char* file,int line);
		Exception(const char* message,const char* file,int line);
		
		Exception(const Exception& obj);
		Exception& operator = (const Exception& obj);

		virtual const char* location()const;
		virtual const char* message()const;	
		
		virtual ~Exception() = 0;
	};

	class ArithmeticException: public Exception 
	{
	public:
		ArithmeticException():Exception(NULL){}
		ArithmeticException(const char* message):Exception(message){}
		ArithmeticException(const char* file,int line):Exception(file,line){}
		ArithmeticException(const char* message,const char* file,int line):Exception(message,file,line){}

		ArithmeticException(const ArithmeticException& obj):Exception(obj){}
		ArithmeticException& operator = (const ArithmeticException& obj)
		{
			Exception::operator=(obj);
			return *this;
		}
	};
		
	class NullPointerException: public Exception 
	{
	public:
		NullPointerException():Exception(NULL){}
		NullPointerException(const char* message):Exception(message){}
		NullPointerException(const char* file,int line):Exception(file,line){}
		NullPointerException(const char* message,const char* file,int line):Exception(message,file,line){}

		NullPointerException(const NullPointerException& obj):Exception(obj){}
		NullPointerException& operator = (const NullPointerException& obj)
		{
			Exception::operator=(obj);
			return *this;
		}
	};
		
	class IdexOutOfBoundException: public Exception 
	{
	public:
		IdexOutOfBoundException():Exception(NULL){}
		IdexOutOfBoundException(const char* message):Exception(message){}
		IdexOutOfBoundException(const char* file,int line):Exception(file,line){}
		IdexOutOfBoundException(const char* message,const char* file,int line):Exception(message,file,line){}

		IdexOutOfBoundException(const IdexOutOfBoundException& obj):Exception(obj){}
		IdexOutOfBoundException& operator = (const IdexOutOfBoundException& obj)
		{
			Exception::operator=(obj);
			return *this;
		}
	};
				
	class NotEnoughMemoryException: public Exception 
	{
	public:
		NotEnoughMemoryException():Exception(NULL){}
		NotEnoughMemoryException(const char* message):Exception(message){}
		NotEnoughMemoryException(const char* file,int line):Exception(file,line){}
		NotEnoughMemoryException(const char* message,const char* file,int line):Exception(message,file,line){}

		NotEnoughMemoryException(const NotEnoughMemoryException& obj):Exception(obj){}
		NotEnoughMemoryException& operator = (const NotEnoughMemoryException& obj)
		{
			Exception::operator=(obj);
			return *this;
		}
	};
		
	class InvalidParameterException: public Exception 
	{
	public:
		InvalidParameterException():Exception(NULL){}
		InvalidParameterException(const char* message):Exception(message){}
		InvalidParameterException(const char* file,int line):Exception(file,line){}
		InvalidParameterException(const char* message,const char* file,int line):Exception(message,file,line){}

		InvalidParameterException(const InvalidParameterException& obj):Exception(obj){}
		InvalidParameterException& operator = (const InvalidParameterException& obj)
		{
			Exception::operator=(obj);
			return *this;
		}
	};
				
	class InvalidOperationException: public Exception 
	{
	public:
		InvalidOperationException():Exception(NULL){}
		InvalidOperationException(const char* message):Exception(message){}
		InvalidOperationException(const char* file,int line):Exception(file,line){}
		InvalidOperationException(const char* message,const char* file,int line):Exception(message,file,line){}

		InvalidOperationException(const InvalidOperationException& obj):Exception(obj){}
		InvalidOperationException& operator = (const InvalidOperationException& obj)
		{
			Exception::operator=(obj);
			return *this;
		}
	};
}

	 
#endif
