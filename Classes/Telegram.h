#ifndef __TELEGRAM_H__
#define __TELEGRAM_H__

#include "cocos2d.h"
#include "GameCharacterAttribute.h"

using namespace cocos2d;

/**
	 ��Ϣ����
*/
enum TelegramEnum
{
    /**
    	 ��ҵ�ָʾ��ָ�����������������Լ�����ָ��
    */
    TELEGRAM_ENUM_USER_MOVE_RIGHT,
    TELEGRAM_ENUM_USER_MOVE_LEFT,
    TELEGRAM_ENUM_USER_IDLE,
    TELEGRAM_ENUM_USER_CHANGE_TARGET,

    /**
    	 ��Ϸ��ɫ֮�����Ϣ
    */
    TELEGRAM_ENUM_NORMAL_ATTACK,                     // ��ͨ����

    /**
    	 ����������еĽ�ɫ֮�����Ϣ
    */
    TELEGRAM_ENUM_TEAM_IDLE,                        // ����֪ͨ��ɫ�ȴ�
    TELEGRAM_ENUM_TEAM_FREE_COMBAT,                 // ����֪ͨ��ɫ����ս��
    TELEGRAM_ENUM_TEAM_CELEBRATE                    // ����֪ͨ��ɫ��ףһ��ʤ��
};

/**
	 ��Ϣ�ṹ�������ϵͳ���û���ʵ�塢ʵ����ʵ��Ľ�������ͨ����Ϣ��������ֱ�ӵĺ������ã�����Ϣ��
     ��һ��ͨ�õ���Ϣ����Ȼ�����Զ�����Ϣ�ṹ�����Ǳ��������̳�
*/
class Telegram : public Ref
{
protected:
    Telegram() 
    {
        senderId        =   0;
        receiverId      =   0;
        dispatchTime    =   0;
    };
    virtual ~Telegram() {};

public:
    int             senderId;               // ������id
    int             receiverId;             // ������id
    TelegramEnum    type;                   // ��Ϣ����
    float           dispatchTime;           // ����ʱ��

    static Telegram *create(int senderId, int receiverId, TelegramEnum type, float dispatchTime)
    {
        Telegram *pRet  =   new Telegram();
        if (pRet != nullptr)
        {
            pRet->senderId      =   senderId;
            pRet->receiverId    =   receiverId;
            pRet->type          =   type;
            pRet->dispatchTime  =   dispatchTime;

            pRet->autorelease();
        }

        return pRet;
    }
};

/**
	 ��ͨ����
*/
class TelegramNormalAttack : public Telegram
{
public:
    TelegramNormalAttack()
    {
        type    =   TELEGRAM_ENUM_NORMAL_ATTACK;
    }

public:
    GameCharacterAttribute  senderAtt;          // �����ߵ����ԣ���������Ŀ���˺���

    static TelegramNormalAttack* create(int senderId, int receiverId, GameCharacterAttribute& senderAtt)
    {
        TelegramNormalAttack* pRet = new TelegramNormalAttack();
        if (pRet)
        {
            pRet->senderId      =   senderId;
            pRet->receiverId    =   receiverId;
            pRet->senderAtt     =   senderAtt;
            pRet->autorelease();
        }

        return pRet;
    }
};

#endif