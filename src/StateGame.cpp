/*
 * StateGame.cpp
 *
 *  Created on: Jun 18, 2013
 *      Author: AT WORK
 */

#include "StateGame.h"

StateGame::StateGame() {
}

StateGame::~StateGame() {
	unload();
}
void StateGame::load(StateArgs arguments) {
	this->arguments = arguments;
	HUDScore = new Text("../ttf/Helvetica LT Black.ttf", "000000000", 15, 0,
			(SDL_Color ) { 255, 255, 255 }, 75 / 2, 40);
	HUDMultiplier = new Text("../ttf/Helvetica LT Black.ttf", "1", 50, 0,
			(SDL_Color ) { 255, 255, 255 }, 100, 170);
	HUDPlayerLives = new Text("../ttf/Helvetica LT Black.ttf", "04", 30, 1,
			(SDL_Color ) { 255, 255, 255 }, 81, 511);
	HUDPlayerBombs = new Text("../ttf/Helvetica LT Black.ttf", "4", 20, 0,
			(SDL_Color ) { 255, 255, 255 }, 72, 337);
	HUDBackground = new Sprite("../gfx/HUD.png");
	int numSpritesPlayer[4] = { 1, 1, 1, 1 };
	PlayerAnimation = new Animation("../gfx/Player_sprites.png", 5, 5,
			numSpritesPlayer, 88, true);
	Background = new Sprite("../gfx/background.jpg");

	int numSpritesDeath[1] = { 4 };
	playerDeath = new Animation("../gfx/EnemyExplosion.png", 150, 1,
			numSpritesDeath, 77, false);

	bulletSprites.push_back(new Sprite("../gfx/Balas_Gorok_003-06.png"));
	bulletSprites.push_back(new Sprite("../gfx/Balas_Gorok_003-07.png"));
	bulletSprites.push_back(new Sprite("../gfx/Balas_Gorok_002-08.png"));
	bulletSprites.push_back(new Sprite("../gfx/Balas_Gorok_002-09.png"));
	bulletSprites.push_back(new Sprite("../gfx/Balas_LASER-10.png"));
	bulletSprites.push_back(new Sprite("../gfx/missiles.png"));
	bulletSprites.push_back(new Sprite("../gfx/laserL1.png"));
	bulletSprites.push_back(new Sprite("../gfx/laserL2.png"));
	bulletSprites.push_back(new Sprite("../gfx/laserL3.png"));

	enemySprites.push_back(new Sprite("../gfx/enemy1.png"));
	enemySprites.push_back(new Sprite("../gfx/enemy2.png"));
	enemySprites.push_back(new Sprite("../gfx/enemy3.png"));
	enemySprites.push_back(new Sprite("../gfx/orbitingEnemy.png"));
	enemySprites.push_back(new Sprite("../gfx/invisibleSprite.png"));

	int num[1] = { 2 };
	enemyHitAnimations.push_back(
			new Animation("../gfx/enemy1Hit.png", 200, 1, num, 100, true));
	enemyHitAnimations.push_back(
			new Animation("../gfx/enemy1Hit.png", 200, 1, num, 100, true));
	enemyHitAnimations.push_back(
			new Animation("../gfx/enemy1Hit.png", 200, 1, num, 100, true));
	enemyHitAnimations.push_back(
			new Animation("../gfx/orbitingEnemy.png", 200, 1, num, 100, true));
	enemyHitAnimations.push_back(
			new Animation("../gfx/bossHit.png", 200, 1, num, 474, true));

	backgroundSprites.push_back(new Sprite("../gfx/Dino BG1.png"));
	backgroundSprites.push_back(new Sprite("../gfx/Dino BG2.png"));
	backgroundSprites.push_back(new Sprite("../gfx/Dino BG3.png"));
	backgroundSprites.push_back(new Sprite("../gfx/Dino BG4.png"));
	backgroundSprites.push_back(new Sprite("../gfx/Dino BG5.png"));
	backgroundSprites.push_back(new Sprite("../gfx/Background.png"));

	bossSprite = new Sprite("../gfx/boss.png");
	lifebarSprite = new Sprite("../gfx/lifebar.png");
	lifebar2Sprite = new Sprite("../gfx/lifebar2.png");

	dropSprites.push_back(new Sprite("../gfx/upgradeSprite.png"));
	dropSprites.push_back(new Sprite("../gfx/spreadUpgradeSprite.png"));
	dropSprites.push_back(new Sprite("../gfx/laserUpgradeSprite.png"));
	dropSprites.push_back(new Sprite("../gfx/missileUpgradeSprite.png"));
	dropSprites.push_back(new Sprite("../gfx/bombSprite.png"));

	focusSprite = new Sprite("../gfx/focusSprite.png");

	initialSpreadGun = new PlayerGunSpread(1, bulletSprites.at(0));
	player = new Player(PlayerAnimation, focusSprite, initialSpreadGun,
			new Circle(Point(300, 500), 0.5), playerDeath);

	testStage = StageParser::parseStage("../stages/stage01script.txt",
			backgroundSprites, enemySprites, bulletSprites, dropSprites,
			enemyHitAnimations, player);

	testWave = new EnemyWave();

	testBoss = new Boss(bossSprite, player,
			new Rect(Point(45, -300), bossSprite->getWidth(),
					bossSprite->getHeight() - 100), enemyHitAnimations.at(4));
	BossState* test;
	test = new BossState(
			EnemyParser::parseEnemy("../stages/boss01Attack02Script.txt",
					enemySprites, bulletSprites, dropSprites,
					enemyHitAnimations, player), lifebarSprite, 100000);
	testBoss->addBossState(test);
	test = new BossState(
			EnemyParser::parseEnemy("../stages/boss01Attack01Script.txt",
					enemySprites, bulletSprites, dropSprites,
					enemyHitAnimations, player), lifebarSprite, 100000);
	testBoss->addBossState(test);
	test = new BossState(
			EnemyParser::parseEnemy("../stages/boss01Attack03Script.txt",
					enemySprites, bulletSprites, dropSprites,
					enemyHitAnimations, player), lifebarSprite, 105000);
	testBoss->addBossState(test);
	int numOfSprites1[1] = { 4 };
	for (int i = 0; i < NUMBER_OF_EXPLOSIONS; i++) {
		testBoss->addExplosionAnimation(
				new Animation("../gfx/EnemyExplosion.png", 500, 1,
						numOfSprites1, 77, false));
		int numOfSprites2[1] = { 7 };
		testBoss->addExplosionAnimation(
				new Animation("../gfx/OrbitExplosion.png", 250, 1,
						numOfSprites2, 79, false));
	}
	testBoss->setScorePoints(100000);
	testWave->AddEnemy(testBoss, 1000);
	testStage->addWave(testWave);
	testStage->start();

	GameArea::inicialize();
	ScoreManager::initialize();

	testMusic = new Music("../sfx/Clima 2.wav");
	testMusic->play(-1);
	testMusic->setVolume(200);

	quitGame = false;
	ending = false;
	nextState = SDLBase::STATENOCHANGE;
}

