#ifndef __GAME_CHARACTER_ATTRIBUTE_H__
#define __GAME_CHARACTER_ATTRIBUTE_H__

#include "cocos2d.h"

/**
	 ��װ�˹��ڽ�ɫ�����Լ���������صĸ��ּ��㣬��Ҫ�ǿ��ǵ��Ժ���㷽ʽ���ܻᾭ���仯�����о���
     ��Щ���ܿ��ܻ�ͬʱ�޸Ķ������
*/
class GameCharacterAttribute
{
public:
    /**
    	 ��ǰ��ʱһ������ֻ��Ѫ��������ֵ������ֵ�Լ��ƶ��ٶ�
    */
    GameCharacterAttribute(float hp = 100, float attack = 10, float defense = 20, 
        float rate = 80, float attDistance = 650);

    /**
    	 ���ܱ��˵���ͨ����������֮���԰ѶԷ����������Զ����룬����Ϊ���ǵ�������ͨ������ɱ�˼���
         ���ܻ����������߰���������йأ����ظý�ɫ��������ĵ�ǰ����
    */
    GameCharacterAttribute& sufferNormalAttack(GameCharacterAttribute& otherAttr);

    CC_SYNTHESIZE(float, m_hp, Hp);
    CC_SYNTHESIZE(float, m_attack, Attack);
    CC_SYNTHESIZE(float, m_defense, Defense);
    CC_SYNTHESIZE(float, m_rate, Rate);
    CC_SYNTHESIZE(float, m_attDistance, AttDistance);
};

#endif