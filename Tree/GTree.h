#ifndef GTREE_H
#define GTREE_H

#include"Tree.h"
#include"GTreeNode.h"
#include"Exception.h"
#include"LinkListQueue.h"

namespace DSL
{
	template <typename T>
	class GTree : public Tree<T>
	{
		LinkListQueue<GTreeNode<T>*> m_queue; // 实现节点顺序存储
		
	protected:
		GTreeNode<T>* find(GTreeNode<T>* root, const T& value) const
		{
			GTreeNode<T>* ret = NULL;
			
			if(root != NULL)
			{
				if(value == root->value)
				{
					return root;
				}
				else
				{
					for(root->m_GTreeNode.move(0); !root->m_GTreeNode.end() && (ret == NULL); root->m_GTreeNode.next())
					{
						find(root->m_GTreeNode.current(),value);
					}
				}
			}
			return ret;
		}

		GTreeNode<T>* find(GTreeNode<T>* root, GTreeNode<T>* node) const
		{
			GTreeNode<T>* ret = NULL;
			
			if(root == node)
			{
				return root;
			}
			else
			{
				if(root != NULL)
				{
					for(root->m_GTreeNode.move(0); !root->m_GTreeNode.end() && (ret == NULL); root->m_GTreeNode.next())
					{
						find(root->m_GTreeNode.current(), node);
					}
				}
			}
			return ret;
		}

		void free(GTreeNode<T>* root)
		{
			if(root == NULL)
			{
				return;
			}
			else
			{
				for(root->m_GTreeNode.move(0); !root->m_GTreeNode.end(); root->m_GTreeNode.next())
				{
					free(root->m_GTreeNode.current());
				}
				if(root->flag())
				{
					delete root;
				}
			}
		}

		int count(GTreeNode<T>* node) const
		{
			int ret = 0;
			if(node == NULL)
			{
				return ret;
			}
			else
			{
				ret = 1; // 加上根节点的
				for(node->m_GTreeNode.move(0); !node->m_GTreeNode.end(); node->m_GTreeNode.next())
				{
					ret = ret + count(node->m_GTreeNode.current());
					// return count(node->m_GTreeNode.current()) + 1; // 1 当前根节点
					// ret = 1 + count(node->m_GTreeNode.current());
				}
			}
			return ret;
		}

		int height(GTreeNode<T>* node) const
		{
			int ret = 0;
			if(node == NULL)
			{
				return ret;
			}
			else
			{
				for(node->m_GTreeNode.move(0); !node->m_GTreeNode.end(); node->m_GTreeNode.next())
				{
					int h = height(node->m_GTreeNode.current());
					if(h < ret)
					{
						h = ret;
					}
				}
				ret = ret + 1; // 子树全部遍历一次，则已知高度加1
			}
		}

		int degree(GTreeNode<T>* node) const
		{
			int ret = 0;
			if(node == NULL)
			{
				return ret;
			}
			else
			{
				ret = node->m_GTreeNode.length();
				for(node->m_GTreeNode.move(0); !node->m_GTreeNode.end(); node->m_GTreeNode.next())
				{
					int temp = degree(node->m_GTreeNode.current());
					if(temp > ret)
					{
						ret = temp;
					}
				}
			}
			return ret;
		}

		
	public:
		GTree() {}
		
		bool insert(TreeNode<T>* node)
		{
			bool ret = ture;
			if(node != NULL)
			{
				if(this->m_root == NULL)
				{
					node->parent = NULL;
					this->m_root = node;
				}
				else
				{
					GTreeNode<T>* parent_node = find(node->parent);
					if(parent_node != NULL)
					{
						// parent_node->m_GTreeNode.insert() 下面可避免重复插入树中有的节点
						GTreeNode<T>* temp_node = dynamic_cast<GTreeNode<T>*>(node);						
						if(parent_node->m_GTreeNode.find(temp_node) < 0)
						{
							parent_node->m_GTreeNode.insert(temp_node);
						}
					}
					else
					{
						ret = false;
					}
				}
			}
			else
			{
				THROW_EXCEPTION(InvalidParameterException, "insert node is NULL!");
			}
			return ret;
		}
		
