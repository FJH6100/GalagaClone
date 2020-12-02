#include "GameScene.h"

USING_NS_CC;

Scene* Game::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vect(0, 0));

	// 'layer' is an autorelease object
	auto layer = Game::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Game::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(Game::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	player = new Player(this);

	resultLabel = Label::createWithTTF("", "fonts/Marker Felt.ttf", 24);
	if (resultLabel == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		resultLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

		// add the label as a child to this layer
		this->addChild(resultLabel, 2);
	}
	gameOver = false;

	left, right = false;
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(Game::keyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(Game::keyReleased, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	this->scheduleUpdate();

	Enemy * enemy = new Enemy(this, (origin.x + visibleSize.width / 2) - 120, (origin.y + visibleSize.height)*.75);
	enemies.push_back(enemy);
	Enemy * enemy2 = new Enemy(this, (origin.x + visibleSize.width / 2) - 60, (origin.y + visibleSize.height)*.75);
	enemies.push_back(enemy2);
	Enemy * enemy3 = new Enemy(this, (origin.x + visibleSize.width / 2), (origin.y + visibleSize.height)*.75);
	enemies.push_back(enemy3);
	Enemy * enemy4 = new Enemy(this, (origin.x + visibleSize.width / 2) + 60, (origin.y + visibleSize.height)*.75);
	enemies.push_back(enemy4);
	Enemy * enemy5 = new Enemy(this, (origin.x + visibleSize.width / 2) + 120, (origin.y + visibleSize.height)*.75);
	enemies.push_back(enemy5);
	Enemy * enemy6 = new Enemy(this, (origin.x + visibleSize.width / 2) - 60, ((origin.y + visibleSize.height)*.75) + 60);
	enemies.push_back(enemy6);
	Enemy * enemy7 = new Enemy(this, (origin.x + visibleSize.width / 2), ((origin.y + visibleSize.height)*.75) + 60);
	enemies.push_back(enemy7);
	Enemy * enemy8 = new Enemy(this, (origin.x + visibleSize.width / 2) + 60, ((origin.y + visibleSize.height)*.75) + 60);
	enemies.push_back(enemy8);
	enemyCount = enemies.size();

	return true;
}

void Game::BulletCollision()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets.at(i)->getPositionY() > Director::getInstance()->getVisibleSize().height)
		{
			this->removeChild(bullets.at(i)->GetSprite());
			this->removeChild(bullets.at(i)->getParent());
			bullets.erase(bullets.begin() + i);
		}
		auto bulletRect = bullets.at(i)->GetBounds();
		for (int j = 0; j < enemies.size(); j++)
		{
			auto targetRect = enemies.at(j)->GetBounds();
			if (bulletRect.intersectsRect(targetRect))
			{
				this->removeChild(bullets.at(i)->GetSprite());
				this->removeChild(enemies.at(j)->GetSprite());
				this->removeChild(bullets.at(i)->getParent());
				this->removeChild(enemies.at(j)->getParent());
				bullets.erase(bullets.begin() + i);
				enemies.erase(enemies.begin() + j);
				enemyCount--;
			}
		}
	}
	if (enemyCount == 0)
		GameOver();
}

void Game::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
		left = true;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
		right = true;
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		if (!gameOver)
		{
			Bullet * b = new Bullet(this, player->GetPlayerPosition());
			bullets.push_back(b);
		}
		break;
	case EventKeyboard::KeyCode::KEY_ENTER:
		if (gameOver)
		{
			auto newScene = Game::createScene();
			Director::getInstance()->replaceScene(newScene);
		}
		break;
	}
}

void Game::keyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
		left = false;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
		right = false;
		break;
	}
}

void Game::update(float dt)
{
	Vec2 loc = player->GetPlayerPosition();
	if (left)
		player->UpdatePlayer(--loc.x, loc.y);
	if (right)
		player->UpdatePlayer(++loc.x, loc.y);
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies.at(i)->UpdateEnemy();
	}
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets.at(i)->UpdateBullet();
	}
	BulletCollision();
}

void Game::GameOver()
{
	this->unscheduleUpdate();
	resultLabel->setString("You win! Press Enter to play again.");
	gameOver = true;
}



void Game::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}