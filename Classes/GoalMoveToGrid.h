#ifndef __GOAL_MOVE_TO_GRID_H__
#define __GOAL_MOVE_TO_GRID_H__

#include "GoalComposite.h"
#include "PathPlanner.h"

class GameCharacter;

/**
*  ǰ���������е�ָ���ĸ��Ӵ�
*/
class GoalMoveToGrid : public GoalComposite<GameCharacter>
{
public:
    GoalMoveToGrid(GameCharacter* owner, int gridIndex);
    ~GoalMoveToGrid();

protected:
    virtual void activate() override;

private:
    int                 m_gridIndex;
    PathPlanner*        m_pathPlanner;
};

#endif