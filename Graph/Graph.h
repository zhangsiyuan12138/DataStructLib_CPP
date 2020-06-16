/*
 *	Graph: 图类
 *	成员变量：
 *				
 *  成员函数：
 *				V getVertex(int i)									获取位置为i的节点
 *				bool getVertex(int i, V& value) 					判断位置为i的节点和value节点是否相等
 *				bool setVertex(int i, const V& value)				设置节点i的为value
 *				SharedPointer< Array<int> > getAdjacent(int i)		获取节点的i的所有邻接节点
 *				E getEdge(int i, int j)								获取节点i和节点j之间的边
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
#include "LinkListQueue.h"
#include "LinkListStack.h"
#include "DynamicArray.h"

using namespace std; 

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

		SharedPointer< Array<int> > BFS(int i)
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
					if(!marked[v])
					{
						SharedPointer< Array<int> > ad = getAdjacent(v);
						for(int j = 0; j < ad->length(); j++)
							tmp_queue.add((*ad)[j]);
						ret_queue.add(v);
					}
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
			}
			else
			{
				THROW_EXCEPTION(IdexOutOfBoundException, "error: index out of bound");
			}
			return output_array;			
		}

		SharedPointer< Array<int> > DFS(int i)
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
					if(!marked[v])
					{
						SharedPointer< Array<int> > temp_ad = getAdjacent(v);
						for(int j = (temp_ad->length() - 1); 0 <= j; j--)
							temp_stack.push((*temp_ad)[j]);
						ret_queue.add(v);
					}
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

		SharedPointer< Array<int> > DFS_R(int i)
		{
			DynamicArray<int>* output_array = NULL;
			if((0 <= i) && (i < vCount()))
			{
				LinkListQueue<int> ret_queue;
				DynamicArray<bool> marked(vCount());
				for(int j = 0; j < vCount(); j++)
					marked.set(j, false);
		
				DFS_R_core(*this, i, marked, ret_queue);

				output_array = new DynamicArray<int>(ret_queue.length());
				if(output_array)
				{
					for(int j = 0; j < output_array->length(); j++, ret_queue.remove())
						output_array->set(j, ret_queue.front());
				}
			}
			else
			{
				THROW_EXCEPTION(IdexOutOfBoundException, "error: index out of bound");
			}
			return output_array;
		}

		void DFS_R_core(Graph<V, E>& g, int i, Array<bool>& marked, LinkListQueue<int>& ret_queue)
		{
			ret_queue.add(i);
			marked[i] = ture; 
			SharedPointer< Array<int> > ad = g.getAdjacent(i);
			for(int j = 0; j < ad->length(); j++)
			{
				if(!marked[(*ad)[j]])
					DFS_R_core(g, (*ad)[j], marked, ret_queue);
			}
		}
	};

}

#endif
