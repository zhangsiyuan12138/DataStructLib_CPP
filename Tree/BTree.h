#ifndef BTREE_H
#define BTREE_H

#include"Tree.h"
#include"BTreeNode.h"
#include"Exception.h"
#include"LinkListQueue.h"
#include"SharedPointer.h"
#include"DynamicArray.h"

namespace DSL
{
	enum TraversalType
	{
		PREORDER,
		INORDER,
		POSORDER,
		LEVELORDER
	};
	
	template <typename T>
	class BTree : public Tree<T>
	{
	protected:
		LinkListQueue<BTreeNode<T>*> m_queue;
	
		virtual BTreeNode<T>* find(BTreeNode<T>* root, const T& value) const
		{
			BTreeNode<T>* ret = NULL;
			if(root != NULL)
			{
				if(root->value == value)
				{
					ret = root;
				}
				else
				{
					if(ret == NULL)
					{
						find(root->left_child, value);
					}
					if(ret == NULL)
					{
						find(root->right_child, value);
					}
				}
			}
			return ret;
		}

		virtual BTreeNode<T>* find(BTreeNode<T>* root, BTreeNode<T>* node) const
		{
			BTreeNode<T>* ret = NULL;
			if(root == node)
			{
				ret = node;
			}
			else
			{
				if(root != NULL)
				{
					if(ret == NULL)
					{
						find(root->left_child, node);
					}
					if(ret == NULL)
					{
						find(root->right_child, node);
					}
				}
			}
			return ret;
		}

		virtual bool insert(BTreeNode<T>* node_parent, BTreeNode<T>* node, ChildDirect direct)
		{
			bool ret = ture;
			if(direct == ANY_DIR)
			{
				if(node_parent->left_child == NULL)
				{
					node_parent->left_child = node;
				}
				else if(node_parent->right_child == NULL)
				{
					node_parent->right_child = node;
				}
				else
				{
					ret = false;
				}
			}
			else if(direct == LEFT_DIR)
			{
				if(node_parent->left_child == NULL)
				{
					node_parent->left_child = node;
				}
				else
				{
					ret = false;
				}
			}
			else if(direct == RIGHT_DIR)
			{
				if(node_parent->right_child == NULL)
				{
					node_parent->right_child = node;
				}
				else
				{
					ret = false;
				}				
			}
			else
			{
				ret = false;
			}
			return ret;
		}

		virtual void remove(BTreeNode<T>* node, BTree<T>*& ret)
		{
			ret = new BTree<T>();
			if(ret == NULL)
			{
				THROW_EXCEPTION(NotEnoughMemoryException, "no enough memory to allocate a tree!");
			}
			else
			{
				BTreeNode<T>* node_parent = dynamic_cast<BTreeNode<T>*>(node->parent);
				if(node_parent->left_child == node)
				{
					node_parent->left_child = NULL;	
				}
				else if(node_parent->right_child == node)
				{
					node_parent->right_child = NULL;
				}
				node->parent = NULL;
			}
			ret->m_root = node;
		}

		virtual void free(BTreeNode<T>* del_node)
		{
			if(del_node ==NULL)
			{
				return;
			}
			else
			{
				free(del_node->left_child);
				free(del_node->right_child);
				if(del_node->flag())
				{
					delete del_node;
				}
			}
		}

		int count(BTreeNode<T>* root) const
		{
			int ret = 0;
			if(root == NULL)
			{
				return ret;
			}
			else
			{
				return (count(root->left_child) + count(root->right_child) + 1); // 1Ϊ��ǰ���ڵ�
			}
			// return ((root != NULL) ? (count(root->left_child) + count(root->right_child) + 1) : 0);
		}

		int height(BTreeNode<T>* root) const
		{
			int ret = 0;
			if(root == NULL)
			{
				return ret;
			}
			else
			{
				int left_height = count(root->left_child);
				int right_height = count(root->right_child);
				if(left_height > right_height)
				{
					ret = left_height + 1; // 1Ϊ��ǰ���ڵ����
				}
				return ret;
				// return (((left_height > right_height) ? left_height : right_height) + 1);
			}
		}

