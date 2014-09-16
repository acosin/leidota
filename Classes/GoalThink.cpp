#include "GoalThink.h"
#include "GoalMoveToGrid.h"

GoalThink::GoalThink( GameCharacter* owner ):GoalComposite<GameCharacter>(owner)
{

}

GoalThink::~GoalThink()
{

}

GoalStateEnum GoalThink::process()
{
    return GoalComposite<GameCharacter>::process();
}

void GoalThink::activate()
{
    // @_@ �����һ��Ѱ·��ȥ
    addSubgoal(new GoalMoveToGrid(m_pOwner, 6));
}
