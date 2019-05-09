#pragma once
#include "event.h"
#include "../Rest/Restaurant.h"
class cancelationEvent :public Event
{
public:
	cancelationEvent(int eTime, int oID);
	~cancelationEvent(void);
    virtual void Execute(Restaurant *pRest);	//override execute function

};

