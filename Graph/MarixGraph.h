/*
 *	MartixGraph: �ڽӾ���
 *
 *	ģ�������
 			  N: �������Ŀ 
 * 			  V: ���������Ԫ������        
 *			  E: �ߵ�����Ԫ������
 *
 *	��Ա������
 *		      V*  m_vertexes[N];	���鱣�涥������Ԫ�أ�ָ�������Ч			
 *			  V*  m_edges[N][N];	����ֵΪ�ߵ�Ȩֵ,��һ��N�ɿ�������λ��
 *			  int m_ecount;			������
 *  ��Ա������
 *				V getVertex(int i)									��ȡλ��Ϊi�Ľڵ�
 *				bool getVertex(int i, V& value) 					�ж�λ��Ϊi�Ľڵ��value�ڵ��Ƿ����
 *				bool setVertex(int i, const V& value)				���ýڵ�i��Ϊvalue
 *				SharedPointer< Array<int> > getAdjacent(int i)		��ȡ�ڵ��i�������ڽӽڵ�
 *				E getEdeg(int i, int j)								��ȡ�ڵ�i�ͽڵ�j֮��ı�
 *				bool getEdge(int i, int j, E& value)				�жϽڵ�i�ͽڵ�j֮��ı��Ƿ��value���
 *				bool setEdge(int i, int j, const E& value)			���ýڵ�i�ͽڵ�j֮��ıߵ�Ȩ��
 *				bool removeEdge(int i, int j)						ȥ���ڵ�i�ͽڵ�j֮���Ȩ��
 *				int vCount()										����ͼ�����еĽڵ�
 *				int eCount()										����ͼ�����еı�
 *				int OD(int i)										����ڵ�i�ĳ���
 *				int ID(int i)										����ڵ�i�����
 *				int TD(int i)										����ڵ�i�Ķ�
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
			if((0 <= i) && (i < vCount()))
			{
				int count = 0;
				for(int j = 0; j < vCount(); j++)
				{
					if(m_edges[i][j] != NULL)
						count++;
				}
				vertex_array = new DynamicArray<int>(count);
				if(vertex_array == NULL)
				{
					THROW_EXCEPTION(NotEnoughMemoryException, "error: no enough memory to malloc new vertex!");
				}
				else
				{
					for(int j = 0, m = 0; j < vCount(); j++)
					{
						if(m_edges[i][j] != NULL)
							vertex_array->set(m++, j);
					}
				}
			}
			else
			{
				THROW_EXCEPTION(InvalidParameterException, "error: invalid params");
			}
			return vertex_array;
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
				if(toDel != NULL)
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
