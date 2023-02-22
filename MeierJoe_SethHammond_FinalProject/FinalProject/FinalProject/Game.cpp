#include "Game.h"
#define gameState(state)(state ? pause() : play())

Game::Game()
{
    bkg = new Sprite;
    hud = new Sprite;
    chars = charsClass.getChars();
    turn = BOSS;
    gameover = true;
    win = false;
    lose = false;
}

Game::~Game()
{
    delete bkg;
    delete hud;
    for (int i = 0; i < buffers.size(); i++)
    {
         delete buffers[i];
         buffers[i] = nullptr;
    }

}
void Game::run()
{
    loadHUD();
    loadSFX();
    Music music;
    music.openFromFile("assets/sounds/music.wav");
    music.setLoop(true);
    music.play();
    while (window.isOpen())
    {
        gameState(gameover);
        window.display();
    }
}

void Game::eventHandler()
{
    Event event;

    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed) { window.close(); }
        if (event.type == Event::KeyPressed)
        {
            if (event.key.code == Keyboard::Escape) { window.close(); }
        }

        if (charsClass.checkTPK()) { sfx[8].play(); lose = true; gameover = true; }
        else if (charsClass.currentHealth(BOSS)) { sfx[13].play(); win = true; gameover = true; }
        else if (turn < 3 && charsClass.currentHealth(turn)) { turn++; }

        else if (turn == 3) 
        {
            uniform_int_distribution<int> randNum(0, 2);
            default_random_engine eng((unsigned int)time(0));
            int bossSkill = randNum(eng);
            action(BOSS, bossSkill);
            turn = 0;
        }
        else if (actionEvent(event)) { turn++; }
    }
}
void Game::play()
{      
        eventHandler();
        turnName.setString(chars[turn].getName());
        window.clear();
        drawHUD();
        window.draw(turnName);
        drawChars();        
}

void Game::pause()
{
    window.clear();
    healthBars.clear();
    actions.clear();
    names.clear();
    turn = BOSS;

    loadHUD();
    charsClass.reset();

    Texture texture;
    texture.loadFromFile("assets/titleScreen.png");
    Sprite titleScreen;
    titleScreen.setTexture(texture);
    Text outcome;
    outcome.setFont(font);
    outcome.setFillColor(Color::Cyan);
    outcome.setStyle(Text::Bold);
    outcome.setString("");
    if(win) { outcome.setString("You defeated Lord Baltam!!!"); }
    if(lose) { outcome.setString("YOU DIED"); }
    outcome.setPosition(Vector2f((window.getSize().x / 2) - (outcome.getGlobalBounds().width / 2), 900));

    Text enter;
    enter.setFont(font);
    enter.setFillColor(Color::Cyan);
    enter.setStyle(Text::Bold);
    enter.setString("Welcome to your Doom -- Enter");
    enter.setPosition(Vector2f((window.getSize().x / 2) - (enter.getGlobalBounds().width / 2), 800));
    Text title;
    title.setFont(font);
    title.setCharacterSize(84);
    title.setFillColor(Color::Cyan);
    title.setStyle(Text::Bold);
    title.setString("Epic Space Battle!!!");
    title.setPosition(Vector2f((window.getSize().x / 2) - (title.getGlobalBounds().width / 2), 100));
    window.draw(titleScreen);
    window.draw(enter);
    window.draw(title);
    window.draw(outcome);
    Event event;
    while (window.pollEvent(event))
    {
        if (event.type == Event::KeyPressed)
        {
            if (event.key.code == Keyboard::Escape) { window.close(); }
            if (event.key.code == Keyboard::Enter) { gameover = false; win = false; lose = false;}
        }
    }

}

