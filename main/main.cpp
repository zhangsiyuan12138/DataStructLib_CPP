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
#include"MarixGraph.h"


using namespace std;  
using namespace DSL;

int main(void)
{
/*
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
*/
	MartixGraph<9, char, int> m_graph;
	const char* V = "abcdefghi";

	for(int i = 0; i < 9; i++)
		m_graph.setVertex(i, V[i]);

	m_graph.setEdge(0, 1, 0);
	m_graph.setEdge(1, 0, 0);
	m_graph.setEdge(0, 3, 0);
	m_graph.setEdge(3, 0, 0);
	m_graph.setEdge(0, 4, 0);
	m_graph.setEdge(4, 0, 0);
	m_graph.setEdge(1, 2, 0);
	m_graph.setEdge(2, 1, 0);
	m_graph.setEdge(1, 4, 0);
	m_graph.setEdge(4, 1, 0);
	m_graph.setEdge(2, 5, 0);
	m_graph.setEdge(5, 2, 0);
	m_graph.setEdge(3, 6, 0);
	m_graph.setEdge(6, 3, 0);
	m_graph.setEdge(4, 6, 0);
	m_graph.setEdge(6, 4, 0);
	m_graph.setEdge(6, 7, 0);
	m_graph.setEdge(7, 6, 0);
	m_graph.setEdge(7, 8, 0);
	m_graph.setEdge(8, 7, 0);

	SharedPointer<Array<int>> m_bfs = m_graph.DFS(0); //Debug...
	
	for(int i = 0; i < m_bfs->length(); i++)
		cout << (*m_bfs)[i] << endl;

	return 0;
} 

