#ifndef __GAMEOVERSCENE__
#define __GAMEOVERSCENE__

#include "cocos2d.h"

class GameOverScene : public cocos2d::Layer
{
	public:
		static cocos2d::Scene* createScene();
		virtual bool init();
		CREATE_FUNC(GameOverScene);
	private:
		void next(cocos2d::Ref* pSender);
};
#endif