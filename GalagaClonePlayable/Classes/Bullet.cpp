#include "Bullet.h"

USING_NS_CC;

Bullet::Bullet(cocos2d::Layer *layer, Vec2 position)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	bullet = Sprite::create("Bullet.png");
	bullet->setPositionX(position.x);
	bullet->setPositionY(position.y+30);

	layer->addChild(bullet, 1);
}

Bullet::~Bullet()
{
	log("Deuces");
}

void Bullet::UpdateBullet()
{
	int x = bullet->getPositionX();
	int y = bullet->getPositionY();

	bullet->setPosition(x, y+2);

}

cocos2d::Rect Bullet::GetBounds()
{
	return bullet->getBoundingBox();
}

cocos2d::Sprite * Bullet::GetSprite()
{
	return bullet;
}
