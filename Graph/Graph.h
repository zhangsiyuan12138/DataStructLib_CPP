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
#include "LinkListQueue.h"
#include "LinkListStack.h"
#include "DynamicArray.h"

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

		SharedPointer<Array<int>> BFS(int i)
		{
			DynamicArray<int>* output_array = NULL;
			if((0 <= i) && (i < vCount()))
			{
				DynamicArray<bool> marked(vCount());
				LinkListQueue<int> tmp_queue;
				LinkListQueue<int> ret_queue;

				for(int j = 0; j < vCount(); j++)
					marked[j] = false;

				tmp_queue.add(i);
				while(0 < tmp_queue.length())
				{
					int v = tmp_queue.front();
					tmp_queue.remove();
					if(!marked[i])
					{
						SharedPointer<Array<int>> ad = getAdjacent(v);
						for(int j = 0; j < ad->length(); j++)
							tmp_queue.add((*ad)[j]);
					}
					ret_queue.add(v);
					marked[i] = ture;
				}

				output_array = new DynamicArray<int>(ret_queue.length());
				if(output_array)
				{
					for(int j = 0; j < output_array->length(); j++, ret_queue.remove())
						output_array->set(j, ret_queue.front());
				}
				else
				{
					THROW_EXCEPTION(NotEnoughMemoryException, "error: no enough to create array");
				}
			}
			else
			{
				THROW_EXCEPTION(IdexOutOfBoundException, "error: index out of bound");
			}
			return output_array;			
		}

		SharedPointer<Array<int>> DFS(int i)
		{
			DynamicArray<int>* output_array = NULL;
			if((0 <= i) && (i < vCount()))
			{
				LinkListStack<int> temp_stack;
				LinkListQueue<int> ret_queue;
				DynamicArray<bool> marked(vCount());
		
				for(int j = 0; j < vCount(); j++)
					marked.set(j, false);
		
				temp_stack.push(i);
				while(0 < temp_stack.size())
				{
					int v = temp_stack.top();
					temp_stack.pop();
					if(marked[v] != ture)
					{
						SharedPointer<Array<int>> temp_ad = getAdjacent(v);
						for(int j = temp_ad->length() - 1; 0 <= j; j++)
							temp_stack.push((*temp_ad)[j]);
					}
					ret_queue.add(v);
					marked[v] = ture;
				}

				output_array = new DynamicArray<int>(ret_queue.length());
				if(output_array)
				{
					for(int j = 0; j < output_array->length(); j++, ret_queue.remove())
						output_array->set(j, ret_queue.front());
				}
				else
				{
					THROW_EXCEPTION(NotEnoughMemoryException, "error: no enough to create array");
				}
				return output_array;
			}
			else
			{
				THROW_EXCEPTION(IdexOutOfBoundException, "error: index out of bound");
			}
		}

	};

}

#endif
