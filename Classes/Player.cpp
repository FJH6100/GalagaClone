#include "Player.h"

USING_NS_CC;

Player::Player(cocos2d::Layer *layer)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	player = Sprite::create("Player1.png");
	player->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 12));

	auto pBody = PhysicsBody::createBox(player->getContentSize());
	pBody->setRotationEnable(false);
	//pBody->setCollisionBitmask(1);
	//pBody->setContactTestBitmask(true);
	player->setPhysicsBody(pBody);

	layer->addChild(player, 1);
}

void Player::UpdatePlayer(float x, float y)
{
	player->setPosition(x, y);
}

Vec2 Player::GetPlayerPosition()
{
	return player->getPosition();
}