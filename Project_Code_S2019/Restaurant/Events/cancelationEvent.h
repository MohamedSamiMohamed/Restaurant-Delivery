#pragma once
#include "event.h"
class cancelationEvent :public Event
{
public:
	cancelationEvent(int eTime, int oID);
	~cancelationEvent(void);
    virtual void Execute(Restaurant *pRest);	//override execute function

};

