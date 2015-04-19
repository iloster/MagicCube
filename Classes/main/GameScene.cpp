#include "GameScene.h"
#include <random>
#include "GameOverScene.h"
#include <stdlib.h>
USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if(!Layer::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();

	lon = (visibleSize.width - 28) / 4; 
	gap = 10;
	step = 0;
	degree = 2;
	dHeight =100;
	startOrientation = this->createRandomNum(2);
	// 创建手势识别的事件监听器  
    auto touchListener = EventListenerTouchOneByOne::create();  
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);  
    touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);  
    // 添加事件监听  
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);  

	this->createColor();
	this->createBg();
	this->createCard();
	this->createShade();
	//this->gameOver();
	//this->createRandomNum();
	return true;
}

void GameScene::createBg()
{
	auto layerColorBg = cocos2d::LayerColor::create(cocos2d::Color4B(200,190,180,255),visibleSize.width,visibleSize.height);
	layerColorBg->setPosition(0,0);
	this->addChild(layerColorBg,0);
}
void GameScene::createShade()
{
	auto layerColorShadeTop = cocos2d::LayerColor::create(cocos2d::Color4B(200,190,180,255),visibleSize.width,lon+gap);
	layerColorShadeTop->setPosition(0,lon * 4 + visibleSize.height / 6+5+dHeight);
	this->addChild(layerColorShadeTop,2);

	auto layerColorShadebottom = cocos2d::LayerColor::create(cocos2d::Color4B(200,190,180,255),visibleSize.width,lon+gap);
	layerColorShadebottom->setPosition(0,-lon+gap + visibleSize.height / 6-20+dHeight);
	this->addChild(layerColorShadebottom,2);

	auto layerColorShadeleft = cocos2d::LayerColor::create(cocos2d::Color4B(200,190,180,255),gap,visibleSize.height);
	layerColorShadeleft->setPosition(0,0);
	this->addChild(layerColorShadeleft,2);

	auto layerColorShaderight = cocos2d::LayerColor::create(cocos2d::Color4B(200,190,180,255),gap+10,visibleSize.height);
	layerColorShaderight->setPosition(visibleSize.width-gap-10,0);
	this->addChild(layerColorShaderight,2);

}

void GameScene::createColor()
{
	 int startArray[] = {0,1, 2, 3};
    //int resultArray[16];//结果存放在里面    
    std::default_random_engine e(time(NULL));
    for (int i = 0; i < 4; i++)
    {
        //int seed = CCRANDOM_0_1(0, 4 - i);//从剩下的随机数里生成    
        std::uniform_int_distribution<> u(0, 3 - i);
        int seed = u(e);
		colorNum[i] = startArray[seed];//赋值给结果数组    
        startArray[seed] = startArray[3 - i];//把随机数产生过的位置替换为未被选中的值。  
    } 
	//for(int i =0;i<16;i++)
	//{
	//	CCLog("%d ",colorNum[i]);
	//}
}

int GameScene::createRandomNum(int n)
{
	struct timeval now;
    gettimeofday(&now, NULL);
     
    //初始化随机种子
    //timeval是个结构体，里边有俩个变量，一个是以秒为单位的，一个是以微妙为单位的 
    unsigned rand_seed = (unsigned)(now.tv_sec*1000 + now.tv_usec/1000);    //都转化为毫秒 
    srand(rand_seed);
    int _rand = rand()%n;
	return _rand;
		
}
//orientation 0:代表水平向左，1:代表水平向右 2:垂直向上 3:垂直向下
void GameScene::transtion(int orientation,int arr[][4])
{
	
	int randNum = this->createRandomNum(4);
	int tmp;
	if(randNum<0&&randNum>4)
	{
		randNum = 0;
	}
	CCLog("randNum=%d",randNum);
	switch(orientation)
	{
	case 0:
		{
			tmp = arr[randNum][0];
			arr[randNum][0] = arr[randNum][1];
			arr[randNum][1] = arr[randNum][2];
			arr[randNum][2] = arr[randNum][3];
			arr[randNum][3] = tmp;
		};break; //水平向左
	case 1:
		{
			tmp = arr[randNum][3];
			arr[randNum][3] = arr[randNum][2];
			arr[randNum][2] = arr[randNum][1];
			arr[randNum][1] = arr[randNum][0];
			arr[randNum][0] = tmp;
		};break;
	case 2:
		{
			tmp = arr[0][randNum];
			arr[0][randNum] = arr[1][randNum];
			arr[1][randNum] = arr[2][randNum];
			arr[2][randNum] = arr[3][randNum];
			arr[3][randNum] = tmp;
		   };break;
	case 3:
		{
			tmp = arr[3][randNum];
			arr[3][randNum] = arr[2][randNum];
			arr[2][randNum] = arr[1][randNum];
			arr[1][randNum] = arr[0][randNum];
			arr[0][randNum] = tmp;
		};break;
		default:break;
	}
}

