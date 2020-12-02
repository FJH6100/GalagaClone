#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"

class Enemy : public cocos2d::Node
{
public:
	Enemy(cocos2d::Layer *layer, float x, float y);
	~Enemy();
	void UpdateEnemy();

	cocos2d::Rect GetBounds();
	cocos2d::Sprite * GetSprite();

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	cocos2d::Sprite *enemy;

	float locx;
	float locy;

	bool left;

};

#endif // __ENEMY_H__
