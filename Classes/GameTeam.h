#ifndef __GAME_TEAM_H__
#define __GAME_TEAM_H__

#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

/**
	 ��Ϸ�ж���ĸ��Ϊ��ʵ�ֶ��鼶�����ϡ�AI�ĸ���
*/
class GameTeam
{
public:
    GameTeam();

private:
    /**
    	 ����֮����û��ֱ��ʹ��GameCharacter����Ϊ���е���ö��Ǵ�EntityManager�л�ȡ
    */
    int         m_leaderId;                     // ����id
    list<int>   m_mercenaryIdList;              // Ӷ��id�б�
};

#endif