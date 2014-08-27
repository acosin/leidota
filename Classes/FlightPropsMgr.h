#ifndef __FLIGHT_PROPS_MGR_H__
#define __FLIGHT_PROPS_MGR_H__

#include "cocos2d.h"
#include "FlightProps.h"

using namespace std;

/**
	 ���е��߹����࣬�������ǰ���ڷ����е����е���
*/
class FlightPropsMgr
{
public:

    typedef map<int, FlightProps*>  FlightPropsMap;

    static FlightPropsMgr* instance();

    /**
    	 ע��
    */
    void registerFlightProps(FlightProps* flight);

    /**
    	 ɾ��
    */
    void removeFlightProps(FlightProps* flight);

    /**
    	 ÿһ֡�ĵ��ã����޸ķ��е��ߵ�λ�ã��Լ���һЩ�������߼�
    */
    void update(float dm);

private:
    FlightPropsMgr(){}

    /**
    	 ����ĳһ��
    */
    bool collisionTest(int id, FlightProps* flight);

    static FlightPropsMgr*      m_instance;                 // ����

    FlightPropsMap              m_allFlights;               // �������ڷ����е�
};

#define FliProMgr   FlightPropsMgr::instance()

#endif