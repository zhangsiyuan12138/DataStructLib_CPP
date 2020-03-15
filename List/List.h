/*
* List�ࣺ���Ա�ӿڡ�
* �̳�TopClass�࣬��SeqList�̳С�
* ���麯�������룬ɾ��������ֵ�����ֵ����ó��ȣ�������Ա�
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
		List(const List&);               // �����಻�ܽ��п���
		List& operator = (const List&);  // �����಻�ܽ��и�ֵ
	public:
		List() {}
		virtual bool insert(const T& obj) = 0;  // Ĭ�ϲ��뷽ʽ�����һ��λ�ò��� 
		virtual bool insert(int pos, const T& obj) = 0;
		virtual bool remove(int pos) = 0;
		virtual bool set(int pos, const T& obj) = 0;
		virtual bool get(int pos, T& obj) const = 0;
		virtual int  length() const = 0;
		virtual void clean() = 0;
	};

}

#endif
