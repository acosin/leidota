#ifndef __GAME_CHARACTER_SHAPE_H__
#define __GAME_CHARACTER_SHAPE_H__

#include "cocos2d.h"
#include "cocostudio/CCArmatureDataManager.h"
#include "cocostudio/CCArmature.h"

using namespace cocos2d;
using namespace cocostudio;
using namespace std;

/**
	 �����һЩ�����ڶ����ļ��е�����
*/
#define IDLE_ACTION     "idle"
#define RUN_ACTION      "run"
#define ATTACK_ACTION   "atk1"
#define WIN_ACTION      "win"

/**
	 ��Ϸ�е����н�ɫ�����Σ���Щ����ӵ���ʾ�б��е�
*/
class GameCharacterShape : public Sprite
{
public:

    typedef std::function<void (string)> ActionFrameEventCallback;

    /**
    	 ���ڽ�ɫ���Σ���ֻ�ö�Ӧһ�����������������ļ�
         @_@ �Ժ���ܻ��һ�µ�
    */
    static GameCharacterShape* create(const std::string& fileName, const std::string& armatureName);

    /**
    	 ���Ŷ�������Ҫ�ṩ�������ƣ����������ң��Ƿ�ѭ��
    */
    void playAction(const std::string& actionName, bool loop = true, ActionFrameEventCallback eventCallBack = nullptr);

    /**
    	 ��������
    */
    void faceToRight();
    void faceToLeft();

    bool init() override;

    /**
    	 �жϵ�ǰ�����Ƿ��Ѿ�����
    */
    bool isNotInAnimation();

    /**
    	 ���ص�ǰ������֡λ��
    */
    int getCurrentFrameIndex();

    /**
    	 �������������ײ�ľ���
    */
    Rect getCollisionRect();

    /**
    	 ���ظý�ɫ���������꣬��Ϊ����Զ�̵�λ�Ĺ���Ŀ��
    */
    Vec2 getCenterPos();

protected:
    GameCharacterShape(const std::string& fileName, const std::string& armatureName);

    /**
    	 ��������������֡�¼���ʱ���ص��ú���
    */
    void onFrameEvent(Bone *bone, const string& evt, int originFrameIndex, int currentFrameIndex);

    Armature* _armature;
    string _currentAnimationName;                   // ��ǰ���ŵĶ���������

    ActionFrameEventCallback   _frameEventCallBack;    // �����Ŷ�����ʱ��֡�¼��Ļص�����
};

#endif