void Game::loadHUD()
{
    RectangleShape healthBar(Vector2f(124, 10));
    healthBar.setFillColor(Color::Cyan);
    healthBar.setPosition(1146, 90);
    healthBars.push_back(healthBar);
    healthBar.setPosition(1174, 194);
    healthBars.push_back(healthBar);
    healthBar.setPosition(1150, 284);
    healthBars.push_back(healthBar);
    healthBar.setFillColor(Color::Magenta);
    healthBar.setPosition(620, 200);
    healthBar.setSize(Vector2f(154, 10));
    healthBars.push_back(healthBar);

    Text text;
    font.loadFromFile("assets/Aiden.otf");
    text.setFont(font);
    //text.setCharacterSize(20);
    text.setFillColor(Color::Cyan);
    text.setStyle(Text::Bold);
    text.setString("Action 1");
    text.setPosition(930, 160);
    actions.push_back(text);
    text.setString("Action 2");
    text.setPosition(930, 200);
    actions.push_back(text);
    text.setString("Action 3");
    text.setPosition(930, 240);
    actions.push_back(text);

    text.setFillColor(Color::Black);
    text.setString(chars[DROID].getName());
    text.setPosition(1110, 42);
    names.push_back(text);
    text.setString(chars[SKIRM].getName());
    text.setPosition(1140, 150);
    names.push_back(text);
    text.setString(chars[SABER].getName());
    text.setPosition(1114, 236);
    names.push_back(text);
    text.setString(chars[BOSS].getName());
    text.setPosition(670, 142);
    names.push_back(text);

    turnName.setFont(font);
    turnName.setFillColor(Color::Cyan);
    turnName.setStyle(Text::Bold);
    turnName.setPosition(1005, 95);
    turnName.setCharacterSize(18);

    Texture* background = new Texture;
    background->loadFromFile("assets/bkg.png");
    bkg->setTexture(*background);

    Texture* menu = new Texture;
    menu->loadFromFile("assets/hud.png");
    hud->setTexture(*menu);
    hud->setPosition(603, 0);
}

void Game::loadSFX()
{
    SoundBuffer* buffer0 = new SoundBuffer;
    buffer0->loadFromFile("assets/sounds/beam.wav");
    buffers.push_back(buffer0);
    Sound sound;
    sound.setBuffer(*buffer0);
    sfx.push_back(sound);

    SoundBuffer* buffer1 = new SoundBuffer;
    buffer1->loadFromFile("assets/sounds/charge.wav");
    buffers.push_back(buffer1);
    sound.setBuffer(*buffer1);
    sfx.push_back(sound);

    SoundBuffer* buffer2 = new SoundBuffer;
    buffer2->loadFromFile("assets/sounds/detonate.wav");
    buffers.push_back(buffer2);
    sound.setBuffer(*buffer2);
    sfx.push_back(sound);

    SoundBuffer* buffer3 = new SoundBuffer;
    buffer3->loadFromFile("assets/sounds/devastate.wav");
    buffers.push_back(buffer3);
    sound.setBuffer(*buffer3);
    sfx.push_back(sound);

    SoundBuffer* buffer4 = new SoundBuffer;
    buffer4->loadFromFile("assets/sounds/die.wav");
    buffers.push_back(buffer4);
    sound.setBuffer(*buffer4);
    sfx.push_back(sound);

    SoundBuffer* buffer5 = new SoundBuffer;
    buffer5->loadFromFile("assets/sounds/ff.wav");
    buffers.push_back(buffer5);
    sound.setBuffer(*buffer5);
    sfx.push_back(sound);

    SoundBuffer* buffer6 = new SoundBuffer;
    buffer6->loadFromFile("assets/sounds/hack.wav");
    buffers.push_back(buffer6);
    sound.setBuffer(*buffer6);
    sfx.push_back(sound);

    SoundBuffer* buffer7 = new SoundBuffer;
    buffer7->loadFromFile("assets/sounds/lightning.wav");
    buffers.push_back(buffer7);
    sound.setBuffer(*buffer7);
    sfx.push_back(sound);

    SoundBuffer* buffer8 = new SoundBuffer;
    buffer8->loadFromFile("assets/sounds/lose.wav");
    buffers.push_back(buffer8);
    sound.setBuffer(*buffer8);
    sfx.push_back(sound);

    SoundBuffer* buffer9 = new SoundBuffer;
    buffer9->loadFromFile("assets/sounds/patch.wav");
    buffers.push_back(buffer9);
    sound.setBuffer(*buffer9);
    sfx.push_back(sound);

    SoundBuffer* buffer10 = new SoundBuffer;
    buffer10->loadFromFile("assets/sounds/ruin.wav");
    buffers.push_back(buffer10);
    sound.setBuffer(*buffer10);
    sfx.push_back(sound);

    SoundBuffer* buffer11 = new SoundBuffer;
    buffer11->loadFromFile("assets/sounds/shield.wav");
    buffers.push_back(buffer11);
    sound.setBuffer(*buffer11);
    sfx.push_back(sound);

    SoundBuffer* buffer12 = new SoundBuffer;
    buffer12->loadFromFile("assets/sounds/swing.wav");
    buffers.push_back(buffer12);
    sound.setBuffer(*buffer12);
    sfx.push_back(sound);

    SoundBuffer* buffer13 = new SoundBuffer;
    buffer13->loadFromFile("assets/sounds/win.wav");
    buffers.push_back(buffer13);
    sound.setBuffer(*buffer13);
    sfx.push_back(sound);

    SoundBuffer* buffer14 = new SoundBuffer;
    buffer14->loadFromFile("assets/sounds/zap.wav");
    buffers.push_back(buffer14);
    sound.setBuffer(*buffer14);
    sfx.push_back(sound);

}

