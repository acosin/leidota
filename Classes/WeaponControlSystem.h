#ifndef __WEAPON_CONTROL_SYSTEM_H__
#define __WEAPON_CONTROL_SYSTEM_H__

#include <map>
#include "Weapon.h"

using namespace std;

class GameCharacter;

/**
* ��������ϵͳ�����︺��ά����ɫ���ϵ����й�����ʽ��������ͨ���������ܹ����ȣ�����
* ʹ�����ַ�ʽ���������߼�Ҳ��������ڹ�����ʽӦ����Ҫ����ĳЩ�������ó�ʹ��ĳ��
* ����������
*/
class WeaponControlSystem
{
public:
    WeaponControlSystem(GameCharacter* owner);
    ~WeaponControlSystem();

    /**
    * ��������ϵͳ����������� 
    */
    void addWeapon(Weapon* aWeapon);

    /**
    * ʹ�õ�ǰ�������ҹ���ĳ��Ŀ�� 
    */
    void takeWeaponAndAttack(GameCharacter* target);

    /**
    * ����ʹ�õ�ǰ����������£�target�Ƿ��ڹ�����Χ��
    */
    bool isInAttackRange(GameCharacter* target);

    /**
    * @_@ ��Ҫ����Ϊ������ϵͳ������ʱ�򣬽�ɫ�ǲ��ܸ���λ�õģ�����
    */
    bool canCharacterMove();

private:
    GameCharacter*                              m_pOwner;           // ��ǰ����ӵ����

    Weapon*                                     m_currentWeapon;    // ��ǰ����
    
    typedef map<WeaponTypeEnum, Weapon*> WeaponMap;
    WeaponMap        m_allWeapons;                                  // ��ǰ��ɫӵ�е���������

    int                                         m_targetId;         // ��ʱ��¼��һ�ι�����Ŀ���id
};

#endif