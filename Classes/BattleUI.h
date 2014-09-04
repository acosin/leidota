#ifndef __BATTLE_UI_H__
#define __BATTLE_UI_H__

#include "ui/CocosGUI.h"
#include "UIView.h"
#include "GameCharacter.h"

using namespace cocos2d;
using namespace ui;

/**
* ս��ʱ���UI���棬��Ҫ����һЩ������һЩ��Ϣ����ʾ
*/
class BattleUI : public UIView
{
public:
    bool init() override;

    void onWee(RefreshUIMsg& msg) override;

    CREATE_FUNC(BattleUI);

protected:
    BattleUI();

    void setWeeList() override;

    /**
    * ˢ��ս��UI�еĽ�ɫ���ݵ���ʾ 
    */
    void refreshCharacter(GameCharacter* character);

    LoadingBar*     m_leaderHpBar;                  // ����hp��
    ImageView*      m_leaderIcon;                   // ���ǵ�ͷ��

    LoadingBar*     m_enemyHpBar;                   // ��ǰ�������ڴ�ĵ��˵�hp
    ImageView*      m_enemyIcon;                    // ����ͷ��
    Node*           m_enemyPanel;                   // ������Ϣ�������ڵ�

    Button*         m_convergeBtn;                  // ���л����İ�ť
    Button*         m_changeTargetBtn;              // ������ǰ���ǵĹ���Ŀ��
    Button*         m_skillBtn;                     // ���ܰ�ť
};

#endif