#include "GameTeamState.h"
#include "TeamManager.h"

void GameTeamWaitState::onEnter(GameTeam* owner)
{
    // ֪ͨ���е����½���idle״̬
    auto tmpMsg =   Telegram::create(0, 0, TELEGRAM_ENUM_TEAM_IDLE, 0);
    owner->sendMsgToAll(*tmpMsg);
}

void GameTeamWaitState::update(GameTeam* owner, float dm)
{
    m_frameCount++;
    if (m_frameCount >= m_waitFrame)
    {
        // �л���ս��״̬
        owner->getFSM()->changeState(GameTeamFreeCombatState::create());
    }
}

void GameTeamFreeCombatState::onEnter(GameTeam* owner)
{
    // ��Ҫ�����µ����н�ɫ������Ϣ����ʾ�����ɫ�ǿ�ʼ����ս��
    auto tmpMsg =   Telegram::create(0, 0, TELEGRAM_ENUM_TEAM_FREE_COMBAT, 0);
    owner->sendMsgToAll(*tmpMsg);
}

void GameTeamFreeCombatState::update(GameTeam* owner, float dm)
{
    // �ж��Ƿ��е��˴��ڣ���ʵҲ���Ǳ������еĶ��飬�����Ҷ���һ�����͵Ķ��飬��˵��ʤ��
    // @_@ Ŀǰ��д���ֻ��һ�����飬����ֻ�е�ǰ������ף״̬��ʱ��
    if (TeamMgr->getTeamMap().size() == 1)
    {
        owner->getFSM()->changeState(GameTeamCelebrateState::create());
    }
}

void GameTeamFreeCombatState::onExit(GameTeam* owner)
{

}
bool GameTeamFreeCombatState::onMessage(GameTeam* owner, Telegram &msg)
{
    return false;
}

void GameTeamGlobalState::update(GameTeam* owner, float dm)
{
    
}

bool GameTeamGlobalState::onMessage(GameTeam* owner, Telegram &msg)
{
    
    return false;
}

void GameTeamCelebrateState::onEnter(GameTeam* owner)
{
    // ֪ͨȫ����ףһ��
    auto tmpMsg =   Telegram::create(0, 0, TELEGRAM_ENUM_TEAM_CELEBRATE, 0);
    owner->sendMsgToAll(*tmpMsg);
}

void GameTeamAdvanceToEndState::onEnter(GameTeam* owner)
{
    // �����д����ҷ���ɫ�ƶ������Ҷ˵ø�����
    owner->moveToEnd();
}