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
    * ����������ڳ�ʼλ���ƶ��˶��٣�����������4������ƶ���ÿ��������ڴ��ƶ���ͬ�ľ��룬���������
    * �Ǹ������ǵ�
    */
    void cameraMove(int x);

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

    /**
    	 �������㽫ĳ�����ﰲ�õ�ĳ�������ϵ�
    */
    void placeOneCharacterToIndex(GameCharacter* character, int nodeIndex);

    /**
    * ÿһ֡�Ļص� 
    */
    void update(float);

    CREATE_FUNC(GameMap);

    /**
    	 ��ͼ�����һЩ�������Ժ�Ӧ�������ñ�����
    */
    const int GRIDW;
    const int GRIDH;
    const int XNUM;
    const int YNUM;

protected:

    GameMap():GRIDW(64),GRIDH(60),XNUM(65),YNUM(5),MOUNTAIN_MOVE_SCALE(0.5f),SKY_MOVE_SCALE(0.2f){}
    ~GameMap();

    /**
    * ���ɵ�ͼ�ı�����4�㣬����ÿһ�㶼��������ͼƬƴ�ɵ�
    */
    Node*       m_bg1;               // �������ڵĵ���
    Node*       m_bg2;               // �����ɽ
    Node*       m_bg3;               // ���������

    MapGrid*    m_mapGrid;          // ��ͼ���湩���ƶ�������

    /**
    * Ϊ���γɷֲ㣬�����������ƶ��ľ�����������ƶ�����ı�ֵ 
    */
    const float MOUNTAIN_MOVE_SCALE;
    const float SKY_MOVE_SCALE;

    /**
    * ��ʱ��¼��ʼ��ʱ���x 
    */
    float   m_initPosX;                 // ��ͼ��ʼ��ʱ���x
};

#endif