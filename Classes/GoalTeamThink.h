#ifndef __GOAL_TEAM_THINK_H__
#define __GOAL_TEAM_THINK_H__

#include "GoalComposite.h"
#include "GoalTeamAdvance.h"
#include "GoalTeamAttackTargetTeam.h"
#include "TeamManager.h"

class GameTeam;

/**
* ���ڶ��鼶������Ŀ�꣬�ڴ˴���Ի��������жϣ�Ȼ�����õ�ǰ����ĺ���Ŀ�� 
*/
class GoalTeamThink : public GoalComposite<GameTeam>
{
public:
    GoalTeamThink(GameTeam* owner):GoalComposite<GameTeam>(owner){}

    // @_@ ��ʱʹ�õģ������ⲿ����Ŀ��
    void setGoal(Goal* aGoal)
    {
        removeAllSubgoals();
        addSubgoal(aGoal);
    }

    virtual void activate() override
    {
        //@_@ ��ʱ����д��һ��ʼ�͸�����һ������ǰ����Ŀ��
        // addSubgoal(new GoalTeamAdvance(m_pOwner));
        // @_@ ��ʱ����д������
        // addSubgoal(new GoalTeamAttackTargetTeam(m_pOwner, TeamMgr->getTeamFromId(1)));
    }

    virtual GoalStateEnum process() override
    {
        return GoalComposite<GameTeam>::process();
    }
};

#endif