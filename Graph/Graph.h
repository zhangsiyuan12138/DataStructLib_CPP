/*
 *	Graph: ͼ��
 *	��Ա������
 *				
 *  ��Ա������
 *				V getVertex(int i)									��ȡλ��Ϊi�Ľڵ�
 *				bool getVertex(int i, V& value) 					�ж�λ��Ϊi�Ľڵ��value�ڵ��Ƿ����
 *				bool setVertex(int i, const V& value)				���ýڵ�i��Ϊvalue
 *				SharedPointer< Array<int> > getAdjacent(int i)		��ȡ�ڵ��i�������ڽӽڵ�
 *				E getEdge(int i, int j)								��ȡ�ڵ�i�ͽڵ�j֮��ı�
 *				bool getEdge(int i, int j, E& value)				�жϽڵ�i�ͽڵ�j֮��ı��Ƿ��value���
 *				bool setEdge(int i, int j, const E& value)			���ýڵ�i�ͽڵ�j֮��ıߵ�Ȩ��
 *				bool removeEdge(int i, int j)						ȥ���ڵ�i�ͽڵ�j֮���Ȩ��
 *				int vCount()										����ͼ�����еĽڵ�
 *				int eCount()										����ͼ�����еı�
 *				int OD(int i)										����ڵ�i�ĳ���
 *				int ID(int i)										����ڵ�i�����
 *				int TD(int i)										����ڵ�i�Ķ�
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
		virtual E getEdge(int i, int j) = 0;
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
