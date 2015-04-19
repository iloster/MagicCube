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
		cocos2d::Size visibleSize;
		CREATE_FUNC(GameScene);

		virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);  
		virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);  

	private:
		int firstX,firstY,endX,endY;
		int lon;
		int gap;
		int step;
		int border;
		int degree;
		int dHeight; //水平高度
		int startOrientation;
		int colorNum[2];
		CardSprite *cardArr[5][5];
		void col_up(int col);
		void col_down(int col);
		void row_right(int row);
		void row_left(int row);
		bool compare4Num(int a,int b,int c, int d);
		bool checkResult();
		void gameOver();
		void transtion(int orientation,int arr[][4]);
		int createRandomNum(int n);
};

#endif