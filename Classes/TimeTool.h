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
    static double getSecondTime()
    {
        struct timeval tv;
        memset(&tv, 0, sizeof(tv));
        gettimeofday(&tv, nullptr);
        double tmpCurrentTime = tv.tv_sec + (double)tv.tv_usec / 1000000.0;
        //CCLOG("tv.tv_sec = %ld, tv.tv_usec = %ld", tv.tv_sec, tv.tv_usec);
        //CCLOG("getSecondTime = %f", tmpCurrentTime);
        return tmpCurrentTime;
    }
};

#endif