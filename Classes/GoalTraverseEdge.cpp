#include "GoalTraverseEdge.h"
#include "GameCharacter.h"
#include "TimeTool.h"
#include "MathTool.h"

GoalTraverseEdge::GoalTraverseEdge( GameCharacter* owner, const NavGraphEdge& edge)
    :Goal<GameCharacter>(owner), m_marginOfError(0.5), m_fuzzyReachGap(10)
{
    m_edge  =   edge;
}

GoalTraverseEdge::~GoalTraverseEdge()
{

}

void GoalTraverseEdge::activate()
{
    /**
    *  ���ڸ�Ŀ�ֻ꣬��Ҫ�ý�ɫ�Ӹñߵ�from��to������ֻ��ҪҪ���ɫ��Ŀ��
    *  �ƶ�
    */ 
    auto tmpRate = m_pOwner->getAttribute().getRate();
    m_pOwner->moveToGridIndex(m_edge.to(), tmpRate);
    
    auto tmpGridMap =   m_pOwner->getMapGrid();
    m_activeTime    =   TimeTool::getSecondTime();
    m_timeExpected  =   m_activeTime + m_marginOfError
        + tmpGridMap->getDistance(m_edge.from(), m_edge.to()) / tmpRate;
}

GoalTraverseEdge::GoalStateEnum GoalTraverseEdge::process()
{
    activateIfInactive();

    // �Ƿ񵽴�Ŀ��
    if (isReach())
    {
        terminate();
    }
    else if (isStuck())
    {
        // �Ƿ�ý�ɫ������ס��
        m_goalState = failed;
    }

    return m_goalState;
}

bool GoalTraverseEdge::isStuck()
{
    return m_timeExpected < TimeTool::getSecondTime();
}

bool GoalTraverseEdge::isReach()
{
    auto tmpGridMap =   m_pOwner->getMapGrid();
    auto tmpPos     =   m_pOwner->getShape()->getPosition();
    auto tmpGrid    =   tmpGridMap->getNodeByIndex(m_edge.to());
    //return (tmpPos.x == tmpGrid.getX()) && (tmpPos.y == tmpGrid.getY());
    // @_@ �����ΪֻҪ��Ŀ���м������������ھ��㵽�ˣ����������ö�������������
    return abs(tmpPos.x - tmpGrid.getX()) <= m_fuzzyReachGap && abs(tmpPos.y - tmpGrid.getY()) <= m_fuzzyReachGap;
}