		bool insert(const T& value, TreeNode<T>* parent)
		{
			bool ret = ture;
			GTreeNode<T>* temp_node = GTreeNode<T>::NewNode();
			if(temp_node != NULL)
			{
				temp_node->value = value;
				temp_node->parent = parent;
				insert(temp_node);
			}
			else
			{
				THROW_EXCEPTION(InvalidOperationException, "no enough memory to create a node!");
			}
			return ret;
 		}
		
		SharedPointer<Tree<T>> remove(TreeNode<T>* node)
		{
			GTree<T>* del_tree;
			if(del_tree == NULL)
			{
				THROW_EXCEPTION(NotEnoughMemoryException, "no enough memory to create new tree!");
			}
			else
			{
				GTreeNode<T>* del_node = dynamic_cast<GTreeNode<T>*>(find(node));
				if(del_node != NULL)
				{
					if(root() == del_node)
					{
						this->m_root = NULL;
					}
					else
					{
						LinkList<GTreeNode<T>*>& par_node_list = dynamic_cast<GTreeNode<T>*>(del_node->parent)->m_GTreeNode;					
						par_node_list.remove(par_node_list.find(del_node));
						del_node->parent = NULL;
						m_queue.clear();
					}
				}
				else
				{
					THROW_EXCEPTION(InvalidParameterException, "can not find a node by value!");
				}
				del_tree->m_root = del_node;
				return del_tree;
			}
		}
			
		SharedPointer<Tree<T>> remove(const T& value)
		{
			GTree<T>* del_tree;
			if(del_tree == NULL)
			{
				THROW_EXCEPTION(NotEnoughMemoryException, "no enough memory to create new tree!");
			}
			else
			{
				GTreeNode<T>* del_node = find(value);
				if(del_node != NULL)
				{
					if(root() == del_node)
					{
						this->m_root = NULL;
					}
					else
					{
						LinkList<GTreeNode<T>*>& par_node_list = dynamic_cast<GTreeNode<T>*>(del_node->parent)->m_GTreeNode;					
						par_node_list.remove(par_node_list.find(del_node));
						del_node->parent = NULL;
						m_queue.clear();
					}
				}
				else
				{
					THROW_EXCEPTION(InvalidParameterException, "can not find a node by value!");
				}
				del_tree->m_root = del_node;
				return del_tree;
			}
		}
		
		GTreeNode<T>* find(TreeNode<T>* node) const
		{
			return find(root(), dynamic_cast<GTreeNode<T>*>(node));
		}
		
		GTreeNode<T>* find(const T& value) const
		{
			return find(root(), value);
		}
		
		GTreeNode<T>* root() const
		{
			return dynamic_cast<GTreeNode<T>*>(this->m_root);
		}
		
		int degree() const
		{
			return degree(root());
		}
		
		int count() const
		{
			return count(root());
		}
		
		int height() const
		{
			return height(root());
		}

		/*
		* 实现树按照横向层次来遍历：通过队列头返回一个节点时，将其子节点全部插入队列尾部实现树的顺序存储和读取。
		* begin()   
		* next()    
		* current() 
		* end()     
		*/
		bool begin()  // 根节点压入队列
		{
			if(root() == NULL)
			{
				return false;
			}
			else
			{
				m_queue.clear();
				m_queue.add(root());
				return ture;
			}
		}

		bool next() // 弹出队头元素，将队头节点孩子压入队列
		{
			if(m_queue.length() <= 0)
			{
				return false;
			}
			else
			{
				GTreeNode<T>* node = m_queue.front();
				m_queue.remove();
				for(node->m_GTreeNode.move(0); !node->m_GTreeNode.end(); node->m_GTreeNode.next())
				{
					m_queue.add(node->m_GTreeNode.current());
				}
				return ture;			
			}
		}

		T current()  // 访问队头元素指向节点的数据
		{
			if(!end())
			{
				return m_queue.front()->value;
			}
			else
			{
				THROW_EXCEPTION(InvalidOperationException, "index out of bound!");
			}
		}

		bool end()
		{
			return (m_queue.length() != 0);
		}
		
		void clear()
		{
			free(root());
			this->m_root = NULL;
			m_queue.clear();
		}

		~GTree()
		{
			clear();
		}
	};
}

#endif
