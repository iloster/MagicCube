#include "GameOverScene.h"
#include "GameScene.h"
USING_NS_CC;

Scene* GameOverScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameOverScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameOverScene::init()
{
	if(!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto bg = Sprite::create("image/scoreBg.png");
	bg->setPosition(visibleSize.width/2,visibleSize.height/2);
	bg->setScaleY(2.5);
	this->addChild(bg,0);

	auto nextBtn = MenuItemSprite::create(Sprite::create("image/uires_5.png"),Sprite::create("image/uires_5.png"),NULL,this,menu_selector(GameOverScene:: next));
	//startBtn->setPosition(visibleSize.width/2,visibleSize.height/2);
	nextBtn->setPosition(Point(0,-100));
	nextBtn->setScale(0.5);

	auto shareTimeLineBtn = MenuItemSprite::create(Sprite::create("image/weixinpyquan.png"),Sprite::create("image/weixinpyquan.png"),NULL,this,menu_selector(GameOverScene:: next));
	//startBtn->setPosition(visibleSize.width/2,visibleSize.height/2);
	shareTimeLineBtn->setPosition(Point(0,100));
	shareTimeLineBtn->setScale(0.5);

	auto shareFriendBtn = MenuItemSprite::create(Sprite::create("image/weixinhaoyou.png"),Sprite::create("image/weixinhaoyou.png"),NULL,this,menu_selector(GameOverScene:: next));
	//startBtn->setPosition(visibleSize.width/2,visibleSize.height/2);
	shareFriendBtn->setPosition(Point(0,0));
	shareFriendBtn->setScale(0.5);

	Menu* menu = Menu::create(nextBtn,shareTimeLineBtn,shareFriendBtn,NULL);
	menu->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(menu,1);
    return true;
}

void GameOverScene::next(Ref* pSender)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}
