#include "TargetControlSystem.h"
#include "GameCharacter.h"
#include "EntityManager.h"
#include "UIViewManager.h"

TargetControlSystem::TargetControlSystem( GameCharacter* owner, float updatePeriod):ControlSystem(owner, updatePeriod)
{
    m_targetId          =   INVALID_GAME_ENTITY_ID;
    m_choiceTargetState =   CHOICE_TARGET_AUTO_PRECEDENCE;

    // һ��ʼ��ǿ��������ȹ���ĳ��Ŀ��
    forceTargetId(m_targetId);
}

TargetControlSystem::~TargetControlSystem()
{

}

GameCharacter* TargetControlSystem::getTargetCharacter()
{
    return dynamic_cast<GameCharacter*>(EntityMgr->getEntityFromID(m_targetId));
}

void TargetControlSystem::updateTarget()
{
    switch (m_choiceTargetState)
    {
    case TargetControlSystem::CHOICE_TARGET_AUTO_PRECEDENCE:
        {
            // �Զ�ѡ��Ŀ��
            // @_@��һ�����߼���ʱ����GameCharacterAutoState��
            m_targetId  =   INVALID_GAME_ENTITY_ID;
        	break;
        }

    case TargetControlSystem::CHOICE_TARGET_USER_PRECEDENCE:
        {
            // �����ѡ���Ŀ�겻�����ˣ����л����Զ�ѡ��
            if (getTargetCharacter() == nullptr)
            {
                m_choiceTargetState =   CHOICE_TARGET_AUTO_PRECEDENCE;
                updateTarget();
            }
        	break;
        }

    default:
        break;
    }
}

void TargetControlSystem::forceTargetId( int id )
{
    m_choiceTargetState =   CHOICE_TARGET_USER_PRECEDENCE;
    setTargetId(id);
}

void TargetControlSystem::setTargetId( int id )
{
    m_targetId      =   id;

    // @_@ ����д�ɣ������ǰ��ɫ�����ǣ���Ҫ�����л�һ�¹���Ŀ��
    RefreshUIMsg    tmpMsg(REFRESH_UI_EVENT_ATTACK_CHARACTER);
    UIViewMgr->refreshView(tmpMsg);

    // ͬʱ��������ǵĻ�����Ҫ�����ǹ���Ŀ������й⻷
    GameCharacter* tmpTarget    =   dynamic_cast<GameCharacter*>(EntityMgr->getEntityFromID(m_targetId));
    if (tmpTarget != nullptr && tmpTarget == EntityMgr->getmainEntity())
    {
        // @_@ ȥ�����˸�Ŀ�����µĹ⻷
        auto tmpIterator    =   EntityMgr->getEntityMap()->begin();
        for (; tmpIterator != EntityMgr->getEntityMap()->end(); tmpIterator++)
        {
            GameCharacter* tmpCharacter =   dynamic_cast<GameCharacter*>(tmpIterator->second);
            if (tmpTarget != tmpCharacter)
            {
                tmpTarget->getShape()->hideHalo();
            }
            else
            {
                tmpTarget->getShape()->showHalo(GameCharacterShape::HALO_RED);
            }
        }
    }
}

void TargetControlSystem::update( float dm )
{
    updateTarget();
}
