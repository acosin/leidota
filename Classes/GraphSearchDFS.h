#ifndef __GRAPH_SEARCH_DFS_H__
#define __GRAPH_SEARCH_DFS_H__

#include "SparseGraph.h"
#include <vector>
#include <stack>

using namespace std;

#define UNVISITED   0
#define VISITED     1

#define NOCHILD    -1

/**
	 ʹ���������������ʽ������һ��ϡ��ͼ
*/
class GraphSearchDFS
{
protected:
    static int m_count;

public:
    /**
    	 ���ƶ�ͼ���������±�ΪsourceIndex�ڵ㵽targetIndex�ڵ��һ��·��
         @return    ����ҵ��ͷ��ش�sourceIndex��ʼ��·���Ľڵ��±꣬���򷵻�һ���յ�
    */
    static vector<int> search(SparseGraph& grap, int sourceIndex, int targetIndex)
    {
        assert(sourceIndex < grap.getNodeNumber() && targetIndex < grap.getNodeNumber()
            && "invalid sourceIndex or targetIndex");

        m_count =   0;

        // ��������·����
        vector<int> route;

        // ��������ÿ���ڵ㱻���ʵ����
        vector<int> nodeVisited(grap.getNodeNumber());

        // ������֧�ڵ��index
        stack<int>  nodeStack;
        while (!nodeStack.empty())
        {
            nodeStack.pop();
        }

        nodeStack.push(sourceIndex);
        nodeVisited[sourceIndex]    =   VISITED;

        while (!nodeStack.empty())
        {
            m_count++;

            int tmpNewIndex =   nodeStack.top();
            nodeStack.pop();

            // ���Ϊ�Ѿ�����
            nodeVisited[tmpNewIndex]    =   VISITED;

            if (route.empty() || route[route.size() - 1] != tmpNewIndex)
            {
                route.push_back(tmpNewIndex);
            }
            
            if (tmpNewIndex == targetIndex)
            {
                return route;
            }

            // ����Χ��δ���ʵĽڵ�ѹջ
            SparseGraph::NodeIterator tmpIterator(&grap, tmpNewIndex);
            NavGraphNode* tmpNode = tmpIterator.begin();
            // ��ʾ�Ƿ�ѹ����ջ
            bool tmpFlag = false;
            for (; !tmpIterator.end(); tmpNode = tmpIterator.next())
            {
                if (nodeVisited[tmpNode->index()] == UNVISITED)
                {
                    if (!tmpFlag)
                    {
                        nodeStack.push(tmpNewIndex);
                        tmpFlag =   true;
                    }
                    nodeStack.push(tmpNode->index());
                }
            }

            if (!tmpFlag)
            {
                route.pop_back();
            }
        }

        route.clear();
        return route;
    }

    /**
    	 ��������һ�ַ�����ֻ�������ջ�ﱣ����Ǳ�
    */
    static vector<int> search2(SparseGraph& grap, int sourceIndex, int targetIndex)
    {
        assert(sourceIndex < grap.getNodeNumber() && targetIndex < grap.getNodeNumber()
            && "invalid sourceIndex or targetIndex");

        m_count =   0;

        // ���ﱣ�����·��������������һ�ַ�ʽ
        vector<int> route(grap.getNodeNumber(), NOCHILD);

        // ������ʱ����ߵ�ջ
        stack<NavGraphEdge*> edgeStack;

        // ����һ���Լ��ı�
        NavGraphEdge dummy(sourceIndex, sourceIndex);
        edgeStack.push(&dummy);

        while (!edgeStack.empty())
        {
            m_count++;

            NavGraphEdge* tmpEdge   =   edgeStack.top();
            edgeStack.pop();

            if (tmpEdge != &dummy)
            {
                route[tmpEdge->from()]    =   tmpEdge->to();
            }

            if (tmpEdge->to() == targetIndex)
            {
                // ��ʾ�ҵ���
                vector<int> retRoute;
                int tmpNext   =   route[sourceIndex];
                retRoute.push_back(sourceIndex);
                while (tmpNext != targetIndex)
                {
                    retRoute.push_back(tmpNext);
                    tmpNext =   route[tmpNext];
                }
                retRoute.push_back(targetIndex);

                return retRoute;
            }

            // �����Ӹýڵ��������Χ�ı�
            SparseGraph::EdgeIterator tmpIterator(&grap, tmpEdge->to());
            tmpEdge =   tmpIterator.begin();
            for (; !tmpIterator.end(); tmpEdge = tmpIterator.next())
            {
                if (route[tmpEdge->to()] == NOCHILD)
                {
                    edgeStack.push(tmpEdge);
                }
            }
        }

        route.clear();
        return route;
    }
};

int GraphSearchDFS::m_count =   0;

#endif