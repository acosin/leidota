#include "GameCharacterState.h"
#include "GraphSearchAStar.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "GameTeam.h"
#include "UIViewManager.h"

// һ�������жϵ�ǰ�Ƿ���ĳ��״̬�ĺ�
#define ISINSTATE(state)    dynamic_cast<state*>(owner->getFSM()->getCurrentState()) != nullptr

// �ж�֮ǰ��״̬
#define ISPREINSTATE(state)     dynamic_cast<state*>(owner->getFSM()->getPreState()) != nullptr

void GameCharacterIdleState::onEnter(GameCharacter* owner)
{
    owner->getShape()->playAction(IDLE_ACTION);
}

void GameCharacterIdleState::update(GameCharacter* owner, float dm)
{
    if (m_reverseStateFrameCount > 0)
    {
        m_reverseStateFrameCount--;
    }
    
    if (m_reverseStateFrameCount == 0)
    {
        owner->getFSM()->reverseState();
    }
}

void GameCharacterIdleState::onExit(GameCharacter* owner)
{
    m_reverseStateFrameCount    =   -1;
}

bool GameCharacterIdleState::onMessage(GameCharacter* owner, Telegram &msg)
{
    return false;
}

void GameCharacterMovingState::onEnter(GameCharacter* owner)
{
    if (movingDirection == MOVING_DIRECTION_LEFT)
    {
        auto tmpLeftGridIndex = owner->getMapGrid()->getLeftGridIndex(owner->getObjectOnGrid()->nodeIndex);
        owner->moveToGridIndex(tmpLeftGridIndex, owner->getAttribute().getRate());
    }
    else if (movingDirection == MOVING_DIRECTION_RIGHT)
    {
        auto tmpRightGridIndex = owner->getMapGrid()->getRightGridIndex(owner->getObjectOnGrid()->nodeIndex);
        owner->moveToGridIndex(tmpRightGridIndex, owner->getAttribute().getRate());
    }
    else if (movingDirection == MOVING_DIRECTION_TOP)
    {
        auto tmpTopGridIndex = owner->getMapGrid()->getTopGridIndex(owner->getObjectOnGrid()->nodeIndex);
        owner->moveToGridIndex(tmpTopGridIndex, owner->getAttribute().getRate());
    }
    else
    {
        auto tmpBottomIndex = owner->getMapGrid()->getBottomGridIndex(owner->getObjectOnGrid()->nodeIndex);
        owner->moveToGridIndex(tmpBottomIndex, owner->getAttribute().getRate());
    }

    // ͬʱ��Ҫ��֪�����Լ������ƶ�
    if (owner->getTeam() != nullptr)
    {
        owner->getTeam()->playerMoving(owner);
    }
}

void GameCharacterMovingState::update(GameCharacter* owner, float dm)
{
    // ���ƶ���Ŀ���ʱ���л���֮ǰ��״̬
    if (!owner->isMoving())
    {
        if (ISPREINSTATE(GameCharacterIdleState))
        {
            owner->getFSM()->changeState(GameCharacterAutoState::create());
        }
        else
        {
            owner->getFSM()->reverseState();
        }
    }
}

void GameCharacterMovingState::onExit(GameCharacter* owner)
{

}

bool GameCharacterMovingState::onMessage(GameCharacter* owner, Telegram &msg)
{
    // �����ǰ���ƶ��У������κ���Ϣ��������
    if (msg.type == TELEGRAM_ENUM_NORMAL_ATTACK)
    {
        return false;
    }
    return true;
}

void GameCharacterAutoState::onEnter(GameCharacter* owner)
{
    if (owner->getShape()->isNotInAnimation())
    {
        owner->getShape()->playAction(IDLE_ACTION);
    }
    update(owner, 0);
}

