#include "Character.h"

Character::Character(string name, string className)
{
	this->name = name;
	this->className = className;
	healthpoints = 0;
	currentHP = 0;
	attack = 0;
	defense = 0;
	speed = 0;
	critRate = 0;
	critDamage = 0;
	level = 1;
	texture = new Texture;
	sprite = new Sprite;
	pos = new Vector2f;
}

void Character::setSkills(Skill* s1, Skill* s2, Skill* s3)
{
	skills.push_back(s1);
	skills.push_back(s2);
	skills.push_back(s3);
}

void Character::setHP(int hp) { healthpoints = hp; }
void Character::setCurrentHP(int currHP) { currentHP = currHP; }
void Character::setATK(int atk) { attack = atk; }
void Character::setDEF(int def) { defense = def; }
void Character::setSPD(int spd) { speed = spd; }
void Character::setCRR(int crr) { critRate = crr; }
void Character::setCRD(int crd) { critDamage = crd; }
void Character::setLVL(int lvl) { level = lvl; }
void Character::setTexture(Texture* texture) { this->texture = texture; }
void Character::setSprite(Sprite* sprite) { this->sprite = sprite; }
void Character::setPos(Vector2f* pos) { this->pos = pos; }
String Character::getName() { return this->name; }
Texture* Character::getTexture() { return texture; }
Vector2f* Character::getPos() { return pos; }
Sprite* Character::getSprite() { return sprite; }

vector<Skill*> Character::getSkills() { return skills; }
int Character::getHP() { return healthpoints; }
int Character::getCurrentHP() { return currentHP; }
int Character::getATK() { return attack; }
int Character::getDEF() { return defense; }
int Character::getCritRate() { return critRate; }
int Character::getCritDamage() { return critDamage; }