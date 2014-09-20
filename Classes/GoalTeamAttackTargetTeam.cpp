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
    activateIfInactive();
    inspectTeamMembers();
    return m_goalState;
}

void GoalTeamAttackTargetTeam::inspectTeamMembers()
{
    // @_@ ��дһ���򵥵Ĺ���
    /**
    GameCharacter* tmpOwnMem    =   *m_pOwner->getMembers().begin();
    GameCharacter* tmpTarget    =   *m_targetTeam->getMembers().begin();
    if (!tmpOwnMem->hasGoal())
    {
        // �������ɫ����һ����Ϣ������ָ����ȥ����Ŀ��
        auto tmpMsg = Telegram::create(0, tmpOwnMem->getId(), TELEGRAM_ENUM_TEAM_ATTACK_SPECIFIED_TARGET, 0, (void*)tmpTarget->getId());
        m_pOwner->sendMessageToOneMember(*tmpMsg, tmpOwnMem);
    }
    if (m_pOwner->getMembers().size() > 1)
    {
        auto tmpIterator            =   m_pOwner->getMembers().begin();
        tmpIterator++;
        GameCharacter* tmpSecMem    =   *tmpIterator;
        if (!tmpSecMem->hasGoal())
        {
            auto tmpMsg = Telegram::create(0, tmpSecMem->getId(), TELEGRAM_ENUM_TEAM_ATTACK_SPECIFIED_TARGET, 0, (void*)tmpTarget->getId());
            m_pOwner->sendMessageToOneMember(*tmpMsg, tmpSecMem);
        }
    }
    */
    /**
    * ���������չ���˳�����θ���Ա���ù���Ŀ�� 
    */
    auto tmpOwnMembers      =   m_pOwner->getMembers();
    auto tmpTargetMembers   =   m_targetTeam->getMembers();
    // ��ʼ�����ҷ���ɫ
    for (auto tmpIterator = tmpOwnMembers.begin(); tmpIterator != tmpOwnMembers.end(); tmpIterator++)
    {
        auto tmpCharacter = dynamic_cast<GameCharacter*>(*tmpIterator);
        if (tmpCharacter->getMovingEntity().getFormationPosId() == 0)
        {

        }
    }
}