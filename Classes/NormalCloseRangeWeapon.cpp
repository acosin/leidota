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
    // @_@ �����ж��Ƿ�����ͨ������Χ�ڵĻ�����ʱû��ɶ�õķ������Ͼ�������Χ�Ǻ�������ص�
    auto tmpOwnerPos    =   m_pOwner->getMovingEntity().getPosition();
    auto tmpTargetPos   =   target->getMovingEntity().getPosition();
    return (tmpOwnerPos - tmpTargetPos).getLengthSq() < 10000;
}

bool NormalCloseRangeWeapon::isReadyForNextAttack()
{
    return m_nextAttackReadyTime < TimeTool::getSecondTime();
}

bool NormalCloseRangeWeapon::isAttacking()
{
    return m_pOwner->getShape()->getCurrentAnimationName() == ACTION_NAME;
}