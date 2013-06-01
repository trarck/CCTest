#include "Man.h"

using namespace cocos2d;
using namespace cocos2d::yhlib;

void Man::wait(CCMessage* message)
{
    //CCLOG("Man:wait");
    ++m_nWait;
}

