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
#include"MarixGraph.h"
#include"Array.h"

*/
#include"ListGraph.h"
#include"SharedPointer.h"
#include"Array.h"


using namespace std;  
using namespace DSL;

int main(void)
{
	ListGraph<char, int> g;
	g.addVertex('a');
	g.addVertex('b');
	g.addVertex('c');
	g.addVertex('d');
	g.removeVertex();
	g.addVertex('d');

	for(int i = 0; i < g.vCount(); i++)
		cout << i << " : " << g.getVertex(i) << endl;

	g.setEdge(0, 1, 5);
	g.setEdge(0, 3, 5);
	g.setEdge(1, 2, 8);
	g.setEdge(2, 3, 2);
	g.setEdge(3, 1, 9);

	cout << "ecount :" << g.eCount() << endl;
	cout << "vcount :" << g.vCount() << endl;

	cout << " W(0,1) :" << g.getEdge(0, 1) << endl;
	cout << " W(0,3) :" << g.getEdge(0, 3) << endl;
	cout << " W(1,2) :" << g.getEdge(1, 2) << endl;
	cout << " W(2,3) :" << g.getEdge(2, 3) << endl;
	cout << " W(3,1) :" << g.getEdge(3, 1) << endl;

	g.removeEdge(3, 1);
	cout << "ecount :" << g.eCount() << endl;

	SharedPointer<Array<int>> ad = g.getAdjacent(0);
	for(int i = 0; i < ad->length(); i++)
			cout << (*ad)[i] << endl;	

	
	g.setEdge(3, 1, 9);

	cout << "ID(1) :" << g.ID(1) << endl;
	cout << "OD(1) :" << g.OD(1) << endl;
	cout << "TD(1) :" << g.TD(1) << endl;

	g.removeVertex();
	cout << "ecount :" << g.eCount() << endl;

	return 0;
} 

