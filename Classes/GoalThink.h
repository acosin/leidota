#ifndef __GOAL_THINK_H__
#define __GOAL_THINK_H__

#include "GoalComposite.h"

class GameCharacter;

/**
* ������߼���Ŀ�꣬�ڴ˴�����ݵ�ǰ���������ǰ��Ŀ�� 
*/
class GoalThink : public GoalComposite<GameCharacter>
{
public:
    GoalThink(GameCharacter* owner);
    ~GoalThink();

    virtual GoalStateEnum process() override;

protected:
    virtual void activate() override;
};

#endif