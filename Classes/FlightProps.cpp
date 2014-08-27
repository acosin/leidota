#include "FlightProps.h"
#include "FlightPropsMgr.h"
#include "MessageDispatcher.h"

FlightProps::FlightProps(FlightPropsTypeEnum type, int senderId, Vec2 velocity)
{
    this->type      =   type;
    this->senderId  =   senderId;
    this->velocity  =   velocity;
    shouldBeDel     =   false;
    isEffective     =   true;
    senderAtt       =   ((GameCharacter*)EntityMgr->getEntityFromID(senderId))->getAttribute();
}

void FlightProps::update(float dm)
{
    // Ĭ�ϵĶ��������˶���
    this->setPosition(this->getPosition() + velocity * dm);
}

Rect FlightProps::getCollisionRect()
{
    auto tmpRect    =   this->getBoundingBox();
    return tmpRect;
}

OneToOneArmatureFlightProps::OneToOneArmatureFlightProps(int senderId, int targetId, 
    Armature* armature, std::string actionName, float rate)
    :FlightProps(FLIGHTPROPS_TYPE_FIXED_POINT_ONE_TARGET, senderId, Vec2(0, 0))
{
    this->m_targetId            =   targetId;
    armature->retain();
    this->m_armature            =   armature;
    this->m_actionName          =   actionName;
    this->setContentSize(armature->getContentSize());

    // �����ٶ�
    auto tmpSenderPos           =   EntityMgr->getEntityFromID(senderId)->getShape()->getPosition();
    auto tmpTargetPos           =   ((GameCharacterShape*)EntityMgr->getEntityFromID(targetId)->getShape())->getCenterPos();
    this->velocity              =   tmpTargetPos - tmpSenderPos;
    this->velocity.normalize();
    this->velocity              *=  rate;
}

OneToOneArmatureFlightProps::~OneToOneArmatureFlightProps()
{
    CC_SAFE_RELEASE(m_armature);
}

bool OneToOneArmatureFlightProps::init()
{
    if (!FlightProps::init())
    {
        return false;
    }

    this->addChild(m_armature);

    // ��Ϊ���ƶ���ʱ��ʹ�õ�һ֡��
    // this->m_armature->getAnimation()->play(m_actionName, -1, 0);
    return true;
}

OneToOneArmatureFlightProps* OneToOneArmatureFlightProps::create(int senderId, int targetId, int skillId)
{
    Armature* tmpArmature   =   nullptr;
    string  tmpActionName   =   "";
    float   tmpRate         =   500;

    switch (skillId)
    {
    case 1:                                     // ѩ�����ѩ�򹥻�
        ArmatureDataManager::getInstance()->addArmatureFileInfo("xuejingling-texiao.ExportJson");
        tmpActionName   =   "atk";
        tmpArmature     =   Armature::create("xuejingling-texiao");
        tmpRate         =   2000;

    default:
        break;
    }

    OneToOneArmatureFlightProps* pRet   =   
        new OneToOneArmatureFlightProps(senderId, targetId, tmpArmature, tmpActionName, tmpRate);
    if (pRet != nullptr)
    {
        pRet->init();
        pRet->autorelease();
    }

    // ���뵽��������
    FliProMgr->registerFlightProps(pRet);
    return pRet;
}

void OneToOneArmatureFlightProps::onCollision(int id)
{
    // �������֮ǰ�趨��Ŀ�꣬������
    if (id != m_targetId)
    {
        return;
    }

    // ����@_@��ʱ����Ϊ�����ͨ������
    // this->shouldBeDel   =   true;
    this->isEffective   =   false;

    // ͬʱ�������Ŷ���
    m_armature->getAnimation()->play(m_actionName, -1, 0);

    // ͬʱ������Ϣ
    auto tmpMsg = TelegramNormalAttack::create(this->senderId, id, this->senderAtt);
    Dispatch->dispatchMessage(*tmpMsg);
}

void OneToOneArmatureFlightProps::update(float dm)
{
    if (this->isEffective)
    {
        FlightProps::update(dm);
    }
    else if (!m_armature->getAnimation()->isPlaying())
    {
        this->shouldBeDel   =   true;
    }
}