/*
 *  Datas.h
 *  Message
 *
 *  Created by trarck trarck on 11-12-16.
 *  Copyright 2011 yitengku.com. All rights reserved.
 *
 */
#include "cocos2d.h"
#include "message.h"

typedef struct Register_Data{
	int type;
	cocos2d::CCObject* sender;
	cocos2d::CCObject* receiver;
    cocos2d::yhlib::SEL_MessageHandler handle;
	
} RegisterData;

typedef struct Dispatch_Data{
	int type;
	cocos2d::CCObject* sender;
	cocos2d::CCObject* receiver;
	cocos2d::CCObject* data;
} DispatchData;

typedef struct DataItem{
	RegisterData regiester;
	DispatchData dispatch;
    int result;
    std::string description;
} DataItem;

enum  {
	MsgAll=0,
	CarStop,
	CarMove,
	DirverCar
};