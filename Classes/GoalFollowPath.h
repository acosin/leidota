#ifndef __GOAL_FOLLOW_PATH_H__
#define __GOAL_FOLLOW_PATH_H__

#include <list>
#include "GoalComposite.h"
#include "NavGraphEdge.h"

using namespace std;

class GameCharacter;

/**
* ��ɫ������ĳ��·���ƶ������Ŀ�꣬�����ɶ��GoalTraverseEdge��ɵ� 
*/
class GoalFollowPath : public GoalComposite<GameCharacter>
{
public:
    GoalFollowPath(GameCharacter* owner, const list<NavGraphEdge>& path);
    ~GoalFollowPath();

protected:
    virtual void activate() override;

    virtual GoalStateEnum process() override;

private:
    list<NavGraphEdge>  m_path;                     // ��Ŀ��Ҫ�صı�·��
};

#endif