#include "GoalTeamAttackTargetTeam.h"
#include "GameCharacter.h"
#include "MessageDispatcher.h"

GoalTeamAttackTargetTeam::GoalTeamAttackTargetTeam( GameTeam* owner, GameTeam* target ) :GoalComposite<GameTeam>(owner)
{
    m_targetTeam    =   target;
    
    // 0��λ
    m_targetRule.push_back(vector<int>());
    m_targetRule[0].push_back(0);
    m_targetRule[0].push_back(1);
    m_targetRule[0].push_back(2);
    m_targetRule[0].push_back(3);
    m_targetRule[0].push_back(4);
    m_targetRule[0].push_back(5);

    // 1��λ
    m_targetRule.push_back(vector<int>());
    m_targetRule[1].push_back(1);
    m_targetRule[1].push_back(0);
    m_targetRule[1].push_back(3);
    m_targetRule[1].push_back(2);
    m_targetRule[1].push_back(5);
    m_targetRule[1].push_back(4);

    // 2��λ
    m_targetRule.push_back(vector<int>());
    m_targetRule[2].push_back(2);
    m_targetRule[2].push_back(1);
    m_targetRule[2].push_back(0);
    m_targetRule[2].push_back(3);
    m_targetRule[2].push_back(4);
    m_targetRule[2].push_back(5);

    // 3��λ
    m_targetRule.push_back(vector<int>());
    m_targetRule[3].push_back(3);
    m_targetRule[3].push_back(1);
    m_targetRule[3].push_back(0);
    m_targetRule[3].push_back(2);
    m_targetRule[3].push_back(5);
    m_targetRule[3].push_back(4);

    // 4��λ
    m_targetRule.push_back(vector<int>());
    m_targetRule[4].push_back(2);
    m_targetRule[4].push_back(3);
    m_targetRule[4].push_back(0);
    m_targetRule[4].push_back(2);
    m_targetRule[4].push_back(5);
    m_targetRule[4].push_back(4);

    // 5��λ
    m_targetRule.push_back(vector<int>());
    m_targetRule[5].push_back(5);
    m_targetRule[5].push_back(1);
    m_targetRule[5].push_back(0);
    m_targetRule[5].push_back(2);
    m_targetRule[5].push_back(3);
    m_targetRule[5].push_back(4);
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
    /**
    * ���������չ���˳�����θ���Ա���ù���Ŀ�� 
    */
    auto tmpOwnMembers      =   m_pOwner->getMembers();
    auto tmpTargetMembers   =   m_targetTeam->getMembers();
    // ��ʼ�����ҷ���ɫ
    for (auto tmpIterator = tmpOwnMembers.begin(); tmpIterator != tmpOwnMembers.end(); tmpIterator++)
    {
        auto tmpOwnCharacter    =   dynamic_cast<GameCharacter*>(*tmpIterator);
        if (tmpOwnCharacter->hasGoal())
        {
            // ��ǰ��Ŀ��Ķ�Ա�Ͳ��ù�
            continue;
        }
        auto tmpRule            =   m_targetRule[tmpOwnCharacter->getMovingEntity().getFormationPosId()];
        GameCharacter* tmpTarget=   nullptr;
        for (auto tmpPosIterator = tmpRule.begin(); tmpPosIterator != tmpRule.end(); tmpPosIterator++)
        {
            // �ӹ�����ǰ��Ѱ�ҵ�һ����λ���˵�
            tmpTarget   =   m_targetTeam->getMemberIdFromFormation(*tmpPosIterator);
            if (tmpTarget != nullptr)
            {
                break;
            }
        }

        if (tmpTarget != nullptr)
        {
            // ������Ϣ��֪����
            auto tmpMsg = Telegram::create(0, tmpOwnCharacter->getId(),
                TELEGRAM_ENUM_TEAM_ATTACK_SPECIFIED_TARGET, 0, (void*)tmpTarget->getId());
            m_pOwner->sendMessageToOneMember(*tmpMsg, tmpOwnCharacter);
        }
    }
}