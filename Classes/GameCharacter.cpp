#include "GameCharacter.h"
#include "GameCharacterState.h"
#include "FlightProps.h"
#include "MessageDispatcher.h"

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
    tmpRet->m_stateMachine  =   StateMachine<GameCharacter>::create(tmpRet);
    tmpRet->m_stateMachine->retain();
    switch (id)
    {
    case 1:                                                 // ��Ӧ������˹
        {
            // ��ͬ�Ľ�ɫ�в�ͬ������
            tmpRet->m_shape         =   GameCharacterShape::create("zhousi.ExportJson", "zhousi");
            tmpRet->m_shape->retain();

            // ��ͬ�Ľ�ɫ�в�ͬ��״̬ת����
            tmpRet->m_stateMachine->changeState(GameCharacterIdleState::create());
            tmpRet->m_stateMachine->setGlobalState(GameCharacterGlobalState::create());

            // ��ͬ�Ľ�ɫ�в�ͬ�ĳ�ʼ����
            tmpRet->m_attribute     =   GameCharacterAttribute(200, 10, 30, 70);

            // ��ɫ���ͣ���˹���ڽ��̹�����λ
            tmpRet->m_characterType =   GAMECHARACTER_TYPE_ENUM_SHORT_RANGE;

            break;
        }

    case 2:                                                 // ����
        {
            tmpRet->m_shape         =   GameCharacterShape::create("xuejingling-qian.ExportJson", "xuejingling-qian");
            tmpRet->m_shape->retain();
            // ��һ��״̬ת����@_@ �Ժ��ܲ��ܽ��ⲿ�ֵ�AI�߼��Ƶ�lua��ȥ����Ȼ��������
            // Ŀǰ��ʹ��һ��AI�߼�@_@  FUCK
            // auto tmpState = GameCharacterPursueState::create();
            // tmpState->targetId  =   4;
            tmpRet->m_stateMachine->changeState(GameCharacterIdleState::create());
            tmpRet->m_stateMachine->setGlobalState(GameCharacterGlobalState::create());

            tmpRet->m_attribute     =   GameCharacterAttribute(100, 40, 10, 90, 700);
            
            // ѩ����Զ�̹�����λ
            tmpRet->m_characterType =   GAMECHARACTER_TYPE_ENUM_LONG_RANGE;

            break;
        }

    case 3:                                                 // ��ʿ
        {
            tmpRet->m_shape         =   GameCharacterShape::create("Aer.ExportJson", "Aer");
            tmpRet->m_shape->retain();

            tmpRet->m_stateMachine->changeState(GameCharacterIdleState::create());
            tmpRet->m_stateMachine->setGlobalState(GameCharacterGlobalState::create());

            tmpRet->m_attribute     =   GameCharacterAttribute(150, 20, 20, 110);
            
            // ��ʿ�����̹�����λ
            tmpRet->m_characterType =   GAMECHARACTER_TYPE_ENUM_SHORT_RANGE;

            break;
        }

    case 4:                                                 // Ұ���
        {
            tmpRet->m_shape         =   GameCharacterShape::create("Pig.ExportJson", "Pig");
            tmpRet->m_shape->retain();

            tmpRet->m_stateMachine->changeState(GameCharacterIdleState::create());
            tmpRet->m_stateMachine->setGlobalState(GameCharacterGlobalState::create());

            tmpRet->m_attribute     =   GameCharacterAttribute(10, 1, 10, 60 + CCRANDOM_0_1() * 20);

            // Ұ��֣����̹�����λ
            tmpRet->m_characterType =   GAMECHARACTER_TYPE_ENUM_SHORT_RANGE;

            break;
        }

    default:
        break;
    }
    
    
    return tmpRet;
}

GameCharacter::GameCharacter()
{
    m_stateMachine                  =   nullptr;
    m_shape                         =   nullptr;
    m_graph                         =   nullptr;
    m_moveAction                    =   nullptr;
    m_frameCount                    =   0;
    m_lastExitNormalAttackFrame     =   0;
}

