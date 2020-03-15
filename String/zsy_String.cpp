#include"zsy_String.h"
#include<cstring>
#include<cstdio>

using namespace std;

namespace DSL
{
	void String::init(const char* s)
	{
		m_str = strdup(s);
		if(m_str)
		{
			m_length = strlen(m_str);
		}
		else
		{
			THROW_EXCEPTION(NotEnoughMemoryException,"error: no enough memeory!");
		}
	}

	bool String::equal(const char* orig_str, const char* insert_str,int insert_len) const
	{
		bool ret = 1;
		for(int i = 0; i < insert_len && ret; i++)
		{
			ret = ret && (orig_str[i] == insert_str[i]);
		}
		return ret;
	}

	int* String::make_mtp(const char* up_str)
	{
		int ll = 0;
		int len = strlen(up_str);
		int* pmt = static_cast<int*>(malloc(sizeof(int) * len));

		if(pmt != NULL)
		{
			pmt[0] = 0;
			for(int i = 0; i < len; i++)
			{
				while((ll > 0) && (pmt[ll] != pmt[i]))
				{
					ll = pmt[ll - 1];			
				}

				if(pmt[ll] == pmt[i])
				{
					++ll;
				}
			}
		}
		return pmt;
	}

	int String::kmp(const char* up_str, const char* sub_str)
	{
		int ret = -1;
		int up_len = strlen(up_str);
		int sub_len = strlen(sub_str);
		int* pmt = make_mtp(up_str);

		if((pmt != NULL && up_len >= sub_len && sub_len > 0))
		{
			for(int i = 0, j = 0;i < up_len ;i++)
			{
				while(j > 0 && up_str[i] != sub_str[j])
				{
					j = pmt[j - 1];
				}
				if(up_str[i] == sub_str[j])
				{
					j++;
				}
				if(j == sub_len)
				{
					ret = i + 1 - sub_len;
					break;
				}
			}
		}
		free(pmt);
		return ret;
	}
		
	String::String()				
	{
		init("");
	}
	
	String::String(char c)
	{
		char temp_str[] = {c,'\0'};
		init(temp_str);
	}
	
	String::String(const char* s)	
	{
		init(s ? s : "");
	}
	
	String::String(const String& s)		
	{
		init(s.m_str);	
	}

	int String::length() const
	{
		return m_length;
	}
	
	const char* String::str() const
	{
		return m_str;
	}
	
	bool String::operator == (const String& obj) const
	{
		return (strcmp(obj.m_str,m_str) == 0);
	}
	
	bool String::operator == (const char* s) const
	{
		return (strcmp(s,m_str) == 0);
	}
	
	bool String::operator != (const String& obj) const
	{
		return (strcmp(obj.m_str,m_str) != 0);
	}
	
	bool String::operator != (const char* s) const
	{
		return (strcmp(s,m_str) != 0);
	}
	
	bool String::operator >= (const String& obj) const
	{
		return (strcmp(obj.m_str,m_str) >= 0);
	}
	
	bool String::operator >= (const char* s) const
	{
		return (strcmp(s,m_str) >= 0);
	}
	
	bool String::operator <= (const String& obj) const
	{
		return (strcmp(obj.m_str,m_str) <= 0);
	}
	
	bool String::operator <= (const char* s) const
	{
		return (strcmp(s,m_str) >= 0);
	}
	
	bool String::operator > (const String& obj) const
	{
		return (strcmp(obj.m_str,m_str) > 0);
	}
	
	bool String::operator > (const char* s) const
	{
		return (strcmp(s,m_str) > 0);
	}
	
	bool String::operator < (const String& obj) const
	{
		return (strcmp(obj.m_str,m_str) < 0);
	}
	
	bool String::operator < (const char* s) const
	{
		return (strcmp(s,m_str) < 0);
	}

	String& String::operator = (const String& obj)
	{
		return (*this = obj.m_str);  //? *this
	}
	
	String& String::operator = (const char* s)
	{
		if(this->m_str != s)
		{
			char* temp_str = strdup(s ? s : "");   //深拷贝
			if(temp_str)
			{
				free(m_str);
				m_str = temp_str;
				m_length = strlen(temp_str);
			}
			else
			{
				THROW_EXCEPTION(NotEnoughMemoryException,"error：no enough memeory to make a string copy!");
			}
		}
		return *this;  // 当前对象作为返回值返回，可以实现连续赋值。
	}				   // (StringA = StringB) = StringC   StringA作为一个存在于栈空间引用变量，
					   // 被赋值之后指向引用变量StringB指向的存在于堆空间的对象，后又指向StringC指向的存在于堆空间的StringC对象。
	
	String& String::operator = (const char c)
	{
		char temp_str[] = {c,'\0'};
		return (*this = temp_str);
	}

	String String::operator + (const String& obj) const
	{
		return (*this + obj.m_str);
	}
	
