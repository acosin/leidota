#ifndef __GAME_MAP_H__
#define __GAME_MAP_H__

#include "cocos2d.h"
#include "MapGrid.h"
#include "GameCharacter.h"

using namespace cocos2d;

/**
	 ��Ϸ��ͼ��ͬʱ�����������
*/
class GameMap : public Layer
{
public:
    bool init () override;

    /**
    	 �������͵Ĳ��ø㣬�ɴ�̶����ˣ�@_@ �Ժ��ٸ��������������������������
         ��Ӧ���������
    */
    void placeCharacter1(GameCharacter* character);
    void placeCharacter2(GameCharacter* character);
    void placeCharacter3(GameCharacter* character);

    /**
    	 ����������ηţ��Ժ�Ҳ��Ҫͨ���ض��ķ�ʽ�������FUCKֱ�ӷŵ��̶���λ����
    */
    void placeEnemyCharacter1(GameCharacter* character);
    void placeEnemyCharacter2(GameCharacter* character);
    void placeEnemyCharacter3(GameCharacter* character);

    CREATE_FUNC(GameMap);

protected:

    GameMap():GRIDW(64),GRIDH(60),XNUM(20),YNUM(5){}
    ~GameMap();

    /**
    	 �������㽫ĳ�����ﰲ�õ�ĳ�������ϵ�
    */
    void placeOneCharacterToIndex(GameCharacter* character, int nodeIndex);

    Node*       m_bg;               // ����ͼƬ
    MapGrid*    m_mapGrid;          // ��ͼ���湩���ƶ�������

    /**
    	 ��ͼ�����һЩ�������Ժ�Ӧ�������ñ�����
    */
    const int GRIDW;
    const int GRIDH;
    const int XNUM;
    const int YNUM;
};

#endif