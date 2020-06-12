/*
 *	ListGraph: �ڽ�����
 *
 *	ģ�������
 * 			  V: ���������Ԫ������        
 *			  E: �ߵ�����Ԫ������
 *
 *	��Ա������
 *			  struct Edges{
 *			  		int e_start;			�ߵ���ʼ��
 *  		  		int e_end;      		�ߵ��յ�
 *			  		E data;}				�ߵ�Ȩֵ
 *
 *			  struct Vertex{
 *					V* data;				���������Ԫ��
 *					LinkList<Edges> edges;} ���������ڽӵ��������ߵ���Ϣ
 * 			  LinkList<Vertex*> m_list		�ڽ�����
 *			  int m_ecount;					������
 *  ��Ա������
 *				int addVertex() 									������β�������µĶ��㣬���ض�����
 *				int addVertex(const& value)							�����µĶ��㲢��Ӷ���Ԫ��
 *				bool removeVertex()									ɾ������β���Ķ���,ɾ����ر�
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

		Edge(int i, int j, const E& value)
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
						int pos = m_list.current()->edge.find(Edge<E>(i, index)); // ɾ�������������صı�
						if(pos >= 0)
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
				if(temp_d == NULL)
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
						ad_array->set(i, temp_v->edge.current().e_end);
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
			return ad_array;
		}

		
		E getEdge(int i, int j)
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
					ret = temp_v->edge.set(pos, Edge<E>(i, j, value));
				}
				else
				{
					ret = temp_v->edge.insert(0, Edge<E>(i, j, value));
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
			for(m_list.move(0); !m_list.end(); m_list.next())
				count += m_list.current()->edge.length();
			return count;
		}

		int ID(int i)									
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

		int OD(int i)									
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
			return (ID(i) + OD(i));
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
