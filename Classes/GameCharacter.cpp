#include "GameCharacter.h"
#include "GameCharacterState.h"
#include "FlightProps.h"
#include "MessageDispatcher.h"
#include "UIViewManager.h"
#include "TargetControlSystem.h"
#include "PathPlanner.h"
#include "GoalThink.h"

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
    tmpRet->m_characterId   =   id;
    switch (id)
    {
    case 1:                                                 // ��Ӧ������˹
        {
            // ��ͬ�Ľ�ɫ�в�ͬ������
            tmpRet->m_shape         =   GameCharacterShape::create("zhousi.ExportJson", "zhousi");
            tmpRet->m_shape->retain();

            // ��ͬ�Ľ�ɫ�в�ͬ��״̬ת����
            //tmpRet->m_stateMachine->changeState(GameCharacterIdleState::create());
            //tmpRet->m_stateMachine->setGlobalState(GameCharacterGlobalState::create());

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
            //tmpRet->m_stateMachine->changeState(GameCharacterIdleState::create());
            //tmpRet->m_stateMachine->setGlobalState(GameCharacterGlobalState::create());

            tmpRet->m_attribute     =   GameCharacterAttribute(100, 40, 10, 90, 700);
            
            // ѩ����Զ�̹�����λ
            tmpRet->m_characterType =   GAMECHARACTER_TYPE_ENUM_LONG_RANGE;

            break;
        }

    case 3:                                                 // ��ʿ
        {
            tmpRet->m_shape         =   GameCharacterShape::create("Aer.ExportJson", "Aer");
            tmpRet->m_shape->retain();

            //tmpRet->m_stateMachine->changeState(GameCharacterIdleState::create());
            //tmpRet->m_stateMachine->setGlobalState(GameCharacterGlobalState::create());

            tmpRet->m_attribute     =   GameCharacterAttribute(150, 20, 20, 80);
            
            // ��ʿ�����̹�����λ
            tmpRet->m_characterType =   GAMECHARACTER_TYPE_ENUM_SHORT_RANGE;

            break;
        }

    case 4:                                                 // Ұ���
        {
            tmpRet->m_shape         =   GameCharacterShape::create("Pig.ExportJson", "Pig");
            tmpRet->m_shape->retain();

            //tmpRet->m_stateMachine->changeState(GameCharacterIdleState::create());
            //tmpRet->m_stateMachine->setGlobalState(GameCharacterGlobalState::create());

            tmpRet->m_attribute     =   GameCharacterAttribute(400, 1, 10, 60 + CCRANDOM_0_1() * 20);

            // Ұ��֣����̹�����λ
            tmpRet->m_characterType =   GAMECHARACTER_TYPE_ENUM_SHORT_RANGE;

            break;
        }

    case 5:                                                 // ţ��
        {
            tmpRet->m_shape         =   GameCharacterShape::create("Niu.ExportJson", "Niu");
            tmpRet->m_shape->retain();

            //tmpRet->m_stateMachine->changeState(GameCharacterIdleState::create());
            //tmpRet->m_stateMachine->setGlobalState(GameCharacterGlobalState::create());

            tmpRet->m_attribute     =   GameCharacterAttribute(400, 1, 10, 50 + CCRANDOM_0_1() * 20);

            // ţ�ˣ����̹�����λ
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
    m_team                          =   nullptr;
    m_frameCount                    =   0;
    m_lastExitNormalAttackFrame     =   0;

    /**
    * ���ֿ���ϵͳ 
    */
    m_targetControlSystem           =   new TargetControlSystem(this, 0.5);

    // ·���滮��
    m_pathPlanner                   =   new PathPlanner(this);

    // ��ɫ�Ĵ���
    m_brain                         =   new GoalThink(this);
}

GameCharacter::~GameCharacter()
{
    // �Ƴ��ý�ɫ����������ռ�Ŀ�λ
    m_graph->removeObjectFromGrid(&m_objectOnGrid);
    CC_SAFE_RELEASE_NULL(m_stateMachine);

    // ���ý�ɫ����ʾ����ʾ�б����Ƴ�
    m_shape->removeFromParent();
    CC_SAFE_RELEASE_NULL(m_shape);

    CC_SAFE_DELETE(m_targetControlSystem);
    m_targetControlSystem   =   nullptr;

    CC_SAFE_DELETE(m_pathPlanner);
    m_pathPlanner           =   nullptr;

    CC_SAFE_DELETE(m_brain);
    m_brain                 =   nullptr;
}

void GameCharacter::update(float dm)
{
    m_brain->process();

    /**
    * ��������ע�⣺��״̬���п��ܻ�ɾ���Լ����������die��ʱ�� 
    */
    m_frameCount++;

    // @_@ ÿһ֡������һ��Ѫ��
    m_shape->setHpRatio(m_attribute.getHp() / m_attribute.getFullHp());

    /**
    * ���¸ý�ɫ���ϵ����п���ϵͳ 
    */
    m_targetControlSystem->tryUpdate();

    // m_stateMachine->update(dm);
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

    NavGraphNode& tmpResourceGrid    =   m_graph->getNodeByIndex(m_objectOnGrid.nodeIndex);
    NavGraphNode& tmpTargetGird      =   m_graph->getNodeByIndex(nodeIndex);

    // ��������
    if (m_graph->testIsAtLeft(m_objectOnGrid.nodeIndex, nodeIndex))
    {
        m_shape->faceToRight();
    }
    else if (m_graph->testIsAtRight(m_objectOnGrid.nodeIndex, nodeIndex))
    {
        m_shape->faceToLeft();
    }

    // ���޸�֮ǰռ�������
    m_graph->removeObjectFromGrid(&m_objectOnGrid);
    // �ж�Ŀ��ڵ��Ƿ�������ߣ�����ýڵ㲻���ߣ��Ͳ����ƶ�
    if (!tmpTargetGird.passable())
    {
        m_shape->playAction(IDLE_ACTION);
        return;
    }
    // �µĿ�λ
    m_objectOnGrid.nodeIndex    =   nodeIndex;
    m_graph->addObjectToGrid(&m_objectOnGrid);

    // �����ƶ��Ķ���
    m_shape->playAction(RUN_ACTION);

    // ���Ƚ���֮ǰ�Ķ���
    if (m_moveAction != nullptr)
    {
        m_shape->stopAction(m_moveAction);
        onMoveOver(nullptr);
    }

    // ���û�����ȥ
    auto tmpDirection       =   (tmpTargetGird.getX() - m_shape->getPositionX()) * (tmpTargetGird.getX() - m_shape->getPositionX()) + 
         (tmpTargetGird.getY() - m_shape->getPositionY()) * (tmpTargetGird.getY() - m_shape->getPositionY());
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
        this->getShape()->playAction(NORMAL_ATTACK_ACTION, false, std::bind(&GameCharacter::onShortAttEffect, this, std::placeholders::_1));
    }
    else if (this->getCharacterType() == GAMECHARACTER_TYPE_ENUM_LONG_RANGE)
    {
        // Զ�̹�����λ������Ҫ���ض�������λ�ö������
        this->getShape()->playAction(NORMAL_ATTACK_ACTION, false, std::bind(&GameCharacter::onLongAttLaunch, this, std::placeholders::_1));
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

vector<GameCharacter*> GameCharacter::getCharactersInView()
{
    vector<GameCharacter*>  pRet;
    
    /**
    *  @_@ ���õ�ǰ�ڳ��ϵĽ�ɫ�������϶���С��̽����Χ����������������Ի��Ǳ������е�
    *  ��ɫ�ɣ����緶Χ��10����ô���ܵ�������������5 * 20 = 100������һ����ͼ�϶�û����ô����
    */
    auto tmpIterator    =   EntityMgr->getEntityMap()->begin();
    for (; tmpIterator != EntityMgr->getEntityMap()->end(); )
    {
        auto tmpCharacter   =   dynamic_cast<GameCharacter*>(tmpIterator->second);
        tmpIterator++;
        
        // �������Լ�
        if (tmpCharacter == this)
        {
            continue;
        }

        if (m_graph->isInScope(m_objectOnGrid.nodeIndex, tmpCharacter->getObjectOnGrid()->nodeIndex, m_attribute.getViewDistance()))
        {
            pRet.push_back(tmpCharacter);
        }
    }

    /**
    * ���ﰴ�վ����������������ǰ�� 
    */
    SortFunc tmpSortFunc    =   std::bind(&GameCharacter::charactersInViewSortFunc, 
        this, std::placeholders::_1, std::placeholders::_2);
    sort(pRet.begin(), pRet.end(), tmpSortFunc);

    return pRet;
}

bool GameCharacter::charactersInViewSortFunc( GameCharacter* character1, GameCharacter* character2 )
{
    auto tmpDistance1   =   
        m_graph->getDistanceInGrid(m_objectOnGrid.nodeIndex, character1->getObjectOnGrid()->nodeIndex);
    auto tmpDistance2   =   
        m_graph->getDistanceInGrid(m_objectOnGrid.nodeIndex, character2->getObjectOnGrid()->nodeIndex);
    return tmpDistance1 < tmpDistance2;
}

vector<GameCharacter*> GameCharacter::getFoeCharactersInView()
{
    auto pRet   =   getCharactersInView();
    
    // �޳����Լ�ͬ���͵ģ�Ҳ����ȥ���Լ��ˣ�ʣ�µľ��ǵ���
    auto tmpIterator    =   pRet.begin();
    while (tmpIterator != pRet.end())
    {
        if ((*tmpIterator)->getType() == this->getType())
        {
            tmpIterator =   pRet.erase(tmpIterator);
        }
        else
        {
            tmpIterator++;
        }
    }

    return pRet;
}

vector<int> GameCharacter::getFollowGridIndex( GameCharacter* other )
{
    vector<int> pRet;
    int tmpOtherGridIndex   =   other->getObjectOnGrid()->nodeIndex;

    // ���other�ǽ�ս�͵ģ������ȿ�ǰ
    auto tmpGridIndex   =   m_graph->getRightGridIndex(tmpOtherGridIndex, 2);
    pRet.push_back(m_graph->getTopGridIndex(tmpGridIndex, 2));
    pRet.push_back(m_graph->getBottomGridIndex(tmpGridIndex, 2));
    pRet.push_back(m_graph->getTopGridIndex(tmpGridIndex));
    pRet.push_back(m_graph->getBottomGridIndex(tmpGridIndex));

    // ǰб��
    tmpGridIndex    =   m_graph->getRightGridIndex(tmpOtherGridIndex);
    pRet.push_back(m_graph->getTopGridIndex(tmpGridIndex, 2));
    pRet.push_back(m_graph->getBottomGridIndex(tmpGridIndex, 2));

    // ����
    pRet.push_back(m_graph->getTopGridIndex(tmpOtherGridIndex, 2));
    pRet.push_back(m_graph->getBottomGridIndex(tmpOtherGridIndex, 2));

    // �����
    tmpGridIndex    =   m_graph->getLeftGridIndex(tmpOtherGridIndex, 2);
    pRet.push_back(m_graph->getTopGridIndex(tmpGridIndex, 2));
    pRet.push_back(m_graph->getBottomGridIndex(tmpGridIndex, 2));
    pRet.push_back(m_graph->getTopGridIndex(tmpGridIndex));
    pRet.push_back(m_graph->getBottomGridIndex(tmpGridIndex));

    // ��б�ǵ�
    tmpGridIndex    =   m_graph->getLeftGridIndex(tmpOtherGridIndex);
    pRet.push_back(m_graph->getTopGridIndex(tmpGridIndex, 2));
    pRet.push_back(m_graph->getBottomGridIndex(tmpGridIndex, 2));

    // �޳�����Ч�ĸ������
    auto tmpIterator    =   pRet.begin();
    while (tmpIterator != pRet.end())
    {
        if (*tmpIterator == INVALID_NODE_INDEX)
        {
            tmpIterator =   pRet.erase(tmpIterator);
        }
        else
        {
            tmpIterator++;
        }
    }

    // ������ý�ɫ�ľ��������У�����̵���ǰ��
    FollowGridSortFunc tmpFunc =   std::bind(&GameCharacter::followGridSortFunc, this, std::placeholders::_1, std::placeholders::_2);
    sort(pRet.begin(), pRet.end(), tmpFunc);

    return pRet;
}

bool GameCharacter::followGridSortFunc( int index1, int index2 )
{
    return m_graph->getDistanceInGrid(m_objectOnGrid.nodeIndex, index1) < m_graph->getDistanceInGrid(m_objectOnGrid.nodeIndex, index2);
}

void GameCharacter::sufferNormalAttack( GameCharacterAttribute& attribute )
{
    int tmpHp    =   m_attribute.getHp();
    // �޸�����
    m_attribute.sufferNormalAttack(attribute);
    tmpHp   -=  m_attribute.getHp();

    char tmpHpStr[20];
    sprintf(tmpHpStr, "-%d", tmpHp);

    if (this->getType() == GAME_ENTITY_TYPE_PLAYER_CHARACTER)
    {
        // �����ҽ�ɫ��Ʈ����
        m_shape->floatNumber(string(tmpHpStr), GameCharacterShape::FLOAT_NUMBER_YELLOW);
    }
    else
    {
        // ����Ʈ����
        m_shape->floatNumber(string(tmpHpStr), GameCharacterShape::FLOAT_NUMBER_RED);
    }

    // @_@ ֪ͨ����
    RefreshUIMsg tmpMsg(REFRESH_UI_EVENT_CHARACTER, this);
    UIViewMgr->refreshView(tmpMsg);
}

std::string GameCharacter::getIconSrc()
{
    string tmpSrc =   "character/icon/";
    switch (m_characterId)
    {
    case 1:
        {
            tmpSrc  +=  "003.png";
            break;
        }

    case 2:
        {
            tmpSrc  +=  "003.png";
            break;
        }

    case 3:
        {
            tmpSrc  +=  "004.png";
            break;
        }

    case 4:
        {
            tmpSrc  +=  "005.png";
            break;
        }

    case 5:
        {
            tmpSrc  +=  "006.png";
            break;
        }

    default:
        break;
    }

    return tmpSrc;
}

PathPlanner* const GameCharacter::getPathPlanner()
{
    return m_pathPlanner;
}
