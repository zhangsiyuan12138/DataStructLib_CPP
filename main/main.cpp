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
#include"GTree.h"
#include"BTree.h"

*/
#include"MarixGraph.h"

using namespace std;  
using namespace DSL;

int main(void)
{
	MartixGraph<3, int, int> g;
	g.setEdge(0, 1, 1);
	g.setEdge(1, 2, 2);
	g.setEdge(1, 0, 3);

	cout << "v count = " << g.vCount() << endl;
	cout << "e count = " << g.eCount() << endl;
	cout << "ID(1)" << g.ID(1) << endl;
	cout << "OD(1)" << g.OD(1) << endl;
	
	
	
	return 0;
} 

