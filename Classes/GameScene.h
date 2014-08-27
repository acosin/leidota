#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "GameMap.h"
#include "PCInputManager.h"
#include "GameMainModel.h"

using namespace cocos2d;

/**
	 ��Ϸ������
*/
class GameScene : public Scene
{
public:
    bool init() override;

    CREATE_FUNC(GameScene);

protected:
    GameMap*    m_map;                  // ��ͼ

    PCInputManager* m_inputManager;     // �������������
    GameMainModel*  m_mainModel;        // ��Ϸ���߼�����
};

#endif