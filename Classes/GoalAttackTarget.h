#ifndef __GOAL_ATTACK_TARGET_H__
#define __GOAL_ATTACK_TARGET_H__

#include <vector>
#include "GoalComposite.h"

using namespace std;

class GameCharacter;

/**
* ֱ����ΪGoalThink��Ŀ����࣬���ڽ�ɫ�ĵ�ǰĿ�꼶�����������ǰ����������Χ��
* Ȼ�󷢶�������һ�����߼�
*/
class GoalAttackTarget : public GoalComposite<GameCharacter>
{
public:
    /**
    *  ����Ŀ���ʱ���������Ҫ������Ŀ��id��Ȼ���Ŀ��ͻ���ȫ���ݸý�ɫ
    *  ȥ������Ŀ�ֱ꣬��Ŀ�����������ϲ�Ŀ��������ֹ�˸�Ŀ��
    */
    GoalAttackTarget(GameCharacter* owner, int targetId);
    ~GoalAttackTarget();

protected:
    virtual void activate() override;

    virtual GoalStateEnum process() override;

private:
    /**
    * �Ƿ��ڹ�����Χ�� 
    */
    bool isInAttackRange();

    /**
    * ����Ϊ�˹����ý�ɫ����Ҫǰ�����ĸ����ӣ������������ѵ�Ŀ�����
    */
    int getAdvanceGridIndex();

    /**
    * ����id���ض���ָ�� 
    */
    GameCharacter* getTarget();

    int             m_targetId;                 // Ŀ��id
};

#endif