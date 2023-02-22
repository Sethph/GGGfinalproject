#pragma once
#include "Character.h"
#include "Skill.h"
#include "AtkSkill.h"
#include "EffectSkill.h"
#define DROID 0
#define SKIRM 1
#define SABER 2
#define BOSS 3

class Characters
{
private:
	vector<Character> chars;
	bool teamBuff;
public:
	Characters();
	~Characters();
	void initDroid();
	void initSkirmisher();
	void initSaber();
	void initBoss();
	void reset();
	vector<Character> getChars();
	double useAtkSkill(int, int, double, double, double);
	vector<double> useEffectSkill(int, int, int, bool);
	double bossSingleAttack(int, double, double, double);
	vector<double> bossMassAttack(double, double, double);
	bool currentHealth(int);
	bool checkTPK();
};