		int degree(BTreeNode<T>* root) const
		{
			int ret = 0;
			if(root == NULL)
			{
				return ret;
			}
			else
			{
				int degree_root = (!!root->left_child) + (!!root->right_child);
				if(ret < 2)
				{
					int degree_left = degree(root->left_child);
					if(degree_left > degree_root)
						ret = degree_left;
				}
				if(ret < 2)
				{
					int degree_right = degree(root->right_child);
					if(degree_right > degree_root)
						ret = degree_right;
				}
				return ret;
			}
		
		/*
			int ret = 0;
			if(root == NULL)
			{
				return ret;
			}
			else
			{
				int degree_left = degree(root->left_child);
				int degree_right = degree(root->right_child);
				int degree_root = (!!root->left_child) + (!!root->right_child);
				if(degree_left > degree_root)
				{
					ret = degree_left;
				}
				if(degree_right > degree_root)
				{
					ret = degree_right;
				}
				if(degree_left > degree_right)
				{
					ret = degree_left;
				}
				return ret;
			}
		*/
		}

		
		// �������:���ڵ��ڿ�ʼλ�ñ�����
		void PreOrderTraversal(BTreeNode<T>* root, LinkListQueue<BTreeNode<T>*>& queue)
		{
			if(root == NULL)
			{
				return;
			}
			else
			{
				queue.add(root);
				PreOrderTraversal(root->left_child, queue);
				PreOrderTraversal(root->right_child, queue);
			}
		}

		//�������:���ڵ����м�λ�ñ�����
		void InOrderTraversal(BTreeNode<T>* root, LinkListQueue<BTreeNode<T>*>& queue)
		{
			if(root == NULL)
			{
				return;
			}
			else
			{
				InOrderTraversal(root->left_child, queue);
				queue.add(root);
				InOrderTraversal(root->right_child, queue);
			}
		}

		//�������:���ڵ������λ�ñ�����
		void PostOrderTraversal(BTreeNode<T>* root, LinkListQueue<BTreeNode<T>*>& queue)
		{
			if(root == NULL)
			{
				return;
			}
			else
			{
				PostOrderTraversal(root->left_child, queue);
				PostOrderTraversal(root->right_child, queue);
				queue.add(root);
			}
		}

		//��α��������ϵ��´����ҡ���һ��������ɲ�δ���ķ��ʣ��ڶ������б�����ʴ���
		void LevelOrderTraversal(BTreeNode<T>* root, LinkListQueue<BTreeNode<T>*>& ret_queue)
		{
			if(root == NULL)
			{
				THROW_EXCEPTION(InvalidParameterException, "can not convert a empty tree!");
			}
			else
			{
				LinkListQueue<BTreeNode<T>*> temp_queue;
				BTreeNode<T>* temp_node;
				temp_queue.add(root);
				while(temp_queue.length() > 0)
				{
					temp_node = temp_queue.front();				
					if(temp_node->left_child)
					{
						temp_queue.add(temp_node->left_child);
					}
					if(temp_node->right_child)
					{
						temp_queue.add(temp_node->right_child);
					}
					temp_queue.remove();
					ret_queue.add(temp_node);
				}
			}
		}

		BTreeNode<T>* clone(const BTreeNode<T>* node) const
		{
			BTreeNode<T>* temp_node = NULL;
			if(node == NULL)
			{
				return NULL;
			}
			else
			{
				if(temp_node == NULL)
				{
					THROW_EXCEPTION(NotEnoughMemoryException, "can not create new node!");
				}
				else
				{
					temp_node->value = node->value;
					temp_node->left_child = clone(node->left_child);
					temp_node->right_child = clone(node->right_child);
					// ��ʼ��ÿ���ڵ�parentָ��
					if(temp_node->left_child)
					{
						temp_node->left_child->parent = temp_node;
					}
					if(temp_node->right_child)
					{
						temp_node->right_child->parent = temp_node;
					}
				}
			}

		}

