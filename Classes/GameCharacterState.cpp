#include "GameCharacterState.h"
#include "GraphSearchAStar.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"

void GameCharacterIdleState::onEnter(GameCharacter* owner)
{
    _frameCount =   0;
    owner->getShape()->playAction(IDLE_ACTION);
}

void GameCharacterIdleState::update(GameCharacter* owner, float dm)
{
    _frameCount++;
    if (_frameCount >= enterToAutoFrame)
    {
        owner->getFSM()->changeState(GameCharacterAutoState::create());
    }
}

void GameCharacterIdleState::onExit(GameCharacter* owner)
{
    _frameCount =   0;
}

bool GameCharacterIdleState::onMessage(GameCharacter* owner, Telegram &msg)
{
    return false;
}

void GameCharacterMovingState::onEnter(GameCharacter* owner)
{
    if (movingDirection == MOVING_DIRECTION_LEFT)
    {
        owner->getShape()->faceToLeft();
        auto tmpLeftGridIndex = owner->getMapGrid()->getLeftGridIndex(owner->getObjectOnGrid()->nodeIndex);
        owner->moveToGridIndex(tmpLeftGridIndex, owner->getAttribute().getRate());
    }
    else if (movingDirection == MOVING_DIRECTION_RIGHT)
    {
        owner->getShape()->faceToRight();
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

    owner->getShape()->playAction(RUN_ACTION);
}

void GameCharacterMovingState::update(GameCharacter* owner, float dm)
{
    // ���ƶ���Ŀ���ʱ���л���֮ǰ��״̬
    if (!owner->isMoving())
    {
        owner->getFSM()->reverseState();
    }
}

void GameCharacterMovingState::onExit(GameCharacter* owner)
{

}

bool GameCharacterMovingState::onMessage(GameCharacter* owner, Telegram &msg)
{
    // �����ǰ���ƶ��У������κ���Ϣ��������
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
    // Ѱ�ҵ��ˣ�ȷ����һ�������λ�ã�Ȼ���л����ƶ�״̬��ȥ
    // �������еĳ��ϵ�ʵ�壬�ҵ����ˣ�ȷ���ĸ�����·�����
    vector<GameCharacter*>  tmpTargetCharacters;
    // ��ʱEntityMgr����������GameCharacter��
    auto tmpAllCharacters = EntityMgr->getEntityMap();
    for (auto tmpIterator = tmpAllCharacters->begin(); tmpIterator != tmpAllCharacters->end(); tmpIterator++)
    {
        if (owner->getType() == GAME_ENTITY_TYPE_PLAYER_CHARACTER && tmpIterator->second->getType() == GAME_ENTITY_TYPE_ENEMY_CHARACTER)
        {
            // ����ý�ɫ����ң�����Ŀǰ�ǵ���
            tmpTargetCharacters.push_back((GameCharacter*)tmpIterator->second);
        }
        if (owner->getType() == GAME_ENTITY_TYPE_ENEMY_CHARACTER && tmpIterator->second->getType() == GAME_ENTITY_TYPE_PLAYER_CHARACTER)
        {
            tmpTargetCharacters.push_back((GameCharacter*)tmpIterator->second);
        }
    }

    // �ж��Ƿ���һ�����˽��빥����Χ������еĻ����ͽ��빥��״̬���������ý�ɫ
    auto tmpInAttackDistanceCharacter = getCharacterInAttackDistance(owner, tmpTargetCharacters);
    if (tmpInAttackDistanceCharacter != nullptr)
    {
        // �л�������״̬
        auto tmpState       =   GameCharacterNormalAttack::create();
        tmpState->targetId  =   tmpInAttackDistanceCharacter->getId();
        owner->getFSM()->changeState(tmpState);
        return;
    }

    // Ѱ�ҹ�ȥ��·��
    vector<int> tmpTargetRoute;
    for (int i = 0; i < tmpTargetCharacters.size(); i++)
    {
        auto tmpRoute = owner->getMapGrid()->getRouteToTargetObj(owner->getObjectOnGrid(), tmpTargetCharacters[i]->getObjectOnGrid());
        if ((tmpRoute.size() > 0) && (tmpTargetRoute.size() == 0 || tmpRoute.size() < tmpTargetRoute.size()))
        {
            tmpTargetRoute  =   tmpRoute;
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
    else if (tmpTargetCharacters.size() > 0)
    {
        // ����Idle״̬һ��
        owner->getFSM()->changeState(GameCharacterIdleState::create());
    }
    else
    {
        // ����������˶��������ˣ��ͽ��뻶��ʤ��״̬
        // �Ѿ�����
        owner->getFSM()->changeState(GameCharacterWinState::create());
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

    // owner->getShape()->playAction(ATTACK_ACTION, false);
    owner->normalAttack(targetId);
}

void GameCharacterNormalAttack::update(GameCharacter* owner, float dm)
{
    if (owner->isNormalAttackFinish())
    {
        // ����������������л���Auto״̬
        //owner->getFSM()->changeState(GameCharacterAutoState::create());
        owner->getFSM()->reverseState();
    }
}

void GameCharacterNormalAttack::onExit(GameCharacter* owner)
{

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
            if (owner->getAttribute().sufferNormalAttack(tmpAttMsg->senderAtt).getHp() <= 0)
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
            tmpState->targetId  =   tmpTaget->getId();
            owner->getFSM()->changeState(tmpState);
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
    return true;
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