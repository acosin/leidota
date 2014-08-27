#ifndef __SPARSE_GRAPH_H__
#define __SPARSE_GRAPH_H__

#include "NavGraphNode.h"
#include "NavGraphEdge.h"

#include <map>
#include <list>
#include <assert.h>

using namespace std;

/**
	 ����ϡ��ͼ�����ݽṹ
*/
class SparseGraph
{
protected:
    typedef map<int, NavGraphNode>  NodeVector;
    typedef list<NavGraphEdge>      EdgeList;
    typedef map<int, EdgeList>      EdgeListVector;

    /**
    	 ���սڵ��index�±걣�����������
    */
    NodeVector      m_nodes;
    /**
    	 �±��ǽڵ��±꣬��Ӧһ���Ӹýڵ���������б�
    */
    EdgeListVector  m_edges;

    bool            m_directed;             // �Ƿ�����

public:
    SparseGraph(bool directed = false)
    {
        m_directed  =   directed;
    }

    ~SparseGraph()
    {
        
    }

    void addNode(NavGraphNode node)
    {
        assert(m_nodes.find(node.index()) == m_nodes.end() && "add node multi");

        m_nodes.insert(make_pair(node.index(), node));
        if (m_edges.find(node.index()) == m_edges.end())
        {
            m_edges.insert(make_pair(node.index(), EdgeList()));
        }
    }

    void addEdge(NavGraphEdge edge)
    {
        assert(m_nodes.find(edge.from()) != m_nodes.end() && m_nodes.find(edge.to()) != m_nodes.end()
            && "invalid edge from or to");
        EdgeList* tmpList   =   &(*m_edges.find(edge.from())).second;
        tmpList->push_back(edge);

        if (!m_directed)
        {
            // ������޷���ģ�����Ҫ����һ���෴��·��
            NavGraphEdge newEdge(edge);
            newEdge.setFrom(edge.to());
            newEdge.setTo(edge.from());
            tmpList =   &(*m_edges.find(newEdge.from())).second;
            tmpList->push_back(newEdge);
        }
    }

    int getNodeNumber()
    {
        return m_nodes.size();
    }

    NavGraphNode& getNodeByIndex(int index)
    {
        assert(m_nodes.find(index) != m_nodes.end());
        return (*m_nodes.find(index)).second;
    }

    /**
    	 �����޸�ĳ���ڵ�Ŀ�ͨ������
    */
    void setNodePassable(int nodeIndex, bool passable)
    {
        // �޸���Ӧ�ڵ�
        m_nodes[nodeIndex].setPassable(passable);
    }

    /**
    	 �������еĸ��Ӷ�����ͨ��
    */
    void resetAllNodePassable()
    {
        for (auto tmpIterator = m_nodes.begin(); tmpIterator != m_nodes.end(); tmpIterator++)
        {
            tmpIterator->second.setPassable(true);
        }
    }

    /**
    	 ���������Ӹýڵ���������бߣ�ֻ�иñ߿���ʹ�ã����Ҹýڵ��Լ���Ӧ��to�ڵ����ʹ�õĲŻ�
         ����
    */
    class EdgeIterator
    {
    protected:
        typedef EdgeList::iterator  CurEdge;

        int             m_nodeIndex;
        SparseGraph*    m_graph;
        CurEdge         m_iterator;
        EdgeList*       m_list;

    public:
        EdgeIterator(SparseGraph* graph, int nodeIndex)
        {
            // Ҫ�����ýڵ���ڣ����ұ����ǿ���ʹ�õĽڵ�
            assert(graph->m_edges.find(nodeIndex) != graph->m_edges.end() && "invalid nodeindex");

            m_graph     =   graph;
            m_nodeIndex =   nodeIndex;
            m_list      =   &((*m_graph->m_edges.find(nodeIndex)).second);
            m_iterator  =   m_list->begin();
        }

        NavGraphEdge* begin()
        {
            m_iterator  =   m_list->begin();

            // ������Ҫ���ؿ���ʹ�õıߣ����Ҹı��toָ��Ľڵ�Ҳ����ʹ��
            while ((!end()) && (!m_iterator->passable() || !m_graph->getNodeByIndex(m_iterator->to()).passable()))
            {
                m_iterator++;
            }

            if (end())
            {
                return nullptr;
            }
            return &(*m_iterator);
        }

        NavGraphEdge* next()
        {
            m_iterator++;

            // Ҳ��Ҫ�жϣ����뷵�ؿ���ʹ�õ�
            while ((!end()) && (!m_iterator->passable() || !m_graph->getNodeByIndex(m_iterator->to()).passable()))
            {
                m_iterator++;
            }

            if (end())
            {
                return nullptr;
            }

            return &(*m_iterator);
        }

        bool end()
        {
            auto tmpIterator    =   m_iterator;
            for (; tmpIterator != m_list->end(); tmpIterator++)
            {
                if (tmpIterator->passable() && m_graph->getNodeByIndex(tmpIterator->to()).passable())
                {
                    return false;
                }
            }

            return true;
        }
    };

    friend class EdgeIterator;

    /**
    	 ��������ĳһ���ڵ���Χ�������ڵ�
    */
    class NodeIterator
    {
    protected:
        typedef EdgeList::iterator  CurEdge;

        int             m_nodeIndex;
        SparseGraph*    m_graph;
        CurEdge         m_iterator;
        EdgeList*       m_list;

    public:
        NodeIterator(SparseGraph* graph, int nodeIndex)
        {
            // �ýڵ�������ʹ��
            assert(graph->m_edges.find(nodeIndex) != graph->m_edges.end() && "invalid nodeindex");

            m_graph     =   graph;
            m_nodeIndex =   nodeIndex;
            m_list      =   &((*m_graph->m_edges.find(nodeIndex)).second);
            m_iterator  =   m_list->begin();
        }

        NavGraphNode* begin()
        {
            m_iterator  =   m_list->begin();

            while ((!end()) && (!m_iterator->passable() || !m_graph->getNodeByIndex(m_iterator->to()).passable()))
            {
                m_iterator++;
            }

            if (end())
            {
                return nullptr;
            }
            return &(*m_graph->m_nodes.find((*m_iterator).to())).second;
        }

        NavGraphNode* next()
        {
            m_iterator++;

            while ((!end()) && (!m_iterator->passable() || !m_graph->getNodeByIndex(m_iterator->to()).passable()))
            {
                m_iterator++;
            }

            if (end())
            {
                return nullptr;
            }
            return &(*m_graph->m_nodes.find((*m_iterator).to())).second;
        }

        bool end()
        {
            auto tmpIterator    =   m_iterator;
            for (; tmpIterator != m_list->end(); tmpIterator++)
            {
                if (tmpIterator->passable() && m_graph->getNodeByIndex(tmpIterator->to()).passable())
                {
                    return false;
                }
            }

            return true;
        }
    };

    friend class NodeIterator;
};

#endif