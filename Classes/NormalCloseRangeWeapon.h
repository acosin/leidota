#ifndef __NORMAL_CLOSE_RANGE_WEAPON_H__
#define __NORMAL_CLOSE_RANGE_WEAPON_H__

#include <string>
#include "Weapon.h"

using namespace std;

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
    const string ACTION_NAME;

    /**
    *  ��ͨ���������ƻ����Ͼ�ֻ����̹������
    */
    float           m_minAttackInterval;
    float           m_lastAttackTime;               // ���һ�ι���ʱ��
    float           m_nextAttackReadyTime;          // ��һ�ι���׼�����ʱ��
};

#endif