#include "GoalTeamAttackTargetTeam.h"
#include "GameCharacter.h"
#include "MessageDispatcher.h"

GoalTeamAttackTargetTeam::GoalTeamAttackTargetTeam( GameTeam* owner, GameTeam* target ) :GoalComposite<GameTeam>(owner)
{
    m_targetTeam    =   target;
}

void GoalTeamAttackTargetTeam::activate()
{

}

GoalStateEnum GoalTeamAttackTargetTeam::process()
{
    // ��������Ӧ�����ݹ۴�֣���ʱ�����ȷ�������ֱ���Է���������Ÿ�Ϊcompleted
    m_goalState = GoalComposite<GameTeam>::process();
    inspectTeamMembers();
    return m_goalState;
}

void GoalTeamAttackTargetTeam::inspectTeamMembers()
{
    // @_@ ��дһ���򵥵Ĺ���
    GameCharacter* tmpOwnMem    =   *m_pOwner->getMembers().begin();
    if (!tmpOwnMem->hasGoal())
    {
        GameCharacter* tmpTarget    =   *m_targetTeam->getMembers().begin();

        // �������ɫ����һ����Ϣ������ָ����ȥ����Ŀ��
        auto tmpMsg = Telegram::create(0, tmpOwnMem->getId(), TELEGRAM_ENUM_TEAM_ATTACK_SPECIFIED_TARGET, 0, (void*)tmpTarget->getId());
        m_pOwner->sendMessageToOneMember(*tmpMsg, tmpOwnMem);
    }
}