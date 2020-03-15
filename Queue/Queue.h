/*
*	Queue: 队列接口
*	成员函数：
*		add()		在队尾(rear)插入一个元素。进队列
*		remove()	删除队列头部(front)的一个元素。出队列。
*		front()		返回队列头部的元素
*		clear()		清空整个队列
*		length()	返回队列元素的个数
*/

#ifndef QUEUE_H
#define QUEUE_H

#include"TopClass.h"

namespace DSL
{
	template <typename T>
	class Queue : public TopClass
	{
	public:
		virtual void add(const T& obj) = 0;		
		virtual void remove() = 0;
		virtual T front() const = 0;
		virtual void clear() = 0;
		virtual int length() const = 0;
	};
}
#endif