StateArgs StateGame::unload() {
	std::vector<std::string> args;
	std::stringstream str1;
	str1 << testStage->getKilledEnemies();
	args.push_back(str1.str());
	std::stringstream str2;
	str2 << player->getLife();
	args.push_back(str2.str());
	std::stringstream str3;
	str3 << player->getNumBombs();
	args.push_back(str3.str());
	delete (player);
	delete (playerDeath);
	delete (initialSpreadGun);
	delete (testStage);
	delete (focusSprite);
	delete (Background);
	delete (HUDPlayerLives);
	delete (PlayerAnimation);
	delete (HUDBackground);
	delete (HUDScore);
	delete (HUDPlayerBombs);
	delete (HUDMultiplier);

	for (std::vector<Sprite*>::iterator it = bulletSprites.begin();
			it != bulletSprites.end(); ++it) {
		delete (*it);
		it = bulletSprites.erase(it);
		it--;
	}
	for (std::vector<Animation*>::iterator it = enemyHitAnimations.begin();
			it != enemyHitAnimations.end(); ++it) {
		delete (*it);
		it = enemyHitAnimations.erase(it);
		it--;
	}

	for (std::vector<Sprite*>::iterator it = enemySprites.begin();
			it != enemySprites.end(); ++it) {
		delete (*it);
		it = enemySprites.erase(it);
		it--;
	}

	for (std::vector<Sprite*>::iterator it = dropSprites.begin();
			it != dropSprites.end(); ++it) {
		delete (*it);
		it = dropSprites.erase(it);
		it--;
	}

	for (std::vector<Sprite*>::iterator it = backgroundSprites.begin();
			it != backgroundSprites.end(); ++it) {
		delete (*it);
		it = backgroundSprites.erase(it);
		it--;
	}

	BulletManager::cleanUp();
	DropManager::cleanUp();
	AnimationManager::cleanUp();
	GameArea::finalize();
	testMusic->stop();
	delete (testMusic);

	return StateArgs(args);
}

