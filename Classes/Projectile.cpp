#include "Projectile.h"
#include "ProjectileGalaxoBall.h"
#include "GameMap.h"
#include "ProjectileManager.h"

int Projectile::m_count =   -1;

Projectile* Projectile::create( GameCharacterAttribute& att, ProjectileTypeEnum type, void* extraInfo )
{
    Projectile* pRet    =   nullptr;
    switch (type)
    {
    case PROJECTILE_TYPE_GALAXO_BALL:               // ������
        {
            pRet    =   new ProjectileGalaxoBall(att, (int)extraInfo);
            break;
        }

    default:
        break;
    }

    if (pRet != nullptr)
    {
        pRet->m_projectileType  =   type;
        pRet->autorelease();

        // ע�ᵽ��������
        ProjectileMgr->addProjectile(pRet);

        // ��ӵ���ͼ��
        GameMap::instance()->addProjectile(pRet);
    }
    return pRet;
}

Projectile::Projectile( GameCharacterAttribute& att )
{
    m_senderAtt     =   att;
    m_state         =   PROJECTILE_STATE_UPDATE | PROJECTILE_STATE_UPDATEMOVEMENT;
    m_projectileId  =   ++m_count;
    m_rate          =   0;
}

void Projectile::setOrientation( Vec2 orientation )
{
    m_velocity  =   orientation * m_rate;
}
