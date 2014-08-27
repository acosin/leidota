#ifndef __NAV_GRAPH_NODE_H__
#define __NAV_GRAPH_NODE_H__

#define INVALID_NODE_INDEX  -1

/**
	 �ڵ���Ϣ
*/
class NavGraphNode
{
protected:
    int     m_iIndex;           // ����
    float   x;                  // ������������
    float   y;
    bool    m_bPassable;        // �ýڵ��Ƿ����ͨ��

public:
    NavGraphNode()
    {
        NavGraphNode(INVALID_NODE_INDEX);
    }

    NavGraphNode(int index, int x = 0, int y = 0, bool passable = true)
    {
        m_iIndex        =   index;
        this->x         =   x;
        this->y         =   y;
        m_bPassable     =   passable;
    }

    int index() {return m_iIndex;}

    void setPassable(bool passable) {m_bPassable = passable;}
    bool passable() {return m_bPassable;}

    float getX() {return x;}
    float getY() {return y;}
};

#endif