	String String::operator + (const char* s) const
	{
		String temp_String;
		int len = strlen((s ? s : "")) + m_length;
		char* temp_str = reinterpret_cast<char*>(malloc(len + 1));
		if(temp_str)
		{
			strcpy(temp_str,m_str);
			strcat(temp_str,(s ? s : ""));
			temp_str[len] = '\0';
			free(temp_String.m_str);  // 为什释放新对象在堆空间的字符串，应该释放this.m_str的啊
			temp_String.m_length = len;
			temp_String.m_str = temp_str;
		}
		else
		{
			THROW_EXCEPTION(NotEnoughMemoryException,"error：no enough memeory to malloc!");
		}	
	    return temp_String;
	}
	
	String& String::operator += (const String& obj)
	{
		return (*this = *this + obj);
	}
	
	String& String::operator += (const char* s)
	{
		return (*this = *this + s);
	}

	String String::operator - (const String& sub_str) const
	{
		return String(*this).remove(sub_str);
	}

	String String::operator - (const char* sub_str) const
	{
		return String(*this).remove(sub_str);
	}

	String& String::operator -= (const String& sub_str)
	{
		return remove(sub_str);
	}

	String& String::operator -= (const char* sub_str)
	{
		return remove(sub_str);
	}

	String& String::replace(const char* target_str, const char* replace_str)
	{
		int pos = indexof(target_str);
		if(pos >= 0)
		{
			remove(target_str);
			insert(pos, replace_str);
		}
		return *this;
	}
	
	String& String::replace(const String& target_str, const char* replace_str)
	{
		return replace(target_str.m_str,replace_str);
	}
	
	String& String::replace(const char* target_str, const String& replace_str)
	{
		return replace(target_str,replace_str.m_str);
	}

	String& String::replace(const String& target_str, const String& replace_str)
	{
		return replace(target_str.m_str,replace_str.m_str);
	}

	char String::operator [] (int i) const
	{
		return (const_cast<String&>(*this)[i]);	
	}
	
	char& String::operator [] (int i)
	{
		if(i >= 0 && i < m_length)
		{
			return m_str[i];
		}
		else
		{
			THROW_EXCEPTION(IdexOutOfBoundException,"error: index out of bound!");
		}
	}
	
	bool String::startwith(const char* str) const
	{
		bool ret = (str ? 1 : false);
		if(ret)
		{
			int len = strlen(str);
			ret = (len < m_length ) && equal(m_str,str,len);
		}
		return ret;
	}
	
	bool String::startwith(const String& obj) const
	{
		return startwith(obj.m_str);
	}
	
	bool String::endof(const char* str) const
	{
		bool ret = (str ? 1 : false);
		if(ret)
		{
			int len = strlen(str);
			char* temp_str = m_str + m_length - len;
			ret = (len < m_length ) && equal(temp_str,str,len);
		}
		return ret;
	}
	
	bool String::endof(const String& obj) const
	{
		return endof(obj.m_str);
	}
	
	String& String::insert(int pos, char* str)
	{
		if((pos >= 0 && pos <= m_length ) && (str != NULL && str[0] != '\0'))
		{
			int len = strlen(str);
			char* temp_str = reinterpret_cast<char*>(malloc(len + m_length + 1));
			if(temp_str)
			{
				strncpy(temp_str, m_str, pos);
				strncpy(temp_str + pos, str, len);
				strncpy(temp_str + pos + len, m_str + pos, m_length - pos);
				temp_str[m_length + len] = '\0';
				free(m_str);

				m_str = temp_str;
				m_length = m_length + len;
			}
			else
			{
				THROW_EXCEPTION(InvalidOperationException,"error: no enougth memory to malloc!");
			}
		}
		return *this;
	}

	
	String& String::insert(int pos, const String& obj)
	{
		return insert(pos,obj.m_str);
	}
	
	String& String::trim()
	{
		int front = 0;
		int tail = m_length - 1;
		while(m_str[front] == ' ') 
		{
			front++;
		}
		while(m_str[tail] == ' ') 
		{
			tail--;
		}
		char* temp_str = reinterpret_cast<char*>(malloc(tail - front + 2));
		strncpy(temp_str, m_str + front, tail - front + 1);
		temp_str[ tail - front + 2] = '\0';
		free(m_str);
		m_str = temp_str;
		m_length = tail - front + 1;
	}

	int String::indexof(const char* sub_str) const
	{
		return kmp(m_str, sub_str ? sub_str : "");
	}
	
	int String::indexof(const String& sub_str) const
	{
		return kmp(m_str, sub_str.m_str);
	}

	String& String::remove(int offset, int len)
	{
		if( 0 <= offset && offset < m_length)
		{
			int start = offset;
			int end = offset + len;
			while(start < end && end < m_length)
			{
				m_str[start++] = m_str[end++];				
			}
			m_str[start] = '\0';
			m_length = end;
		}
		return *this;
	}

	String& String::remove(const char* sub_str)
	{
		remove(indexof(sub_str), strlen(sub_str));
	}

	String& String::remove(const String& sub_str)
	{
		remove(indexof(sub_str), sub_str.m_length);
	}
	
	String::~String()
	{
		free(m_str);
	}
}
