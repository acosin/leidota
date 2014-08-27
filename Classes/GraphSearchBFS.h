#ifndef __GRAPH_SEARCH_BFS_H__
#define __GRAPH_SEARCH_BFS_H__

#include "SparseGraph.h"
#include <queue>
#include <vector>

using namespace std;

#define UNVISITED   0
#define VISITED     1

#define NOPARENT    -1

/**
	 ���ù�����������ķ�ʽ
*/
class GraphSearchBFS
{
protected:
    static int m_count;

public:
    static vector<int> search(SparseGraph& grap, int sourceIndex, int targetIndex)
    {
        assert(sourceIndex < grap.getNodeNumber() && targetIndex < grap.getNodeNumber()
            && "invalid sourceIndex or targetIndex");

        // һ��·���������ֻ����3->9->11��route[9] = 3, route[11] = 9
        vector<int> route(grap.getNodeNumber(), NOPARENT);
        queue<NavGraphEdge*> edgeQueue;

        NavGraphEdge    dummy(sourceIndex, sourceIndex);
        edgeQueue.push(&dummy);

        m_count =   0;

        while (!edgeQueue.empty())
        {
            m_count++;

            NavGraphEdge* tmpEdge   =   edgeQueue.front();
            edgeQueue.pop();

            route[tmpEdge->to()]  =   tmpEdge->from();

            if (tmpEdge->to() == targetIndex)
            {
                // ������
                vector<int> retRoute;
                retRoute.push_back(targetIndex);
                int tmpParent = route[targetIndex];
                while (tmpParent != sourceIndex)
                {
                    retRoute.push_back(tmpParent);
                    tmpParent   =   route[tmpParent];
                }
                retRoute.push_back(sourceIndex);

                reverse(retRoute.begin(), retRoute.end());
                return retRoute;
            }

            // �����ýڵ�����ı�
            SparseGraph::EdgeIterator   tmpIterator(&grap, tmpEdge->to());
            tmpEdge = tmpIterator.begin();
            for (; !tmpIterator.end(); tmpEdge = tmpIterator.next())
            {
                if (route[tmpEdge->to()] == NOPARENT)
                {
                    edgeQueue.push(tmpEdge);
                }
            }
        }

        route.clear();
        return route;
    }
};

int GraphSearchBFS::m_count =   0;

#endif