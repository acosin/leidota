#include "WeaponControlSystem.h"
#include "NormalCloseRangeWeapon.h"

WeaponControlSystem::WeaponControlSystem( GameCharacter* owner )
{
    m_pOwner            =   owner;
    m_currentWeapon     =   nullptr;
}

WeaponControlSystem::~WeaponControlSystem()
{
    for (auto tmpIterator = m_allWeapons.begin(); tmpIterator != m_allWeapons.end(); tmpIterator++)
    {
        delete tmpIterator->second;
    }

    m_allWeapons.clear();
}

void WeaponControlSystem::addWeapon(Weapon* aWeapon)
{
    // ��ӵ�m_allWeapons��
    m_allWeapons.insert(WeaponMap::value_type(aWeapon->getWeaponType(), aWeapon));

    // @_@ ��ǰ������д
    m_currentWeapon     =   aWeapon;
}

void WeaponControlSystem::takeWeaponAndAttack( GameCharacter* target )
{
    // ʹ�õ�ǰ��������������
    if (m_currentWeapon->isInAttackRange(target) && m_currentWeapon->isReadyForNextAttack())
    {
        m_currentWeapon->attack(target);
    }
}
