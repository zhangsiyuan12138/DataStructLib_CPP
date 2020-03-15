/*
*		String: 字符串类			字符串保存在堆空间，对象只有其地址和长度
*		成员变量：	
*				char* str		堆空间字符串地址
*				m_length		堆空间字符串长度
*		成员函数：
*				init()					初始化，使用strdup将参数字符串拷贝一份到堆区，并返回其指针和长度值
*				String()				默认构造函数将""做为字符串内容，在初始化
*				String(char c)			在单	个字符后加上'\0'作为字符串，在初始化
*				String(char* s)			判断非空后初始化
*				String(String& s)		初始化
*				make_mtp(up_str)		生成匹配表	
*				kmp(up_str, sub_str)	up_str中寻找是否有匹配sub_str的子串
*
*				operator ==(String&)	使用strcmp() == 0判断
*				operator ==(char*)		使用strcmp() == 0判断
*				operator !=(String&)	使用strcmp() != 0判断
*				operator !=(char*)		使用strcmp() != 0判断
*				operator >=(String&)	使用strcmp() >= 0判断
*				operator >=(char*)		使用strcmp() >= 0判断
*				operator <=(String&)	使用strcmp() <= 0判断
*				operator <=(char*)		使用strcmp() <= 0判断
*				operator >(String&)		使用strcmp() > 0判断
*				operator >(char*)		使用strcmp() > 0判断
*				operator <(String&)		使用strcmp() < 0判断
*				operator <(char*)		使用strcmp() < 0判断
*
*				operator =(String&)		
*				operator =(char *)		判断是否是自赋值，为s在堆空间做一份拷贝，释放m_str原来的字符串，并用其拷贝值初始化m_str和m_length
*				operator =(char c)		
*
*				operator +(String&)		
*				operator +(char*)		申请一个长度为m_str+s+1的空间，将m_str和s的内容保存进去，释放m_str原来的字符串，再设置m_str和m_length的值
*				operator +=(String&)	
*				operator +=(char*)	
*				
*				String operator - (String&) 字符串本身不会被修改，产生一个新的字符串
*				String operator - (char*)
*				String& operator -= (String&)
*				String& operator -= (char*)
*
*				String& replace(target_str,replace_str); 在父串中寻找到与target_str的位置并用replace_str代替
*
*				operator [] (i)			重载数组访问			
*				startwith(str)			判断String类是以str为开头
*				endof(str)				判断String类是以str为结尾
*				insert(i,str)			在i处插入str字符串
*				trim()					去掉String类头尾的空格
*
*				int indexof(const char* sub_str) const;
*				int indexof(const String& sub_str) const;
*				String& remove(int offset, int len);
*				String& remove(const char* sub_str);
*				String& remove(const String& sub_str);
*
*
*/

#ifndef STRING_H
#define STRING_H

#include<cstdlib>
#include"TopClass.h" //TopClass.h 和 cstdlib 必须放在一起？？

#include"Exception.h"

namespace DSL
{
	class String : public TopClass
	{
	protected:
		char* m_str;
		int m_length;
		void init(const char* c);
		bool equal(const char* orig_str, const char* insert_str,int insert_len) const;
		static int* make_mtp(const char* up_str);
		static int kmp(const char* up_str, const char* sub_str);
	public:
		String();				
		String(char c);			
		String(const char* s);		
		String(const String& s);		

		int length() const;
		const char* str() const;
	
		bool operator == (const String& obj) const;
		bool operator == (const char* s) const;
		bool operator != (const String& obj) const;
		bool operator != (const char* s) const;
		bool operator >= (const String& obj) const;
		bool operator >= (const char* s) const;
		bool operator <= (const String& obj) const;
		bool operator <= (const char* s) const;
		bool operator > (const String& obj) const;
		bool operator > (const char* s) const;
		bool operator < (const String& obj) const;
		bool operator < (const char* s) const;

		String& operator = (const String& obj);  // (StringA = StringB) = StringC 赋值表达式的返回值是一个引用，表达式整体可以再被当作左值。
		String& operator = (const char* s); //引用代表可以被赋值，也就是可以出现在赋值符号的左边，也就是非const对象
		String& operator = (const char c);

		String operator + (const String& obj) const; //  相加的字符串对象指针存在于栈中，不可当作左值，也就不可以引用临时字符串对象指针
		String operator + (const char* s) const;
		String& operator += (const String& obj);
		String& operator += (const char* s);

		String operator - (const String& sub_str) const;
		String operator - (const char* sub_str) const;
		String& operator -= (const String& sub_str);
		String& operator -= (const char* sub_str);

		String& replace(const char* target_str, const char* replace_str);
		String& replace(const String& target_str, const char* replace_str);
		String& replace(const char* target_str, const String& replace_str);
		String& replace(const String& target_str, const String& replace_str);

		char operator [] (int i) const;
		char& operator [] (int i);
		bool startwith(const char* str) const;
		bool startwith(const String& obj) const;
		bool endof(const char* str) const;
		bool endof(const String& obj) const;
		String& insert(int i, char* str);
		String& insert(int i, const String& obj);
		String& trim();

		int indexof(const char* sub_str) const;
		int indexof(const String& sub_str) const;
		String& remove(int offset, int len);
		String& remove(const char* sub_str);
		String& remove(const String& sub_str);

		~String();
	};
}
#endif
