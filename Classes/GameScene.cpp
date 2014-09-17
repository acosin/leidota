#include "GameScene.h"
#include "GameCharacter.h"
#include "TeamManager.h"
#include "GameTeamState.h"
#include "EntityManager.h"
#include "BattleUI.h"

#define ADDPCINPUT

bool GameScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    m_celebrateFrameCount   =   0;
    m_map   =   GameMap::create();
    this->addChild(m_map);

    /**
    	 ���ˣ���ʱ�ʹ˴�����Ϸ��ɫ��ӵ���ͼ��
    */

    auto tmpRole1 = GameCharacter::create(3);
    tmpRole1->setType(GAME_ENTITY_TYPE_PLAYER_CHARACTER);
    tmpRole1->retain();
    m_map->placeCharacter1(tmpRole1);
    tmpRole1->getSteeringBehaviros()->separationOn();
    tmpRole1->getSteeringBehaviros()->wallAvoidanceOn();
    tmpRole1->getSteeringBehaviros()->keepFormationOn();
    tmpRole1->getMovingEntity().setFormationPosId(0);

    auto tmpRole2 = GameCharacter::create(1);
    tmpRole2->setType(GAME_ENTITY_TYPE_PLAYER_CHARACTER);
    tmpRole2->retain();
    m_map->placeCharacter2(tmpRole2);
    tmpRole2->getSteeringBehaviros()->separationOn();
    tmpRole2->getSteeringBehaviros()->wallAvoidanceOn();
    tmpRole2->getSteeringBehaviros()->keepFormationOn();
    tmpRole2->getMovingEntity().setFormationPosId(3);

    auto tmpRole3 = GameCharacter::create(1);
    tmpRole3->setType(GAME_ENTITY_TYPE_PLAYER_CHARACTER);
    tmpRole3->retain();
    m_map->placeCharacter3(tmpRole3);
    tmpRole3->getSteeringBehaviros()->separationOn();
    tmpRole3->getSteeringBehaviros()->wallAvoidanceOn();
    tmpRole3->getSteeringBehaviros()->keepFormationOn();
    tmpRole3->getMovingEntity().setFormationPosId(4);

    // @_@ ����Ϊһ������
    auto tmpTeam1   =   GameTeam::create();
    tmpTeam1->setLeaderId(tmpRole2);
    tmpTeam1->addMercenaryIds(tmpRole1);
    tmpTeam1->addMercenaryIds(tmpRole3);
    TeamMgr->registerTeam(tmpTeam1);

    tmpTeam1->getTeamFormation().setFormationAnchor(Vec2(1000, 260));

    m_mainModel     =   new GameMainModel();
    m_mainModel->setMainGameCharacter(tmpRole2);
    
#ifdef ADDPCINPUT                   // ��������ʹ��PC��������
    m_pcInputManager  =   new PCInputManager();
    m_pcInputManager->setDelegate(m_mainModel);
    m_pcInputManager->init();
#endif

    /**
    	 ���ﻹ��Ҫ����3������
    */
/**
    auto tmpRole4 = GameCharacter::create(4);
    tmpRole4->setType(GAME_ENTITY_TYPE_ENEMY_CHARACTER);
    tmpRole4->retain();
    tmpRole4->getShape()->faceToLeft();
    m_map->placeEnemyCharacter1(tmpRole4);

    auto tmpRole5 = GameCharacter::create(4);
    tmpRole5->setType(GAME_ENTITY_TYPE_ENEMY_CHARACTER);
    tmpRole5->retain();
    tmpRole5->getShape()->faceToLeft();
    m_map->placeEnemyCharacter2(tmpRole5);

    auto tmpRole6 = GameCharacter::create(4);
    tmpRole6->setType(GAME_ENTITY_TYPE_ENEMY_CHARACTER);
    tmpRole6->retain();
    tmpRole6->getShape()->faceToLeft();
    m_map->placeEnemyCharacter3(tmpRole6);

    // ����Ҳ��Ϊһ��
    auto tmpTeam2   =   GameTeam::create();
    tmpTeam2->addMercenaryIds(tmpRole4);
    tmpTeam2->addMercenaryIds(tmpRole5);
    tmpTeam2->addMercenaryIds(tmpRole6);
    TeamMgr->registerTeam(tmpTeam2);
*/
    /**
    * ���ӵ�����һ����� 
    */
/**
    auto tmpRole7 = GameCharacter::create(5);
    tmpRole7->setType(GAME_ENTITY_TYPE_ENEMY_CHARACTER);
    tmpRole7->retain();
    m_map->placeOneCharacterToIndex(tmpRole7, 20);

    auto tmpRole8 = GameCharacter::create(4);
    tmpRole8->setType(GAME_ENTITY_TYPE_ENEMY_CHARACTER);
    tmpRole8->retain();
    m_map->placeOneCharacterToIndex(tmpRole8, 20 + 3 * m_map->XNUM);

    auto tmpTeam3   =   GameTeam::create();
    tmpTeam3->addMercenaryIds(tmpRole7);
    tmpTeam3->addMercenaryIds(tmpRole8);
    TeamMgr->registerTeam(tmpTeam3);

    auto tmpRole9   =   GameCharacter::create(4);
    tmpRole9->setType(GAME_ENTITY_TYPE_ENEMY_CHARACTER);
    tmpRole9->retain();
    //tmpTeam3->addMercenaryIds(tmpRole9);
    m_map->placeOneCharacterToIndex(tmpRole9, 9);
*/
    // ս��UI
    auto tmpUI  =   BattleUI::create();
    //this->addChild(tmpUI);
    // �����ֻ�����ģ�Ҳ������Ļ���뷽ʽ
    m_mobileInputManager    =   tmpUI;
    m_mobileInputManager->setDelegate(m_mainModel);

    return true;
}