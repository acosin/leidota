#ifndef __FLIGHT_PROPS_H__
#define __FLIGHT_PROPS_H__

#include "cocos2d.h"
#include "cocostudio/CCArmature.h"
#include "GameCharacter.h"
#include "EntityManager.h"

using namespace cocos2d;
using namespace cocostudio;
using namespace std;

/**
	 ���е�������
*/
enum FlightPropsTypeEnum
{
    FLIGHTPROPS_TYPE_FIXED_POINT_ONE_TARGET                 // �����Ŀ������̶�����ֻ����һ�����˵ķ��е���
};

/**
	 �����еĵ��ߣ��ڴ����õ��ߵ�ʱ����Ҫ�������ݳߴ磬�Է���
     �ཻ���
*/
class FlightProps : public Sprite
{
protected:
    FlightProps(FlightPropsTypeEnum type, int senderId, Vec2 velocity);

public:
    /**
    	 ���µ�ǰ���ڷ����еĵ���
    */
    virtual void update(float dm);

    /**
    	����⵽��ײ��ʱ��Ļص�
    */
    virtual void onCollision(int id){};

    /**
    	 �������������ײ�ľ���
    */
    virtual Rect getCollisionRect();

    FlightPropsTypeEnum     type;                       // ��������
    int                     senderId;                   // ������id
    Vec2                    velocity;                   // �����ٶ�
    GameCharacterAttribute  senderAtt;                  // �����ߵ����ԣ����ڼ���Ч���������ڷ��й����з����������ˣ�

    bool                    shouldBeDel;                // Ҫ��ɾ���ı��
    bool                    isEffective;                // �Ƿ���Ч�����ܴ��ڸ÷��е�����Ȼ���ڣ������Ѿ���Ч��
};

/**
    ��Ե��Զ�̹��������ҷ��е�����Armature�����Ա����ڹ̶�֡���ڵ�������ٶ�
    ���ǹ̶���
*/
class OneToOneArmatureFlightProps : public FlightProps
{
protected:
    int         m_targetId;                         // ������id
    string      m_actionName;                       // ��������
    Armature*   m_armature;                         // ����

    /**
    	 ���͡������ߣ����ŵĶ����Լ���������
    */
    OneToOneArmatureFlightProps(int senderId, int targetId, Armature* armature, string actionName, float rate);
    ~OneToOneArmatureFlightProps();

    /**
    	 �Բۣ��ڹ��캯���н�Armature����
    */
    bool init() override;

public:
    /**
    	 ����һ����Ե㹥���ķ��е���
    */
    static OneToOneArmatureFlightProps* create(int senderId, int targetId, int skillId);
    void onCollision(int id);

    void update(float dm);
};

#endif