void Game::drawHUD()
{
    window.draw(*bkg);
    window.draw(*hud);

    for (const auto& healthBar : healthBars) { window.draw(healthBar); }
    for (const auto& name : names) { window.draw(name); }

    if (!gameover)
    {
        for (int i = 0; i < actions.size(); i++)
        {
            actions[i].setString(chars[turn].getSkills().at(i)->getSkillName());
            window.draw(actions[i]);
        }
    }
}

void Game::drawChars()
{
    for (int i = 0; i < chars.size(); i++)
    {
        Sprite sprite = *chars[i].getSprite();
        if ((int)clock.getElapsedTime().asSeconds() % 2 == 0 && i == turn)
        {
            sprite.move(5.0f, 0.0f);
            sprite.rotate(5);
        }
        window.draw(sprite);
    }
}

bool Game::actionEvent(Event event)
{

    if (event.type == Event::MouseButtonPressed)
    {

        if (actions[0].getGlobalBounds().contains((float)event.mouseButton.x, (float)event.mouseButton.y))
        {
            action(turn, 0);
            return true;
        }

        if (actions[1].getGlobalBounds().contains((float)event.mouseButton.x, (float)event.mouseButton.y))
        {
            action(turn, 1);
            return true;
        }

        if (actions[2].getGlobalBounds().contains((float)event.mouseButton.x, (float)event.mouseButton.y))
        {
            action(turn, 2);
            return true;
        }
    }
    if (event.type == Event::MouseMoved)
    {
        //cout << "x: " << event.mouseMove.x << " y: " << event.mouseMove.y << endl;

        if (actions[0].getGlobalBounds().contains((float)event.mouseMove.x, (float)event.mouseMove.y))
        {
            actions[0].setCharacterSize(22);
        }
        else { actions[0].setCharacterSize(20); }

        if (actions[1].getGlobalBounds().contains((float)event.mouseMove.x, (float)event.mouseMove.y))
        {
            actions[1].setCharacterSize(22);
        }
        else { actions[1].setCharacterSize(20); }

        if (actions[2].getGlobalBounds().contains((float)event.mouseMove.x, (float)event.mouseMove.y))
        {
            actions[2].setCharacterSize(22);
        }
        else { actions[2].setCharacterSize(20); }
    }
    return false;
}

void Game::action(int player, int action)
{

    switch (player)
    {
    case SABER:
        saberAction(action);
        break;
    case SKIRM:
        skirmAction(action);
        break;
    case DROID:
        droidAction(action);
        break;
    case BOSS:
        bossAction(action);
        break;
    default:
        cout << "Invalid" << endl;
        break;
    }
}

