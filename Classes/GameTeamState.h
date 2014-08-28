#ifndef __TEAM_STATE_H__
#define __TEAM_STATE_H__

#include "State.h"
#include "GameTeam.h"

/**
	 �˴���Ҫ�����˶��鼶���AI״̬���������磺���ɽ��������𡢸ùؿ���������ƽ���Ӯ��ʤ��
*/

/**
	 ���鴦�ڵȴ���֪ͨ���еĽ�ɫ����idle״̬���ȴ�����֡��Ȼ��ͻ��������ս��
*/
class GameTeamWaitState : public State<GameTeam>
{
protected:
    GameTeamWaitState():m_waitFrame(30)
    {
        m_frameCount    =   0;
    }

    const int m_waitFrame;
    int       m_frameCount;  
public:
    virtual void onEnter(GameTeam* owner) override;
    virtual void update(GameTeam* owner, float dm) override;
    virtual void onExit(GameTeam* owner) override {m_frameCount = 0;}
    virtual bool onMessage(GameTeam* owner, Telegram &msg) override {return false;}

    CREATE_FUNC(GameTeamWaitState);
};

/**
	 ���鴦������ս��״̬����Ա֮��û���κ����
*/
class GameTeamFreeCombatState : public State<GameTeam>
{
public:
    virtual void onEnter(GameTeam* owner) override;
    virtual void update(GameTeam* owner, float dm) override;
    virtual void onExit(GameTeam* owner) override;
    virtual bool onMessage(GameTeam* owner, Telegram &msg) override;

    CREATE_FUNC(GameTeamFreeCombatState);
};

/**
	 ����ȫ�ֵ�״̬����Ҫ����һЩ���鼶����ж�
*/
class GameTeamGlobalState : public State<GameTeam>
{
public:
    virtual void onEnter(GameTeam* owner) override {};
    virtual void update(GameTeam* owner, float dm) override;
    virtual void onExit(GameTeam* owner) override {};
    virtual bool onMessage(GameTeam* owner, Telegram &msg) override;

    CREATE_FUNC(GameTeamGlobalState);
};

/**
	 ������������ף״̬
*/
class GameTeamCelebrateState : public State<GameTeam>
{
public:
    virtual void onEnter(GameTeam* owner) override;
    virtual void update(GameTeam* owner, float dm) override {};
    virtual void onExit(GameTeam* owner) override {};
    virtual bool onMessage(GameTeam* owner, Telegram &msg) override {return false;};

    CREATE_FUNC(GameTeamCelebrateState);
};

#endif