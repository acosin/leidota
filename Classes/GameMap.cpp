#include "GameMap.h"

bool GameMap::init()
{
    if (!Layer::init())
    {
        return false;
    }

    // ��ӱ���ͼ
    m_bg    =   Sprite::create("gamemapbg.png");
    m_bg->setAnchorPoint(Vec2(0, 0));
    this->addChild(m_bg);

    // �������еĽ�ɫ������ӵ��������
    m_mapGrid   =   MapGrid::create(GRIDW, GRIDH, XNUM, YNUM);
    this->addChild(m_mapGrid);

    return true;
}

void GameMap::placeCharacter1(GameCharacter* character)
{
    placeOneCharacterToIndex(character, 0);
}

void GameMap::placeCharacter2(GameCharacter* character)
{
    placeOneCharacterToIndex(character, 2 * XNUM);
}

void GameMap::placeCharacter3(GameCharacter* character)
{
    placeOneCharacterToIndex(character, 4 * XNUM);
}

void GameMap::placeOneCharacterToIndex(GameCharacter* character, int nodeIndex)
{
    // ������ʱ��������
    auto tmpGrid = character->getObjectOnGrid();
    tmpGrid->placeType  =   PLACEHOLDER_TYPE_CROSS;
    tmpGrid->nodeIndex  =   nodeIndex;

    m_mapGrid->addGameCharacter(character);
}

void GameMap::placeEnemyCharacter1(GameCharacter* character)
{
    placeOneCharacterToIndex(character, XNUM - 1);
}

void GameMap::placeEnemyCharacter2(GameCharacter* character)
{
    placeOneCharacterToIndex(character, 3 * XNUM - 1);
}

void GameMap::placeEnemyCharacter3(GameCharacter* character)
{
    placeOneCharacterToIndex(character, 5 * XNUM - 1);
}