GameCharacter::~GameCharacter()
{
    // �Ƴ��ý�ɫ����������ռ�Ŀ�λ
    m_graph->removeObjectFromGrid(&m_objectOnGrid);
    CC_SAFE_RELEASE_NULL(m_stateMachine);

    // ���ý�ɫ����ʾ����ʾ�б����Ƴ�
    m_shape->removeFromParent();
    CC_SAFE_RELEASE_NULL(m_shape);
}

void GameCharacter::update(float dm)
{
    /**
    * ��������ע�⣺��״̬���п��ܻ�ɾ���Լ����������die��ʱ�� 
    */
    m_frameCount++;
    m_stateMachine->update(dm);
}

bool GameCharacter::handleMessage(Telegram& msg)
{
    return m_stateMachine->handleMessage(msg);
}

StateMachine<GameCharacter>* GameCharacter::getFSM()
{
    return m_stateMachine;
}

GameCharacterShape* GameCharacter::getShape()
{
    return m_shape;
}

void GameCharacter::setGridGraph(MapGrid* graph)
{
    m_graph =   graph;
}

ObjectOnMapGrid* GameCharacter::getObjectOnGrid()
{
    return &m_objectOnGrid;
}

void GameCharacter::moveToGridIndex(int nodeIndex, float rate)
{
    // ����ƶ�Ŀ������Ч�ĸ�������
    if (nodeIndex == INVALID_NODE_INDEX)
    {
        return;
    }

    auto tmpResourceGrid    =   m_graph->getNodeByIndex(m_objectOnGrid.nodeIndex);
    auto tmpTargetGird      =   m_graph->getNodeByIndex(nodeIndex);

    // ���޸�֮ǰռ�������
    m_graph->removeObjectFromGrid(&m_objectOnGrid);
    m_objectOnGrid.nodeIndex    =   nodeIndex;
    m_graph->addObjectToGrid(&m_objectOnGrid);

    // ���Ƚ���֮ǰ�Ķ���
    if (m_moveAction != nullptr)
    {
        m_shape->stopAction(m_moveAction);
        onMoveOver(nullptr);
    }

    // ���û�����ȥ
    auto tmpDirection       =   (tmpTargetGird.getX() - tmpResourceGrid.getX()) * (tmpTargetGird.getX() - tmpResourceGrid.getX()) + 
         (tmpTargetGird.getY() - tmpResourceGrid.getY()) * (tmpTargetGird.getY() - tmpResourceGrid.getY());
    tmpDirection        =   sqrt(tmpDirection);
    m_moveAction        =   MoveTo::create(tmpDirection / rate, Vec2(tmpTargetGird.getX(), tmpTargetGird.getY()));
    // ����һ�����������Ļص�
    m_shape->runAction(Sequence::create(m_moveAction, CallFuncN::create(std::bind(&GameCharacter::onMoveOver, this, std::placeholders::_1)), nullptr));
}

MapGrid* GameCharacter::getMapGrid()
{
    return m_graph;
}

bool GameCharacter::isMoving()
{
    return m_moveAction != nullptr;
}

void GameCharacter::onMoveOver(Node* pNode)
{
    m_moveAction    =   nullptr;
}

GameCharacterAttribute& GameCharacter::getAttribute()
{
    return m_attribute;
}

void GameCharacter::die()
{
    // Ŀǰ��ֱ��ɾ�����Լ���
    CC_SAFE_RELEASE(this);
}

GameCharacterTypeEnum GameCharacter::getCharacterType()
{
    return m_characterType;
}

void GameCharacter::normalAttack(int id)
{
    m_normatAttTargetId =   id;
    if (this->getCharacterType() == GAMECHARACTER_TYPE_ENUM_SHORT_RANGE)
    {
        // ���ڽ��̹�����λ��ֻ�ò��Ŷ�����OK��
        this->getShape()->playAction(ATTACK_ACTION, false, std::bind(&GameCharacter::onShortAttEffect, this, std::placeholders::_1));
    }
    else if (this->getCharacterType() == GAMECHARACTER_TYPE_ENUM_LONG_RANGE)
    {
        // Զ�̹�����λ������Ҫ���ض�������λ�ö������
        this->getShape()->playAction(ATTACK_ACTION, false, std::bind(&GameCharacter::onLongAttLaunch, this, std::placeholders::_1));
    }
}

