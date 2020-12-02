#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include <vector>

class Game : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void BulletCollision();

	void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

	void GameOver();

	void update(float dt);

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(Game);

private:
	bool left, right;

	std::vector<Enemy*> enemies;
	std::vector<Bullet*> bullets;
	int enemyCount;

	cocos2d::Label *resultLabel;
	bool gameOver;

	Player * player;
};

#endif // __GAME_SCENE_H__