void GameCharacterAutoState::update(GameCharacter* owner, float dm)
{
    vector<GameCharacter*> tmpTargetCharacters = owner->getFoeCharactersInView();   // ��Χ�ڵ����е���
    
    if (tmpTargetCharacters.size() == 0)
    {
        // ���ӷ�Χ��û�е��ˣ�����idle״̬��������֮֡���ٻ���
        auto tmpState = GameCharacterIdleState::create();
        tmpState->setReverseStateFrameCount(20);
        owner->getFSM()->changeState(tmpState);
    }
    else
    {
        // �ڿ��ӷ�Χ���ҵ�����
        // �ж��Ƿ���һ�����˽��빥����Χ������еĻ����ͽ��빥��״̬���������ý�ɫ
        auto tmpInAttackDistanceCharacter = getCharacterInAttackDistance(owner, tmpTargetCharacters);
        if (tmpInAttackDistanceCharacter != nullptr)
        {
            if (!owner->canNormalAttack())
            {
                // ��Ҫ�ȴ�����֡
                auto tmpState   =   GameCharacterIdleState::create();
                tmpState->setReverseStateFrameCount(owner->getNextNormatAttackLeftCount());
                owner->getFSM()->changeState(tmpState);
                return;
            }

            // �л�������״̬
            auto tmpState       =   GameCharacterNormalAttack::create();
            tmpState->targetId  =   tmpInAttackDistanceCharacter->getId();
            owner->getFSM()->changeState(tmpState);
            return;
        }

        // Ѱ�ҹ�ȥ��·����ֻҪ�ҵ���һ��·��
        vector<int> tmpTargetRoute;
        for (int i = 0; i < tmpTargetCharacters.size(); i++)
        {
            tmpTargetRoute = owner->getMapGrid()->getRouteToTargetObj(owner->getObjectOnGrid(), tmpTargetCharacters[i]->getObjectOnGrid());
            if (tmpTargetRoute.size() > 0)
            {
                break;
            }
        }

        // �������·��ѡ����һ��������ƶ�
        if (tmpTargetRoute.size() > 0)
        {
            auto tmpTargetGridIndex =   tmpTargetRoute[1];
            // �л����ƶ�״̬������Ѱ�ҷ���
            auto tmpState = GameCharacterMovingState::create();
            if (tmpTargetGridIndex == owner->getMapGrid()->getLeftGridIndex(owner->getObjectOnGrid()->nodeIndex))
            {
                tmpState->movingDirection   =   GameCharacterMovingState::MOVING_DIRECTION_LEFT;
            }
            else if (tmpTargetGridIndex == owner->getMapGrid()->getTopGridIndex(owner->getObjectOnGrid()->nodeIndex))
            {
                tmpState->movingDirection   =   GameCharacterMovingState::MOVING_DIRECTION_TOP;
            }
            else if (tmpTargetGridIndex == owner->getMapGrid()->getRightGridIndex(owner->getObjectOnGrid()->nodeIndex))
            {
                tmpState->movingDirection   =   GameCharacterMovingState::MOVING_DIRECTION_RIGHT;
            }
            else
            {
                tmpState->movingDirection   =   GameCharacterMovingState::MOVING_DIRECTION_BOTTOM;
            }
            owner->getFSM()->changeState(tmpState);
        }
        else
        {
            // ����Idle״̬һ��
            auto tmpState   =   GameCharacterIdleState::create();
            tmpState->setReverseStateFrameCount(20);
            owner->getFSM()->changeState(tmpState);
        }
    }
}

void GameCharacterAutoState::onExit(GameCharacter* owner)
{

}

bool GameCharacterAutoState::onMessage(GameCharacter* owner, Telegram &msg)
{
    return false;
}

GameCharacter* GameCharacterAutoState::getCharacterInAttackDistance(GameCharacter* owner, vector<GameCharacter*>& targets)
{
    for (int i = 0; i < targets.size(); i++)
    {
        if (isInAttackDistance(owner, targets[i]))
        {
            return targets[i];
        }
    }

    return nullptr;
}

bool GameCharacterAutoState::isInAttackDistance(GameCharacter* owner, GameCharacter* target)
{
    return owner->isInAttackDistance(target);
}

void GameCharacterNormalAttack::onEnter(GameCharacter* owner)
{
    // ��������
    GameCharacter* target   =   (GameCharacter*)EntityMgr->getEntityFromID(targetId);
    if (target == nullptr)
    {
        owner->getFSM()->changeState(GameCharacterAutoState::create());
        return;
    }

    if (owner->getMapGrid()->testIsAtLeft(owner->getObjectOnGrid()->nodeIndex, target->getObjectOnGrid()->nodeIndex))
    {
        owner->getShape()->faceToRight();
    }
    else
    {
        owner->getShape()->faceToLeft();
    }

    // �����ǰ�Ľ����������ǣ����ڱ�����Ŀ������ѡ��⻷
    if (EntityMgr->getmainEntity() == owner)
    {
        target->getShape()->showHalo(GameCharacterShape::HALO_RED);
        RefreshUIMsg tmpMsg(REFRESH_UI_EVENT_ATTACK_CHARACTER, target);
        UIViewMgr->refreshView(tmpMsg);
    }

    owner->normalAttack(targetId);
}

