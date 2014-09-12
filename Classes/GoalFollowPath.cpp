#include "GoalFollowPath.h"
#include "GoalTraverseEdge.h"

GoalFollowPath::GoalFollowPath( GameCharacter* owner, const list<NavGraphEdge>& path )
    :GoalComposite<GameCharacter>(owner)
{
    m_path  =   path;
}

GoalFollowPath::~GoalFollowPath()
{

}

void GoalFollowPath::activate()
{
    // @_@ ������һ�ΰ����е�Ŀ�괴������
    for (auto tmpIterator = m_path.rbegin(); tmpIterator != m_path.rend(); tmpIterator++)
    {
        addSubgoal(new GoalTraverseEdge(m_pOwner, *tmpIterator));
    }
}

GoalFollowPath::GoalStateEnum GoalFollowPath::process()
{
    /**
    *  ����ֱ��ʹ��Ĭ�ϵģ�����ֻҪ�ڽ�ɫ���ű��ƶ��Ĺ����г����ˣ���Ŀ��Ҳ�ᱨ��
    *  Ȼ��������һ��Ŀ�������Ѳ��Ŀ��
    */ 
    return GoalComposite<GameCharacter>::process();
}