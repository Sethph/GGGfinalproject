#include "Characters.h"

Characters::Characters()
{
	initDroid();
	initSkirmisher();
	initSaber();
	initBoss();
	teamBuff = false;
}

Characters::~Characters()
{
	for (int i = 0; i < chars.size(); i++)
	{
		delete chars[i].getPos();
		delete chars[i].getTexture();
		delete chars[i].getSprite();
		chars[i].setPos(nullptr);
		chars[i].setTexture(nullptr);
		chars[i].setSprite(nullptr);
		for (int j = 0; j < chars[i].getSkills().size(); j++)
		{
			delete chars[i].getSkills().at(j);
			
		}
		chars[i].setSkills(nullptr, nullptr, nullptr);
	}
}

void Characters::initDroid()
{
	Character character("Enz-10", "Droid");
	character.setHP(125);
	character.setCurrentHP(125);
	character.setATK(30);
	character.setDEF(35);
	character.setSPD(80);
	character.setCRR(15);
	character.setCRD(100);
	character.setLVL(20);
	Texture* texture = new Texture;
	texture->loadFromFile("assets/droid.png");
	character.setTexture(texture);
	Vector2f* pos = new Vector2f;
	pos->x = 1350;
	pos->y = 500;
	character.setPos(pos);
	Sprite* sprite = new Sprite;
	sprite->setTexture(*texture);
	sprite->setPosition(*pos);
	character.setSprite(sprite);
	Skill* s1 = new AtkSkill("Zap", "Enz-10 zaps the enemy with electric shuriken", 0);
	Skill* s2 = new EffectSkill("Patch up", "Enz-10 heals the ally with the lowest health", 2);
	Skill* s3 = new EffectSkill("Hack", "Enz-10 hacks the enemy lowering their defenses", 4);
	character.setSkills(s1, s2, s3);
	chars.push_back(character);
}

void Characters::initSkirmisher()
{
	Character character("Kyvothe", "Skirmisher");
	character.setHP(100);
	character.setCurrentHP(100);
	character.setATK(20);
	character.setDEF(30);
	character.setSPD(20);
	character.setCRR(75);
	character.setCRD(300);
	character.setLVL(20);
	Texture* texture = new Texture;
	texture->loadFromFile("assets/skirm.png");
	character.setTexture(texture);
	Vector2f* pos = new Vector2f;
	pos->x = 1600;
	pos->y = 575;
	character.setPos(pos);
	Sprite* sprite = new Sprite;
	sprite->setTexture(*texture);
	sprite->setPosition(*pos);
	character.setSprite(sprite);
	Skill* s1 = new AtkSkill("Pot shot", "Kyvothe shoots a uncharged shot at the choosen target", 0);
	Skill* s2 = new AtkSkill("Charged shot", "Kyvothe charges his blaster to deliver a massive shot", 2);
	Skill* s3 = new AtkSkill("Bombs Away!", "Kyvothe throws a themal detanator that deals massive damage", 4);
	character.setSkills(s1, s2, s3);
	chars.push_back(character);
}

void Characters::initSaber()
{
	Character character("Lyra", "Saber");
	character.setHP(60);
	character.setCurrentHP(60);
	character.setATK(20);
	character.setDEF(20);
	character.setSPD(20);
	character.setCRR(20);
	character.setCRD(20);
	character.setLVL(20);
	Texture* texture = new Texture;
	texture->loadFromFile("assets/saber.png");
	character.setTexture(texture);
	Vector2f* pos = new Vector2f;
	pos->x = 1400;
	pos->y = 750;
	character.setPos(pos);
	Sprite* sprite = new Sprite;
	sprite->setTexture(*texture);
	sprite->setPosition(*pos);
	character.setSprite(sprite);
	Skill* s1 = new AtkSkill("Swing", "Lyra swings her saber at the targeted enemy", 0);
	Skill* s2 = new AtkSkill("Unlimited Power!", "Lyra produces lighting from her hand that attacks the enemies.", 3);
	Skill* s3 = new EffectSkill("Stand behind me!", "Lyra positions herself to reflect some of the damaged recieved back.", 3);
	character.setSkills(s1, s2, s3);
	chars.push_back(character);
}

void Characters::initBoss()
{
	Character character("Lord Baltam", "Boss");
	character.setHP(500);
	character.setCurrentHP(500);
	character.setATK(30);
	character.setDEF(50);
	character.setSPD(20);
	character.setCRR(50);
	character.setCRD(150);
	character.setLVL(20);
	Texture* texture = new Texture;
	texture->loadFromFile("assets/boss.png");
	character.setTexture(texture);
	Vector2f* pos = new Vector2f;
	pos->x = 150;
	pos->y = 350;
	character.setPos(pos);
	Sprite* sprite = new Sprite;
	sprite->setTexture(*texture);
	sprite->setPosition(*pos);
	character.setSprite(sprite);
	Skill* s1 = new AtkSkill("Ruin", "Lord Baltam attack one ", 0);
	Skill* s2 = new AtkSkill("Devastate", "Lord Baltam attack all", 2);
	Skill* s3 = new EffectSkill("Final Form", "Lord Baltam bolsters", 4);
	character.setSkills(s1, s2, s3);
	chars.push_back(character);
}

