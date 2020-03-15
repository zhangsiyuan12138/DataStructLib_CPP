#include<iostream>
/*

#include"DynamicArray.h"
#include"Exception.h"
#include"TopClass.h"
#include"StaticList.h"
#include"DynamicList.h"
#include"StaticLinkList.h"
#include"SmartPointer.h"
#include"SharedPointer.h"
#include"CircularList.h"
#include"DualList.h"
#include"LinkListStack.h"
#include"StaticQueue.h" 
#include"LinuxQueue.h"
#include"StackToQueue.h"
#include"QueueToStack.h" 
#include"zsy_String.h"
#include"EightQueue.h"
#include"Sort.h"

*/
#include"GTree.h"
#include"BTree.h"



using namespace std;  
using namespace DSL;

int main(void)
{
	BTree<int> b_tree;
	BTreeNode<int>* b_node = NULL;

	b_tree.insert(1, NULL);
	b_node = b_tree.find(1);
	b_tree.insert(2, b_node);
	b_tree.insert(3, b_node);



/*		
	GTree<char> tree;
	GTreeNode<char>* node = NULL;

	tree.insert('a', NULL);
	node = tree.find('a');
	tree.insert('b', node);
	tree.insert('c', node);
	
	node = tree.find('b');
	tree.insert('d', node);
	tree.insert('e', node);
	
	node = tree.find('c');
	tree.insert('f', node);
	tree.insert('g', node);

	const char* s = "ceg";
	for(int i = 0; i < 3; i++)
	{
		TreeNode<char>* node = tree.find(s[i]);
		while(node != NULL)
		{
			cout << node->value;
			node = node->parent;
		}
		cout << endl;
	}
*/
	
	return 0;
} 

