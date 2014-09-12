#ifndef __TIME_TOOL_H__
#define __TIME_TOOL_H__

#include "cocos2d.h"

using namespace cocos2d;

/**
* ��Ҫ����һЩʱ�乤�ߣ������ȡ��ǰ��
*/
class TimeTool
{
public:
    /**
    * ���ص�ǰ����Ϊ��λ��ʱ�䣬������ܻ���ֵ��������ڿ����ʱ��
    */
    static float getSecondTime()
    {
        struct timeval tv;
        memset(&tv, 0, sizeof(tv));
        gettimeofday(&tv, nullptr);
        float tmpCurrentTime = tv.tv_sec + tv.tv_usec / 1000000.0;
        return tmpCurrentTime;
    }
};

#endif