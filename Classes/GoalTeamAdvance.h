#ifndef __GOAL_TEAM_ADVANCE_H__
#define __GOAL_TEAM_ADVANCE_H__

#include "Goal.h"
#include "GameTeam.h"

/**
* ���鼯����ǰ�ƶ���Ŀ��
* @_@ ����ֻ�ܶ����ƽ���OK�ˣ�����Ҫ��ʲô��ǰ�Ļ���
*/
class GoalTeamAdvance : public Goal<GameTeam>
{
public:
    GoalTeamAdvance( GameTeam* owner ):Goal<GameTeam>(owner){}

protected:
    virtual void activate() override
    {
        m_pOwner->collectiveForwardStart();
    }

    virtual GoalStateEnum process() override
    {
        activateIfInactive();
        return m_goalState;
    }

    virtual void terminate() override
    {
        m_pOwner->collectiveForwardEnd();
    }
};

#endif