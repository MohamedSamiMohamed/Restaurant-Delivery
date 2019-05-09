#include "promotionEvent.h"


promotionEvent::promotionEvent(int eTime, int oID,int ex_money):Event(eTime,oID)
{
	money=ex_money;
}


promotionEvent::~promotionEvent(void)
{
}

void promotionEvent::Execute(Restaurant* pRest){

	bool found=false;
	Region*pRegion;
	for(int i=0;i<REG_CNT;i++){
		if(!found){
			pRegion=pRest->get_region((REGION)i);
			found=pRegion->promoteOrder(OrderID,money);
		}
		else{
		break;
		}
	
	}
}