#ifndef __FORMATION_H__
#define __FORMATION_H__

#include "cocos2d.h"

using namespace cocos2d;

/**
* С�ӵ��ƶ����ͣ��ڲ��Ӽ����ƶ���ʱ��Ҫ����������ͣ������������
* ������ߵ�
* 4      2     0 
* 5      3     1
* �����ұߵ�
* 0      2     4
* 1      3     5
*/
class Formation
{
public:
    /**
    * ������ʽ 
    */
    enum FormationTypeEnum
    {
        FORMATION_TYPE_RIGHT,               // �����ұߵ�����
        FORMATION_TYPE_LEFT,                // ������ߵ�����
    };

    Formation(FormationTypeEnum type = FORMATION_TYPE_RIGHT):m_xPosInterval(200), m_yPosInterval(200)
    {
        m_formationType =   type;
    }

    /**
    * �������е�ÿ��һ����ɫ����һ����ţ����ݱ�ţ��������ƶ���ʱ��ᾡ������ָ����λ����
    * ������Ǹ��������еı�ŷ��ض�Ӧ������
    */
    Vec2 getPositionByPosId(int posId)
    {
        float   tmpxInterval    =   0;
        switch (m_formationType)
        {
        case FORMATION_TYPE_LEFT:
            tmpxInterval    =   m_xPosInterval;
            break;

        case FORMATION_TYPE_RIGHT:
            tmpxInterval    =   -m_xPosInterval;
            break;
        }

        for (int i = 0; i < 6; i++)
        {
            m_formationPos[i]   =   m_formationAnchor + Vec2(i / 2 * tmpxInterval, - i % 2 * m_yPosInterval);
        }

        return m_formationPos[posId];
    }

    CC_SYNTHESIZE(Vec2, m_formationAnchor, FormationAnchor);                // ���͵�ê�㣬��ʵ����0��λ
    CC_SYNTHESIZE(FormationTypeEnum, m_formationType, FormationType);       // ������ʽ

private:
    Vec2                    m_formationPos[6];              // ���͵ĸ�������

    /**
    * �����е�һЩ���� 
    */
    const float             m_xPosInterval;                 // x�����ϵ�ƫ��
    const float             m_yPosInterval;                 // y�����ϵ�ƫ��
};

#endif