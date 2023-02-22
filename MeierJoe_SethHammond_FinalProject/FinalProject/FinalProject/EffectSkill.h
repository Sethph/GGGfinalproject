#pragma once
#include "Skill.h"
#include "Character.h"
class EffectSkill :
    public Skill
{
public:
    EffectSkill(string, string, int);

    double healSkill(int hpRegen) override;
};

