#ifndef __PATH_PLANNER_H__
#define __PATH_PLANNER_H__

#include <vector>
#include <list>
#include "NavGraphEdge.h"

using namespace std;

class GameCharacter;
class MapGrid;

/**
* ·���滮�࣬��ɫͨ������Ķ�����������ͼ������Ҫ��ﵽĿ����Ҫ�ߵ�·�� 
*/
class PathPlanner
{
public:
    typedef vector<int> NodeIndexPath;          // �Խڵ���Ź��ɵ�·��
    typedef list<NavGraphEdge> EdgePath;        // �Ա߹��ɵ�·��

    PathPlanner(GameCharacter* owner);
    ~PathPlanner();

    /**
    * ����ĳ��ָ��λ�õ�·��
    */
    bool requestPathToGridIndex(int gridIndex);

    /**
    * �����Խڵ���Ź��ɵ�·��
    */
    const NodeIndexPath& getNodeIndexPath();

    /**
    *  �����Ա߹��ɵ�·��
    */
    const EdgePath& getEdgeListPath();

private:
    GameCharacter*  m_pOwner;                   // ��·���滮��ӵ����
    MapGrid*        m_graph;                    // ���ڵĵ�ͼ
    
    // ���һ������·���Ľ����������Ϊ���Ժ��·���������ȡ·���滮�������
    NodeIndexPath   m_currentIndexPath;
    EdgePath        m_currentEdgePath;
};

#endif