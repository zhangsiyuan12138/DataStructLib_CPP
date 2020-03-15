/*
*	DualLinkList:	双向循环链表
*	成员变量：
*			Node:		节点实体
*			m_header:	头节点
*			m_length	链表长度
*			m_step		步进长度
*			m_current	当前节点前一个节点	
*	成员函数：
*			create()	申请一个新节点		
*			destroy()	删除一个新节点
*			
*			DualLinList()		构造函数初始化成员变量
*			insert()			参数判断，申请新节点，寻找节点，插入节点。分四步：
*			remove()			参数判断，寻找节点，删除节点。							  分三步：
*			set()				参数判断，寻找节点，设置节点值
*			get()				参数判断，寻找节点，获取节点值
*			length() 			获取链表长度
*			clean()				释放所有节点空间
*			find()      		返回对应值得节点下标
*			position()		 	返回下标pos节点的上一个的节点指针
*			~LinkList()			释放所有节点空间
*
*			bool move() 		移动游标到指定位置
*			bool end()			判断游标是否到最后
*			T current()			回去当前游标节点值
*			bool next()			移动步长的节点数
*			bool pre()			移动步长的节点数	
*/

#ifndef DUALLINKLIST_H
#define DUALLINKLIST_H

#include"DualList.h"

namespace DSL
{
	template<typename T>
	class DualCircularList : public DualList<T>
	{
	protected:
		typedef typename DualList<T>::Node Node;
	public:
		DualCircularList()
		{
			this->m_length = 0;
			this->m_step = 1;
			this->m_current = NULL;
			this->m_header.next = NULL;
		}
		
		bool insert(const T& obj)
		{
			insert(this->m_length,obj);
		}

		bool insert(int pos, const T& obj)
		{
			bool ret  = ((pos >= 0) && (pos <= this->m_length));
			if(ret)
			{
				

			}
			return ret;
		}


	};
	
}

#endif
