#ifndef __GRAPH_SEARCH_DIJKSTRA_H__
#define __GRAPH_SEARCH_DIJKSTRA_H__

#include <vector>
#include "PriorityQLow.h"
#include "SparseGraph.h"

using namespace std;

/**
	Dijkstra�����㷨
*/
class GraphSearchDijkstra
{
protected:
    static int m_count;                                 // ͳ��ѭ������

    /**
    	 ������Ϊ�˷�ֹÿ��search��Ҫ��ջ�д���һ��
    */
    static vector<NavGraphEdge*> m_shortestPathTree;    // �����õ���С·����
    static vector<float> m_costToThisNode;              // ��¼��ǰ����ýڵ����С����
    static vector<NavGraphEdge*> m_searchFroniter;      // ��ʱ��¼��ǰ����ĳ���ڵ�ĸ���

public:
    static vector<int> search(SparseGraph& grap, int sourceIndex, int targetIndex)
    {
        if (sourceIndex == targetIndex)
        {
            return vector<int>();
        }

        if (m_shortestPathTree.size() != grap.getNodeNumber())
        {
            m_shortestPathTree  =   vector<NavGraphEdge*>(grap.getNodeNumber(), nullptr);
        }
        else
        {
            for (int n = 0; n < m_shortestPathTree.size(); n++)
            {
                m_shortestPathTree[n]   =   nullptr;
            }
        }

        if (m_costToThisNode.size() != grap.getNodeNumber())
        {
            m_costToThisNode    =   vector<float>(grap.getNodeNumber(), 0);
        }
        else
        {
            for (int i = 0; i < m_costToThisNode.size(); i++)
            {
                m_costToThisNode[i] =   0;
            }
        }

        if (m_searchFroniter.size() != grap.getNodeNumber())
        {
            m_searchFroniter    =   vector<NavGraphEdge*>(grap.getNodeNumber(), nullptr);
        }
        else
        {
            for (int n = 0; n < m_searchFroniter.size(); n++)
            {
                m_searchFroniter[n] =   nullptr;
            }
        }

        // һ�����ȼ�����
        PriorityQLow prioQ(m_costToThisNode);

        // ���Լ�����
        prioQ.insert(sourceIndex);

        m_count =   0;
        while (!prioQ.empty())
        {
            m_count++;

            int tmpNodeIndex    =   prioQ.pop();

            // ������С·������
            m_shortestPathTree[tmpNodeIndex]    =   m_searchFroniter[tmpNodeIndex];

            if (tmpNodeIndex == targetIndex)
            {
                // ������
                vector<int> tmpRet;
                tmpRet.push_back(targetIndex);
                NavGraphEdge* tmpTreeEdge   =   m_shortestPathTree[targetIndex];
                while (tmpTreeEdge->from() != sourceIndex)
                {
                    tmpRet.push_back(tmpTreeEdge->from());
                    tmpTreeEdge =   m_shortestPathTree[tmpTreeEdge->from()];
                }
                tmpRet.push_back(sourceIndex);

                reverse(tmpRet.begin(), tmpRet.end());
                return tmpRet;
            }

            // ��ʼ�����ýڵ���Χ�ı�
            SparseGraph::EdgeIterator tmpIterator(&grap, tmpNodeIndex);
            NavGraphEdge* tmpEdge   =   tmpIterator.begin();
            for (; !tmpIterator.end(); tmpEdge = tmpIterator.next())
            {
                float tmpNewCost    =   m_costToThisNode[tmpNodeIndex] + tmpEdge->cost();

                if (m_searchFroniter[tmpEdge->to()] == nullptr)
                {
                    m_searchFroniter[tmpEdge->to()] =   tmpEdge;
                    m_costToThisNode[tmpEdge->to()] =   tmpNewCost;
                    prioQ.insert(tmpEdge->to());
                }
                else if (tmpNewCost < m_costToThisNode[tmpEdge->to()])
                {
                    // ��Ҫ�ɱ�
                    m_searchFroniter[tmpEdge->to()] =   tmpEdge;
                    m_costToThisNode[tmpEdge->to()] =   tmpNewCost;
                    prioQ.reOrder();
                }
            }
        }

        return vector<int>(0);
    }
};

#endif