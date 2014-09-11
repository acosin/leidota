#ifndef __TARGET_CONTROL_SYSTEM_H__
#define __TARGET_CONTROL_SYSTEM_H__

#include "cocos2d.h"
#include "ControlSystem.h"

using namespace cocos2d;

/**
* Ŀ�����ϵͳ����ɫͨ���ö�����������ǰ�Ĺ���Ŀ�֮꣬ǰ�Ƿ���Auto�У�ÿ�θ��µ�ʱ�򶼻���һ�£�����
* ����Ŀ����޷��̶�����������Ҳ����д����Ĳ��֣����Խ����߼�������Ŀ�����ϵͳ��
* @_@ ����Ŀǰ������ҪGameCharacterAutoState������
*/
class TargetControlSystem : public ControlSystem
{
public:
    TargetControlSystem(GameCharacter* owner, float updatePeriod = 0);
    ~TargetControlSystem();

    /**
    * �ⲿǿ�Ƹý�ɫ����ĳ��Ŀ��
    */
    void forceTargetId(int id);

    /**
    * ������Ĳ�ͬ������ǿ�����ù���Ŀ�꣬��ΪĿǰ���Զ�״̬�¹���Ŀ���ѡ������GameCharacterAutoState�е��߼�
    * �����Ƶģ������ṩ�ýӿ�
    */
    void setTargetId(int id);

    /**
    * ���ص�ǰ�ý�ɫ�Ĺ���Ŀ��
    */
    GameCharacter* getTargetCharacter();
   
    /**
    *  ��ǰϵͳ��״̬��������Ŀ��ѡ��ķ�ʽ
    */
    enum ChoiceTargetState
    {
        CHOICE_TARGET_AUTO_PRECEDENCE,                                      // �����Զ�ѡ��Ŀ�꣨һ����Ǹ��ݾ��룩
        CHOICE_TARGET_USER_PRECEDENCE                                       // ����ѡ�����ָ���ģ�ֻ�е��޷�������ʱ��Ż��л�Ϊ�Զ�
    };
    CC_SYNTHESIZE_READONLY(ChoiceTargetState, m_choiceTargetState, ChoiceTargetState);

protected:
    void update(float dm) override;

    /**
    *  �����ڲ����߼�������ǰ������Ŀ��
    */
    void updateTarget();

    int m_targetId;                                 // ����Ŀ��id
};

#endif