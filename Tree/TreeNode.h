#ifndef TREENODE_H
#define TREENODE_H

#include"TopClass.h"

namespace DSL
{
	template <typename T>
	class TreeNode : public TopClass
	{
	protected:
		bool m_flag;
		TreeNode(const TreeNode<T>&);
		TreeNode<T>& operator = (const TreeNode<T>&);
		void* operator new(size_t size) throw()
		{
			return TopClass::operator new(size);
		}
	public:
		T value;
		TreeNode<T>* parent;

		bool flag()
		{
			return m_flag;
		}
		
		TreeNode()
		{
			value = 0;
			parent = NULL;
		}

		virtual ~TreeNode() = 0;
	};
	template <typename T>
	TreeNode<T>::~TreeNode() {}
}

#endif
