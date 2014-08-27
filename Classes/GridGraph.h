#ifndef __GRID_GRAPH_H__
#define __GRID_GRAPH_H__

#include "SparseGraph.h"

/**
	 �ܶ�ط�ʹ������ͼ��������������һЩ�������ϰ��޷�ͨ��
*/
class GridGraph : public SparseGraph
{
protected:
    int _xNum;
    int _yNum;
    int _gridW;
    int _gridH;

public:
    /**
    	 ����һ��ȫͨ������
         @grieW         ����������
         @gridH         ��������߶�
         @xNum          ˮƽ��������
         @yNum          ��ֱ��������
    */
    GridGraph(int gridW, int gridH, int xNum, int yNum)
    {
        _gridW  =   gridW;
        _gridH  =   gridH;
        _xNum   =   xNum;
        _yNum   =   yNum;

        // ����ӽڵ�
        for (int y = 0; y < yNum; y++)
        {
            for (int x = 0; x < xNum; x++)
            {
                this->addNode(NavGraphNode(y * xNum + x, gridW * x + gridW / 2, gridH * y + gridH / 2));
            }
        }

        // ��ӱ�
        for (int y = 0; y < yNum; y++)
        {
            for (int x = 0; x < xNum; x++)
            {
                if (x < xNum - 1)
                {
                    this->addEdge(NavGraphEdge(y * xNum + x, y * xNum + x + 1));
                }
                
                if (y < yNum - 1)
                {
                    this->addEdge(NavGraphEdge(y * xNum + x, (y + 1) * xNum + x));
                }
            }
        }
    }
};

#endif