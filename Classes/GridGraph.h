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
    GridGraph(int gridW, int gridH, int xNum, int yNum);

    /**
    *  �ж���centerΪ���ģ���distanceΪ��Χ��target�Ƿ��ڷ�Χ��
    */
    bool isInScope(int center, int target, int distance);
};

#endif