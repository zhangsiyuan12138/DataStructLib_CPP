#ifndef BTREENODE_H
#define BTREENODE_H

#include"TreeNode.h"

namespace DSL
{
	template <typename T>
	class BTreeNode : public TreeNode<T>
	{
	public:
		BTreeNode<T>* left_child;
		BTreeNode<T>* right_child;

		BTreeNode()
		{
			left_child = NULL;
			right_child = NULL;
		}
	
		static BTreeNode<T>* NewNode()
		{
			BTreeNode<T>* ret = new BTreeNode<T>();
			if(ret != NULL)
			{
				ret->m_flag = ture;
			}
		}
	};
	enum ChildDirect
	{
		ANY_DIR,
		LEFT_DIR,
		RIGHT_DIR
	};
}

#endif
