#include "cancelationEvent.h"


cancelationEvent::cancelationEvent(int eTime, int oID):Event(eTime, oID)

{}


cancelationEvent::~cancelationEvent(void)
{
}


void cancelationEvent::Execute(Restaurant* pRest)
{
	//PlaceHolder for region
	Region* OrdRegion;
	bool found = false;
	//loop on four regions to search for order
	for (int i = 0; i < REG_CNT; i++)
	{
		if (!found)
		{
			OrdRegion = pRest->get_region((REGION)i);
			found = OrdRegion->CancelOrder(OrderID);
		}
		else
		{
			break;
		}
	}
	 
}