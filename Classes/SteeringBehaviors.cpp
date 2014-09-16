#include "SteeringBehaviors.h"
#include "GameCharacter.h"
#include "MathTool.h"

SteeringBehaviors::SteeringBehaviors( GameCharacter* owner ):m_arrivePrecision(1)
{
    m_pOwner        =   owner;
    m_behaviorsFlag =   NONE;
}

SteeringBehaviors::~SteeringBehaviors()
{

}

cocos2d::Vec2 SteeringBehaviors::calculate()
{
    m_vSteeringForce.setPoint(0, 0);

    /**
    * Ҫ֪��ÿһ�������������ȼ���ʵ�ǲ�ͬ�ģ�������Ҫ��Ҫ��֤����֮�䲻���ص���
    * ײǽ��Ȼ�����arrive��seek
    */


    // @_@ ��ʱ����д
    if (On(SEEK))
    {
        m_vSteeringForce    +=  seek(m_vTarget);
    }
    if (On(ARRIVE))
    {
        m_vSteeringForce    +=  arrive(m_vTarget);
    }

    return m_vSteeringForce;
}

cocos2d::Vec2 SteeringBehaviors::seek( const Vec2 &target )
{
    auto tmpMovingEntity    =   m_pOwner->getMovingEntity();
    Vec2 tmpDesiredVelocity = 
        (target - tmpMovingEntity.getPosition()).getNormalized()
        * tmpMovingEntity.getMaxSpeed();
    return tmpDesiredVelocity - tmpMovingEntity.getVelocity();
}

cocos2d::Vec2 SteeringBehaviors::arrive( const Vec2& target )
{
    auto tmpMovingEntity    =   m_pOwner->getMovingEntity();
    Vec2 tmpToTarget        =   target - tmpMovingEntity.getPosition();

    float dist  =   tmpToTarget.length();
    dist        =   dist < m_arrivePrecision ? 0 : dist;
    if (dist > 0)
    {
        // �������ٶȣ����������Ŀ϶��������ķ�ʽ�ӽ���ȥ
        float tmpSpeed  =   dist * 10;
        tmpSpeed = tmpSpeed > tmpMovingEntity.getMaxSpeed() ? tmpMovingEntity.getMaxSpeed() : tmpSpeed;
        Vec2 tmpDesiredVelocity =   tmpToTarget * tmpSpeed / dist;
        return tmpDesiredVelocity - tmpMovingEntity.getVelocity();
    }

    return Vec2(0,0);
}

cocos2d::Vec2 SteeringBehaviors::separation()
{
    // �����ҵ���ʵ����Χ����Ӱ�췶Χ�ڵ��ƶ���

}

cocos2d::Vec2 SteeringBehaviors::wallAvoidance()
{
    // 

}