void Game::saberAction(int action)
{
    switch (action)
    {
    case 0:
        swing();
        break;
    case 1:
        lightning();
        break;
    case 2:
        shield();
        break;
    default:
        cout << "Invalid" << endl;
        break;
    }
}

void Game::skirmAction(int action)
{
    switch (action)
    {
    case 0:
        beam();
        break;
    case 1:
        chargedShot();
        break;
    case 2:
        detonator();
        break;
    default:
        cout << "Invalid" << endl;
        break;
    }
}

void Game::droidAction(int action)
{
    switch (action)
    {
    case 0:
        zap();
        break;
    case 1:
        patch(DROID);
        break;
    case 2:
        hack();
        break;
    default:
        cout << "Invalid" << endl;
        break;
    }
}

void Game::bossAction(int action)
{
    switch (action)
    {
    case 0:
        ruin();
        break;
    case 1:
        devastate();
        break;
    case 2:
        finalForm();
        break;
    default:
        cout << "Invalid" << endl;
        break;
    }
}

//Saber Skills
void Game::swing()
{
    double hpPercent = charsClass.useAtkSkill(SABER, 0, 1.0, 1.1, 1.5);
    healthBars[BOSS].setSize(Vector2f(154 * hpPercent, 10));

    sfx[12].play();
    Clock dt;
    Vector2f pos = *chars[SABER].getPos();
    Sprite boss = *chars[BOSS].getSprite();
    chars[SABER].getSprite()->setTextureRect(IntRect(chars[SABER].getSprite()->
        getGlobalBounds().width, 0, -chars[SABER].getSprite()->getGlobalBounds().width,
        chars[SABER].getSprite()->getGlobalBounds().height));
    chars[SABER].getSprite()->setPosition(0, boss.getPosition().y - 100);
    int file = 1;
    int speed = 200;
    Sprite sprite;
    sprite.setPosition(150, boss.getPosition().y);
    sprite.rotate(30);
    

    while (true)
    {
        Texture texture;
        window.clear();
        drawHUD();
        drawChars();
        texture.loadFromFile("assets/swing/" + std::to_string(file) + ".png");
        sprite.setTexture(texture);
        sprite.move(1 * dt.restart().asSeconds() * speed, 0);
        window.draw(sprite);
        window.display();
        file++;
        if (file == 8) { file = 1; }
        if (sprite.getGlobalBounds().contains(boss.getPosition().x + 300,
            sprite.getPosition().y)) {
            chars[SABER].getSprite()->setPosition(pos);
            chars[SABER].getSprite()->setTextureRect(IntRect(0, 0,
                chars[SABER].getSprite()->getGlobalBounds().width,
                chars[SABER].getSprite()->getGlobalBounds().height));
            return;
        }
    } 
}
void Game::lightning()
{
    double hpPercent = charsClass.useAtkSkill(SABER, 1, 1.0, 1.1, 1.5);
    healthBars[BOSS].setSize(Vector2f(154 * hpPercent, 10));

    sfx[7].play();
    Clock dt;
    Vector2f pos = *chars[SABER].getPos();
    Sprite boss = *chars[BOSS].getSprite();
    int file = 0;
    int speed = 2000;
    bool asc = true;
    Sprite sprite;
    sprite.setPosition(pos.x - 150, pos.y - 50);
    while (true)
    {
        Texture texture;
        texture.loadFromFile("assets/lightning/" + std::to_string(file) + ".png");
        sprite.setTexture(texture);
        float dtTime = dt.restart().asSeconds();
        float curSpeedX = dtTime * (speed + 750);
        float curSpeedY = dtTime * speed;
        if (asc) { sprite.move(-1 * curSpeedX, -1 * curSpeedY); }
        else { sprite.move(-1 * curSpeedX, curSpeedY); }
        if (sprite.getPosition().y < 300) { asc = false; }
        window.draw(sprite);
        window.display();
        file++;
        if (file == 18) { file = 0; }
        if (sprite.getGlobalBounds().contains(boss.getPosition().x + 150, sprite.getPosition().y)) { return; }
    }
}

