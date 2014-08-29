#include "GameTeam.h"
#include "MessageDispatcher.h"
#include "GameTeamState.h"
#include "EntityManager.h"
#include "TeamManager.h"
#include "GameCharacter.h"

int GameTeam::m_nextValidId =   0;

GameTeam::GameTeam()
{
    m_teamId        =   m_nextValidId++;
    m_leaderId      =   INVALID_GAME_ENTITY_ID;
    m_stateMachine  =   TeamStateMachine::create(this);
    m_stateMachine->retain();
    m_stateMachine->changeState(GameTeamWaitState::create());
    m_stateMachine->setGlobalState(GameTeamGlobalState::create());
    m_mercenaryIdList.clear();
}

GameTeam::~GameTeam()
{
    CC_SAFE_RELEASE(m_stateMachine);
}

void GameTeam::setLeaderId(int id)
{
    m_leaderId  =   id;
}

void GameTeam::addMercenaryIds(int id)
{
    m_mercenaryIdList.push_back(id);
    m_type  =   EntityMgr->getEntityFromID(id)->getType();
}

void GameTeam::update(float dm)
{
    m_stateMachine->update(dm);

    // �ж�����ö���������˶��Ѿ���Ϣ���ͽ��Լ�ɾ��
    if (EntityMgr->getEntityFromID(m_leaderId) != nullptr)
    {
        return;
    }

    for (auto tmpIterator = m_mercenaryIdList.begin(); tmpIterator != m_mercenaryIdList.end(); tmpIterator++)
    {
        if (EntityMgr->getEntityFromID(*tmpIterator) != nullptr)
        {
            return;
        }
    }

    TeamMgr->removeTeam(this);
}

void GameTeam::sendMsgToAll(Telegram& msg)
{
    msg.receiverId  =   m_leaderId;
    Dispatch->dispatchMessage(msg);

    auto tmpIterator    =   m_mercenaryIdList.begin();
    for (; tmpIterator != m_mercenaryIdList.end(); )
    {
        msg.receiverId  =   *tmpIterator;
        tmpIterator++;
        Dispatch->dispatchMessage(msg);
    }
}

bool GameTeam::init()
{
    return true;
}

GameTeam::TeamStateMachine* GameTeam::getFSM()
{
    return m_stateMachine;
}

void GameTeam::moveToEnd()
{
    // �ȼ���Ŀǰһ���������3����
    auto tmpCharacter   =   (GameCharacter*)EntityMgr->getEntityFromID(m_leaderId);
    if (tmpCharacter != nullptr)
    {
        tmpCharacter->walkOff();
    }

    auto tmpIterator    =   m_mercenaryIdList.begin();
    tmpCharacter        =   (GameCharacter*)EntityMgr->getEntityFromID(*tmpIterator);
    if (tmpCharacter != nullptr)
    {
        tmpCharacter->walkOff();
    }

    tmpIterator++;
    tmpCharacter        =   (GameCharacter*)EntityMgr->getEntityFromID(*tmpIterator);
    if (tmpCharacter != nullptr)
    {
        tmpCharacter->walkOff();
    }
}

bool GameTeam::isMoving()
{
    // �ȼ���Ŀǰһ���������3����
    auto tmpCharacter   =   (GameCharacter*)EntityMgr->getEntityFromID(m_leaderId);
    if (tmpCharacter != nullptr && tmpCharacter->isMoving())
    {
        return true;
    }

    auto tmpIterator    =   m_mercenaryIdList.begin();
    tmpCharacter        =   (GameCharacter*)EntityMgr->getEntityFromID(*tmpIterator);
    if (tmpCharacter != nullptr && tmpCharacter->isMoving())
    {
        return true;
    }

    tmpIterator++;
    tmpCharacter        =   (GameCharacter*)EntityMgr->getEntityFromID(*tmpIterator);
    if (tmpCharacter != nullptr && tmpCharacter->isMoving())
    {
        return true;
    }

    return false;
}
