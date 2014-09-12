#ifndef __GOAL_TRAVERSE_EDGE_H__
#define __GOAL_TRAVERSE_EDGE_H__

#include "Goal.h"
#include "NavGraphEdge.h"

class GameCharacter;

/**
*  ��������ĳһ�����ƶ���ԭ��Ŀ��
*/
class GoalTraverseEdge : public Goal<GameCharacter>
{
public:
    GoalTraverseEdge(GameCharacter* owner, const NavGraphEdge& edge);
    ~GoalTraverseEdge();

protected:
    virtual void activate() override;

    virtual GoalStateEnum process() override;

private:
    /**
    * �жϸý�ɫ�Ƿ��Ѿ�����ñߵ�Ŀ�� 
    */
    bool isReach();

    /**
    * �ж��Ƿ�ס�� 
    */
    bool isStuck();

    NavGraphEdge    m_edge;                 // ��Ŀ��Ҫʵ�ֵ���ĳ�����ƶ�
    
    /**
    * ��Ϊ���ܻ����֮ǰ�ȹ滮��һ��·�ߣ����������Ϊ�����޷������ˣ�����
    * ��ͨ���޶���ɸ�Ŀ���ʱ�����޶�������ڹ涨��ʱ����û�е���Ŀ�꣬��
    * �ж�Ϊ��Ŀ��ִ��ʧ��
    */
    float           m_activeTime;           // ����activate�ĵ�ǰʱ��
    float           m_timeExpected;         // �����ĵ���ʱ��

    const float     m_marginOfError;        // ��һЩ�����ʱ��
};

#endif