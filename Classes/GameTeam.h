#ifndef __GAME_TEAM_H__
#define __GAME_TEAM_H__

#include "cocos2d.h"
#include "StateMachine.h"
#include "Telegram.h"
#include "BaseGameEntity.h"

using namespace cocos2d;
using namespace std;

/**
	 ��Ϸ���ҷ�����ĸ��Ϊ��ʵ�ֶ��鼶�����ϡ�AI�ĸ���
     @_@    ����Ͳ����ǵз������������
*/
class GameTeam : public Ref
{
public:
    typedef StateMachine<GameTeam>  TeamStateMachine;

    GameTeam();
    ~GameTeam();

    /**
    	 ��������ȫ������id
    */
    void setLeaderId(int id);

    /**
    	 ���Ӷ��
    */
    void addMercenaryIds(int id);

    /**
    	 ÿһ֡�лص�
    */
    void update(float dm);

    bool init();

    /**
    	 ��ȫ���Ա����ĳ����Ϣ
    */
    void sendMsgToAll(Telegram& msg);

    /**
    	 ����״̬����������״̬���޸�
    */
    TeamStateMachine* getFSM();

    /**
    	 ����id������ȫ��Ψһ��ʾһ������
    */
    CC_SYNTHESIZE(int, m_teamId, TeamId);
    CC_SYNTHESIZE_READONLY(GameEntityTypeEnum, m_type, TeamType);

    CREATE_FUNC(GameTeam);

private:

    static int m_nextValidId;                                   // ��һ����Ч�ض���id
    /**
    	 ����֮����û��ֱ��ʹ��GameCharacter����Ϊ���е���ö��Ǵ�EntityManager�л�ȡ
    */
    int                         m_leaderId;                     // ����id
    list<int>                   m_mercenaryIdList;              // Ӷ��id�б�
    TeamStateMachine*           m_stateMachine;                 // �ö����״̬��
};

#endif