void GameScene::createCard()
{
	int test[4][4] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	for(int i = 0;i<degree;i++)
	{
		if(startOrientation == 0)
		{
			this->transtion(this->createRandomNum(2),test);
			this->transtion(this->createRandomNum(2)+2,test);
		}else
		{
			this->transtion(this->createRandomNum(2)+2,test);
			this->transtion(this->createRandomNum(2),test);			
		}
	}
	for(int i = 0;i < 4;i++)
	{
		for(int j = 0;j < 4;j++)
		{
			//auto cardLayer = cocos2d::LayerColor::create();

			
			CCLog("%d %d",colorNum);
			//CardSprite *card = CardSprite::createCardSprite(4*i+j, lon, lon, lon * j + gap, lon * i + gap + visibleSize.height / 6);
			CardSprite *card = CardSprite::createCardSprite(test[i][j], lon, lon, lon * j + gap, lon * i + gap + visibleSize.height / 6);
			cardArr[i][j] = card;
			this->addChild(card,1);
		}
	}
}

bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	Point touchP0 = touch->getLocation();
	firstX = touchP0.x;
	firstY = touchP0.y;
	CCLog("%d %d",firstX,firstY);
	return true;
}

void GameScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
	Point touchP1 = touch->getLocation();
	endX = touchP1.x;
	endY = touchP1.y;
	step++;
	if(firstX > gap && firstX < gap + lon)
	{
		if(abs(endX - firstX)<lon && abs(endX-firstX)<abs(endY - firstY))
		{
			if(endY - firstY>=2/3*lon)
			{
				CCLog("%s","1------up");
				col_up(0);
			}else if(endY - firstY<=-2/3*lon)
			{
				CCLog("%s","1------down");
				col_down(0);
			}
		}
	}

	if(firstX > gap + lon && firstX < gap + 2*lon)
	{
		if(abs(endX - firstX)<lon && abs(endX-firstX)<abs(endY - firstY))
		{
			if(endY - firstY>=2/3*lon)
			{
				CCLog("%s","2------up");
				col_up(1);
			}else if(endY - firstY<=-2/3*lon)
			{
				CCLog("%s","2------down");
				col_down(1);
			}
		}
	}

	if(firstX > gap + 2*lon && firstX < gap + 3*lon)
	{
		if(abs(endX - firstX)<lon && abs(endX-firstX)<abs(endY - firstY))
		{
			if(endY - firstY>=2/3*lon)
			{
				CCLog("%s","3------up");
				col_up(2);
			}else if(endY - firstY<=-2/3*lon)
			{
				CCLog("%s","3------down");
				col_down(2);
			}
		}
	}

	if(firstX > gap + 3*lon && firstX < gap + 4*lon)
	{
		if(abs(endX - firstX)<lon && abs(endX-firstX)<abs(endY - firstY))
		{
			if(endY - firstY>=2/3*lon)
			{
				CCLog("%s","4------up");
				col_up(3);
			}else if(endY - firstY<=-2/3*lon)
			{
				CCLog("%s","4------down");
				col_down(3);
			}
		}
	}

	if(firstY > (gap + visibleSize.height / 6+dHeight) && firstY < (gap + lon + visibleSize.height/6+dHeight))
	{
		if(abs(endX - firstX)>lon && abs(endX-firstX)>abs(endY - firstY))
		{
			if(endX - firstX>=2/3*lon)
			{
				CCLog("%s","0------row right");
				row_right(0);
				
			}else if(endX - firstX<=-2/3*lon)
			{
				CCLog("%s","0------row left");
				row_left(0);
				
			}
		}
	}

	if(firstY > (gap + lon+visibleSize.height / 6+dHeight) && firstY < (gap + lon*2 + visibleSize.height/6+dHeight))
	{
		if(abs(endX - firstX)>lon && abs(endX-firstX)>abs(endY - firstY))
		{
			if(endX - firstX>=2/3*lon)
			{
				CCLog("%s","1------row right");
				row_right(1);
				
			}else if(endX - firstX<=-2/3*lon)
			{
				CCLog("%s","1------row left");
				row_left(1);
			}
		}
	}
	if(firstY > (gap + lon*2 + visibleSize.height / 6+dHeight) && firstY < (gap + lon*3 + visibleSize.height/6+dHeight))
	{
		if(abs(endX - firstX)>lon && abs(endX-firstX)>abs(endY - firstY))
		{
			if(endX - firstX>=2/3*lon)
			{
				CCLog("%s","2------row right");
				row_right(2);
				
				
			}else if(endX - firstX<=-2/3*lon)
			{
				CCLog("%s","2------row left");
				row_left(2);
			}
		}
	}
	if(firstY > (gap + lon*3 + visibleSize.height / 6+dHeight) && firstY < (gap + lon*4 + visibleSize.height/6+dHeight))
	{
		if(abs(endX - firstX)>lon && abs(endX-firstX)>abs(endY - firstY))
		{
			if(endX - firstX>=2/3*lon)
			{
				CCLog("%s","3------row right");
				row_right(3);
				
			}else if(endX - firstX<=-2/3*lon)
			{
				CCLog("%s","3------row left");
				row_left(3);
			}
		}
	}

}

