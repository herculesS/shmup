/*
 * StateGame.h
 *
 *  Created on: Jun 18, 2013
 *      Author: AT WORK
 */

#ifndef STATEGAME_H_
#define STATEGAME_H_
#define SCORELENGTH 12
#define WAIT_TO_END 3000

#include "State.h"
#include "PlayerGunSpread.h"
#include "PlayerGunLaser.h"
#include "PlayerGunMissile.h"
#include "Text.h"
#include "Sprite.h"
#include "Animation.h"
#include "Shape.h"
#include "Rect.h"
#include "Player.h"
#include "Timer.h"
#include "Droppable.h"
#include "Enemy.h"
#include "EnemyWave.h"
#include "EnemyParser.h"
#include "EnemyWaveParser.h"
#include "EnemyMoveAction.h"
#include "EnemyShootAction.h"
#include "EnemyWaitAction.h"
#include "Boss.h"
#include "BossState.h"
#include "BulletPatternSpread.h"
#include "BulletPatternFlower.h"
#include "BulletPatternBurst.h"
#include "AnimationManager.h"
#include "ScoreManager.h"
#include "Stage.h"
#include "StageParser.h"
#include "Bomb.h"
#include "BombManager.h"
#include "Music.h"
#include "SoundEraser.h"
#include <sstream>

class StateGame: public State {
private:
	Sprite* HUDBackground;
	Sprite* Background;
	Sprite* focusSprite;
	Sprite* bossSprite;
	Sprite* lifebarSprite;
	Sprite* lifebar2Sprite;
	Animation* PlayerAnimation;
	Animation* playerDeath;
	std::vector<Sprite*> enemySprites;
	std::vector<Sprite*> bulletSprites;
	std::vector<Sprite*> dropSprites;
	std::vector<Sprite*> backgroundSprites;
	std::vector<Animation*> enemyHitAnimations;

	Text* HUDScore;
	Text* HUDMultiplier;
	Text* HUDPlayerBombs;
	Text* HUDPlayerLives;
	std::string ScoreText;
	std::string MultiplierText;
	std::string PlayerLivesText;
	std::string playerBombsText;

	Player* player;
	PlayerGunSpread* initialSpreadGun;
	PlayerGunLaser* laserGun;
	PlayerGunMissile* missileGun;

	Enemy* testEnemy;
	EnemyWave* testWave;
	Stage* testStage;
	Boss* testBoss;

	Timer waitToEndTimer;
	bool ending;
	bool quitGame;

	Music* testMusic;

	void checkPlayerBounds();
	void checkCollisions();
	void checkClosestTarget();

public:
	StateGame();
	virtual void load(StateArgs arguments);
	virtual StateArgs unload();
	virtual void input();
	virtual int update(double dt);
	virtual void render();
	virtual ~StateGame();
};

#endif /* STATEGAME_H_ */