		bool equal(BTreeNode<T>* left_tree, BTreeNode<T>* right_tree) const
		{
			if(left_tree == right_tree)
			{
				return ture;
			}
			else if((left_tree != NULL) && (right_tree != NULL))
			{
				return ((left_tree->value == right_tree->value) && (equal(left_tree->left_child, right_tree->left_child)) && (equal(left_tree->right_child, right_tree->right_child)));
			}
			else // һ�ö�����Ϊ�գ�һ�Ŷ�������Ϊ��
			{
				return false;
			}
		}

		BTreeNode<T>* add(BTreeNode<T>* tree1_root, BTreeNode<T>* tree2_ndoe) const
		{
			BTreeNode<T>* temp_node = NULL;
			if((tree1_root == NULL) && (tree2_ndoe != NULL))
			{
				return clone(tree2_ndoe);
			}
			else if((tree1_root != NULL) && (tree2_ndoe == NULL))
			{
				return clone(tree1_root);
			}
			else if((tree1_root != NULL) && (tree2_ndoe != NULL))
			{
				temp_node = BTreeNode<T>::NewNode();
				if(temp_node == NULL)
				{
					THROW_EXCEPTION(NotEnoughMemoryException, "no enought memory to create new node!");
				}
				else
				{
					temp_node->value = tree1_root->value + tree2_ndoe->value;
					temp_node->left_child = add(tree1_root->left_child,tree2_ndoe->left_child);
					temp_node->right_child = add(tree1_root->right_child, tree2_ndoe->right_child);
					// ��ʼ��ÿ���ڵ�parentָ��
					if(temp_node->left_child)
					{
						temp_node->left_child->parent = temp_node;
					}
					if(temp_node->right_child)
					{
						temp_node->right_child->parent = temp_node;
					}
				}
			}
			else // ��������Ϊ��
			{
				return NULL;
			}
		}

		// ������STEP1�����������rootת�����ݱ�������type���������䰴�ձ���˳������ret_queue������
		void traversal(BTreeNode<T>* root, LinkListQueue<BTreeNode<T>*>& ret_queue, TraversalType type)
		{
			switch (type)
			{
				case PREORDER:
					PreOrderTraversal(root, ret_queue);
					break;
				case INORDER:
					InOrderTraversal(root, ret_queue);
					break;
				case POSORDER:
					PostOrderTraversal(root, ret_queue);
					break;
				case LEVELORDER:
					LevelOrderTraversal(root, ret_queue);
					break;
				default:
					THROW_EXCEPTION(InvalidParameterException, "unknown traversal type!");
					break;
			}
		}

		//������STEP2��������ڵ�Ϊ���ڵ��queueת��Ϊ˫������������˫������ͷ�ڵ�
		//             ���Ӷ����еĽڵ�(rightָ���̣�leftָ��ǰ��)�γ�˫������
		BTreeNode<T>* connect(LinkListQueue<BTreeNode<T>*>& queue)
		{
			BTreeNode<T>* list_head = NULL, slider = NULL;
			if(queue == NULL && queue.length() > 0)
			{
				return NULL;
			}
			else
			{
				list_head = queue.front();
				slider = queue.front();
				queue.remove();
				slider->left_child = NULL;
				while(queue.length() > 0)
				{
					slider->right_child = queue.front();
					queue.front()->right_child = slider;
					slider = queue.front();
					queue.remove();
				}
				slider->right_child = NULL;
			}
			return list_head;
		}
		
	public:
		bool insert(TreeNode<T>* node)
		{
			return insert(node, ANY_DIR);
		}

