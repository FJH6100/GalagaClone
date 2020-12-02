#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"

class Player
{
public:
	Player(cocos2d::Layer *layer);

	void UpdatePlayer(float x, float y);

	cocos2d::Vec2 GetPlayerPosition();

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	cocos2d::Sprite *player;

	float locx;
	float locy;

};

#endif // __PLAYER_H__
