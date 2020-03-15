#ifndef TREE_H
#define TREE_H

#include"TopClass.h"
#include"TreeNode.h"
#include"SharedPointer.h"

namespace DSL
{
	template <typename T>
	class Tree : public TopClass
	{
	protected:
		TreeNode<T>* m_root;

		Tree(const Tree<T>&); // 私有化构造函数和赋值函数，防止树与树之间赋值
		Tree<T>& operator = (const Tree<T>&);
	public:
		Tree() {m_root = NULL;}
		virtual bool insert(TreeNode<T>* node) = 0;
		virtual bool insert(const T& value, TreeNode<T>* parent) = 0;
		virtual SharedPointer<Tree<T>> remove(TreeNode<T>* node) = 0;
		virtual SharedPointer<Tree<T>> remove(const T& value) = 0;//引用，实际为指针常量，表示不可以指向其他对象		
		virtual TreeNode<T>* find(TreeNode<T>* node) const = 0;
		virtual TreeNode<T>* find(const T& value) const = 0;//const引用，字面值可以传送进去，也不需要额外的复制操作，但函数不能修改这个参数
		virtual TreeNode<T>* root() const = 0;
		virtual int degree() const = 0;
		virtual int count() const = 0;
		virtual int height() const = 0;
		virtual void clear() = 0;
		virtual bool begin() = 0;
		virtual bool next() = 0;
		virtual bool end() = 0;
		virtual T current() = 0;
	};
}

#endif
