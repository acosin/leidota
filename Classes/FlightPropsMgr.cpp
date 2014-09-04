#include "FlightPropsMgr.h"
#include "EntityManager.h"

FlightPropsMgr* FlightPropsMgr::m_instance  =   nullptr;

FlightPropsMgr* FlightPropsMgr::instance()
{
    if (m_instance == nullptr)
    {
        m_instance  =   new FlightPropsMgr();
    }

    return m_instance;
}

void FlightPropsMgr::registerFlightProps(FlightProps* flight)
{
    flight->retain();
    m_allFlights.insert(FlightPropsMap::value_type((int)flight, flight));
}

void FlightPropsMgr::removeFlightProps(FlightProps* flight)
{
    m_allFlights.erase((int)flight);
    flight->removeFromParent();
    flight->release();
}

void FlightPropsMgr::update(float dm)
{
    // ���µ�ǰ���е��ߵ�λ�á�״̬��
    for (auto tmpFlightIterator = m_allFlights.begin(); tmpFlightIterator != m_allFlights.end();)
    {
        auto tmpFlight  =   tmpFlightIterator->second;
        // @_@ ���ھ��õ��������
        tmpFlightIterator++;
        tmpFlight->update(dm);

        // ɾ�������ΪҪɾ���ķ��е���
        if (tmpFlight->shouldBeDel)
        {
            removeFlightProps(tmpFlight);
            continue;
        }

        // ����÷������Ѿ���Ч�����ǿ��ܻ��ڲ��ŷ������Ķ��������Ի���������update
        if (!tmpFlight->isEffective)
        {
            continue;
        }

        // �������еĳ��Ͻ�ɫ�����μ����ײ
        auto tmpMap =   EntityMgr->getEntityMap();
        for (auto tmpCharacterIterator = tmpMap->begin(); tmpCharacterIterator != tmpMap->end();)
        {
            auto tmpCharacter   =   tmpCharacterIterator->second;
            tmpCharacterIterator++;
            // ���Լ���Ч
            if (tmpCharacter->getId() == tmpFlight->senderId)
            {
                continue;
            }
            if (collisionTest(tmpCharacter->getId(), tmpFlight))
            {
                tmpFlight->onCollision(tmpCharacter->getId());
                if (tmpFlight->shouldBeDel || !tmpFlight->isEffective)
                {
                    break;
                }
            }
        }

        // ������������г�����Ļ��Ҳɾ��
        auto tmpWinSize     =   Director::getInstance()->getVisibleSize();
        auto tmpOrig        =   Director::getInstance()->getVisibleOrigin();
        // �����ȡ�������е�����
        auto tmpFlightPos   =   tmpFlight->convertToWorldSpace(Vec2(0, 0));
        if (tmpFlightPos.x < 0 || tmpFlightPos.x > tmpWinSize.width || tmpFlightPos.y < 0 || tmpFlightPos.y > tmpWinSize.height)
        {
            tmpFlight->shouldBeDel  =   true;
        }

        // ɾ�������ΪҪɾ���ķ��е���
        if (tmpFlight->shouldBeDel)
        {
            removeFlightProps(tmpFlight);
        }
    }
}

bool FlightPropsMgr::collisionTest(int id, FlightProps* flight)
{
    auto tmpShape = (GameCharacterShape*)EntityMgr->getEntityFromID(id)->getShape();
    //return tmpShape->getCollisionRect().intersectsRect(flight->getCollisionRect());
    //return flight->getCollisionRect().containsPoint(tmpShape->getCenterPos());
    return tmpShape->getCollisionRect().containsPoint(flight->getPosition());
}