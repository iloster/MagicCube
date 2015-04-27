#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "CardSprite.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void createBg();
    void createCard();
    void createShade();
    void createColor();
    void createButton();
    
    cocos2d::Size visibleSize;
    CREATE_FUNC(GameScene);
    
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void onRestBtnClick(cocos2d::Ref *ref);
    
private:
    int firstX,firstY,endX,endY;
    int lon;
    int gap;
    int step;
    int border;
    int degree;
    int dHeight; //ÀÆ∆Ω∏ﬂ∂»
    int startOrientation;
    int resetFlag = 0; //重置的标志0:表示正常 1:表示重置
    int colorNum[2];
    int cardNumArr[4][4]; //= {{0,1,2,3},{4,5,6,7},{8,9,10,11},{12,13,14,15}};
    //int test[4][4];
    CardSprite *cardArr[5][5];
    void initCardArr();
    void col_up(int col);
    void col_down(int col);
    void row_right(int row);
    void row_left(int row);
    bool compare4Num(int a,int b,int c, int d);
    bool checkResult();
    void gameOver();
    void transtion(int orientation,int arr[][4]);
    int createRandomNum(int n);
    void createArr();
    void initCardNumArr();
    void saveCardNumArr();
    void getCardNumArr();
};

#endif