void GameCharacter::onShortAttEffect(string evt)
{
    // ���Է�������Ϣ
    auto tmpMsg = TelegramNormalAttack::create(this->getId(), m_normatAttTargetId, this->getAttribute());
    Dispatch->dispatchMessage(*tmpMsg);
}

void GameCharacter::onLongAttLaunch(string evt)
{
    // �������
    // Ŀ�껹��
    if (EntityMgr->getEntityFromID(m_normatAttTargetId) != nullptr)
    {
        auto tmpSnowBall    =   OneToOneArmatureFlightProps::create(this->getId(), m_normatAttTargetId, 1);
        tmpSnowBall->setPosition(this->getShape()->getCenterPos());
        this->getShape()->getParent()->addChild(tmpSnowBall);
    }
}

bool GameCharacter::isNormalAttackFinish()
{
    // Ŀǰ���ò��ڶ���������Ϊ����
    return this->getShape()->isNotInAnimation();
}

bool GameCharacter::isInAttackDistance(GameCharacter* other)
{
    // ���̹�����λ�ж��Ƿ��ڹ�����Χ�ķ�����Զ�̹�����λ�жϷ�����ͬ
    if (this->getCharacterType() == GAMECHARACTER_TYPE_ENUM_SHORT_RANGE)
    {
        // ���̹�����λ
        auto tmpOwnerObject     =   this->getObjectOnGrid();
        auto tmpTargetObject    =   other->getObjectOnGrid();

        // �����һ��ˮƽ���ϣ����Ҽ����3��������
        if (this->getMapGrid()->testTwoIndexInOneHorizon(tmpOwnerObject->nodeIndex, tmpTargetObject->nodeIndex) 
            && abs(tmpTargetObject->nodeIndex - tmpOwnerObject->nodeIndex) <= 3)
        {
            return true;
        }

        // ����ڽ���λ�ô�
        if (tmpOwnerObject->nodeIndex == other->getMapGrid()->getLeftTopGridIndex(tmpTargetObject->nodeIndex)
            || tmpOwnerObject->nodeIndex == other->getMapGrid()->getRightTopGridIndex(tmpTargetObject->nodeIndex)
            || tmpOwnerObject->nodeIndex == other->getMapGrid()->getRightBottomGridIndex(tmpTargetObject->nodeIndex)
            || tmpOwnerObject->nodeIndex == other->getMapGrid()->getLeftBottomGridIndex(tmpTargetObject->nodeIndex))
        {
            return true;
        }
    }
    else if (this->getCharacterType() == GAMECHARACTER_TYPE_ENUM_LONG_RANGE)
    {
        // Զ�̹�����λ�԰뾶�ж�
        return (this->getShape()->getPosition() - other->getShape()->getPosition()).getLength() 
            <= other->getAttribute().getAttDistance();
    }

    return false;
}
void GameCharacter::walkOff()
{
    // �л�����
    this->getShape()->playAction(RUN_ACTION);
    this->getShape()->faceToRight();

    // ����
    Vec2 tmpStartPos    =   this->getShape()->getPosition();
    Vec2 tmpTargetPos   =   tmpStartPos;
    tmpTargetPos.x      =   m_graph->getContentSize().width + 200;
    auto tmpDirection   =   tmpTargetPos.x - tmpStartPos.x;
    if (m_moveAction != nullptr)
    {
        m_shape->stopAction(m_moveAction);
    }
    m_moveAction        =   MoveTo::create(tmpDirection / this->m_attribute.getRate(), tmpTargetPos);
    m_shape->runAction(Sequence::create(m_moveAction, 
        CallFuncN::create(std::bind(&GameCharacter::onMoveOver, this, std::placeholders::_1)), nullptr));
}

void GameCharacter::exitNormalAttack()
{
    m_lastExitNormalAttackFrame =   m_frameCount;
}

bool GameCharacter::canNormalAttack()
{
    return (m_frameCount - m_lastExitNormalAttackFrame) > m_attribute.getAttInterval();
}

int GameCharacter::getNextNormatAttackLeftCount()
{
    return m_attribute.getAttInterval() - (m_frameCount - m_lastExitNormalAttackFrame) + 1;
}
