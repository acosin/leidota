#ifndef __GOAL_TEAM_RECOVER_FORMATION_H__
#define __GOAL_TEAM_RECOVER_FORMATION_H__

#include "Goal.h"
#include "GameTeam.h"
#include "Telegram.h"
#include "GameCharacter.h"

/**
* ����ָ���ǰ���͵�Ŀ�� 
*/
class GoalTeamRecoverFormation : public Goal<GameTeam>
{
public:
    GoalTeamRecoverFormation(GameTeam* owner):Goal<GameTeam>(owner)
    {

    }

protected:
    virtual void activate() override
    {
        // ֪ͨ��ұ�������
        auto tmpMsg = Telegram::create(0, 0, TELEGRAM_ENUM_TEAM_COLLECTIVE_FORWARD);
        m_pOwner->sendMessageToAllMember(*tmpMsg);
    }

    virtual GoalStateEnum process() override
    {
        activateIfInactive();

        // �������˵��ٶȱ�Ϊ0��ʱ����������
        if (m_pOwner->isEveryMemberInPos())
        {
            return completed;
        }

        return active;
    }

    virtual void terminate() override
    {
        auto tmpMsg = Telegram::create(0, 0, TELEGRAM_ENUM_TEAM_CANCEL_COLLECTIVE_FORWARD);
        m_pOwner->sendMessageToAllMember(*tmpMsg);
    }
};

#endif