#ifndef __GAME_CHARACTER_H__
#define __GAME_CHARACTER_H__

#include "BaseGameEntity.h"
#include "GameCharacterShape.h"
#include "StateMachine.h"
#include "MapGrid.h"
#include "GameCharacterAttribute.h"

using namespace std;

/**
	 ��Ϸ��ɫ����
*/
enum GameCharacterTypeEnum
{
    GAMECHARACTER_TYPE_ENUM_SHORT_RANGE,                // ���̹�����λ
    GAMECHARACTER_TYPE_ENUM_LONG_RANGE                  // Զ�̹�����λ
};

/**
	 �ڴ����е���Ϸ��ɫ
*/
class GameCharacter : public BaseGameEntity
{
public:
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

    /**
    	 ���ظ������״̬��
    */
    StateMachine<GameCharacter> *getFSM();

    GameCharacterShape *getShape() override;

    /**
    	 ���øý�ɫ���ڵ�����
    */
    void setGridGraph(MapGrid* graph);

    /**
    	 �������ʺ��޸ĸö����������ϵ�ռλ
    */
    ObjectOnMapGrid* getObjectOnGrid();

    /**
    	 ���ý�ɫ�ƶ���������������ΪnodeIndex�ĸ��ӣ�һ����һ�����ڵĸ��ӣ�����������
         ռλ�ã�Ȼ�󻺶���ȥ������Ҫ��֤nodeIndex�ǿ����ߵ�
    */
    void moveToGridIndex(int nodeIndex, float rate = 10);

    /**
    	 ���û�����AI�ܹ�ֱ�ӷ���������Щ
    */
    MapGrid* getMapGrid();

    /**
    	 ��ǰ�Ƿ����ƶ���
    */
    bool isMoving();

    /**
    	 ���ڽ�ɫ���ԵĲ���
    */
    GameCharacterAttribute& getAttribute();

    /**
    	 ��ɫ����ʱ�Ĵ���
    */
    void die();

    /**
    	 ���ؽ�ɫ����
    */
    GameCharacterTypeEnum getCharacterType();

    /**
    	 ��ͨ�������������л�״̬��ʱ��ص�callBack
    */
    void normalAttack(int id);

    /**
    	 ��������ͨ������������Ҫ֪��ʲôʱ��������������߼�֡���ж�
    */
    bool isNormalAttackFinish();

    /**
    	 �ж���һ�������Ƿ��ڸý�ɫ�Ĺ�����Χ��
    */
    bool isInAttackDistance(GameCharacter* other);

protected:
    GameCharacter();
    ~GameCharacter();

    /**
    	 ���ƶ�������ʱ��
    */
    void onMoveOver(Node* pNode);

    /**
    	 �����̹�����Ч����ʱ���ڴ˴���Ŀ�귢��֪ͨ
    */
    void onShortAttEffect(string evt);

    /**
    	 ��Զ�̹�����λҪ�������е��ߵ�ʱ��ص����ڴ˴���ɷ��е��ߵĴ���
    */
    void onLongAttLaunch(string evt);

    StateMachine<GameCharacter>*    m_stateMachine;             // �ý�ɫ��״̬�����൱�ڸý�ɫ��AI
    GameCharacterShape*             m_shape;                    // �ý�ɫ������
    MapGrid*                        m_graph;                    // �ý�ɫ���ڵ�����
    ObjectOnMapGrid                 m_objectOnGrid;             // �ö����������ϵ�ռλ
    GameCharacterAttribute          m_attribute;                // �ý�ɫ�ĸ�������
    GameCharacterTypeEnum           m_characterType;            // ��ɫ����

    MoveTo*    m_moveAction;                                    // �����ƶ���

    int m_normatAttTargetId;                                    // ��ʱ����Ĺ���Ŀ��id
};

#endif