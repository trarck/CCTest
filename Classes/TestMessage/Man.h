#ifndef CCLIBSTEST_MAN_H_
#define CCLIBSTEST_MAN_H_

#include "cocos2d.h"
#include "message.h"

class Man : public cocos2d::CCObject
{
public:

    void wait(cocos2d::yhlib::CCMessage* message);

    int m_nWait;
};

#endif  // CCLIBSTEST_MAN_H_