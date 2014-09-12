#include "MapGrid.h"
#include "GameCharacter.h"
#include "GraphSearchAStar.h"
#include "EntityManager.h"

#define DRAW_MAP_GRID

/**
* ��Ҫ����Ϊ�ڱ���android��ʱ����û�ж���abs����Ӧ��ʹ��fabs 
*/
#ifndef WIN32
    #define abs(value)  fabs(value)
#endif

bool MapGrid::init()
{
    if (!Layer::init())
    {
        return false;
    }

    // ���ô�С
    this->setContentSize(Size(_gridW * _xNum, _gridH * _yNum));

    // ��������
#ifdef DRAW_MAP_GRID
    m_drawNode  =   DrawNode::create();
    this->addChild(m_drawNode);
#endif
    drawGrid();

    return true;
}

MapGrid::MapGrid(int gridW, int gridH, int xNum, int yNum):GridGraph(gridW, gridH, xNum, yNum),m_gridColor(1.0f, 0.0f, 0.0f, 1.0f)
{
    this->setContentSize(Size(gridW * xNum, gridH * yNum));
}

MapGrid::~MapGrid()
{

}

void MapGrid::drawGrid()
{
    // ���������passable
    resetAllNodePassable();
    for (auto tmpObjectIterator  =   m_Objects.begin(); tmpObjectIterator != m_Objects.end(); tmpObjectIterator++)
    {
        setObjectOccupyGrid(*tmpObjectIterator);
    }

#ifdef DRAW_MAP_GRID
    // �������
    m_drawNode->clear();
    // ����ˮƽ��
    for (int y = 0; y <= _yNum; y++)
    {
        m_drawNode->drawSegment(Vec2(0, y * _gridH), Vec2(_xNum * _gridW, y * _gridH), 1, m_gridColor);
    }

    // ������ֱ��
    for (int x = 0; x <= _xNum; x++)
    {
        m_drawNode->drawSegment(Vec2(x * _gridW, 0), Vec2(x * _gridW, _yNum * _gridH), 1, m_gridColor);
    }

    // ��䲻��ʹ�õĸ��ӣ�����һ������һ�����ӵĲ���
    auto tmpIterator = m_nodes.begin();
    for (; tmpIterator != m_nodes.end(); tmpIterator++)
    {
        auto tmpGrid = tmpIterator->second;
        if (!tmpGrid.passable())
        {
            // ����ͨ�е�
            Vec2 tmpPoints[4];
            tmpPoints[0].setPoint(tmpGrid.getX() - _gridW / 2, tmpGrid.getY() - _gridH / 2);
            tmpPoints[1].setPoint(tmpGrid.getX() + _gridW / 2, tmpGrid.getY() - _gridH / 2);
            tmpPoints[2].setPoint(tmpGrid.getX() + _gridH / 2, tmpGrid.getY() + _gridH / 2);
            tmpPoints[3].setPoint(tmpGrid.getX() - _gridW / 2, tmpGrid.getY() + _gridH / 2);
            m_drawNode->drawPolygon(tmpPoints, 4, m_gridColor, 0, m_gridColor);
        }
    }
#endif
}

void MapGrid::addObjectToGrid(ObjectOnMapGrid* object)
{
    m_Objects.push_back(object);
    /**
    	 ÿ���޸�������ռλ�õ�ʱ�򣬶�Ҫ�����������
    */
    adjustGameCharacterZOrder();
    drawGrid();
}

void MapGrid::removeObjectFromGrid(ObjectOnMapGrid* object)
{
    for (auto tmpIteator = m_Objects.begin(); tmpIteator != m_Objects.end(); tmpIteator++)
    {
        if (object == *tmpIteator)
        {
            m_Objects.erase(tmpIteator);
            break;
        }
    }
    drawGrid();
}

void MapGrid::setObjectOccupyGrid(ObjectOnMapGrid* object)
{
    setNodePassable(object->nodeIndex, false);

    switch (object->placeType)
    {
    case PLACEHOLDER_TYPE_ONE:                          // ֻռһ������
        break;

    case PLACEHOLDER_TYPE_CROSS:                        // ռһ��ʮ�ָ���
        {
            auto tmpGridIndex = getTopGridIndex(object->nodeIndex);
            if (tmpGridIndex != INVALID_NODE_INDEX)
            {
                setNodePassable(tmpGridIndex, false);
            }
            tmpGridIndex = getLeftGridIndex(object->nodeIndex);
            if (tmpGridIndex != INVALID_NODE_INDEX)
            {
                setNodePassable(tmpGridIndex, false);
            }
            tmpGridIndex = getBottomGridIndex(object->nodeIndex);
            if (tmpGridIndex != INVALID_NODE_INDEX)
            {
                setNodePassable(tmpGridIndex, false);
            }
            tmpGridIndex = getRightGridIndex(object->nodeIndex);
            if (tmpGridIndex != INVALID_NODE_INDEX)
            {
                setNodePassable(tmpGridIndex, false);
            }
            break;
        }

    default:
        break;
    }
}

