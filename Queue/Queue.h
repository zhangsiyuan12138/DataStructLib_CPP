/*
*	Queue: ���нӿ�
*	��Ա������
*		add()		�ڶ�β(rear)����һ��Ԫ�ء�������
*		remove()	ɾ������ͷ��(front)��һ��Ԫ�ء������С�
*		front()		���ض���ͷ����Ԫ��
*		clear()		�����������
*		length()	���ض���Ԫ�صĸ���
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
