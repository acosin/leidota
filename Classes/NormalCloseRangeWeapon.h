#ifndef __NORMAL_CLOSE_RANGE_WEAPON_H__
#define __NORMAL_CLOSE_RANGE_WEAPON_H__

#include "cocos2d.h"
#include "Weapon.h"

using namespace std;
using namespace cocos2d;

/**
* ��ͨ�Ľ����빥��������������������н�ս�ͽ�ɫ�ر������� 
*/
class NormalCloseRangeWeapon : public Weapon
{
public:
    NormalCloseRangeWeapon(GameCharacter* owner, float minAttackInterval = 3, string actionName = "atk1");
    virtual ~NormalCloseRangeWeapon();

    virtual void attack(GameCharacter* target) override;
    virtual bool isInAttackRange(GameCharacter* target) override;
    virtual bool isReadyForNextAttack() override;
    virtual bool isAttacking() override;

private:
    /**
    *  ��Ӧ�Ķ����ļ��еĶ������ƣ���Ҫ�ǿ��ǵ����������ļ���ʱ���������淶��ԭ��
    *  ��ͨ�Ľ����빥�����������Ͼ�ֻ��Ҫ���Ŷ�����OK��
    */
    const string m_actionName;

    /**
    * ��ͨ�����ķ�Χƫ�� 
    */
    const int   m_xOffset;                          // �����߾��뱻�����ߵ�x�����ϵľ����ȥ˫�������ʣ�µ�ֵ
    const int   m_yOffset;                          // ��������y�����ϵ�����ƫ��Ӧ���뱻�����ߵİ뾶�йأ����ǿ��ܻ�С��뾶

    /**
    *  ��ͨ���������ƻ����Ͼ�ֻ����̹������
    */
    float           m_minAttackInterval;
    float           m_lastAttackTime;               // ���һ�ι���ʱ��
    float           m_nextAttackReadyTime;          // ��һ�ι���׼�����ʱ��
};

#endif