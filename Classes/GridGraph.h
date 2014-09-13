#ifndef __GRID_GRAPH_H__
#define __GRID_GRAPH_H__

#include <vector>
#include "SparseGraph.h"
#include "MathTool.h"

using namespace std;

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

    /**
    *  ���������и��������±�ľ��룬��λ��������
    */
    int getDistanceInGrid(int index1, int index2);

    /**
    *  ���������и����±�ļ��ξ���
    */
    int getDistance(int index1, int index2);

    /**
    * ������centerIndexΪ���ģ�radius������Ϊ�뾶�ķ����ڻ�û��ʹ�õ��������� 
    */
    vector<int> getUnusedGridIndex(int centerIndex, int radius);
};

#endif