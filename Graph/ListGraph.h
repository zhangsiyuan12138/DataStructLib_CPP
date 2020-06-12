/*
 *	ListGraph: 邻接链表
 *
 *	模板参数：
 * 			  V: 顶点的数据元素类型        
 *			  E: 边的数据元素类型
 *
 *	成员变量：
 *			  struct Edges{
 *			  		int e_start;			边的起始点
 *  		  		int e_end;      		边的终点
 *			  		E data;}				边的权值
 *
 *			  struct Vertex{
 *					V* data;				顶点的数据元素
 *					LinkList<Edges> edges;} 保存所有邻接到这个顶点边的信息
 * 			  LinkList<Vertex*> m_list		邻接链表
 *			  int m_ecount;					边总数
 *  成员函数：
 *				int addVertex() 									在链表尾部插入新的顶点，返回顶点编号
 *				int addVertex(const& value)							增加新的顶点并添加顶点元素
 *				bool removeVertex()									删除链表尾部的顶点,删除相关边
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

#ifndef LISTGRAPH_H
#define LISTGRAPH_H

#include "Graph.h"
#include "LinkList.h"
#include "Exception.h"
#include "DynamicArray.h"

namespace DSL 
{
	template<typename E>
	struct Edge : public TopClass
	{
		int e_sta;
		int e_end;
		E data;

		Edge(int i = -1, int j = -1)
		{
			e_sta = i;
			e_end = j;
		}

		Edge(int i, int j, E& value)
		{
			e_sta = i;
			e_end = j;
			data = value;
		}

		bool operator == (const Edge<E>& obj)
		{
			return 	((e_sta == obj.e_sta) && (e_end == obj.e_end));
		}

		bool operator != (const Edge<E>& obj)
		{
			return 	!(obj == *this);
		}

	};

	template <typename V, typename E>
	class ListGraph : public TopClass
	{
	protected:
		struct Vertex : public TopClass
		{
			V* data;
			LinkList<Edge<E>> edge;
			
			Vertex()
			{
				data = NULL;
			}
		};
	
		LinkList<Vertex*> m_list;

	public:
		ListGraph(unsigned int pos = 0)
		{
			for(int i = 0; i < pos; i++)
				addVertex();
		}

		int addVertex()
		{
			int pos = -1;
			Vertex* temp_v = new Vertex();
			if(temp_v != NULL)
			{
				m_list.insert(temp_v);
				pos = m_list.length() - 1;
			}
			else
			{
				THROW_EXCEPTION(NotEnoughMemoryException, "error: no enough memory to create Vertex");
			}
			return pos;
		}
		
		int addVertex(const V& value)
		{
			int pos = addVertex();
			if(pos >= 0)
			{
				setVertex(pos, value);
			}
			else
			{
				THROW_EXCEPTION(IdexOutOfBoundException, "error: index out of bound");
			}
		}

		
		bool removeVertex()					
		{
			int index = m_list.length() - 1;
			if(index >= 0)
			{
				Vertex* v = m_list.get(index);
				if(m_list.remove(index))
				{
					for(int i = (m_list.move(0), 0); !m_list.end(); i++,  m_list.next())
					{
						int pos = m_list.current()->edge.find(Edge<E>(i, index)); // 删除与这个顶点相关的边
						if(pos > 0)
							m_list.current()->edge.remove(pos);
					}
				}
				delete v->data;
				delete v;
				return ture;
			}
			else
			{
				THROW_EXCEPTION(InvalidOperationException, "error: no vertex in this graph");
			}
		}
		
		V getVertex(int i)	
		{
			V ret;
			if(!getVertex(i, ret))
				THROW_EXCEPTION(IdexOutOfBoundException, "error: index out of bound");
			return ret;
		}
		
		bool getVertex(int i, V& value)
		{
			bool ret = ((0 <= i) && (i < vCount()));
			if(ret)
			{
				Vertex* temp_v = m_list.get(i);
				if(temp_v->data != NULL)
				{
					value = *(temp_v->data);
				}
				else
				{
					THROW_EXCEPTION(InvalidOperationException, "error: no value assigned to this vertex");
				}
			}
			return ret;

		}
		
		bool setVertex(int i, const V& value)			
		{
			bool ret = ((0 <= i) && (i < vCount()));
			if(ret)
			{
				Vertex* temp_v = m_list.get(i);
				V* temp_d = temp_v->data;
				if(temp_d)
				{
					temp_d = new V();
					if(temp_d)
					{
						*temp_d = value;
						temp_v->data = temp_d;
						ret = ture;
					}
					else
					{
						THROW_EXCEPTION(NotEnoughMemoryException, "error: no enough memory to create data");
					}
				}
			}
			else
			{
				THROW_EXCEPTION(IdexOutOfBoundException, "error: index out of bound");
			}
			return ret;
		}

		SharedPointer< Array<int> > getAdjacent(int i)
		{
			DynamicArray<int>* ad_array = NULL;
			if((0 <= i) && (i < vCount()))
			{
				Vertex* temp_v = m_list.get(i);
				ad_array = new DynamicArray<int>(temp_v->edge.length());
				if(ad_array != NULL)
				{
					for(int i = (temp_v->edge.move(0), 0); !temp_v->edge.end(); i++, temp_v->edge.next())
					{
						ad_array[i].set(i, temp_v->edge.current().e_end);
					}
				}
				else
				{
					THROW_EXCEPTION(NotEnoughMemoryException, "error: no enough memory to create data");
				}
			}
			else
			{
				THROW_EXCEPTION(IdexOutOfBoundException, "error: index out of bound");
			}
		}

		
		E getEdeg(int i, int j)
		{
			E ret;
			if(!getEdge(i, j, ret)) 
				THROW_EXCEPTION(InvalidParameterException, "error: Invalid Parameter");
			
			return ret;
		}

		bool getEdge(int i, int j, E& value)
		{
			bool ret = ((0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount()));
			if(ret)
			{
				Vertex* temp_v = m_list.get(i);
				int pos = temp_v->edge.find(Edge<E>(i, j));
				if(pos >= 0)
				{
					value = temp_v->edge.get(pos).data;
				}
				else
				{
					THROW_EXCEPTION(IdexOutOfBoundException, "error: index out of bound");
				}
			}
			else
			{
				THROW_EXCEPTION(IdexOutOfBoundException, "index out of bound");
			}
			return ret;
		}
		
		bool setEdge(int i, int j, const E& value)
		{
			bool ret = ((0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount()));
			if(ret)
			{
				Vertex* temp_v = m_list.get(i);
				int pos = temp_v->edge.find(Edge<E>(i, j));
				if(pos >= 0)
				{
					ret = temp_v->edge.set(pos, value);
				}
				else
				{
					ret = temp_v->edge.insert(value);
				}
			}
			else
			{
				THROW_EXCEPTION(IdexOutOfBoundException, "index out of bound");
			}
			return ret;
		}
		
		bool removeEdge(int i, int j)					
		{
			bool ret = ((0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount()));
			if(ret)
			{
				Vertex* temp_v = m_list.get(i);
				int pos = temp_v->edge.find(Edge<E>(i, j));
				if(pos >= 0)
				{
					ret = temp_v->edge.remove(pos);
				}
				else
				{
					THROW_EXCEPTION(IdexOutOfBoundException, "index out of bound");
				}
			}
			else
			{
				THROW_EXCEPTION(IdexOutOfBoundException, "index out of bound");
			}
			return ret;
		}

		int vCount()
		{
			return m_list.length();
		}

		int eCount()									
		{
			int count = 0;
			for(m_list.move(0); m_list.end(); m_list.next())
				count += m_list.current()->edge.length();
			return count;
		}

		int OD(int i)									
		{
			int count = 0;
			if((0 <= i) && (i < vCount()))
			{
				for(m_list.move(0); !m_list.end(); m_list.next())
				{
					for(m_list.current()->edge.move(0); !m_list.current()->edge.end(); m_list.current()->edge.next())
					{
						if(m_list.current()->edge.current().e_end == i)
						{
							count++;
							break;
						}
					}
				}
			}
			else
			{
				THROW_EXCEPTION(IdexOutOfBoundException, "index out of bound");
			}
			return count;
		}

		int ID(int i)									
		{
			int count = 0;
			if((0 <= i) && (i < vCount()))
			{
				count = m_list.get(i)->edge.length();
			}
			else
			{
				THROW_EXCEPTION(IdexOutOfBoundException, "index out of bound");
			}
			return count;
		}

		int TD(int i)									
		{
			return (ID() + OD());
		}

		~ListGraph()
		{
			while(m_list.length() > 0)
			{
				Vertex* toDel = m_list.get(0);
				m_list.remove(0);
				delete toDel->data;
				delete toDel;
			}
		}
	};
}

#endif
