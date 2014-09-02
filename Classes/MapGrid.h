#ifndef __MAP_GRID_H__
#define __MAP_GRID_H__

#include "cocos2d.h"
#include "GridGraph.h"

class GameCharacter;

using namespace cocos2d;
using namespace std;

/**
	 ռλ��ʽ������ֻռһ�����ӣ�ռһ��ʮ�ּܷ�ʽ��
*/
enum PlaceHolderTypeEnum
{
    PLACEHOLDER_TYPE_ONE,           // ֻռ�е�ǰһ������
    PLACEHOLDER_TYPE_CROSS          // ռ��һ��ʮ�ּܵ�
};

/**
	 ���������ƶ������壬��ͬʱռ�кü������ӣ����в�ͬ��ռ���ӵķ�ʽ
*/
class ObjectOnMapGrid
{
public:
    int                     nodeIndex;              // ��ǰ���ڵĽڵ�
    PlaceHolderTypeEnum     placeType;              // ռλ��ʽ
};

/**
	 ��ͼ��������ʵ�ֽ�ɫ���ƶ���ͬʱ�־�������·���Ĺ���
*/
class MapGrid : public Layer, public GridGraph
{
public:
    bool init() override;

    static MapGrid* create(int gridW, int gridH, int xNum, int yNum)
    {
        auto pRet   =   new MapGrid(gridW, gridH, xNum, yNum);
        if (pRet && pRet->init())
        {
            pRet->autorelease();
            return pRet;
        }

        return nullptr;
    }

    /**
    	 �����������һ��ռ������Ķ�����Ҫ��һ�������Ѿ���������Ҫ����
    */
    void addObjectToGrid(ObjectOnMapGrid* object);

    /**
    	 ���������Ƴ�һ��ռ������Ķ��󣬱�����ĳ������Ҫ��ʼѰ·֮ǰ���Ȱ��Լ����������Ƴ�
         Ȼ����Ѱ·��Ȼ��������������ռλ��
    */
    void removeObjectFromGrid(ObjectOnMapGrid* object);

    /**
    	 �������������Ϸ��ɫ
    */
    void addGameCharacter(GameCharacter* character);

    /**
    	 ������ȡĳ�����ӵĸ����ĸ�����ţ����û�У��ͷ���INVALID_NODE_INDEX
    */
    int getLeftGridIndex(int nodeIndex, int distance = 1);
    int getTopGridIndex(int nodeIndex, int distance = 1);
    int getRightGridIndex(int nodeIndex, int distance = 1);
    int getBottomGridIndex(int nodeIndex, int distance = 1);

    int getLeftTopGridIndex(int nodeIndex);
    int getRightTopGridIndex(int nodeIndex);
    int getRightBottomGridIndex(int nodeIndex);
    int getLeftBottomGridIndex(int nodeIndex);

    /**
    	 ���ش������Ŀ���·�������յ�Ŀ�������ſ϶�����target��nodeIndex�����Ҫ����
         ռλ��ʽ�Լ���ǰ����Χ��ռλ��ʽ������
    */
    vector<int> getRouteToTargetObj(ObjectOnMapGrid* source, ObjectOnMapGrid* target);

    /**
    	 ���������������ӵ�
    */
    static float calculateH(SparseGraph& grap, int sourceIndex, int targetIndex);

    /**
    	 �������������Ƿ���һ��ˮƽ����
    */
    bool testTwoIndexInOneHorizon(int nodeIndex1, int nodeIndex2);

    /**
    	 ����nodeIndex1�Ƿ���nodeIndex2�����
    */
    bool testIsAtLeft(int nodeIndex1, int nodeIndex2);
    /**
    	 ����nodeIndex1�Ƿ���nodeIndex2������
    */
    bool testIsAtTop(int nodeIndex1, int nodeIndex2);
    /**
    	 ����nodeIndex1�Ƿ���nodeIndex2���ұ�
    */
    bool testIsAtRight(int nodeIndex1, int nodeIndex2);
    /**
    	 ����nodeIndex1�Ƿ���nodeIndex2������
    */
    bool testIsAtBottom(int nodeIndex1, int nodeIndex2);

protected:
    MapGrid(int gridW, int gridH, int xNum, int yNum);
    ~MapGrid();

    /**
    	 �������񣬶��ڲ�����ʹ�õĸ��ӣ������ɫ
    */
    void drawGrid();

    /**
    	 �����������øö���ռ�е�λ�ò���ͨ��
    */
    void setObjectOccupyGrid(ObjectOnMapGrid* object);

    /**
    	 ��Ϊ�������ƶ���ʱ��Ҫ��ͣ�ĸ���yֵ����ǰ�󼶹�ϵ
    */
    void adjustGameCharacterZOrder();

    DrawNode*   m_drawNode;                             // �������Ƶĵط���������Ӧ�����
    vector<ObjectOnMapGrid*> m_Objects;                 // �������������ƶ�������

    const Color4F m_gridColor;                          // ����ʹ�õ���ɫ
};

#endif