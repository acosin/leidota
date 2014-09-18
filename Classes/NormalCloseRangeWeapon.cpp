#include "NormalCloseRangeWeapon.h"
#include "Telegram.h"
#include "GameCharacter.h"
#include "TimeTool.h"
#include "MathTool.h"

NormalCloseRangeWeapon::NormalCloseRangeWeapon( GameCharacter* owner, float minAttackInterval, string actionName )
    :Weapon(owner, Weapon::WeaponTypeEnum::NORMAL_CLOSE_RANGE_WEAPON), ACTION_NAME(actionName)
{
    m_minAttackInterval     =   minAttackInterval;
}

NormalCloseRangeWeapon::~NormalCloseRangeWeapon()
{

}

void NormalCloseRangeWeapon::attack( GameCharacter* target )
{
    // ������ͨ�Ľ��̹���ֻ��Ҫ���Ŷ�����Ȼ���ڶ�Ӧ�Ķ���֡������Ϣ��OK��
    m_pOwner->getShape()->playAction(ACTION_NAME);
    m_lastAttackTime        =   TimeTool::getSecondTime();
    m_nextAttackReadyTime   =   m_lastAttackTime + m_minAttackInterval;
}

bool NormalCloseRangeWeapon::isInAttackRange( GameCharacter* target )
{
    return false;
}

bool NormalCloseRangeWeapon::isReadyForNextAttack()
{
    return m_nextAttackReadyTime < TimeTool::getSecondTime();
}
