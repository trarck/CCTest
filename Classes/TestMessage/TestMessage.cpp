#include "TestMessage.h"
#include "Datas.h"
#include "Man.h"
#include "Car.h"

using namespace cocos2d;
using namespace cocos2d::yhlib;

void showTestFail(const char* msg)
{
    CCLOG("=========test fail{============\n%s",msg);
    CCLOG("=========}test fail============");
}

void TestMessage::run()
{
    CCLOG("CTestMessagear::run");
    testRegiestAndSend();
	testRemove();

}

void TestMessage::testRegiestAndSend()
{
    CCLOG("********TestMessage::testRegiestAndSend{***************");
    Man *aMan=new Man();
	Car *aCar=new Car();
	
	
	DataItem datas[]={
        //regist man CarStop from car 
        //  car send CarStop to man
		{CarStop,aCar,aMan,message_selector(Man::wait),CarStop,aCar,aMan,NULL,1,""},
        //  car send CarStop to all
		{CarStop,aCar,aMan,message_selector(Man::wait),CarStop,aCar,NULL,NULL,1,""},
        //  null send CarStop to man
		{CarStop,aCar,aMan,message_selector(Man::wait),CarStop,NULL,aMan,NULL,0,""},//no
        //  null send CarStop to all
		{CarStop,aCar,aMan,message_selector(Man::wait),CarStop,NULL,NULL,NULL,0,""},//no
        //regist man CarStop from all
        //  car send CarStop to man
		{CarStop,NULL,aMan,message_selector(Man::wait),CarStop,aCar,aMan,NULL,1,""},
         // car send CarStop to all
		{CarStop,aCar,aMan,message_selector(Man::wait),CarStop,aCar,NULL,NULL,1,""},
        //  null send CarStop to man
		{CarStop,NULL,aMan,message_selector(Man::wait),CarStop,NULL,aMan,NULL,1,""},
        //  null send CarStop to all
		{CarStop,NULL,aMan,message_selector(Man::wait),CarStop,NULL,NULL,NULL,1,""},
        //regist man ALL from car
		{MsgAll,aCar,aMan,message_selector(Man::wait),CarStop,aCar,aMan,NULL,1,""}
	};

	int dataLength=sizeof(datas)/sizeof(DataItem);
	DataItem it;
	
	struct timeval start;
    struct timeval end;
	gettimeofday(&start,NULL);
	
    for(int j=0;j<100;++j){

	    for(int i=0;i<dataLength;i++){
		    //CCLOG("do test %d",i);
            aMan->m_nWait=0;

		    it=datas[i];
		    RegisterData rd=it.regiester;
		    DispatchData dd=it.dispatch;
		    //regiester
		    CCMessageManager * mm=new CCMessageManager();
            mm->init();
            mm->registerReceiver(rd.receiver,rd.handle,rd.type,rd.sender);

		    //dispatch
		    CCMessage *message=new CCMessage();
            message->initWithType(dd.type,dd.sender,dd.receiver,dd.data);       
            mm->dispatchMessage(message);
            mm->release();
            if(aMan->m_nWait!=it.result){
                char buffer[255];
                //sprintf(buffer,"index:%d,%s",i,it.description.c_str());
                showTestFail(buffer);
            }
	    }
    }
    gettimeofday(&end,NULL);
    CCLOG("use:%ld,%d",end.tv_sec-start.tv_sec,end.tv_usec-start.tv_usec);
    CCLOG("********}TestMessage::testRegiestAndSend***************");
}


void TestMessage::testRemove()
{
    CCLOG("********TestMessage::testRemove{***************");
    Man *aMan=new Man();
	Car *aCar=new Car();
	
	
	DataItem datas[]={
        //regist man CarStop from car 
        //  car send CarStop to man
		{CarStop,aCar,aMan,message_selector(Man::wait),CarStop,aCar,aMan,NULL,0,""},
        //  car send CarStop to all
		{CarStop,aCar,aMan,message_selector(Man::wait),CarStop,aCar,NULL,NULL,0,""},
       
	};

	int dataLength=sizeof(datas)/sizeof(DataItem);
	DataItem it;
	
	struct timeval start;
    struct timeval end;
	gettimeofday(&start,NULL);
	
	for(int i=0;i<dataLength;i++){
		CCLOG("do test %d",i);
        aMan->m_nWait=0;

		it=datas[i];
		RegisterData rd=it.regiester;
		DispatchData dd=it.dispatch;
		//regiester
		CCMessageManager * mm=new CCMessageManager();
        mm->init();
        mm->registerReceiver(rd.receiver,rd.handle,rd.type,rd.sender);

        //remove register
        mm->removeReceiver(rd.receiver);

		//dispatch
		CCMessage *message=new CCMessage();
        message->initWithType(dd.type,dd.sender,dd.receiver,dd.data);       
        mm->dispatchMessage(message);
        mm->release();
        if(aMan->m_nWait!=it.result){
            char buffer[255];
            sprintf(buffer,"index:%d,%s",i,it.description.c_str());
            showTestFail(buffer);
        }
	}
    gettimeofday(&end,NULL);
    CCLOG("use:%ld,%d",end.tv_sec-start.tv_sec,end.tv_usec-start.tv_usec);
    CCLOG("********}TestMessage::testRemove***************");
}