void MapGrid::addGameCharacter(GameCharacter* character)
{
    // ��ӽ�ɫ����
    auto tmpGridNode    =   this->getNodeByIndex(character->getObjectOnGrid()->nodeIndex);
    auto tmpShape       =   character->getShape();
    tmpShape->setPosition(tmpGridNode.getX(), tmpGridNode.getY());
    this->addChild(tmpShape);

    // ��������ռ�ø���
    this->addObjectToGrid(character->getObjectOnGrid());

    // ����ý�ɫ���ʸ�����
    character->setGridGraph(this);
}

void MapGrid::adjustGameCharacterZOrder()
{
    // �����������������
    auto tmpAllCharacters   =   EntityMgr->getEntityMap();
    for (auto tmpChildIterator = tmpAllCharacters->begin(); tmpChildIterator != tmpAllCharacters->end(); tmpChildIterator++)
    {
        auto tmpCharacter   =   (GameCharacter*)tmpChildIterator->second;
        tmpCharacter->getShape()->setZOrder(_xNum - tmpCharacter->getObjectOnGrid()->nodeIndex / _xNum);
    }
}

int MapGrid::getLeftGridIndex(int nodeIndex, int distance)
{
    if (nodeIndex == INVALID_NODE_INDEX || nodeIndex % _xNum < distance)
    {
        return INVALID_NODE_INDEX;
    }

    return nodeIndex - distance;
}

int MapGrid::getTopGridIndex(int nodeIndex, int distance)
{
    if (nodeIndex == INVALID_NODE_INDEX || nodeIndex >= _xNum * (_yNum - distance))
    {
        return INVALID_NODE_INDEX;
    }

    return nodeIndex + _xNum * distance;
}

int MapGrid::getRightGridIndex(int nodeIndex, int distance)
{
    if (nodeIndex == INVALID_NODE_INDEX || nodeIndex % _xNum >= _xNum - distance)
    {
        return INVALID_NODE_INDEX;
    }

    return nodeIndex + distance;
}

int MapGrid::getBottomGridIndex(int nodeIndex, int distance)
{
    if (nodeIndex == INVALID_NODE_INDEX || nodeIndex < _xNum * distance)
    {
        return INVALID_NODE_INDEX;
    }

    return nodeIndex - _xNum * distance;
}

int MapGrid::getLeftTopGridIndex(int nodeIndex)
{
    return getTopGridIndex(getLeftGridIndex(nodeIndex));
}

int MapGrid::getRightTopGridIndex(int nodeIndex)
{
    return getTopGridIndex(getRightGridIndex(nodeIndex));
}

int MapGrid::getRightBottomGridIndex(int nodeIndex)
{
    return getBottomGridIndex(getRightGridIndex(nodeIndex));
}

int MapGrid::getLeftBottomGridIndex(int nodeIndex)
{
    return getBottomGridIndex(getLeftGridIndex(nodeIndex));
}