void GameCharacterNormalAttack::update(GameCharacter* owner, float dm)
{
    if (owner->isNormalAttackFinish())
    {
        if (ISPREINSTATE(GameCharacterMovingState))
        {
            owner->getFSM()->changeState(GameCharacterAutoState::create());
        }
        else
        {
            owner->getFSM()->reverseState();
        }
    }
}

void GameCharacterNormalAttack::onExit(GameCharacter* owner)
{
    owner->exitNormalAttack();

    // ����Է���ɫ���ڣ����뿪ս��ʱ�������ѡ��⻷
    auto tmpTarget  =   dynamic_cast<GameCharacter*>(EntityMgr->getEntityFromID(targetId));
    if (tmpTarget != nullptr)
    {
        tmpTarget->getShape()->hideHalo();
    }
    RefreshUIMsg tmpMsg(REFRESH_UI_EVENT_ATTACK_CHARACTER, nullptr);
    UIViewMgr->refreshView(tmpMsg);
}

bool GameCharacterNormalAttack::onMessage(GameCharacter* owner, Telegram &msg)
{
    return false;
}

void GameCharacterGlobalState::onEnter(GameCharacter* owner)
{

}

void GameCharacterGlobalState::update(GameCharacter* owner, float dm)
{
    
}

void GameCharacterGlobalState::onExit(GameCharacter* owner)
{

}

bool GameCharacterGlobalState::onMessage(GameCharacter* owner, Telegram &msg)
{
    switch (msg.type)
    {
    case TELEGRAM_ENUM_USER_MOVE_LEFT:
        {
            // �ж��Ƿ���������ƶ�
            auto tmpLeftGridIndex   =   owner->getMapGrid()->getLeftGridIndex(owner->getObjectOnGrid()->nodeIndex);
            if (tmpLeftGridIndex != INVALID_NODE_INDEX)
            {
                // ���Ƴ��Լ���ռ�е�����Ȼ���ѯ�Ƿ���Թ�ȥ��������ԣ����ƶ���ȥ
                owner->getMapGrid()->removeObjectFromGrid(owner->getObjectOnGrid());
                auto tmpRoute = GraphSearchAStar::search(*owner->getMapGrid(), owner->getObjectOnGrid()->nodeIndex, tmpLeftGridIndex, MapGrid::calculateH);
                if (tmpRoute.size() > 0)
                {
                    // ����ҵ���·�����л��������ƶ�״̬
                    auto tmpState               =   GameCharacterMovingState::create();
                    tmpState->movingDirection   =   GameCharacterMovingState::MOVING_DIRECTION_LEFT;
                    owner->getFSM()->changeState(tmpState);
                }
                else
                {
                    owner->getMapGrid()->addObjectToGrid(owner->getObjectOnGrid());
                }
            }

            return true;
        }

    case TELEGRAM_ENUM_USER_MOVE_RIGHT:
        {
            // �ж��Ƿ���������ƶ�
            auto tmpLeftGridIndex   =   owner->getMapGrid()->getRightGridIndex(owner->getObjectOnGrid()->nodeIndex);
            if (tmpLeftGridIndex != INVALID_NODE_INDEX)
            {
                // ���Ƴ��Լ���ռ�е�����Ȼ���ѯ�Ƿ���Թ�ȥ��������ԣ����ƶ���ȥ
                owner->getMapGrid()->removeObjectFromGrid(owner->getObjectOnGrid());
                auto tmpRoute = GraphSearchAStar::search(*owner->getMapGrid(), owner->getObjectOnGrid()->nodeIndex, tmpLeftGridIndex, MapGrid::calculateH);
                if (tmpRoute.size() > 0)
                {
                    auto tmpState               =   GameCharacterMovingState::create();
                    tmpState->movingDirection   =   GameCharacterMovingState::MOVING_DIRECTION_RIGHT;
                    owner->getFSM()->changeState(tmpState);
                }
                else
                {
                    owner->getMapGrid()->addObjectToGrid(owner->getObjectOnGrid());
                }
            }

            return true;
        }

    case TELEGRAM_ENUM_NORMAL_ATTACK:
        {
            // �ܵ���ͨ����������һ���˺�
            auto tmpAttMsg  =   (TelegramNormalAttack*)&msg;
            owner->sufferNormalAttack(tmpAttMsg->senderAtt);
            if (owner->getAttribute().getHp() <= 0)
            {
                // ����������
                owner->getFSM()->changeState(GameCharacterDieState::create());
            }

            return true;
        }

    case TELEGRAM_ENUM_USER_CHANGE_TARGET:
        {
            // �л�����Ŀ��
            auto tmpState   =   GameCharacterPursueState::create();
            // ��һ������
            auto tmpTaget   =   EntityMgr->getOneEntity(GAME_ENTITY_TYPE_ENEMY_CHARACTER);
            if (tmpTaget != nullptr)
            {
                tmpState->targetId  =   tmpTaget->getId();
                owner->getFSM()->changeState(tmpState); 
            }
            else
            {
                owner->getFSM()->changeState(GameCharacterAutoState::create());
            }
            
            return true;
        }

    case TELEGRAM_ENUM_TEAM_IDLE:                       // ����֪ͨ������ͣ�ж�
        {
            owner->getFSM()->changeState(GameCharacterIdleState::create());
            return true;
        }

    case TELEGRAM_ENUM_TEAM_FREE_COMBAT:                // ����֪ͨ��������ս��
        {
            owner->getFSM()->changeState(GameCharacterAutoState::create());
            return true;
        }

    case TELEGRAM_ENUM_TEAM_CELEBRATE:                  // ����֪ͨ������ף
        {
            owner->getFSM()->changeState(GameCharacterWinState::create());
            return true;
        }

    case TELEGRAM_ENUM_TEAM_FOLLOW_SPECIFIED_PLAYER:    // ����֪ͨ����ȥ����ĳ����ɫ
        {
            auto tmpTarget  =   (GameCharacter*)msg.extraInfo;
            if (owner != tmpTarget)
            {
                auto tmpState   =   GameCharacterFollowOne::create();
                tmpState->followTargetId    =   tmpTarget->getId();
                owner->getFSM()->changeState(tmpState);
            }
            return true;
        }
        
    default:
        break;
    }

    return false;
}