void StateGame::input() {
	if (InputManager::getInstance()->QuitGame())
		quitGame = true;

	if (InputManager::getInstance()->isKeyPressed(SDLK_DELETE)) {
		player->setIndestructible(true);
	}
}

int StateGame::update(double dt) {
	player->update(dt);
	testStage->update(dt);
	GameArea::update(dt);
	BulletManager::update(dt);
	DropManager::update(dt);
	BombManager::update(dt);
	AnimationManager::update(dt);
	SoundEraser::update();
	if (!ending) {
		checkCollisions();
	}
	ScoreManager::update(player->getShape());
	checkClosestTarget();

	BulletManager::removeOffScreenBullets(GAME_AREA_WIDTH, GAME_AREA_HEIGHT);
	DropManager::removeOffScreenDrops(GAME_AREA_WIDTH + 150,
			GAME_AREA_HEIGHT + 150);

	std::stringstream strs1, strs2, strs3, strs4;
	strs1 << ScoreManager::getScore();
	strs2 << ScoreManager::getScoreMultiplier() << "x";
	strs3 << player->getLife();
	strs4 << player->getNumBombs();

	ScoreText = strs1.str();
	MultiplierText = strs2.str();
	PlayerLivesText = strs3.str();
	playerBombsText = strs4.str();
	while (ScoreText.length() < SCORELENGTH) {
		ScoreText = '0' + ScoreText;
	}
	if (PlayerLivesText.length() == 1) {
		PlayerLivesText = '0' + PlayerLivesText;
	}
	HUDScore->setText(ScoreText);
	HUDMultiplier->setText(MultiplierText);
	HUDPlayerLives->setText(PlayerLivesText);
	HUDPlayerBombs->setText(playerBombsText);

	if (quitGame)
		nextState = SDLBase::STATEQUIT;

	if (player->getLife() <= 0)
		nextState = SDLBase::STATELOSE;

	if (testStage->isFineshed() && !ending) {
		ending = true;
		waitToEndTimer.start(WAIT_TO_END);
	}
	if (ending) {
		waitToEndTimer.update();
		if (waitToEndTimer.isDone()) {
			nextState = SDLBase::STATEWIN;
		}
	}

	return nextState;
}

void StateGame::render() {
	Background->render(0, 0, 0);

	testStage->renderBackground();

	player->render(0, 0);

	DropManager::render();
	BulletManager::render(0, 0);

	testStage->render();
	AnimationManager::render();
	GameArea::render();
	HUDBackground->render(0, 0, 0);
	HUDScore->render(0, 0, 0);
	HUDMultiplier->render(0, 0, 1);

	HUDPlayerLives->render(0, 0, 1);
	HUDPlayerBombs->render(0, 0, 1);

}

void StateGame::checkCollisions() {

	Bullet* tempBullet;
	std::vector<Bullet*> tempBulletVector;
	Droppable* tempDrop;

	if (!player->isDead()) {
		if ((tempBullet = BulletManager::checkCollision(player, false)) != NULL) {
			tempBullet->onCollisionWith(player);
		}

		if ((tempDrop = DropManager::checkCollision(player)) != NULL) {
			tempDrop->onCollisionWithPlayer(player);
		}
	}

	if (BombManager::getBomb()) {
		tempBulletVector = BulletManager::checkCollisions(
				BombManager::getBomb(), false);

		for (std::vector<Bullet*>::iterator it = tempBulletVector.begin();
				it != tempBulletVector.end(); ++it) {
			(*it)->setDead(true);
		}
	}

	testStage->checkCollision(GAME_AREA_WIDTH, GAME_AREA_HEIGHT);

	checkPlayerBounds();
}
void StateGame::checkClosestTarget() {
	Point* target = NULL;
	target = testStage->getClosestEnemyPosition(
			player->getShape()->getCenterRef(), GAME_AREA_WIDTH,
			GAME_AREA_HEIGHT);
	if (target != NULL) {
		player->setTarget(*target);
	} else {
		player->setTarget(Point(400, -600));
	}

}
void StateGame::checkPlayerBounds() {
	if (player->getShape()->getX() > GAME_AREA_WIDTH)
		player->getShape()->setX(GAME_AREA_WIDTH);
	if (player->getShape()->getX() < 0)
		player->getShape()->setX(0);
	if (player->getShape()->getY() > GAME_AREA_HEIGHT)
		player->getShape()->setY(GAME_AREA_HEIGHT);
	if (player->getShape()->getY() < 0)
		player->getShape()->setY(0);
}
