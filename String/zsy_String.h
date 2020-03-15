/*
*		String: �ַ�����			�ַ��������ڶѿռ䣬����ֻ�����ַ�ͳ���
*		��Ա������	
*				char* str		�ѿռ��ַ�����ַ
*				m_length		�ѿռ��ַ�������
*		��Ա������
*				init()					��ʼ����ʹ��strdup�������ַ�������һ�ݵ���������������ָ��ͳ���ֵ
*				String()				Ĭ�Ϲ��캯����""��Ϊ�ַ������ݣ��ڳ�ʼ��
*				String(char c)			�ڵ�	���ַ������'\0'��Ϊ�ַ������ڳ�ʼ��
*				String(char* s)			�жϷǿպ��ʼ��
*				String(String& s)		��ʼ��
*				make_mtp(up_str)		����ƥ���	
*				kmp(up_str, sub_str)	up_str��Ѱ���Ƿ���ƥ��sub_str���Ӵ�
*
*				operator ==(String&)	ʹ��strcmp() == 0�ж�
*				operator ==(char*)		ʹ��strcmp() == 0�ж�
*				operator !=(String&)	ʹ��strcmp() != 0�ж�
*				operator !=(char*)		ʹ��strcmp() != 0�ж�
*				operator >=(String&)	ʹ��strcmp() >= 0�ж�
*				operator >=(char*)		ʹ��strcmp() >= 0�ж�
*				operator <=(String&)	ʹ��strcmp() <= 0�ж�
*				operator <=(char*)		ʹ��strcmp() <= 0�ж�
*				operator >(String&)		ʹ��strcmp() > 0�ж�
*				operator >(char*)		ʹ��strcmp() > 0�ж�
*				operator <(String&)		ʹ��strcmp() < 0�ж�
*				operator <(char*)		ʹ��strcmp() < 0�ж�
*
*				operator =(String&)		
*				operator =(char *)		�ж��Ƿ����Ը�ֵ��Ϊs�ڶѿռ���һ�ݿ������ͷ�m_strԭ�����ַ����������俽��ֵ��ʼ��m_str��m_length
*				operator =(char c)		
*
*				operator +(String&)		
*				operator +(char*)		����һ������Ϊm_str+s+1�Ŀռ䣬��m_str��s�����ݱ����ȥ���ͷ�m_strԭ�����ַ�����������m_str��m_length��ֵ
*				operator +=(String&)	
*				operator +=(char*)	
*				
*				String operator - (String&) �ַ��������ᱻ�޸ģ�����һ���µ��ַ���
*				String operator - (char*)
*				String& operator -= (String&)
*				String& operator -= (char*)
*
*				String& replace(target_str,replace_str); �ڸ�����Ѱ�ҵ���target_str��λ�ò���replace_str����
*
*				operator [] (i)			�����������			
*				startwith(str)			�ж�String������strΪ��ͷ
*				endof(str)				�ж�String������strΪ��β
*				insert(i,str)			��i������str�ַ���
*				trim()					ȥ��String��ͷβ�Ŀո�
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
#include"TopClass.h" //TopClass.h �� cstdlib �������һ�𣿣�

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

		String& operator = (const String& obj);  // (StringA = StringB) = StringC ��ֵ���ʽ�ķ���ֵ��һ�����ã����ʽ��������ٱ�������ֵ��
		String& operator = (const char* s); //���ô�����Ա���ֵ��Ҳ���ǿ��Գ����ڸ�ֵ���ŵ���ߣ�Ҳ���Ƿ�const����
		String& operator = (const char c);

		String operator + (const String& obj) const; //  ��ӵ��ַ�������ָ�������ջ�У����ɵ�����ֵ��Ҳ�Ͳ�����������ʱ�ַ�������ָ��
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
