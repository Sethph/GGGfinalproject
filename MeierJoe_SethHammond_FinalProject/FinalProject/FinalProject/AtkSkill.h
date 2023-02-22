#pragma once
#include "Skill.h"
#include "Character.h"
class AtkSkill :
    public Skill
{
private:
    double damage;

public:
    AtkSkill(string, string, int);
    double multipliers(int, double, double, double, int, int) override;
};