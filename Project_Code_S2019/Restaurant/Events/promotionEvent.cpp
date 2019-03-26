#include "promotionEvent.h"


promotionEvent::promotionEvent(int eTime, int oID,int ex_money):Event(eTime,oID)
{
	money=ex_money;
}


promotionEvent::~promotionEvent(void)
{
}

void promotionEvent::Execute(Restaurant* pRest){

	 return;
}