void Game::shield()
{
    sfx[11].play();
    Vector2f pos = *chars[SABER].getPos();
    int file = 1;
    int initial = clock.getElapsedTime().asMilliseconds();
    Sprite sprite;
    sprite.setPosition(pos.x - 250, pos.y - 300);
    while (true)
    {
        Texture texture;
        window.clear();
        drawHUD();
        drawChars();
        texture.loadFromFile("assets/shield/" + std::to_string(file) + ".png");
        sprite.setTexture(texture);
        window.draw(sprite);
        window.display();
        file++;
        if (file == 17) { file = 1; }
        int check = clock.getElapsedTime().asMilliseconds() - initial;
        if (check >= 1000) { return; }
    }
}

//Skirmisher Skills
void Game::beam()
{
    double hpPercent = charsClass.useAtkSkill(SKIRM, 0, 1.0, 1.1, 1.5);
    healthBars[BOSS].setSize(Vector2f(154 * hpPercent, 10));
    
    sfx[0].play();
    Clock dt;
    Vector2f pos = *chars[SKIRM].getPos();
    Sprite boss = *chars[BOSS].getSprite();
    int file = 1;
    int speed = 2000;
    Sprite sprite;
    sprite.setPosition(pos.x - 70, pos.y - 50);
    while (true)
    {
        Texture texture;
        window.clear();
        drawHUD();
        drawChars();
        texture.loadFromFile("assets/beam/" + std::to_string(file) + ".png");
        sprite.setTexture(texture);
        sprite.move(-1 * dt.restart().asSeconds() * speed, 0);
        window.draw(sprite);
        window.display();
        file++;
        if (file == 9) { file = 1; }
        if (sprite.getGlobalBounds().contains(boss.getPosition().x + 150,
            sprite.getPosition().y)) {
            return;
        }
    }
}

void Game::chargedShot()
{
    double hpPercent = charsClass.useAtkSkill(SKIRM, 1, 1.0, 1.25, 1.75);
    healthBars[BOSS].setSize(Vector2f(154 * hpPercent, 10));

    sfx[1].play();
    Clock dt;
    Vector2f pos = *chars[SKIRM].getPos();
    Sprite boss = *chars[BOSS].getSprite();
    float speed = 900;
    int file = 1;
    Sprite sprite;
    sprite.setPosition(pos.x - 300, pos.y - 50);
    while (true)
    {
        Texture texture;

        window.clear();
        drawHUD();
        drawChars();
        texture.loadFromFile("assets/chargedShot/" + std::to_string(file) + ".png");
        sprite.setTexture(texture);
        sprite.move(-1 * dt.restart().asSeconds() * speed, 0);
        window.draw(sprite);
        window.display();
        file++;
        if (file == 7) { file = 1; }
        if (sprite.getGlobalBounds().contains(boss.getPosition().x + 150,
            sprite.getPosition().y)) {
            return;
        }
    }
}

