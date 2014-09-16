#include "TargetControlSystem.h"
#include "EntityManager.h"
#include "GameCharacter.h"

TargetControlSystem::TargetControlSystem( GameCharacter* owner )
{
    m_pOwner        =   owner;
    m_targetId      =   INVALID_GAME_ENTITY_ID;
}

TargetControlSystem::~TargetControlSystem()
{

}

void TargetControlSystem::update()
{
    // @_@ ������߼�������д
    if (getTarget() != nullptr)
    {
        return;
    }
    else
    {
        // @_@ ����Ҳ������д����ΪĿǰ��ֻ��2����
        if (m_pOwner->getId() == 0)
        {
            m_targetId  =   1;
        }
        else
        {
            m_targetId  =   0;
        }
    }
}

GameCharacter* TargetControlSystem::getTarget()
{
    return dynamic_cast<GameCharacter*>(EntityMgr->getEntityFromID(m_targetId));
}
