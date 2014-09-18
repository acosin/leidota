#include "GameCharacter.h"
#include "FlightProps.h"
#include "MessageDispatcher.h"
#include "UIViewManager.h"
#include "GoalThink.h"
#include "NormalCloseRangeWeapon.h"
#include "TimeTool.h"

GameCharacter* GameCharacter::create(int id)
{
    /**
    	 ��ʱ�ʹ���һ�ֽ�ɫ�������ǽ����һ����Ϸ��ɫ�Ĳ���ƴ����һ��
    */
    auto tmpRet = new GameCharacter();
    tmpRet->autorelease();

    /**
    	 Fuck��Ҫ���Ժ���ж����������ɣ���ʱ��������
    */
    /**
        �ڴ˴�ƴװ״̬�������ε�
    */
    tmpRet->m_characterId   =   id;
    switch (id)
    {
    case 1:                                                 // ��Ӧ������˹
        {
            // ��ͬ�Ľ�ɫ�в�ͬ������
            tmpRet->m_shape         =   GameCharacterShape::create("zhousi.ExportJson", "zhousi");
            tmpRet->m_shape->retain();

            // ��ͬ�Ľ�ɫ�в�ͬ�ĳ�ʼ����
            tmpRet->m_attribute     =   GameCharacterAttribute(200, 10, 30, 70);

            // ����һЩ����
            tmpRet->getWeaponControlSystem()->addWeapon(new NormalCloseRangeWeapon(tmpRet));

            break;
        }

    case 2:                                                 // ����
        {
            tmpRet->m_shape         =   GameCharacterShape::create("xuejingling-qian.ExportJson", "xuejingling-qian");
            tmpRet->m_shape->retain();

            tmpRet->m_attribute     =   GameCharacterAttribute(100, 40, 10, 90, 700);

            break;
        }

    case 3:                                                 // ��ʿ
        {
            tmpRet->m_shape         =   GameCharacterShape::create("Aer.ExportJson", "Aer");
            tmpRet->m_shape->retain();

            tmpRet->m_attribute     =   GameCharacterAttribute(150, 20, 20, 80);

            break;
        }

    case 4:                                                 // Ұ���
        {
            tmpRet->m_shape         =   GameCharacterShape::create("Pig.ExportJson", "Pig");
            tmpRet->m_shape->retain();

            tmpRet->m_attribute     =   GameCharacterAttribute(400, 1, 10, 60 + CCRANDOM_0_1() * 20);

            break;
        }

    case 5:                                                 // ţ��
        {
            tmpRet->m_shape         =   GameCharacterShape::create("Niu.ExportJson", "Niu");
            tmpRet->m_shape->retain();

            tmpRet->m_attribute     =   GameCharacterAttribute(400, 1, 10, 50 + CCRANDOM_0_1() * 20);

            break;
        }

    default:
        break;
    }
    
    
    return tmpRet;
}

GameCharacter::GameCharacter()
{
    m_shape                         =   nullptr;
    m_team                          =   nullptr;
    m_state                         =   alive;

    // ��������ϵͳ
    m_weaponControlSystem           =   new WeaponControlSystem(this);
    // Ŀ��ѡ��ϵͳ
    m_targetControlSystem           =   new TargetControlSystem(this);

    // ��ɫ�Ĵ���
    m_brain                         =   new GoalThink(this);

    // ��������������
    m_steeringBehaviors             =   new SteeringBehaviors(this);

    m_lastUpdateTime                =   -1;
}

GameCharacter::~GameCharacter()
{
    // ���ý�ɫ����ʾ����ʾ�б����Ƴ�
    m_shape->removeFromParent();
    CC_SAFE_RELEASE_NULL(m_shape);

    CC_SAFE_DELETE(m_weaponControlSystem);
    m_weaponControlSystem   =   nullptr;

    CC_SAFE_DELETE(m_targetControlSystem);
    m_targetControlSystem   =   nullptr;

    CC_SAFE_DELETE(m_brain);
    m_brain                 =   nullptr;

    CC_SAFE_DELETE(m_steeringBehaviors);
    m_steeringBehaviors     =   nullptr;
}

void GameCharacter::update(float dm)
{
    // �����ǰ��ɫ�������ģ���ô�Ͳ���update��
    if (m_state == dead)
    {
        return;
    }

    if (m_lastUpdateTime == -1)
    {
        m_lastUpdateTime    =   TimeTool::getSecondTime();
    }
    auto tmpDmTime     =    TimeTool::getSecondTime() - m_lastUpdateTime;

    // ����MovingEntity������Shape������
    updateMovement(tmpDmTime);

    // ������hp������Ϊ�����ı�׼��Ȼ����һ��ͳһ�ĵط�ɾ����������״̬��
    if (getAttribute().getHp() <= 0)
    {
        m_state =   dead;
    }

    m_lastUpdateTime    =   TimeTool::getSecondTime();
}

bool GameCharacter::handleMessage(Telegram& msg)
{
    return false;
}

GameCharacterShape* GameCharacter::getShape()
{
    return m_shape;
}

GameCharacterAttribute& GameCharacter::getAttribute()
{
    return m_attribute;
}

WeaponControlSystem* const GameCharacter::getWeaponControlSystem()
{
    return m_weaponControlSystem;
}

TargetControlSystem* const GameCharacter::getTargetControlSystem()
{
    return m_targetControlSystem;
}

void GameCharacter::updateMovement(float dm)
{
    /**
    *  @_@ ������ʵҪ���������������ٶȡ��ٶȵȣ�������MovingEntity�е�
    *  ��Ϣ
    */
    // �ܵĺ���
    Vec2 tmpForce   =   m_steeringBehaviors->calculate();
    if (tmpForce.getLengthSq() < 5)
    {
        // �������С����ֱ�Ӱ��ٶȽ�Ϊ0
        const double BrakingRate = 0.1; 
        m_movingEntity.setVelocity(m_movingEntity.getVelocity() * BrakingRate);                                     
    }
    else
    {
        // ���ٶ�
        Vec2 tmpAccel   =   tmpForce / m_movingEntity.getMass();
        // �ı䵱ǰ�ٶ�
        m_movingEntity.setVelocity(m_movingEntity.getVelocity() + tmpAccel * dm);
    }

    // �����ƶ��Ķ���
    if (m_movingEntity.getSpeed() > 5)
    {
        if (m_movingEntity.getVelocity().x > 0)
        {
            m_shape->faceToRight();
        }
        else
        {
            m_shape->faceToLeft();
        }
        m_shape->playAction(RUN_ACTION);
    }
    else
    {
        m_shape->playAction(IDLE_ACTION);
    }

    // �ı䵱ǰ����
    m_movingEntity.setPosition(m_movingEntity.getPosition() + m_movingEntity.getVelocity() * dm);
    m_shape->setPosition(m_movingEntity.getPosition());
}
