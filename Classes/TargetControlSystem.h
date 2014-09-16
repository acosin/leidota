#ifndef __TARGET_CONTROL_SYSTEM_H__
#define __TARGET_CONTROL_SYSTEM_H__

class GameCharacter;

/**
* Ŀ�����ϵͳ��������ý�ɫ���ù���Ŀ�꣬������Ϊ�˷�װĿ��ѡ����߼�
*/
class TargetControlSystem
{
public:
    TargetControlSystem(GameCharacter* owner);
    ~TargetControlSystem();

    /**
    *  ����һ�µ�ǰ��Ŀ��ѡ��ϵͳ���ڲ���Ϣ
    */
    void update();

    /**
    * ���ص�ǰ��Ŀ�� 
    */
    GameCharacter* getTarget();

private:
    GameCharacter*  m_pOwner;                   // ������
    int             m_targetId;                 // ��ǰѡ���Ĺ���Ŀ��id
};

#endif