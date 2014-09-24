#include "ProjectileGalaxoBall.h"
#include "MathTool.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"

ProjectileGalaxoBall::ProjectileGalaxoBall( GameCharacterAttribute& att, int targetId )
    :Projectile(att)
{
    ArmatureDataManager::getInstance()->addArmatureFileInfo("xuejingling-texiao.ExportJson");
    m_ball      =   Armature::create("xuejingling-texiao");
    m_ball->retain();
    m_rate      =   1800;
    m_targetId  =   targetId;
    GameCharacter* tmpTarget    =   dynamic_cast<GameCharacter*>(EntityMgr->getEntityFromID(m_targetId));
    m_targetPos =   tmpTarget->getShape()->getCenterPos();
}

ProjectileGalaxoBall::~ProjectileGalaxoBall()
{
    if (m_ball->getParent() != nullptr)
    {
        m_ball->removeFromParent();
    }
    CC_SAFE_RELEASE_NULL(m_ball);
}

void ProjectileGalaxoBall::update( float dm )
{
    // �ж��Ƿ񵽴�
    if (canUpdateMovement())
    {
        float tmpDistance    =   (m_position - m_targetPos).getLengthSq();
        if (tmpDistance <= 400)
        {
            // ��ֹ����λ��
            updateMovementOff();
            // ˵�������������Ѿ���λ����ʼ�������Ŷ���
            m_ball->getAnimation()->play("atk", -1, 0);

            // ������Ϣ���ܻ��ߣ�@_@������idû�б�Ҫ
            auto tmpMsg = TelegramNormalAttack::create(0, m_targetId, m_senderAtt);
            Dispatch->dispatchMessage(*tmpMsg);
        }
    }
    else
    {
        // ������������Ϻ��
        if (!m_ball->getAnimation()->isPlaying())
        {
            updateOff();
        }
    }
}

void ProjectileGalaxoBall::updateMovement( float dm )
{
    // ��ȡ��ǰλ��
    GameCharacter* tmpTarget    =   dynamic_cast<GameCharacter*>(EntityMgr->getEntityFromID(m_targetId));
    if (tmpTarget != nullptr)
    {
        // �����ǰ��ɫ��û����ʧ����Ҫ��ͣ���޸��ٶ�������Ŀ��
        m_targetPos =   tmpTarget->getShape()->getCenterPos();
        Vec2 tmpToTarget    =   m_targetPos - m_position;
        tmpToTarget.normalize();
        m_velocity          =   tmpToTarget * m_rate;
    }

    // �޸�λ��
    m_position          +=  m_velocity * dm;
    m_ball->setPosition(m_position);
}

Node* ProjectileGalaxoBall::getShape()
{
    return m_ball;
}
