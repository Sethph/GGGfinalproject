#pragma once
#include "Skill.h"
#include <Vector>
#include <SFML/Graphics.hpp>
using namespace sf;

class Character
{
private:
	string name;
	string className;
	int healthpoints;
	int currentHP;
	int attack;
	int defense;
	int speed;
	int critRate;
	int critDamage;
	int level;
	Texture* texture;
	Sprite* sprite;
	Vector2f* pos;
	vector<Skill*> skills;

public:
	Character(string, string);
	void setSkills(Skill*, Skill*, Skill*);
	void setHP(int);
	void setCurrentHP(int);
	void setATK(int);
	void setDEF(int);
	void setSPD(int);
	void setCRR(int);
	void setCRD(int);
	void setLVL(int);
	void setTexture(Texture*);
	void setSprite(Sprite*);
	void setPos(Vector2f*);
	String getName();
	Texture* getTexture();
	Vector2f* getPos();
	Sprite* getSprite();

	vector<Skill*> getSkills();

	int getHP();
	int getCurrentHP();
	int getATK();
	int getDEF();
	int getCritRate();
	int getCritDamage();
};


