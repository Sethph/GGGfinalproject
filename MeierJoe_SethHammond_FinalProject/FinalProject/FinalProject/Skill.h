#pragma once
#include <string>
#include <random>
#include <ctime>
#include <iostream>
using namespace std;

class Skill
{
protected:
	string skillName;
	string desc;
	int maxCD;
	int cooldown;

public:
	Skill(string, string, int);
	string getSkillName();
	string getDesc();
	int getMaxCD();
	virtual double multipliers(int, double, double, double, int, int);
	virtual double healSkill(int);
};

