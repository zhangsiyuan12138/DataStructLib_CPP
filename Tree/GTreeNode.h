#ifndef GTREENODE_H
#define GTREENODE_H

#include"Tree.h"
#include"LinkList.h"

namespace DSL
{
	template <typename T>
	class GTreeNode : public TreeNode<T>
	{
	public:
		LinkList<GTreeNode<T>*> m_GTreeNode;
		static GTreeNode<T>* NewNode() // ����ģʽ
		{
			GTreeNode<T>* ret = new GTreeNode<T>();
			if(ret != NULL)
			{
				ret->m_flag = ture; // ��ʶ�ѿռ�����Ķ���
			}
		}
	};
}

#endif