void GameScene::col_up(int col)
{
	
	for(int j = 0;j<4;j++)
	{
		CCActionInterval *action = CCMoveBy::create(0.25,ccp(0,lon));
		cardArr[j][col]->runAction(action);
	}
	//this->removeChild(cardArr[3][0]);
	int number = cardArr[3][col]->getNumber();
	for(int j = 3;j>0;j--)
	{
		 cardArr[j][col] = cardArr[j-1][col] ;
	}
	cardArr[0][col] = CardSprite::createCardSprite(number, lon, lon, lon * col + gap, -lon + gap + visibleSize.height / 6);
	this->addChild(cardArr[0][col]);	
	CCActionInterval *action = CCMoveBy::create(0.25,ccp(0,lon));
	cardArr[0][col]->runAction(action);
	this->gameOver();
}

void GameScene::col_down(int col)
{
	for(int j = 0 ;j<4;j++)
	{
		CCActionInterval *action = CCMoveBy::create(0.25,ccp(0,-lon));
		cardArr[j][col]->runAction(action);
	}
	int number = cardArr[0][col]->getNumber();
	for(int j = 0;j<3;j++)
	{
		cardArr[j][col] = cardArr[j+1][col];
	}
	cardArr[3][col] = CardSprite::createCardSprite(number, lon, lon, lon * col + gap, lon*4 + gap + visibleSize.height / 6);
	this->addChild(cardArr[3][col]);	
	CCActionInterval *action = CCMoveBy::create(0.25,ccp(0,-lon));
	cardArr[3][col]->runAction(action);
	this->gameOver();
}

void GameScene::row_right(int row)
{
	for(int i = 0;i<4;i++)
	{
		CCActionInterval *action = CCMoveBy::create(0.25,ccp(lon,0));
		cardArr[row][i]->runAction(action);
	}
	int number = cardArr[row][3]->getNumber();
	for(int i = 3;i>0;i--)
	{
		cardArr[row][i] = cardArr[row][i-1];
	}
	cardArr[row][0] = CardSprite::createCardSprite(number,lon,lon,-lon+gap,lon*row +gap+visibleSize.height/6);
	this->addChild(cardArr[row][0]);	
	CCActionInterval *action = CCMoveBy::create(0.25,ccp(lon,0));
	cardArr[row][0]->runAction(action);
	this->gameOver();
}

void GameScene::row_left(int row)
{
	for(int i = 0;i<4;i++)
	{
		CCActionInterval *action = CCMoveBy::create(0.25,ccp(-lon,0));
		cardArr[row][i]->runAction(action);
	}
	int number = cardArr[row][0]->getNumber();
	for(int i = 0 ;i<3;i++)
	{
		cardArr[row][i] = cardArr[row][i+1];
	}
	cardArr[row][3] = CardSprite::createCardSprite(number,lon,lon,4*lon+gap,lon*row +gap+visibleSize.height/6);
	this->addChild(cardArr[row][3]);	
	CCActionInterval *action = CCMoveBy::create(0.25,ccp(-lon,0));
	cardArr[row][3]->runAction(action);
	this->gameOver();

}
bool GameScene::compare4Num(int a,int b,int c,int d)
{
	if(a==b && b==c && c==d && a==d)
	{
		return true;
	}else
	{
		return false;
	}
}
bool GameScene::checkResult()
{
	bool tag1[4];
	bool tag2[4];
	for(int i =0 ;i<4;i++)
	{
		 tag1[i] = compare4Num(cardArr[i][0]->getNumber(),cardArr[i][1]->getNumber(),cardArr[i][2]->getNumber(),cardArr[i][3]->getNumber());
		 tag2[i] = compare4Num(cardArr[0][i]->getNumber(),cardArr[1][i]->getNumber(),cardArr[2][i]->getNumber(),cardArr[3][i]->getNumber());
	}
	return (tag1[1]&&tag1[2]&&tag1[3]&&tag1[0])||(tag2[1]&&tag2[2]&&tag2[3]&&tag2[0]);
}

void GameScene::gameOver()
{
	if(this->checkResult())
	{
		CCLog("%s","-----------------success-------------------");
		/*auto scene = GameOverScene::createScene();
		Director::getInstance()->replaceScene(scene);*/
		GameOverScene* scene = GameOverScene::create();
		scene->setContentSize(CCSizeMake(400,300));
		this->addChild(scene,3);

	}
}