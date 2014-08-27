#ifndef __PRIORITY_Q_LOW_H__
#define __PRIORITY_Q_LOW_H__

#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

/**
	����������Сֵ�����ȼ�����
*/
class PriorityQLow
{
private:
    vector<float>&   m_priorityValues;           // �������ֵ
    vector<int>     m_highToLow;                // �Ӵ�С����

public:
    PriorityQLow(vector<float>& priorityValues):m_priorityValues(priorityValues)
    {
        m_highToLow.clear();
    }

    /**
    	����һ���µĽڵ�
    */
    void insert(int index)
    {
        m_highToLow.push_back(index);
        reOrder();
    }

    /**
    	�ж��Ƿ�Ϊ��
    */
    bool empty()
    {
        return m_highToLow.empty();
    }

    /**
    	ȡ��һ����С��
    */
    int pop()
    {
        int tmpRet  =   m_highToLow.back();
        m_highToLow.pop_back();
        return tmpRet;
    }

    /**
    	������һ����
    */
    void reOrder()
    {
        std::function<bool (const int&, const int&)> ff = 
            std::bind(&PriorityQLow::sortFunc, this, std::placeholders::_1, std::placeholders::_2);
        sort(m_highToLow.begin(), m_highToLow.end(), ff);
    }

protected:
    bool sortFunc(const int& m1, const int& m2)
    {
        return m_priorityValues[m1] > m_priorityValues[m2];
    }
};

#endif