#include "GameCharacter.h"
#include "MessageDispatcher.h"
#include "UIViewManager.h"
#include "GoalCharacterThink.h"
#include "NormalCloseRangeWeapon.h"
#include "NormalLongRangeWeapon.h"
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
            tmpRet->m_attribute     =   GameCharacterAttribute(80, 10, 30, 70);

            // ����һЩ����
            tmpRet->getWeaponControlSystem()->addWeapon(new NormalCloseRangeWeapon(tmpRet));

            break;
        }

    case 2:                                                 // ����
        {
            tmpRet->m_shape         =   GameCharacterShape::create("xuejingling-qian.ExportJson", "xuejingling-qian");
            tmpRet->m_shape->retain();

            tmpRet->m_attribute     =   GameCharacterAttribute(100, 40, 10, 90, 700);

            tmpRet->getWeaponControlSystem()->addWeapon(
                new NormalLongRangeWeapon(tmpRet, PROJECTILE_TYPE_GALAXO_BALL, 
                tmpRet->getAttribute().getAttDistance()));

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

    // ��ɫ�Ĵ���
    m_brain                         =   new GoalCharacterThink(this);

    // ��������������
    m_steeringBehaviors             =   new SteeringBehaviors(this);

    m_lastUpdateTime                =   -1;

    // Ĭ�Ͼʹ򿪼���������
    m_steeringBehaviors->wallAvoidanceOn();
    m_steeringBehaviors->separationOn();
}

GameCharacter::~GameCharacter()
{
    // ���ý�ɫ����ʾ����ʾ�б����Ƴ�
    m_shape->removeFromParent();
    CC_SAFE_RELEASE_NULL(m_shape);

    CC_SAFE_DELETE(m_weaponControlSystem);
    m_weaponControlSystem   =   nullptr;

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
    //CCLOG("%f", tmpDmTime);
    // ˼��һ��
    m_brain->process();

    // ����MovingEntity������Shape������
    updateMovement(tmpDmTime);

    // ������hp������Ϊ�����ı�׼��Ȼ����һ��ͳһ�ĵط�ɾ����������״̬��
    if (getAttribute().getHp() <= 0)
    {
        m_state =   dead;
    }

    m_lastUpdateTime    =   TimeTool::getSecondTime();

    // @_@ ��������ֱ�ǩ
    m_shape->setPosNumber(m_movingEntity.getFormationPosId());
}

bool GameCharacter::handleMessage(Telegram& msg)
{
    // ���Ȱ���Ϣ�����ó�Ա���Դ�
    if (m_brain->handleMessage(msg)) return true;

    /**
    *	������Ҫ����һЩ��AI����Ϣ 
    */
    switch (msg.type)
    {
    case TELEGRAM_ENUM_NORMAL_ATTACK:                       // �յ���ͨ������
        {
            // ��ͨ����ֻ��Ѫ��ͬʱ��ҪƮ��
            TelegramNormalAttack* tmpMsg    =   dynamic_cast<TelegramNormalAttack*>(&msg);
            auto tmpFrontHp                 =   m_attribute.getHp();
            m_attribute.sufferNormalAttack(tmpMsg->senderAtt);
            auto tmpHp                      =   tmpFrontHp - m_attribute.getHp();
            if (this->getType() == GAME_ENTITY_TYPE_PLAYER_CHARACTER)
            {
                m_shape->floatNumber(tmpHp, GameCharacterShape::FLOAT_NUMBER_YELLOW);
            }
            else if (this->getType() == GAME_ENTITY_TYPE_ENEMY_CHARACTER)
            {
                m_shape->floatNumber(tmpHp, GameCharacterShape::FLOAT_NUMBER_RED);
            }
            if (m_attribute.getHp() <= 0)
            {
                m_state =   dead;
            }
            m_shape->setHpRatio(m_attribute.getHp() / m_attribute.getFullHp());
            return true;
        }

    default:
        break;
    }
    return false;
}

void GameCharacter::updateMovement(float dm)
{
    m_shape->setPosition(m_movingEntity.getPosition());
    // �����ǰ����ϵͳʹ�øý�ɫ�޷��ƶ�
   if (!m_weaponControlSystem->canCharacterMove())
   {
       return;
   }
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

bool GameCharacter::hasGoal()
{
    return m_brain->hasSubgoal();
}