void GameCharacterPursueState::onEnter(GameCharacter* owner)
{

}

void GameCharacterPursueState::update(GameCharacter* owner, float dm)
{
    // ����׷��״̬��ʱ����Ѱ��Ҫ׷����Ŀ�꣬���Ŀ�겻���ˣ����л���Auto
    auto tmpTargetCharacter = (GameCharacter*)EntityMgr->getEntityFromID(targetId);
    if (tmpTargetCharacter == nullptr)
    {
        owner->getFSM()->changeState(GameCharacterAutoState::create());
        return;
    }

    // ����ڹ�����Χ�ڣ���ֱ�ӹ���
    if (owner->isInAttackDistance(tmpTargetCharacter))
    {
        // �鿴�����Ƿ���Թ���
        if (!owner->canNormalAttack())
        {
            // ��Ҫ�ȴ�����֡
            auto tmpState   =   GameCharacterIdleState::create();
            tmpState->setReverseStateFrameCount(owner->getNextNormatAttackLeftCount());
            owner->getFSM()->changeState(tmpState);
            return;
        }

        // �л�������״̬
        auto tmpState       =   GameCharacterNormalAttack::create();
        tmpState->targetId  =   targetId;
        owner->getFSM()->changeState(tmpState);
        return;
    }

    // Ѱ�ҹ�ȥ��·
    auto tmpRoute = owner->getMapGrid()->getRouteToTargetObj(owner->getObjectOnGrid(), 
        tmpTargetCharacter->getObjectOnGrid());
    if (tmpRoute.size() == 0)
    {
        // ����Ҳ���·��������Auto
        owner->getFSM()->changeState(GameCharacterAutoState::create());
    }
    else
    {
        // �ҵ���ǰ����·�����ƶ���ȥ
        auto tmpTargetGridIndex =   tmpRoute[1];
        auto tmpMagGrid         =   owner->getMapGrid();
        auto tmpOwnerGridIndex  =   owner->getObjectOnGrid()->nodeIndex;
        auto tmpState           =   GameCharacterMovingState::create();   
        if (tmpMagGrid->testIsAtTop(tmpTargetGridIndex, tmpOwnerGridIndex))
        {
            tmpState->movingDirection   =   GameCharacterMovingState::MOVING_DIRECTION_TOP;
        }
        else if (tmpMagGrid->testIsAtRight(tmpTargetGridIndex, tmpOwnerGridIndex))
        {
            tmpState->movingDirection   =   GameCharacterMovingState::MOVING_DIRECTION_RIGHT;
        }
        else if (tmpMagGrid->testIsAtBottom(tmpTargetGridIndex, tmpOwnerGridIndex))
        {
            tmpState->movingDirection   =   GameCharacterMovingState::MOVING_DIRECTION_BOTTOM;
        }
        else
        {
            tmpState->movingDirection   =   GameCharacterMovingState::MOVING_DIRECTION_LEFT;
        }
        owner->getFSM()->changeState(tmpState);
    }
}