vector<Character> Characters::getChars() { return chars; }

double Characters::useAtkSkill(int attacker, int atk, double m1, double m2, double m3)
{
	double dmg = chars[attacker].getSkills().at(atk)->multipliers(chars[attacker].getATK(),
		m1, m2, m3, chars[attacker].getCritRate(), chars[attacker].getCritDamage());
	dmg *= ((100 - (double)chars[BOSS].getDEF()) / 100);
	double newHP = chars[BOSS].getCurrentHP() - dmg;
	(newHP < 0) ? chars[BOSS].setCurrentHP(0) : chars[BOSS].setCurrentHP((int)newHP);
	double cHp = chars[BOSS].getCurrentHP();
	double hp = chars[BOSS].getHP();
	return cHp / hp;
}

vector<double> Characters::useEffectSkill(int character, int skill, int scaleStat, bool buffSkill)
{
	vector<double> hpPercent;
	if (buffSkill)
	{
		if (character == BOSS)
		{
			chars[character].setDEF(75);
			teamBuff = false;
		}
		if (character == DROID) {
			chars[BOSS].setDEF(chars[BOSS].getDEF() / 2);
		}
		if (character == SABER) { teamBuff = true; };
	}
	else
	{
		int regen = (int)chars[character].getSkills().at(skill)->healSkill(chars[character].getHP());
		if (!currentHealth(SABER))
		{
			int saberHP = chars[SABER].getCurrentHP() + regen;
			if (saberHP > chars[SABER].getHP()) { chars[SABER].setCurrentHP(chars[SABER].getHP()); }
			else { chars[SABER].setCurrentHP(saberHP); }
		}
		if (!currentHealth(SKIRM))
		{
			int skirmHP = chars[SKIRM].getCurrentHP() + regen;
			if (skirmHP > chars[SKIRM].getHP()) { chars[SKIRM].setCurrentHP(chars[SKIRM].getHP()); }
			else { chars[SKIRM].setCurrentHP(skirmHP); }
		}
		if (!currentHealth(DROID))
		{
			int droidHP = chars[DROID].getCurrentHP() + regen;
			if (droidHP > chars[DROID].getHP()) { chars[DROID].setCurrentHP(chars[DROID].getHP()); }
			else { chars[DROID].setCurrentHP(droidHP); }
		}

		for (int i = 0; i < BOSS; i++)
		{
			double cHp = chars[i].getCurrentHP();
			double hp = chars[i].getHP();
			hpPercent.push_back(cHp / hp);
		}
	}
	return hpPercent;

}

double Characters::bossSingleAttack(int defender, double m1, double m2, double m3)
{
	int mitigation = 1;
	if (teamBuff) { mitigation = 2; }
	chars[BOSS].setDEF(50);
	double dmg = chars[BOSS].getSkills().at(0)->multipliers(chars[BOSS].getATK(),
		m1, m2, m3, chars[BOSS].getCritRate(), chars[BOSS].getCritDamage()) / mitigation;
	dmg *= ((100 - (double)chars[defender].getDEF()) / 100);
	double newHP = chars[defender].getCurrentHP() - dmg;
	(newHP < 0) ? chars[defender].setCurrentHP(0) : chars[defender].setCurrentHP((int)newHP);
	double cHp = chars[defender].getCurrentHP();
	double hp = chars[defender].getHP();
	teamBuff = false;
	return cHp / hp;
}

vector<double> Characters::bossMassAttack(double m1, double m2, double m3)
{
	int mitigation = 1;
	if (teamBuff) { mitigation = 2; }
	chars[BOSS].setDEF(50);
	double dmg = chars[BOSS].getSkills().at(1)->multipliers(chars[BOSS].getATK(),
		m1, m2, m3, chars[BOSS].getCritRate(), chars[BOSS].getCritDamage()) / mitigation;

	vector<double> dmgs;
	for (int i = 0; i < BOSS; i++)
	{
		double defDmg = dmg * ((100 - (double)chars[i].getDEF()) / 100);
		double newHP = chars[i].getCurrentHP() - defDmg;
		(newHP < 0) ? chars[i].setCurrentHP(0) : chars[i].setCurrentHP((int)newHP);
		double cHp = chars[i].getCurrentHP();
		double hp = chars[i].getHP();
		dmgs.push_back(cHp / hp);
	}
	teamBuff = false;
	return dmgs;
}

bool Characters::currentHealth(int turn) {
	return chars[turn].getCurrentHP() <= 0;
}

bool Characters::checkTPK()
{
	for (int i = 0; i < chars.size(); i++)
	{
		if (currentHealth(i))
		{
			chars[i].getSprite()->setPosition(Vector2f(1930, 0));
		}		
	}
	if (currentHealth(DROID) && currentHealth(SKIRM) && currentHealth(SABER)) { return true; }
	return false;
}

void Characters::reset()
{
	for (int i = 0; i < chars.size(); i++)
	{
		chars[i].setCurrentHP(chars[i].getHP());
		chars[i].getSprite()->setPosition(*chars[i].getPos());
	}
}
