#include "Skill.h"


Skill::Skill(string skillName, string desc, int maxCD) {
	this->skillName = skillName;
	this->desc = desc;
	this->maxCD = maxCD;
	cooldown = 0;
}

string Skill::getSkillName() { return skillName; }
string Skill::getDesc() { return desc; }
int Skill::getMaxCD() { return maxCD; }
double Skill::multipliers(int, double, double, double, int, int) { return NULL; }
double Skill::healSkill(int) { return NULL; }
