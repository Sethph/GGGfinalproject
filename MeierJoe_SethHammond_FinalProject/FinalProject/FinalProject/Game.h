#pragma once
#include "Characters.h"
#include <SFML/Audio.hpp>

class Game
{
private:
	RenderWindow window{ VideoMode(1920,1080),//"Spaceballs 2 the game: The search for more money" };
	"The Epic Space Battle of the Really No Good Lord Baltam Against the Mighty Trio of Heroes" };
	Clock clock;
	Characters charsClass;
	vector<Character> chars;
	Font font;
	Text turnName;
	Sprite* bkg;
	Sprite* hud;
	vector<RectangleShape> healthBars;
	vector<Text> actions;
	vector<Text> names;
	vector<SoundBuffer*> buffers;
	vector<Sound> sfx;
	bool gameover;
	bool win;
	bool lose;
	int turn;

public:
	Game();
	~Game();
	void run();
	void play();
	void pause();
	void eventHandler();
	void loadHUD();
	void loadSFX();
	void drawHUD();
	void drawChars();
	bool actionEvent(Event);
	void action(int, int);
	void saberAction(int);
	void skirmAction(int);
	void droidAction(int);
	void bossAction(int);
	//Saber Skills
	void swing();
	void lightning();
	void shield();
	//Skirmisher Skills
	void beam();
	void chargedShot();
	void detonator();
	//Droid Skills
	void zap();
	void patch(int);
	void hack();
	//Boss Skills
	void ruin();
	void devastate();
	void finalForm();

};