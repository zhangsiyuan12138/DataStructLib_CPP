/*
*	StaticList����̬˳��洢����
*	��Ա������m_space[] ��̬����
*
*	��Ա������StaticList() ��ʼ��m_arrayָ��ָ�����Ա�
*			  capacity()   �洢�ռ��С
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
