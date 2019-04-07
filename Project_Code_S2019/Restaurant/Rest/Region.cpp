#include "Region.h"



//take care of the includes when adding the class inside its suitable place



Region::Region()
{
}
//////////////////////////////////////////////////////////////////////////////////////
//Takes a motorcycle and inserts it into its suitable List
//returns false if it couldn't add to the List
bool Region::AddMotorcycle(Motorcycle * moto)
{
	bool Added;
	ORD_TYPE MotoType = moto->GetType();
	switch (MotoType)
	{
	case(TYPE_NRM):
		Added = normal_motor.enqueue(moto, moto->GetSpeed());
		break;
	case(TYPE_VIP):
		Added = vip_motor.enqueue(moto, moto->GetSpeed());
		break;
	case(TYPE_FROZ):
		Added = frozen_motor.enqueue(moto, moto->GetSpeed());
		break;
	}
	return Added;
}
/////////////////////////////////////////////////////////////////////////////////////////
bool Region::AddOrder(Order * ord)
{
	bool Added;
	ORD_TYPE OrderType = ord ->GetType();
	switch (OrderType)
	{
	case(TYPE_NRM):
		Added = normal_order.InsertEnd(ord);
		break;
	case(TYPE_VIP):
		Added = vip_order.enqueue(ord, ord->GetPriority());
		break;
	case(TYPE_FROZ):
		Added = frozen_order.enqueue(ord);
		break;
	}

	return Added;

}
///////////////////////////////////////////////////////////////////////////////////////////
//called at the end of each TimeStep to add the waiting orders in the current region to the ordListForDrawing
void Region::AddActiveOrdersToDraw(GUI * pGUI)
{
	//a place holder for active orders
	Order* ord;
	Queue<Order*> temp;
	//First : VIP ORDERS
	//number of currently active VIP Orders
	int CNT_VIP = vip_order.get_item_count();
	//temporary queue to loop get all VIP Orders for Drawing
	for (int i = 0; i < CNT_VIP; i++)
	{
		vip_order.dequeue(ord);
		pGUI->AddOrderForDrawing(ord);
		//place them in a temporary queue to get them back FIFO
		temp.enqueue(ord);
	}
	//After Adding all of them to the ORDLISTFORDRAWING Return them again to the queue
	for (int i = 0; i < CNT_VIP; i++)
	{
		temp.dequeue(ord);
		vip_order.enqueue(ord, ord->GetPriority());
	}
	//-----------------------------------------------------------------------------------------------------//
	//SECOND : FROZEN ORDERS
	int CNT_FROZ = frozen_order.GetCount();
	for (int i = 0; i < CNT_FROZ; i++)
	{
		frozen_order.dequeue(ord);
		pGUI->AddOrderForDrawing(ord);
		temp.enqueue(ord);
	}
	//return orders to Frozen List after putting them in the ORDLISTFORDRAWING
	for (int i = 0; i < CNT_FROZ; i++)
	{
		temp.dequeue(ord);
		frozen_order.enqueue(ord);
	}
	//-----------------------------------------------------------------------------------------------------//

	//Last : NORMAL ORDERS
	//number of normal orders
	int CNT_NRM = normal_order.GetCount();
	for (int i = 0; i < CNT_NRM; i++)
	{
		normal_order.GetItemAt(i,ord);
		//adds active normal orders to be drawn
		pGUI->AddOrderForDrawing(ord);
	}
}
//////////////////////////////////////////////////////////////////////////////////////
bool Region::IsNormalEmpty() const
{
	bool Empty = normal_order.isEmpty();
	return Empty;
}
bool Region::IsVIPEmpty() const
{
	return vip_order.isEmpty();
}
bool Region::IsFrozenEmpty() const
{
	return frozen_order.isEmpty();
}
////////////////////////////////////////////////////////////////////////////////////
void Region::AssignNormal(Order * &Ord)
{
	normal_order.RemoveBeg(Ord);
}
void Region::AssignVIP(Order *& Ord)
{
	vip_order.dequeue(Ord);
}
void Region::AssignFroz(Order * &Ord)
{
	frozen_order.dequeue(Ord);
}
void Region::getCounts(int &vipM_count, int & nM_count, int & fM_count, int & vipO_count, int & nO_count, int & fO_count)
{
	vipM_count	= vip_motor.get_item_count();
	nM_count	= normal_motor.get_item_count();
	fM_count	= frozen_motor.get_item_count();

	vipO_count	= vip_order.get_item_count();
	nO_count	= normal_order.GetCount();
	fO_count	= frozen_order.GetCount();
}
///////////////////////////////////////////////////////////////////////////////////////////////////

bool Region::IsRegionActive() const
{
	bool Active = !(vip_order.isEmpty()) || !(frozen_order.isEmpty()) || !(normal_order.isEmpty());
	return Active;
}

Region::~Region()
{

}