void Game::detonator()
{
    double hpPercent = charsClass.useAtkSkill(SKIRM, 2, 1.5, 1.75, 1.95);
    healthBars[BOSS].setSize(Vector2f(154 * hpPercent, 10));

    
    Clock dt;
    Vector2f pos = *chars[SKIRM].getPos();
    Sprite boss = *chars[BOSS].getSprite();
    int file = 0;
    int speed = 500;
    bool asc = true;
    bool explode = false;
    Sprite sprite;
    sprite.setPosition(pos.x + 150, pos.y + 50);
    while (true)
    {
        Texture texture;
        window.clear();
        drawHUD();
        drawChars();
        texture.loadFromFile("assets/detonate/" + std::to_string(file) + ".png");
        sprite.setTexture(texture);
        float dtTime = dt.restart().asSeconds();
        float curSpeedX = dtTime * (speed + 750);
        float curSpeedY = dtTime * speed;
        if (!explode)
        {
            if (asc) { sprite.move(-1 * curSpeedX, -1 * curSpeedY); }
            else { sprite.move(-1 * curSpeedX, curSpeedY); }
            if (sprite.getPosition().y < 300) { asc = false; }
        }
        window.draw(sprite);
        window.display();

        if (sprite.getGlobalBounds().contains(boss.getPosition().x + 150,
            sprite.getPosition().y)) {
            sfx[2].play();
            Sprite spr;
            file++;
            spr.setPosition(boss.getPosition().x + 10,
                boss.getPosition().y + 30);
            while (true)
            {
                Texture texture;
                window.clear();
                drawHUD();
                drawChars();
                texture.loadFromFile("assets/detonate/" + std::to_string(file) + ".png");
                spr.setTexture(texture);
                window.draw(spr);
                window.display();
                file++;
                if (file == 25) { return; }
            }
        }
    }
}

//Droid Skills

void Game::zap()
{
    sfx[14].play();
    double hpPercent = charsClass.useAtkSkill(DROID, 0, 1.0, 1.1, 1.5);
    healthBars[BOSS].setSize(Vector2f(154 * hpPercent, 10));

    Clock dt;
    Vector2f pos = *chars[DROID].getPos();
    Sprite boss = *chars[BOSS].getSprite();
    int file = 1;
    int speed = 500;
    Sprite sprite;
    sprite.setPosition(pos.x - 70, pos.y - 50);
    while (true)
    {
        Texture texture;
        window.clear();
        drawHUD();
        drawChars();
        texture.loadFromFile("assets/zap/" + std::to_string(file) + ".png");
        sprite.setTexture(texture);
        sprite.move(-1 * dt.restart().asSeconds() * speed, 0);
        window.draw(sprite);
        window.display();
        file++;
        if (file == 7) { file = 1; }
        if (sprite.getGlobalBounds().contains(boss.getPosition().x + 150, sprite.getPosition().y)) { return; }
    }
}

void Game::patch(int target)
{
    vector<double> hpPercents = charsClass.useEffectSkill(DROID, 1, chars[DROID].getHP(), false);
    for (int i = 0; i < BOSS; i++)
    {
        healthBars[i].setSize(Vector2f(124 * hpPercents[i], 10));
    }

    sfx[9].play();
    Vector2f pos = *chars[target].getPos();
    int file = 1;
    int initial = clock.getElapsedTime().asMilliseconds();
    Sprite sprite;
    sprite.setPosition(pos.x - 150, pos.y - 50);
    while (true)
    {
        Texture texture;
        window.clear();
        drawHUD();
        drawChars();
        texture.loadFromFile("assets/patch/" + std::to_string(file) + ".png");
        sprite.setTexture(texture);
        window.draw(sprite);
        window.display();
        file++;
        if (file == 9) { file = 1; }
        int check = clock.getElapsedTime().asMilliseconds() - initial;
        if (check >= 1000) { return; }
    }
}

void Game::hack()
{
    sfx[6].play();
    charsClass.useEffectSkill(DROID, 1, chars[DROID].getHP(), true);
    Vector2f pos = *chars[BOSS].getPos();
    int file = 1;
    int initial = clock.getElapsedTime().asMilliseconds();
    Sprite sprite;
    sprite.setPosition(pos.x - 100, pos.y);
    while (true)
    {
        Texture texture;
        window.clear();
        drawHUD();
        drawChars();
        texture.loadFromFile("assets/hack/" + std::to_string(file) + ".png");
        sprite.setTexture(texture);
        window.draw(sprite);
        window.display();
        file++;
        if (file == 9) { file = 1; }
        int check = clock.getElapsedTime().asMilliseconds() - initial;
        if (check >= 1000) { return; }
    }
}

