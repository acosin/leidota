#include "GameCharacterAttribute.h"

GameCharacterAttribute::GameCharacterAttribute(float hp, float attack, float defense, float rate, float attDistance)
{
    m_hp            =   hp;
    m_attack        =   attack;
    m_defense       =   defense;
    m_rate          =   rate;
    m_attDistance   =   attDistance;
}

GameCharacterAttribute& GameCharacterAttribute::sufferNormalAttack(GameCharacterAttribute& otherAttr)
{
    // @_@ ����͸�һ���򵥵ļ��㹫ʽ
    m_hp    -=  otherAttr.getAttack();
    m_hp    =   m_hp < 0 ? 0 : m_hp;
    return *this;
}