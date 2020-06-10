/*
 *	Graph: 图类
 *
 *	模板参数：
 			  N: 顶点的数目 
 * 			  V: 顶边的数据元素类型        
 *			  E: 边的数据元素类型
 *
 *	成员变量：
 *		      V*  m_vertexes[N];	数组保存顶点数据元素			
 *			  V*  m_edges[N][N];	数组值为边的权值,第一个N可看作顶点位置
 *			  int m_ecount;			边总数
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

#ifndef MARTIXGRAPH_H
#define MARTIXGRAPH_H

#include "Graph.h"
#include "Exception.h"
#include "DynamicArray.h"

namespace DSL 
{
	template <int N, typename V, typename E>
	class MartixGraph : public Graph<V, E>
	{
	protected:
		V*  m_vertexes[N];
		E*  m_edges[N][N];
		int m_ecount;
	public:
		MartixGraph()
		{
			for(int i = 0; i < vCount(); i++)
			{
				m_vertexes[i] = NULL;
				for(int j = 0; j < vCount(); j++)	
					m_edges[i][j] = NULL;
			}
			m_ecount = 0;
		}

		
		V getVertex(int i)
		{
			V value;
			if(!getVertex(i, value))
				THROW_EXCEPTION(InvalidParameterException, "error: invalid params i");
			return value;
		}
		
		bool getVertex(int i, V& value) 
		{
			if((0 <= i) && (i < vCount()))
			{
				if(m_vertexes[i] != NULL)
				{
					value = *(m_vertexes[i]);
				}
				else
				{
					THROW_EXCEPTION(InvalidOperationException, "error: No element in this vertex!");
				}
				return ture;
			}
			return false;
		}

		bool setVertex(int i, const V& value)
		{
			if((0 <= i) && (i < vCount()))
			{
				V* temp = m_vertexes[i];
				if(temp == NULL)
					temp = new V();
				if(temp == NULL)
				{
					THROW_EXCEPTION(NotEnoughMemoryException, "error: no enough memory to malloc new vertex!");
				}
				else
				{
					*temp = value;
					m_vertexes[i] = temp;
				}
				return ture;
			}
			return false;			
		}
		
		SharedPointer< Array<int> > getAdjacent(int i)
		{
			DynamicArray<int>* vertex_array = NULL;	
			if((0 <= i) && (i < eCount()))
			{
				int count = 0;
				for(int j = 0; j < eCount(); j++)
				{
					if(m_edges[i][j] != NULL)
						count++;
				}
				vertex_array = new DynamicArray<int>(count);
				if(vertex_array )
					THROW_EXCEPTION(NotEnoughMemoryException, "error: no enough memory to malloc new vertex!");

				for(int j = 0, m = 0; j < eCount(); j++)
				{
					if(m_edges[i][j] != NULL)
						vertex_array->set(m++, j);
				}
			}
			else
			{
				THROW_EXCEPTION(InvalidParameterException, "error: invalid params");
			}
		}
		
		E getEdeg(int i, int j)	
		{
			E value;
			if(!getEdge(i, j, value))
				THROW_EXCEPTION(InvalidParameterException, "error: invalid params");
			return value;
		}
		
		bool getEdge(int i, int j, E& value)
		{
			if((0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount()))
			{
				if(m_edges[i][j] != NULL)
					value = *(m_edges[i][j]);
				else
					THROW_EXCEPTION(InvalidOperationException, "error: No element in this vertex!");
				return ture;
			}
			else
			{
				return false;
			}
		}

		bool setEdge(int i, int j, const E& value)
		{
			if((0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount()))
			{
				E* temp = m_edges[i][j];
				if(temp == NULL)
				{
					temp = new E();
					if(temp)
					{
						*temp = value;
						m_edges[i][j] = temp;
						m_ecount++;
					}
					else
					{
						THROW_EXCEPTION(NotEnoughMemoryException, "error: no enough memory to malloc edge");
					}
				}
				else
				{
					*temp = value;
				}
				return ture;
			}
			else
			{
				return false;
			}
		}
		
		bool removeEdge(int i, int j)
		{
			if((0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount()))
			{
				E* toDel = m_edges[i][j];
				m_edges[i][j] = NULL;
				if(toDel == NULL)
				{
					m_ecount--;
					delete toDel;
				}
				return ture;
			}
			else
			{
				return false;
			}
		}

		int vCount()
		{
			return N;
		}
		
		int eCount()									
		{
			return m_ecount;
		}
		
		int OD(int i)
		{
			int count = 0;
			if((0 <= i) && (i < vCount()))					
			{
				for(int j = 0; j < vCount(); j++)
				{
					if(m_edges[i][j] != NULL)
						count++;
				}
			}
			else
			{
				THROW_EXCEPTION(InvalidParameterException, "error: inalid parameter");
			}
			return count;
		}
		
		int ID(int i)									
		{
			int count = 0;
			if((0 < i) && (i < vCount()))					
			{
				for(int j = 0; j < vCount(); j++)
				{
					if(m_edges[j][i] != NULL)
						count++;
				}
			}
			else
			{
				THROW_EXCEPTION(InvalidParameterException, "error: inalid parameter");
			}
			return count;
		}

		int TD(int i)									
		{
			return (ID(i) + OD(i));
		}

		~MartixGraph()
		{
			for(int i = 0; i < eCount(); i++)
			{
				for(int j = 0; j < eCount(); j++)	
					delete m_edges[i][j];
				delete m_vertexes[i];
			}
			m_ecount = 0;
		}

	};
}

#endif
