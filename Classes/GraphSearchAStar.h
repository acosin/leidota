#ifndef __GRAPH_SEARCH_A_STAR_H__
#define __GRAPH_SEARCH_A_STAR_H__

#include <vector>
#include "SparseGraph.h"
#include "PriorityQLow.h"

using namespace std;

/**
	 ���������������ӵĻص�����
*/ 
typedef float (*HeuristicFunc)(SparseGraph& grap, int sourceIndex, int targetIndex);

/**
	 A���㷨����·��
*/
class GraphSearchAStar
{
protected:
    static int m_count;                                 // ͳ��ѭ������
    static vector<float> m_GCosts;                      // ���ýڵ���ۼƿ���
    static vector<float> m_FCosts;                      // ͨ������m_GCosts��ÿ���ڵ�������������ӵĽ��
    static vector<NavGraphEdge*> m_shortestPathTree;    // ��С·����
    static vector<NavGraphEdge*> m_searchFrontier;      // �����õ�

public:
    static vector<int> search(SparseGraph& grap, int sourceIndex, int targetIndex, HeuristicFunc heuristicFunc)
    {
        if (sourceIndex == targetIndex)
        {
            return vector<int>(0);
        }

        if (m_GCosts.size() != grap.getNodeNumber())
        {
            m_GCosts    =   vector<float>(grap.getNodeNumber(), 0);
        }
        else
        {
            for (int n = 0; n < m_GCosts.size(); n++)
            {
                m_GCosts[n] =   0;
            }
        }

        if (m_FCosts.size() != grap.getNodeNumber())
        {
            m_FCosts    =   vector<float>(grap.getNodeNumber(), 0);
        }
        else
        {
            for (int n = 0; n < m_FCosts.size(); n++)
            {
                m_FCosts[n] =   0;
            }
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

        if (m_searchFrontier.size() != grap.getNodeNumber())
        {
            m_searchFrontier    =   vector<NavGraphEdge*>(grap.getNodeNumber(), nullptr);
        }
        else
        {
            for (int n = 0; n < m_searchFrontier.size(); n++)
            {
                m_searchFrontier[n] =   nullptr;
            }
        }

        // ���ȼ�����
        PriorityQLow prioQ(m_FCosts);

        // ���Լ�����
        prioQ.insert(sourceIndex);

        m_count =   0;
        while (!prioQ.empty())
        {
            m_count++;

            int tmpNodeIndex    =   prioQ.pop();

            // ������С·������
            m_shortestPathTree[tmpNodeIndex]    =   m_searchFrontier[tmpNodeIndex];

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
                // ��Դ�ڵ㵽�ýڵ������
                float tmpGCost  =   m_GCosts[tmpNodeIndex] + tmpEdge->cost();
                // ������Ǽ�����������
                float tmpHCost  =   heuristicFunc(grap, tmpEdge->to(), targetIndex);

                if (m_searchFrontier[tmpEdge->to()] == nullptr)
                {
                    m_searchFrontier[tmpEdge->to()] =   tmpEdge;
                    m_GCosts[tmpEdge->to()] =   tmpGCost;
                    m_FCosts[tmpEdge->to()] =   tmpGCost + tmpHCost;
                    prioQ.insert(tmpEdge->to());
                }
                else if (tmpGCost < m_GCosts[tmpEdge->to()])
                {
                    // ��Ҫ�ɱ�
                    m_searchFrontier[tmpEdge->to()] =   tmpEdge;
                    m_GCosts[tmpEdge->to()]         =   tmpGCost;
                    m_FCosts[tmpEdge->to()]         =   tmpGCost + tmpHCost;
                    prioQ.reOrder();
                }
            }
        }

        return vector<int>(0);
    }
};

#endif