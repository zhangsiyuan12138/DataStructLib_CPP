/*
*	StaticList：静态顺序存储链表
*	成员变量：m_space[] 静态数组
*
*	成员函数：StaticList() 初始化m_array指针指向线性表
*			  capacity()   存储空间大小
*	
*	
*/

#ifndef STATICLIST_H
#define STATICLIST_H

#include"SeqList.h"

namespace DSL
{
	template <typename T, int 	N>
	class StaticList : public SeqList<T>
	{
	protected:
		T m_space[N];
	public:
		StaticList()
		{
			this->m_array = m_space;
			this->m_length = 0;
		}
		int capacity() const
		{
			return N;
		}

};

}

#endif
