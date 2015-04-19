#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "platform/android/jni/JniHelper.h"
#include <cocos2d.h>
#endif

using namespace cocos2d;

class WeChatShare
{
public:
    WeChatShare();
    virtual ~WeChatShare();
    static void sendToFriend();
    static void sendToTimeLine();
};