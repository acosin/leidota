#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include "BaseGameEntity.h"
#include "cocos2d.h"

/**
	 ��������ʵ��������������ʵ��ᱻ������ƽ���ķ����ڲ�ͬ�������ϣ�Ȼ����ÿһ֡��
     ֻ�����һ�����������update����Ϊ�������û��Ҫ��ô��
*/ 
#define ENTITY_UPDATE_LIST_NUM     1

/**
	ȫ�ֵ�����������Ϸ�д��ڵ�����ʵ�壬��Ϊ����
*/
class EntityManager
{
public:
    typedef std::map<int, BaseGameEntity*> EntityMap;

private:
    EntityMap* _entityMap;     // ȫ�ֵ�ʵ��id--->ʵ���ӳ��
    static EntityManager *_instance;

    EntityManager();
    ~EntityManager();
    EntityManager(const EntityManager&);
    EntityManager &operator=(const EntityManager&);

    int _lastReturnGetOneId;                        // ����һ�ε���getOneEntity���ص�id

    EntityMap _entityUpdateList[ENTITY_UPDATE_LIST_NUM];  // �������µ�
    int _lastUpdateListIndex;                       // ��һ�ε���update����������

public:
    static EntityManager* instance();
    
    /**
    	 ע��һ��ʵ�壬��idΪ��
    */
    void registerEntity(BaseGameEntity *entity);

    /**
    	 ����ʵ��id���ض�Ӧ��ʵ��
    */
    BaseGameEntity* getEntityFromID(int id);

    /**
    	 �Ƴ�ĳ��ʵ��
    */
    void removeEntity(BaseGameEntity *entity);

    /**
    	 ִ������ʵ���update
    */
    void executeUpdate(float dm);

    /**
    	 Ϊ�˷����ⲿ������ǰ���е�ʵ��
    */
    const EntityMap* getEntityMap();

    /**
    	 ����ʵ�壬Ҳ���ǽ����û������
    */
    CC_SYNTHESIZE(BaseGameEntity*, _mainEntity, mainEntity);

    /**
    	 @_@ ����ָ�����͵�һ�����󣬾�����ÿ�ε��÷��ز�ͬ��
    */
    BaseGameEntity* getOneEntity(GameEntityTypeEnum type);
};

#define EntityMgr   EntityManager::instance()

#endif