		bool insert(TreeNode<T>* node, ChildDirect direct)
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
					BTreeNode<T>* node_parent = find(node->parent);
					if(node_parent != NULL)
					{
						if(!insert(dynamic_cast<BTreeNode<T>*>(node), node_parent, direct))
						{
							ret = false;
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
			return insert(value, parent, ANY_DIR);			
		}

		bool insert(const T& value, TreeNode<T>* parent, ChildDirect direct)
		{
			bool ret = ture;
			BTreeNode<T>* temp_node = BTreeNode<T>::NewNode();
			if(temp_node != NULL)
			{
				temp_node->value = value;
				temp_node->parent = parent;
				if(!insert(temp_node, direct))
				{
					delete temp_node;
					ret = false;
				}
			}
			else
			{
				THROW_EXCEPTION(InvalidParameterException, "can not allcote new node!");
			}
			return ret;
		}
		
		SharedPointer<Tree<T>> remove(TreeNode<T>* node)
		{
			BTree<T>* ret_tree = NULL;
			node = find(node);
			if(node == NULL)
			{
				THROW_EXCEPTION(InvalidParameterException, "remove node is not in tree!");
			}
			else
			{
				remove(dynamic_cast<BTreeNode<T>*>(node), ret_tree);
				m_queue.clear(); //��ն��У�
			}
			return ret_tree;
		}
		
		SharedPointer<Tree<T>> remove(const T& value)
		{
			BTree<T>* ret_tree = NULL;
			BTreeNode<T>* node = find(value);
			if(node == NULL)
			{
				THROW_EXCEPTION(InvalidParameterException, "remove node is not in tree!");
			}
			else
			{
				remove(node, ret_tree);
				m_queue.clear(); //��ն��У�
			}
			return ret_tree;
		}
		
		BTreeNode<T>* find(TreeNode<T>* node) const
		{
			return find(root(), dynamic_cast<BTreeNode<T>*>(node));
		}
		
		BTreeNode<T>* find(const T& value) const
		{	
			return find(root(), value);
		}
		
		BTreeNode<T>* root() const
		{
			return dynamic_cast<BTreeNode<T>*>(this->m_root);
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

		// �������Ĳ�α���
		bool begin()
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
		
		bool next()
		{
			if(m_queue.length() <= 0)
			{
				return false;
			}
			else
			{
				BTreeNode<T>* head_node = m_queue.front();
				m_queue.remove();
			   if(head_node->left_child) 
				{
					m_queue.add(head_node->left_child); 
			   	}
			   	if(head_node->right_child) 
				{
					m_queue.add(head_node->right_child); 
			   	}
				return ture;
			}
		}
		
		bool end()
		{
			return (m_queue.length() == 0);
		}
		
		T current()
		{
			if(end())
			{	
				THROW_EXCEPTION(InvalidOperationException, "index out of bound!");
			}
			else
			{
				return m_queue.front()->value;
			}
		}

		// ���������������򣬺�������
		SharedPointer<DynamicArray<T>> traversal(BTreeNode<T>* root, TraversalType type)
		{
			LinkListQueue<BTreeNode<T>*> queue;
			DynamicArray<T>* array = NULL;
		
			if(root() == NULL)
			{
				THROW_EXCEPTION(InvalidOperationException, "empty tree can not be traversaled!");
			}
			else
			{
				traversal(root, queue, type);
				array = new DynamicArray<T>(queue.length());
				if(array == NULL)
				{
					THROW_EXCEPTION(NotEnoughMemoryException, "no enough to create a new array!");
				}
				else
				{
					for(int i = 0; i < array.length(); i++, queue.remove())
					{
						array.set(i, queue.front()->value);
					}
				}

			}
		}

		//�������ڵ�Ϊtree_root�Ķ�����
		SharedPointer<Tree<T>>* clone(BTreeNode<T>* tree_root) const
		{
			BTree<T>* temp_tree = new BTree<T>();
			if(temp_tree == NULL)
			{
				THROW_EXCEPTION(NotEnoughMemoryException, "no enough memory to create tree!");
			}
			else
			{
				temp_tree->m_root = clone(tree_root);
			}
			return temp_tree;
		}

		//�Զ�����ÿ��Ԫ�ؽ��бȽ�
		bool operator == (const BTree<T>* tree) const
		{
			return equal(root(), tree.root());
		}

		bool operator != (const BTree<T>* tree) const
		{
			return !(*this == tree);
		}

		//��������Ӳ���������ǰ��������������ڶ�Ӧ�ڵ����ֵ���
		//����ֵ�Ƕѿռ�������¶�����
		SharedPointer<BTree<T>> add(const BTree<T>&  btree) const
		{
			BTree<T>* temp_tree = new BTree<T>();
			if(temp_tree == NULL)
			{
				THROW_EXCEPTION(NotEnoughMemoryException, "no enough memory to create a new tree!");
			}
			else
			{	
				temp_tree->m_root = add(root(), btree.root());
			}
			return temp_tree;
		}

		// ����������������������ת����˫������
		BTreeNode<T>* threaded(BTree<T>* tree, TraversalType type)
		{
			if(root == NULL)
			{
				return NULL;
			}
			else
			{
				BTreeNode<T>* list_head = NULL;
				LinkListQueue<BTreeNode<T>*> queue = NULL;
				traversal(tree.root(), queue, LEVELORDER);
				list_head = connect(queue);
				tree.m_root = NULL;
				tree.clear();
				return list_head;
			}
		}

		// ɾ�������ڵ�Ϊroot�еĵ��Ƚڵ�
		BTreeNode<T>* delete_single_drgree_node(BTreeNode<T>* root)
		{
			BTreeNode<T>* head = NULL;
			if(root == NULL)
			{
				return NULL;
			}
			else
			{
				if(((root->left_child == NULL) && (root->right_child != NULL)) || ((root->left_child != NULL) && (root->right_child ==NULL)))// �������
				{
					BTreeNode<T>* parent = dynamic_cast<BTreeNode<T>*>(root->parent);
					BTreeNode<T>* child = ((root->left_child != NULL) ? root->left_child : root->right_child);
					if(parent != NULL)
					{
						((parent->left_child != NULL) ? parent->left_child : parent->right_child) = child; // C++��Ŀ������ʽ���ر�������
						child->parent = parent;
					}
					if(parent == NULL) // ������ڵ���ǵ��Ƚڵ�����
					{
						child->parent = NULL;
					}
					if(root->flag())
					{
						delete root;
					}
					head = delete_single_drgree_node(child);
				}
				else // ���Ƕ�Ϊ0��2����� 
				{
					delete_single_drgree_node(root->left_child);
					delete_single_drgree_node(root->right_child);
					head = root;
				}
			}
			return head;
		}

		// ɾ�������ڵ�Ϊroot�еĵ��Ƚڵ㣬���ظ��ڵ�Ϊroot������ û�и��ڵ�
		void delete_single_drgree_node(BTreeNode<T>*& root)
		{
			if(root == NULL)
			{
				THROW_EXCEPTION(InvalidParameterException, "can not do delete single degree node for empty tree!");
			}
			else
			{
				if(((root->left_child != NULL) && (root->right_child ==NULL)) || ((root->left_child == NULL) && (root->right_child != NULL)))
				{
					BTreeNode<T>* child = ((root->left_child != NULL) ? root->left_child : root->right_child);
					if(root->flag())
						delete root;
					root = child;
					delete_single_drgree_node(root);
				}
				else
				{
					delete_single_drgree_node(root->left_child);
					delete_single_drgree_node(root->right_child);
				}
			}
		}
		
		
		void clear()
		{
			free(root());
			m_queue.clear(); //��ն��У�
			this->m_root = NULL;
		}

		~BTree()
		{
			clear();
		}
	};
}

#endif