vector<int> MapGrid::getRouteToTargetObj(ObjectOnMapGrid* source, ObjectOnMapGrid* target)
{
    // ��Ѱ·ǰ���������Ƴ�֮ǰ��ռ�е�����
    this->removeObjectFromGrid(source);
    vector<int> retShortRoute;

    // �������Ŀ��ռ�е�����������Ѱ·Ŀ��
    switch (target->placeType)
    {
    case PLACEHOLDER_TYPE_ONE:
        {
            // ����ֻռ��һ�����ӵģ�ֻ������ǰ������Ŀ��
            vector<int> tmpToFrontRoute;
            vector<int> tmpToBackRoute;
            auto tmpFrontGridIndex   =   getLeftGridIndex(target->nodeIndex);
            if (tmpFrontGridIndex != INVALID_NODE_INDEX)
            {
                // Ѱ��·��
                tmpToFrontRoute = GraphSearchAStar::search(*this, source->nodeIndex, tmpFrontGridIndex, MapGrid::calculateH);
            }

            auto tmpBackGridIndex    =   getRightGridIndex(target->nodeIndex);
            if (tmpBackGridIndex != INVALID_NODE_INDEX)
            {
                tmpToBackRoute = GraphSearchAStar::search(*this, source->nodeIndex, tmpBackGridIndex, MapGrid::calculateH);
            }

            // ѡ�������
            if (tmpToFrontRoute.size() != 0 && tmpToFrontRoute.size() <= tmpToBackRoute.size())
            {
                retShortRoute = tmpToFrontRoute;
            }
            else
            {
                retShortRoute = tmpToBackRoute;
            }

            break;
        }
        

    case PLACEHOLDER_TYPE_CROSS:
        {
            // ����ʮ�ּܣ��еĿ���Ŀ���̫����
            vector<int> tmpTargetGridIndexs;
            auto tmpGridIndex   =   getLeftGridIndex(getLeftGridIndex(target->nodeIndex));
            if (tmpGridIndex != INVALID_NODE_INDEX)
            {
                tmpTargetGridIndexs.push_back(tmpGridIndex);
            }
            tmpGridIndex    =   getTopGridIndex(getLeftGridIndex(target->nodeIndex));
            if (tmpGridIndex != INVALID_NODE_INDEX)
            {
                tmpTargetGridIndexs.push_back(tmpGridIndex);
            }
            tmpGridIndex    =   getBottomGridIndex(getLeftGridIndex(target->nodeIndex));
            if (tmpGridIndex != INVALID_NODE_INDEX)
            {
                tmpTargetGridIndexs.push_back(tmpGridIndex);
            }
            tmpGridIndex    =   getTopGridIndex(getRightGridIndex(target->nodeIndex));
            if (tmpGridIndex != INVALID_NODE_INDEX)
            {
                tmpTargetGridIndexs.push_back(tmpGridIndex);
            }
            tmpGridIndex    =   getBottomGridIndex(getRightGridIndex(target->nodeIndex));
            if (tmpGridIndex != INVALID_NODE_INDEX)
            {
                tmpTargetGridIndexs.push_back(tmpGridIndex);
            }
            tmpGridIndex    =   getRightGridIndex(getRightGridIndex(target->nodeIndex));
            if (tmpGridIndex != INVALID_NODE_INDEX)
            {
                tmpTargetGridIndexs.push_back(tmpGridIndex);
            }
            // ���������Ż������Ѱ·����̫����
            if (source->nodeIndex % _xNum > target->nodeIndex % _xNum)
            {
                reverse(tmpTargetGridIndexs.begin(), tmpTargetGridIndexs.end());
            }

            // Ѱ�����·����
            for (int i = 0; i < tmpTargetGridIndexs.size(); i++)
            {
                auto tmpRoute   =   GraphSearchAStar::search(*this, source->nodeIndex, tmpTargetGridIndexs[i], MapGrid::calculateH);
                if ((retShortRoute.size() == 0 || tmpRoute.size() < retShortRoute.size()) && tmpRoute.size() > 0)
                {
                    retShortRoute   =   tmpRoute;
                    break;
                }
            }

            break;
        }
        
    default:
        break;
    }

    this->addObjectToGrid(source);
    return retShortRoute;
}

float MapGrid::calculateH(SparseGraph& grap, int sourceIndex, int targetIndex)
{
    MapGrid* tmpMapGrid =   (MapGrid*)&grap;
    auto tmpSourceGrid  =   grap.getNodeByIndex(sourceIndex);
    auto tmpTargetGrid  =   grap.getNodeByIndex(targetIndex);

    // ����֮��ľ���
    int tmpXDistance    =   abs(tmpSourceGrid.index() % tmpMapGrid->_xNum - tmpTargetGrid.index() % tmpMapGrid->_xNum);
    int tmpYDistance    =   abs(tmpSourceGrid.index() / tmpMapGrid->_xNum - tmpTargetGrid.index() / tmpMapGrid->_xNum);
    return tmpXDistance + tmpYDistance;
}

bool MapGrid::testTwoIndexInOneHorizon(int nodeIndex1, int nodeIndex2)
{
    return nodeIndex1 / _xNum == nodeIndex2 / _xNum;
}

bool MapGrid::testIsAtLeft(int nodeIndex1, int nodeIndex2)
{
    return nodeIndex1 % _xNum < nodeIndex2 % _xNum;
}

bool MapGrid::testIsAtTop(int nodeIndex1, int nodeIndex2)
{
    return nodeIndex1 / _xNum > nodeIndex2 / _xNum;
}

bool MapGrid::testIsAtRight(int nodeIndex1, int nodeIndex2)
{
    return nodeIndex1 % _xNum > nodeIndex2 % _xNum;
}

bool MapGrid::testIsAtBottom(int nodeIndex1, int nodeIndex2)
{
    return nodeIndex1 / _xNum < nodeIndex2 / _xNum;
}