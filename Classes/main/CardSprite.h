#ifndef __CARDSPRITE__
#define __CARDSRPITE__

#include "cocos2d.h"

 class CardSprite : public cocos2d::Sprite
{
	public:
		static CardSprite * createCardSprite(int number,int width,int height,float CardSpriteX,float CardSpriteY);
		virtual bool init();
		 int getNumber();
		CREATE_FUNC(CardSprite);

	private:
		int number;
		void enemyInit(int numbers, int width, int height, float CardSpriteX, float CardSpriteY);  
		//cocos2d::LabelTTF *labelTTFCardNumber;
		 cocos2d::LayerColor *layerColorBG;  
		 cocos2d::Color4B color;
		 cocos2d::Sprite *sprite;
		 std::string spritePath;

};

#endif