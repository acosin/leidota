#include "GoalAttackTarget.h"
#include "GameCharacter.h"
#include "PathPlanner.h"
#include "EntityManager.h"
#include "GoalMoveToGrid.h"

GoalAttackTarget::GoalAttackTarget( GameCharacter* owner, int targetId )
    :GoalComposite<GameCharacter>(owner)
{
    m_targetId      =   targetId;
}

GoalAttackTarget::~GoalAttackTarget()
{

}

void GoalAttackTarget::activate()
{
    
}

GoalStateEnum GoalAttackTarget::process()
{
    activateIfInactive();

    do 
    {
        // �鿴�����Ƿ񻹴���
        if (EntityMgr->getEntityFromID(m_targetId) == nullptr)
        {
            m_goalState =   completed;
            break;
        }

        // ����ڹ���������
        if (isInAttackRange())
        {
            // ����ֱ�ӹ���
            m_pOwner->getWeaponControlSystem()->takeWeaponAndAttack(getTarget());
        }
        else
        {
            // ����һ��ǰ����ָ�����ӵ���Ŀ��
            addSubgoal(new GoalMoveToGrid(m_pOwner, getAdvanceGridIndex()));
        }
    } while (0);
    
    return m_goalState;
}

bool GoalAttackTarget::isInAttackRange()
{
    // @_@ ������д��
    return true;
}

int GoalAttackTarget::getAdvanceGridIndex()
{
    // @_@ ������д��
    return 1;
}

GameCharacter* GoalAttackTarget::getTarget()
{
    return dynamic_cast<GameCharacter*>(EntityMgr->getEntityFromID(m_targetId));
}
