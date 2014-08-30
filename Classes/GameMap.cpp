#include "GameMap.h"
#include "EntityManager.h"

bool GameMap::init()
{
    if (!Layer::init())
    {
        return false;
    }

    // ��������
    m_bg4   =   Sprite::create("gamesky.png");
    m_bg4->setAnchorPoint(Vec2(0, 1));
    m_bg4->setPosition(0, 800);
    this->addChild(m_bg4);

    // �����ɽ
    m_bg3   =   Sprite::create("gamemountain.png");
    m_bg3->setAnchorPoint(Vec2(0, 0));
    this->addChild(m_bg3);

    // �������ڵı���
    m_bg2   =   Sprite::create("gameground.png");
    m_bg2->setAnchorPoint(Vec2(0, 0));
    this->addChild(m_bg2);

    // �������еĽ�ɫ������ӵ��������
    m_mapGrid   =   MapGrid::create(GRIDW, GRIDH, XNUM, YNUM);
    this->addChild(m_mapGrid);
    this->setContentSize(m_mapGrid->getContentSize());

    // ǰ��Ĳ�
    m_bg1    =   Sprite::create("gamegrass.png");
    m_bg1->setAnchorPoint(Vec2(0, 0));
    this->addChild(m_bg1);

    m_initPosX  =   0;

    this->scheduleUpdate();

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

GameMap::~GameMap()
{

}

void GameMap::setStartBgPos(int x)
{
    auto tmpBgSize      =   m_bg2->getContentSize();
    auto tmpVisiSize    =   Director::getInstance()->getVisibleSize();
    x   =   x < 0 ? 0 : x;
    x   =   x > tmpBgSize.width - tmpVisiSize.width ? tmpBgSize.width - tmpVisiSize.width : x;

    // ����λ��
    x   =   -x;
    m_bg1->setPositionX(x);
    m_bg2->setPositionX(x);
    m_bg3->setPositionX(x);
    m_bg4->setPositionX(x);

    m_initPosX  =   x;
}

void GameMap::cameraMove(int x)
{
    // ������Ե�ͼ�ƶ���x�ľ���
    auto tmpCharacterPosX    =   EntityMgr->getEntityFromID(1)->getShape()->getPositionX();

    // ɽ���ƶ���@_@�����ȼ�����������
    m_bg3->setPositionX(m_initPosX + -tmpCharacterPosX * MOUNTAIN_MOVE_SCALE);

    // ���
    m_bg4->setPositionX(m_initPosX + -tmpCharacterPosX * SKY_MOVE_SCALE);
}

void GameMap::update( float )
{
    cameraMove(0);
}
