#ifndef __STEERING_BEHAVIORS_H__
#define __STEERING_BEHAVIORS_H__

#include "cocos2d.h"

using namespace cocos2d;

class GameCharacter;

/**
* ����������Ϊ���������߼����֣�ʩ����һ����ɫ���ϵĺ����ڴ˴����������
*/
class SteeringBehaviors
{
public:
    SteeringBehaviors(GameCharacter* owner);
    ~SteeringBehaviors();

    /**
    * �ⲿ��ȡ��ǰ���������Ľӿ� 
    */
    Vec2 calculate();

    void setTarget(Vec2 t) {m_vTarget = t;}
    
    /**
    * �����������Ŀ����͹ر� 
    */
    void seekOn() { m_behaviorsFlag |= SEEK; }
    void seekOff() { if (On(SEEK)) m_behaviorsFlag ^= SEEK;}

private:
    /**
    *  ����������Ϊ
    */
    Vec2 seek(const Vec2 &target);

private:
    /**
    * ��ǰʹ�õ���Ϊ�����ı�� 
    */
    enum BehaviorTypeEnum
    {
        NONE                =   0,                      // ��ʼ����
        SEEK                =   1,                      // �嵽ָ����λ��
        ARRIVE              =   1 << 1,                 // ����ָ��λ��
        SEPARATION          =   1 << 2,                 // �������밤��һ��Ľ�ɫ
        WALL_AVOIDANCE      =   1 << 3,                 // �����ܿ�ǽ�ڵ� 
    };

    // ���ĳ�����͵��������Ƿ���
    bool On(BehaviorTypeEnum bt){return (m_behaviorsFlag & bt) == bt;}

    GameCharacter*  m_pOwner;

    int             m_behaviorsFlag;                    // ������¼��ǰ��������Щ����
    Vec2            m_vSteeringForce;                   // ��ǰ���������������

    /**
    * ��seek��arrive��Ϊ�йص����� 
    */
    Vec2            m_vTarget;                          // Ŀ������

};

#endif