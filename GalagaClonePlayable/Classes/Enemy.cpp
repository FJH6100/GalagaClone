#include "Enemy.h"

USING_NS_CC;

Enemy::Enemy(cocos2d::Layer *layer, float initX, float initY)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	enemy = Sprite::create("Enemy.png");
	enemy->setPosition(Vec2(initX, initY));

	locx = initX;
	locy = initY;
	left = true;

	layer->addChild(enemy, 1);
}

Enemy::~Enemy()
{
	log("Onces");
}

void Enemy::UpdateEnemy()
{
	int x = enemy->getPositionX();
	int y = enemy->getPositionY();
	if (left)
		enemy->setPosition(--x, y);
	else
		enemy->setPosition(++x, y);
	
	if (enemy->getPositionX() <= locx - 60)
		left = false;

	if (enemy->getPositionX() >= locx + 60)
		left = true;

}

cocos2d::Rect Enemy::GetBounds()
{
	return enemy->getBoundingBox();
}

cocos2d::Sprite * Enemy::GetSprite()
{
	return enemy;
}
