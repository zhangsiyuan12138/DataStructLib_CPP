/*
*  	Exception��  �����쳣������   
*	ArithmeticException��       �����쳣�����㣩
*	NullPointerException��      ��ָ���쳣����
*	IdexOutOfBoundException��   Խ���쳣������Խ�磩
*	NotEnoughMemoryException�� �ڴ治���쳣�� ��
*	InvalidParameterException�����������쳣�������Ƿ�Ϸ���
*	InvalidOperationException: ��Ա����������ʱ����״̬����ȷ����ò����쳣
*
*	Exception�ࣺ
*	���ܣ���ӡ�쳣��Ϣ����ӡ�쳣��ַ
*	���캯���������������������캯������ֵ���غ�������Ϣ��ӡ��������ַ��ӡ������
*	��ַ����Ϣ
*
*/


#ifndef EXCEPTION_H	
#define EXCEPTION_H

#include<cstdlib>
#include"TopClass.h"

namespace DSL
{
#define THROW_EXCEPTION(obj,msg) (throw obj(msg,__FILE__,__LINE__)) // obj�׳��쳣�����ͣ�msg�׳����쳣��Ϣ
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
