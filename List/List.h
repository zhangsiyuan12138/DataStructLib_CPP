/*
* List类：线性表接口。
* 继承TopClass类，被SeqList继承。
* 纯虚函数：插入，删除，设置值，获得值，获得长度，清除线性表。
*
*/

#ifndef LIST_H
#define LIST_H

#include"TopClass.h"

namespace DSL
{
	template <typename T>
	class List: public TopClass 
	{
	protected:
		List(const List&);               // 容器类不能进行拷贝
		List& operator = (const List&);  // 容器类不能进行赋值
	public:
		List() {}
		virtual bool insert(const T& obj) = 0;  // 默认插入方式在最后一个位置插入 
		virtual bool insert(int pos, const T& obj) = 0;
		virtual bool remove(int pos) = 0;
		virtual bool set(int pos, const T& obj) = 0;
		virtual bool get(int pos, T& obj) const = 0;
		virtual int  length() const = 0;
		virtual void clean() = 0;
	};

}

#endif
