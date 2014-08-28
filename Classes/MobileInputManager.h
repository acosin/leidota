#ifndef __MOBILE_INPUT_MANAGER_H__
#define __MOBILE_INPUT_MANAGER_H__

#include "cocos2d.h"
#include "InputManager.h"

using namespace cocos2d;

/**
	 ��Ϊ�ֻ��˵���������ֻ��˾��ǿ�������ָ�ӵ�
*/
class MobileInputManager : public InputManager
{
public:
    MobileInputManager();
    ~MobileInputManager();
    bool init();

private:
    /**
    	 ���Ʒ���
    */
    enum ControlDirection
    {
        INVALID_CONTROL_DIRECTION,
        RIGHT_CONTROL_DIRECTION,
        LEFT_CONTROL_DIRECTION
    };

    EventListenerTouchOneByOne* m_touchListener;            // ��������
    Point                       m_lastTouchPoint;           // ��һ�δ�������Ļ����
    ControlDirection            m_controlDirection;         // ��ǰ�Ŀ��Ʒ���

    // ÿһ֡�Ļص�
    void update(float dm);

    // ���������¼���
    bool onTouchBegin(Touch* pTouch, Event* pEvent);
    void onTouchEnd(Touch* pTouch, Event* pEvent);
};

#endif