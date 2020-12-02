#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"

class Bullet : public cocos2d::Node
{
public:
	Bullet(cocos2d::Layer *layer, cocos2d::Vec2 position);
	~Bullet();
	void UpdateBullet();
	cocos2d::Rect GetBounds();
	cocos2d::Sprite * GetSprite();

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	cocos2d::Sprite *bullet;
};

#endif // __BULLET_H__

