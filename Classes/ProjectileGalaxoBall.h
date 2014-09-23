#ifndef __PROJECTILE_GALAXO_BALL_H__
#define __PROJECTILE_GALAXO_BALL_H__

#include "Projectile.h"

/**
*	�����򣬸�����
*/
class ProjectileGalaxoBall : public Projectile
{
public:
    ProjectileGalaxoBall(GameCharacterAttribute& att, int targetId);
    virtual ~ProjectileGalaxoBall();

    virtual void update(float dm) override;
    virtual void updateMovement(float dm) override;
    virtual Node* getShape() override;

private:
    Armature*       m_ball;         // ������Ķ�������Ϊ�����������ʾ
    int             m_targetId;     // ����Ŀ��
    Vec2            m_targetPos;    // Ŀ������
};

#endif