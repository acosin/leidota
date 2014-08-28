#ifndef __GAME_CHARACTER_STATE_H__
#define __GAME_CHARACTER_STATE_H__

#include "State.h"
#include "GameCharacter.h"

/**
	 ����idle״̬�����״̬�����ڸտ�ʼ��ʱ���Լ����ֹͣ��������֮֡��
*/
class GameCharacterIdleState : public State<GameCharacter>
{
public:
    virtual void onEnter(GameCharacter* owner) override;
    virtual void update(GameCharacter* owner, float dm) override;
    virtual void onExit(GameCharacter* owner) override;
    virtual bool onMessage(GameCharacter* owner, Telegram &msg) override;

    CREATE_FUNC(GameCharacterIdleState);
};

/**
	 ��ɫ���ڴ�һ�������ƶ�����һ�����ӵĹ�����
*/
class GameCharacterMovingState : public State<GameCharacter>
{
public:
    /**
    	 �ƶ�����
    */
    enum MovingDirection
    {
        MOVING_DIRECTION_RIGHT,
        MOVING_DIRECTION_LEFT,
        MOVING_DIRECTION_TOP,
        MOVING_DIRECTION_BOTTOM
    };

    MovingDirection movingDirection;                // �ƶ�����

    virtual void onEnter(GameCharacter* owner) override;
    virtual void update(GameCharacter* owner, float dm) override;
    virtual void onExit(GameCharacter* owner) override;
    virtual bool onMessage(GameCharacter* owner, Telegram &msg) override;

    CREATE_FUNC(GameCharacterMovingState);
};

/**
	 �Զ������ս��Ѱ�����Ŀ�꣬Ȼ���ƶ���ȥ
*/
class GameCharacterAutoState : public State<GameCharacter>
{
public:
    virtual void onEnter(GameCharacter* owner) override;
    virtual void update(GameCharacter* owner, float dm) override;
    virtual void onExit(GameCharacter* owner) override;
    virtual bool onMessage(GameCharacter* owner, Telegram &msg) override;

    CREATE_FUNC(GameCharacterAutoState);

protected:
    /**
    	 ����һ���ڹ�����Χ�ڵĶ��֣����û�У��ͷ���nullptr
    */
    GameCharacter* getCharacterInAttackDistance(GameCharacter* owner, vector<GameCharacter*>& targets);

    /**
    	 �ж�target�Ƿ���owner�Ĺ�����Χ��
    */
    bool isInAttackDistance(GameCharacter* owner, GameCharacter* target);
};

/**
	 ��ͨ����
*/
class GameCharacterNormalAttack : public State<GameCharacter>
{
protected:
    GameCharacterNormalAttack():realAttackFrame(9)
    {
        _executed   =   false;
    }
    bool _executed;                     // �Ƿ��Ѿ�ִ��

public:
    int targetId;                       // ����Ŀ��id
    const int realAttackFrame;          // ���ǹ��������ڵڼ�֡

    virtual void onEnter(GameCharacter* owner) override;
    virtual void update(GameCharacter* owner, float dm) override;
    virtual void onExit(GameCharacter* owner) override;
    virtual bool onMessage(GameCharacter* owner, Telegram &msg) override;

    CREATE_FUNC(GameCharacterNormalAttack);
};

/**
	 ȫ��״̬
*/
class GameCharacterGlobalState : public State<GameCharacter>
{
public:
    virtual void onEnter(GameCharacter* owner) override;
    virtual void update(GameCharacter* owner, float dm) override;
    virtual void onExit(GameCharacter* owner) override;
    virtual bool onMessage(GameCharacter* owner, Telegram &msg) override;

    CREATE_FUNC(GameCharacterGlobalState);
};

/**
	 ׷��ĳ��ָ����ɫ
*/
class GameCharacterPursueState : public State<GameCharacter>
{
public:
    int targetId;                   // ׷��Ŀ��

    virtual void onEnter(GameCharacter* owner) override;
    virtual void update(GameCharacter* owner, float dm) override;
    virtual void onExit(GameCharacter* owner) override;
    virtual bool onMessage(GameCharacter* owner, Telegram &msg) override;

    CREATE_FUNC(GameCharacterPursueState);
};

/**
	 ������ףʤ��״̬
*/
class GameCharacterWinState : public State<GameCharacter>
{
public:
    virtual void onEnter(GameCharacter* owner) override;
    virtual void update(GameCharacter* owner, float dm) override;
    virtual void onExit(GameCharacter* owner) override;
    virtual bool onMessage(GameCharacter* owner, Telegram &msg) override;

    CREATE_FUNC(GameCharacterWinState);
};

/**
	 ��������״̬
*/
class GameCharacterDieState : public State<GameCharacter>
{
public:
    virtual void onEnter(GameCharacter* owner) override;
    virtual void update(GameCharacter* owner, float dm) override;
    virtual void onExit(GameCharacter* owner) override;
    virtual bool onMessage(GameCharacter* owner, Telegram &msg) override;

    CREATE_FUNC(GameCharacterDieState);
};

#endif