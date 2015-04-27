#include "CardSprite.h"

USING_NS_CC;

CardSprite* CardSprite::createCardSprite(int number,int width,int height,float CardSpriteX,float CardSpriteY)
{
    CardSprite *enemy = new CardSprite();
    if(enemy && enemy->init())
    {
        //enemy->autorelease();
        enemy->enemyInit(number,width,height,CardSpriteX,CardSpriteY);
        return enemy;
    }
    //CC_SAFE_DELETE(enemy);
    return NULL;
}

bool CardSprite::init()
{
    if(!Sprite::init())
    {
        return false;
    }
    return true;
}

void CardSprite::enemyInit(int numbers,int width,int height,float CardSpriteX,float CardSpriteY)
{
    number = numbers%4;
//    switch (number)
//    {
//    case 0:color = cocos2d::Color4B(240, 90, 60, 255);break;
//    case 1:color = cocos2d::Color4B(240, 140, 90, 255);break;
//    case 2:color = cocos2d::Color4B(240, 200, 70, 255);break;
//    case 3:color = cocos2d::Color4B(240, 230, 220,255);break;
//    default:
//    	break;
//    }
//     layerColorBG = cocos2d::LayerColor::create(color, width - 8, height - 8);
//        layerColorBG->setPosition(Point(CardSpriteX, CardSpriteY));
//     this->addChild(layerColorBG);
    switch(number)
    {
        case 0:spritePath = "image/pink.png";break;
        case 1:spritePath = "image/red.png";break;
        case 2:spritePath = "image/blue.png";break;
        case 3:spritePath = "image/green.png";break;
        default:
            break;
    }
    int x = CardSpriteX+60;
    int y = CardSpriteY+150;
    sprite = Sprite::create(spritePath);
    sprite->setPosition(Point(x,y));
    sprite->setScale(0.52);
    sprite->setAnchorPoint(Point(0.5,0.5));
    this->addChild(sprite);
}
void CardSprite::setNumber(int n)
{
    this->number = n;
}

int CardSprite::getNumber()
{
    //CCLog("number is %d",number);
    return number;
}
