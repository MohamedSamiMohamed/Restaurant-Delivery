#pragma once
#include "event.h"
#include "../Rest/Restaurant.h"
class promotionEvent :
	public Event
{
private:
	int money;
public:
	promotionEvent(int eTime, int oID,int ex_money);
	~promotionEvent(void);
     virtual void Execute(Restaurant *pRest);	//override execute function
};

