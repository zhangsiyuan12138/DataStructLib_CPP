/*
 *	Graph: 图类
 *	成员变量：
 *				
 *  成员函数：
 *				V getVertex(int i)									获取位置为i的节点
 *				bool getVertex(int i, V& value) 					判断位置为i的节点和value节点是否相等
 *				bool setVertex(int i, const V& value)				设置节点i的为value
 *				SharedPointer< Array<int> > getAdjacent(int i)		获取节点的i的所有邻接节点
 *				E getEdeg(int i, int j)								获取节点i和节点j之间的边
 *				bool getEdge(int i, int j, E& value)				判断节点i和节点j之间的边是否和value相等
 *				bool setEdge(int i, int j, const E& value)			设置节点i和节点j之间的边的权重
 *				bool removeEdge(int i, int j)						去掉节点i和节点j之间的权重
 *				int vCount()										计算图中所有的节点
 *				int eCount()										计算图中所有的边
 *				int OD(int i)										计算节点i的出度
 *				int ID(int i)										计算节点i的入度
 *				int TD(int i)										计算节点i的度
*/


#ifndef GRAPH_H
#define GRAPH_H

#include "TopClass.h"
#include "SharedPointer.h"
#include "Array.h"

namespace DSL
{
	template <typename V, typename E>
	class Graph : public TopClass
	{
	public:
		virtual V getVertex(int i) = 0;
		virtual bool getVertex(int i, V& value) = 0;
		virtual bool setVertex(int i, const V& value) = 0;
		virtual SharedPointer< Array<int> > getAdjacent(int i) = 0;		
		virtual E getEdeg(int i, int j) = 0;
		virtual bool getEdge(int i, int j, E& value) = 0;
		virtual bool setEdge(int i, int j, const E& value) = 0;
		virtual bool removeEdge(int i, int j) = 0;
		virtual int vCount() = 0;
		virtual int eCount() = 0;
		virtual int OD(int i) =0;
		virtual int ID(int i) = 0;
		virtual int TD(int i) = 0;
	};

}

#endif
