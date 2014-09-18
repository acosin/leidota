#ifndef __GAME_CHARACTER_H__
#define __GAME_CHARACTER_H__

#include "BaseGameEntity.h"
#include "GameCharacterShape.h"
#include "GameCharacterAttribute.h"

#include "WeaponControlSystem.h"
#include "TargetControlSystem.h"

#include "MovingEntity.h"
#include "SteeringBehaviors.h"

using namespace std;

class GameTeam;
class GoalThink;

/**
	 �ڴ����е���Ϸ��ɫ
*/
class GameCharacter : public BaseGameEntity
{
public:
    /**
    * ��ɫ�ĵ�ǰ״̬
    * @_@ Ŀǰֻ�����ͻ�����״̬
    */
    enum GameCharacterStateEnum
    {
        alive,                  // ��ǰ����
        dead,                   // �Ѿ�����
    };

    /**
    	 @_@ ��Ҫ�Ǵ���һ����ɫ��Ҫ�Ĳ���̫�࣬�Ժ�Ӧ���Ǵ����ñ��л�ȡ��
         ��������дһЩ��ɫ����
    */
    static GameCharacter* create(int id);

    /**
    	 ÿһ֡�ĸ���
    */
    virtual void update(float dm) override;

    /**
    	 ����������Ϣ��
    */
    virtual bool handleMessage(Telegram& msg) override;

    GameCharacterShape *getShape() override;

    /**
    	 ���ڽ�ɫ���ԵĲ���
    */
    GameCharacterAttribute& getAttribute();
    WeaponControlSystem* const getWeaponControlSystem();
    TargetControlSystem* const getTargetControlSystem();
    MovingEntity& getMovingEntity() { return m_movingEntity; }
    SteeringBehaviors* const getSteeringBehaviros() { return m_steeringBehaviors; }

    // ���úͷ��ظý�ɫ�����Ķ��� 
    CC_SYNTHESIZE(GameTeam*, m_team, Team);

    // ��ɫid����ʾһ�����͵����� 
    CC_SYNTHESIZE_READONLY(int, m_characterId, CharacterId);

    // ��ɫ�ĵ�ǰ״̬
    CC_SYNTHESIZE_READONLY(GameCharacterStateEnum, m_state, State);

protected:
    GameCharacter();
    ~GameCharacter();

    /**
    * ���µ�ǰ������ 
    */
    void updateMovement(float dm);

    GameCharacterShape*             m_shape;                    // �ý�ɫ������
    GameCharacterAttribute          m_attribute;                // �ý�ɫ�ĸ�������

    GoalThink*                      m_brain;                    // ��Ϊ���Դ��ڵģ���Ŀ��滮����߼���

    /**
    * һЩϵͳ
    */
    WeaponControlSystem*            m_weaponControlSystem;      // ����ϵͳ
    TargetControlSystem*            m_targetControlSystem;      // Ŀ��ѡ��ϵͳ

    MovingEntity                    m_movingEntity;             // ���������ɫ�ƶ��Ķ���
    SteeringBehaviors*              m_steeringBehaviors;        // ��������������

    float                           m_lastUpdateTime;           // ���һ�ε���update��ʱ��
};

#endif