#include"Exception.h"
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<iostream>

using namespace std; 

namespace DSL 
{
	void Exception::init(const char* message, const char* file, int line)
	{
		pt_message = (message ? strdup(message) : strdup("no message!")); // strdup(const char *p)返回一个指针，这个指针指向p的一个复制串
		if(file != NULL)
		{
			char str[10];
			sprintf(str,"%d",line);
			pt_location = static_cast<char*>(malloc(sizeof(str) + sizeof(file) + 2));
			if(pt_location != NULL)
				{
					pt_location = strcpy(pt_location, file);
					pt_location = strcat(pt_location, ":"); 
					pt_location = strcat(pt_location, str);
					cout << "Error info : " << pt_message << endl;
					cout << "Error location : " << pt_location << endl;
				}
		}
		else
		{
			pt_location = NULL;	
		}	
	}

	Exception::Exception(const char * message)
	{
		init(message,NULL,0);
	}

	Exception::Exception(const char * file,int line)
	{
		init(NULL,file,line);
	}

	Exception::Exception(const char*message,const char * file, int line)
	{
		init(message,file,line);
	}

	Exception::Exception(const Exception& obj)
	{
		pt_location = strdup(obj.pt_location);
		pt_message = strdup(obj.pt_message);
	}

	Exception& Exception::operator = (const Exception& obj)
	{
		if(this != &obj)
		{
			free(obj.pt_location);
			free(obj.pt_message);
			pt_location = strdup(obj.pt_location);
			pt_message = strdup(obj.pt_message);
		}
		else
		{
			return *this;
		}

	}

	const char* Exception::location() const
	{
		return pt_location;
	}

	const char* Exception::message() const
 	{
 		return pt_message;
	}

	Exception::~Exception()
	{
		delete pt_location;
		delete pt_message;
	}

}