void GameCharacterPursueState::onExit(GameCharacter* owner)
{

}

bool GameCharacterPursueState::onMessage(GameCharacter* owner, Telegram &msg)
{
    return false;
}

void GameCharacterWinState::onEnter(GameCharacter* owner)
{
    owner->getShape()->playAction(WIN_ACTION);
}

void GameCharacterWinState::update(GameCharacter* owner, float dm)
{

}

void GameCharacterWinState::onExit(GameCharacter* owner)
{

}

bool GameCharacterWinState::onMessage(GameCharacter* owner, Telegram &msg)
{
    // ������ʤ��״̬��ʱ������û���������Ϣ��������
    return msg.type >= TELEGRAM_ENUM_USER_MOVE_RIGHT && msg.type <= TELEGRAM_ENUM_USER_CHANGE_TARGET;
}

void GameCharacterDieState::onEnter(GameCharacter* owner)
{
    owner->getShape()->stopAllActions();
}

void GameCharacterDieState::update(GameCharacter* owner, float dm)
{
    owner->die();
}

void GameCharacterDieState::onExit(GameCharacter* owner)
{

}

bool GameCharacterDieState::onMessage(GameCharacter* owner, Telegram &msg)
{
    return true;
}

void GameCharacterFollowOne::onEnter( GameCharacter* owner )
{
    auto tmpMap         =   owner->getMapGrid();
    auto tmpSourceIndex =   owner->getObjectOnGrid()->nodeIndex;

    // ����һ���������λ�õ�·��
    auto tmpTargetCharacter =   dynamic_cast<GameCharacter*>(EntityMgr->getEntityFromID(followTargetId));
    if (tmpTargetCharacter == nullptr)
    {
        // ˵������Ŀ��û���ˣ�����Auto
        owner->getFSM()->changeState(GameCharacterAutoState::create());
        return;
    }

    // ��ȡ����λ��
    auto tmpTargetGrids =   owner->getFollowGridIndex(tmpTargetCharacter);
    if (tmpTargetGrids.size() == 0)
    {
        // ���û�и���λ����
        owner->getFSM()->changeState(GameCharacterAutoState::create());
        return;
    }
    
    // ������ھ��ڸ���λ���У��Ͳ��ö�
    for (int i = 0; i < tmpTargetGrids.size(); i++)
    {
        if (tmpTargetGrids[i] == tmpSourceIndex)
        {
            owner->getFSM()->changeState(GameCharacterAutoState::create());
            return;
        }
    }

    // ��ȡ��ȥ��·��
    vector<int> tmpRoute;
    for (int i = 0; i < tmpTargetGrids.size(); i++)
    {
        // @_@ �����Ȱ��Լ�ռ�ÿ�λ�Ƴ�
        tmpMap->removeObjectFromGrid(owner->getObjectOnGrid());
        tmpRoute    =   GraphSearchAStar::search(*tmpMap, tmpSourceIndex, tmpTargetGrids[i], MapGrid::calculateH);
        tmpMap->addObjectToGrid(owner->getObjectOnGrid());
        if (tmpRoute.size() != 0)
        {
            break;
        }
    }

    // �����ƶ���ȥ
    auto tmpState   =   GameCharacterMovingState::create();
    if (tmpRoute[1] == tmpMap->getLeftGridIndex(tmpSourceIndex))
    {
        tmpState->movingDirection   =   GameCharacterMovingState::MOVING_DIRECTION_LEFT;
    }
    else if (tmpRoute[1] == tmpMap->getTopGridIndex(tmpSourceIndex))
    {
        tmpState->movingDirection   =   GameCharacterMovingState::MOVING_DIRECTION_TOP;
    }
    else if (tmpRoute[1] == tmpMap->getRightGridIndex(tmpSourceIndex))
    {
        tmpState->movingDirection   =   GameCharacterMovingState::MOVING_DIRECTION_RIGHT;
    }
    else
    {
        tmpState->movingDirection   =   GameCharacterMovingState::MOVING_DIRECTION_BOTTOM;
    }
    owner->getFSM()->changeState(tmpState);
}