//Boss Skills
void Game::ruin()
{
    uniform_int_distribution<int> randNum(0, 2);
    default_random_engine eng((unsigned int)time(0));
    int defender = randNum(eng);
    while (charsClass.currentHealth(defender)) { defender = randNum(eng); }
    double hpPercent = charsClass.bossSingleAttack(defender, 1.0, 1.1, 1.5);
    if (hpPercent <= 0.0) { sfx[4].play(); }
    healthBars[defender].setSize(Vector2f(124 * hpPercent, 10));

    sfx[10].play();
    Clock dt;
    Vector2f pos = *chars[BOSS].getPos();
    Sprite dfdr = *chars[defender].getSprite();
    int file = 1;
    int file2 = 1;
    int xSpeed = 1000;
    int ySpeed = 300;
    //int initial = clock.getElapsedTime().asMilliseconds();
    Sprite sprite;
    sprite.setPosition(pos.x + 300, pos.y);
    Sprite inside;
    inside.setPosition(pos.x + 300, pos.y);

    while (true)
    {
        Texture texture;
        Texture texture2;
        float dtT = dt.restart().asSeconds();
        window.clear();
        drawHUD();
        drawChars();
        texture.loadFromFile("assets/ruin/" + std::to_string(file) + ".png");
        sprite.setTexture(texture);
        texture2.loadFromFile("assets/ruin/internal/" + std::to_string(file2) + ".png");
        inside.setTexture(texture2);

        sprite.move(dtT * xSpeed, dtT * ySpeed);
        inside.move(dtT * xSpeed, dtT * ySpeed);
        window.draw(sprite);
        window.draw(inside);
        window.display();
        file++; file2++;
        if (file == 26) { file = 1; }
        if (file2 == 14) { file2 = 1; }
        if (sprite.getGlobalBounds().contains(dfdr.getPosition().x + 150,
            dfdr.getPosition().y + 100)) {
            return;
        }
    }

}

void Game::devastate()
{
    vector<double> hpPercents = charsClass.bossMassAttack(1.0, 1.1, 1.5);
    for (int i = 0; i < BOSS; i++)
    {
        if (hpPercents[i] <= 0.0) { sfx[4].play(); }
        healthBars[i].setSize(Vector2f(124 * hpPercents[i], 10));
    }

    sfx[3].play();
    Vector2f pos = *chars[DROID].getPos();
    int file = 1;
    int file2 = 1;
    int initial = clock.getElapsedTime().asMilliseconds();
    Sprite sprite;
    sprite.setPosition(pos.x - 150, pos.y - 50);
    Sprite inside;
    inside.setPosition(pos.x, pos.y + 100);

    while (true)
    {
        Texture texture;
        Texture texture2;
        window.clear();
        drawHUD();
        drawChars();
        texture.loadFromFile("assets/devastate/" + std::to_string(file) + ".png");
        sprite.setTexture(texture);
        texture2.loadFromFile("assets/devastate/internal/" + std::to_string(file2) + ".png");
        inside.setTexture(texture2);
        window.draw(sprite);
        window.draw(inside);
        window.display();
        file++; file2++;
        if (file == 26) { file = 1; }
        if (file2 == 9) { file2 = 1; }
        int check = clock.getElapsedTime().asMilliseconds() - initial;
        if (check >= 5000) { return; }
    }
}

void Game::finalForm()
{
    sfx[5].play();
    charsClass.useEffectSkill(BOSS, 1, chars[BOSS].getHP(), true);
    Vector2f pos = *chars[BOSS].getPos();
    int file = 1;
    int initial = clock.getElapsedTime().asMilliseconds();
    Sprite sprite;
    sprite.setPosition(pos.x - 150, pos.y - 210);
    while (true)
    {
        Texture texture;
        window.clear();
        drawHUD();
        drawChars();
        texture.loadFromFile("assets/ff/" + std::to_string(file) + ".png");
        sprite.setTexture(texture);
        window.draw(sprite);
        window.display();
        file++;
        if (file == 12) { file = 1; }
        int check = clock.getElapsedTime().asMilliseconds() - initial;
        if (check >= 1000) { return; }
    }
}
