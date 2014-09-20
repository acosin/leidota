#ifndef __GAME_TEAM_H__
#define __GAME_TEAM_H__

#include "cocos2d.h"
#include "Telegram.h"
#include "BaseGameEntity.h"
#include "Formation.h"

using namespace cocos2d;
using namespace std;

class GameCharacter;
class GoalTeamThink;

/**
	 ��Ϸ���ҷ�����ĸ��Ϊ��ʵ�ֶ��鼶�����ϡ�AI�ĸ���
     @_@    ����Ͳ����ǵз������������
*/
class GameTeam : public Ref
{
public:
    ~GameTeam();

    // ���ö�����ӳ�Ա��ͬʱָ���ý�ɫ�������е�λ�ñ��
    void addMember(GameCharacter* player, int posId = 0);

    // ÿһ֡�лص����������������г�Ա��update
    void update(float dm);

    // ���ض�������
    Formation& getTeamFormation() { return m_formation; }

    // ��ʼ����ǰ��
    void collectiveForwardStart();

    // ��������ǰ�����ڿ�ʼ�����з�����֮ǰҪ����������������͵�Լ����
    void collectiveForwardEnd();

    // �����еĳ�Ա������Ϣ�������Ժ���鼶�����Ϊ��Ա���Դ�����ÿһ����Ա����Ŀ��
    void sendMessageToAllMember(Telegram& msg);

    // ��ĳ��ָ���Ľ�ɫ������Ϣ
    void sendMessageToOneMember(Telegram& msg, GameCharacter* aCharacter);

    // �ж��Ƿ������˶�������ָ��λ��
    bool isEveryMemberInPos();

    // ���������ҵ�ָ��λ��id�ĳ�Ա�����û���ˣ��ͷ���null
    GameCharacter* getMemberIdFromFormation(int posId);

    const list<GameCharacter*>& getMembers() { return m_members; }

    // ���ض������
    GoalTeamThink* getTeamBrain() { return m_teamBrain; }

    // ����id������ȫ��Ψһ��ʾһ������
    CC_SYNTHESIZE(int, m_teamId, TeamId);

    // ����һ�����飬�ڵ������������ö���ͱ����뵽TeamMgr����
    static GameTeam* create();

private:
    GameTeam();

    // ɾ����������״̬�Ľ�ɫ
    void removeDeadCharacter();

    static int m_nextValidId;                                   // ��һ����Ч�ض���id

    list<GameCharacter*>        m_members;                      // ��������г�Ա
    Formation                   m_formation;                    // ����

    GoalTeamThink*              m_teamBrain;                    // ���鼶��Ĵ���

    float m_advanceRate;                                        // �����ƽ��ٶ�
};

#endif