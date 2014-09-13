#include "GoalThink.h"
#include "GoalMoveToGrid.h"

GoalThink::GoalThink( GameCharacter* owner ):GoalComposite<GameCharacter>(owner)
{

}

GoalThink::~GoalThink()
{

}

GoalThink::GoalStateEnum GoalThink::process()
{
    return GoalComposite<GameCharacter>::process();
}

void GoalThink::activate()
{
    // @_@ �����һ��Ѱ·��ȥ
    addSubgoal(new GoalMoveToGrid(m_pOwner, 10));
    addSubgoal(new GoalMoveToGrid(m_pOwner, 21));
    addSubgoal(new GoalMoveToGrid(m_pOwner, 31));
}
