#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"


ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType, REGION reg):Event(eTime, oID)
{
	OrdType = oType;
	OrdRegion = reg;
}


ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType,int dist,double mon, REGION reg) : Event(eTime, oID)
{
	OrdType = oType;
	OrdRegion = reg;
	OrdDistance= dist;
	OrdMoney = mon;

}

void ArrivalEvent::Execute(Restaurant* pRest)
{
	

	Order* pOrd = new Order(OrderID, OrdType, OrdRegion,OrdDistance,OrdMoney,EventTime);
	Region* OrdReg = pRest->get_region(OrdRegion);
	OrdReg->AddOrder(pOrd);
	//This function should create an order and fills its data 
   // Then adds it to normal, frozen, or VIP order lists that you will create in phase1

	
	
	///For the sake of demo, this function will just create an order and add it to DemoQueue
	///Remove the next code lines in phase 1&2
	
	
}
