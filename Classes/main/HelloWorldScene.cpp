#include "HelloWorldScene.h"
#include "GameScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
 
	auto layerColorBg = cocos2d::LayerColor::create(cocos2d::Color4B(200,190,180,255),visibleSize.width,visibleSize.height);
	layerColorBg->setPosition(0,0);
	this->addChild(layerColorBg);

	auto startBtn = MenuItemSprite::create(Sprite::create("image/uires_2.png"),Sprite::create("image/uires_2.png"),NULL,this,menu_selector(HelloWorld::start));
	//startBtn->setPosition(visibleSize.width/2,visibleSize.height/2);
	startBtn->setPosition(Point(0,0));
	Menu* menu = Menu::create(startBtn,NULL);
	menu->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(menu,1);
    return true;
}

void HelloWorld::start(Ref* pSender)
{
	CCLog("%s","test");
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
