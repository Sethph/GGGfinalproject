#include "AtkSkill.h"

AtkSkill::AtkSkill(string skillName, string skillDesc, int cooldown) : 
	Skill(skillName, skillDesc,cooldown)
{ 
	damage = 0;
}

double AtkSkill::multipliers(int attack, double mult1, double mult2, double mult3, 
	int critRate, int critDmg) 
{
	damage = (double)attack * mult1 * mult2 * mult3;
	uniform_int_distribution<int> randNum(0, 100);
	default_random_engine eng((unsigned int)time(0));
	int critRatio = randNum(eng);
	if (critRate > critRatio) {
		double dmgRatio = (double)critDmg * .01;
		damage = damage * dmgRatio;
	}
	cooldown = maxCD;
	return damage;
}