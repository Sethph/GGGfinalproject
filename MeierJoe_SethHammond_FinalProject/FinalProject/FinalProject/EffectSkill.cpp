#include "EffectSkill.h"

EffectSkill::EffectSkill(string skillName, string skillDesc, int cooldown) :
	Skill(skillName, skillDesc, cooldown)
{
}

double EffectSkill::healSkill(int hpRegen)
{
	return hpRegen * .15;
}
