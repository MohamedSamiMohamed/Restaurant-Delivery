#include "Region.h"



//take care of the includes when adding the class inside its suitable place



Region::Region()
{
	normal_order_count=0;
	froz_order_count=0;
	vip_order_count=0;
	normal_orders_money=0;
	FROZ_orders_money=0;
	VIP_orders_money=0;

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
	case(TYPE_NRM):{
		Added = normal_order.InsertEnd(ord);
		normal_order_count++;
		normal_orders_money+=ord->get_total_money();
		break;}
	case(TYPE_VIP):{
		Added = vip_order.enqueue(ord, ord->GetPriority());
		vip_order_count++;
		VIP_orders_money+=ord->get_total_money();

		break;}
	case(TYPE_FROZ):{
		Added = frozen_order.enqueue(ord);
		froz_order_count++;
	    FROZ_orders_money+=ord->get_total_money();

		break;}
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
bool Region::IsNormalMotoEmpty() const
{
	return normal_motor.isEmpty();
}
bool Region::IsVipMotoEmpty() const
{
	return vip_motor.isEmpty();
}
bool Region::IsFrozenMotoEmpty() const
{
	return frozen_motor.isEmpty();
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
void Region::sendNormalMoto(Motorcycle *& Moto)
{
	normal_motor.dequeue(Moto);
}
void Region::sendVIPMoto(Motorcycle *& Moto)
{
	vip_motor.dequeue(Moto);
}
void Region::sendFrozMoto(Motorcycle *& Moto)
{
	frozen_motor.dequeue(Moto);
}
///////////////////////////////////////////////////////////////////////////////////////////////////

bool Region::IsRegionActive() const
{
	bool Active = !(vip_order.isEmpty()) || !(frozen_order.isEmpty()) || !(normal_order.isEmpty());
	return Active;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
bool Region::CancelOrder(int ID)
{
	//PlaceHolder for Normal Order
	Order* Ord;
	bool found = false;
	for (int i = 0; i < normal_order.GetCount(); i++)
	{
		normal_order.GetItemAt(i,Ord);
		if (Ord->GetID() == ID)
		{
			//if found
			normal_order.Remove(Ord);
			delete Ord;
			found = true;
			normal_order_count--;
			break;
		}
	}
	return found;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void Region::print(GUI * pGUI, int i)
{

	char temp[10];
	outputs = "REG[";
	outputs += (char)(i + 65); //ASCI code for 'A' is 65 in DEC
	outputs += "] :";

	itoa(vip_motor.get_item_count(), temp, 10);
	outputs += " |VIPMot: ";
	outputs = outputs + temp;

	outputs += " |FROZMot: ";
	itoa(frozen_motor.get_item_count(), temp, 10);
	outputs = outputs + temp;

	outputs += " |NORMot: ";
	itoa(normal_motor.get_item_count(), temp, 10);
	outputs = outputs + temp;



	outputs += " |VIPOrd: ";
	itoa(vip_order.get_item_count(), temp, 10);
	outputs = outputs + temp;

	outputs += " |FROZOrd: ";
	itoa(frozen_order.GetCount(), temp, 10);
	outputs = outputs + temp;

	outputs += " |NOROrd: ";
	itoa(normal_order.GetCount(), temp, 10);
	outputs = outputs + temp;

	outputs += " || ";

	pGUI->printMessageAt(outputs, i + 1);
}


Region::~Region()
{
	//destruct the motorcycles
	//Place Holder for motorcycles
	Motorcycle* moto;
	while (vip_motor.dequeue(moto))
		delete moto;
	while (frozen_motor.dequeue(moto))
		delete moto;
	while (normal_motor.dequeue(moto))
		delete moto;
}

int Region::get_all_count(){
	return (normal_order_count+froz_order_count+vip_order_count);
}

int Region::get_normal_count(){
	return normal_order_count;
}

int Region::get_frozen_count(){
	return froz_order_count;
}
int Region::get_vip_count(){
	return vip_order_count;
}

int Region::get_all_motors_count(){

	return normal_motor.get_item_count()+vip_motor.get_item_count()+frozen_motor.get_item_count();
}

int Region::get_frozen_motors_count(){
	return frozen_motor.get_item_count();
}

int Region::get_normal_motors_count(){
	return normal_motor.get_item_count();
}
int Region::get_vip_motors_count(){
	return vip_motor.get_item_count();
}

double Region::get_all_money(){
	return normal_orders_money+FROZ_orders_money+VIP_orders_money;
}

double Region::get_NORM_money(){
	return normal_orders_money;
}

double Region::get_FROZ_money(){
	return FROZ_orders_money;
}

double Region::get_VIP_money(){
	return VIP_orders_money;
}
bool Region::promoteOrder(int ID,double extMoney){
	Order*ord;
	Order*new_ord;
	int priority;
	bool found=false;
	double money;
	for(int i=0;i<normal_order.GetCount();i++){
		normal_order.GetItemAt(i,ord);
		if(ord->GetID()==ID){
			priority=(5*ord->get_total_money())-(20*(ord->GetDistance())*(ord->get_arrival_time()));
			money=ord->get_total_money()+extMoney;
			ord->set_type(TYPE_VIP);
			ord->SetPriority(priority);
			ord->SetMoney(money);
			AddOrder(ord);
			normal_order.Remove(ord);
			normal_order_count--;
			found=true;
			break;
		}
	}
	return found;
	}

void Region::searchForPromotion(int currTimeS,int promotion_time){
	
	Order*ord;
	Order*new_ord;
	int priority;
	for(int i=0;i<normal_order.GetCount();i++){
		normal_order.GetItemAt(i,ord);
		if((currTimeS-ord->get_arrival_time())>=promotion_time){
			priority=(5*ord->get_total_money())-(20*(ord->GetDistance())*(ord->get_arrival_time()));
			ord->set_type(TYPE_VIP);
			ord->SetPriority(priority);
			AddOrder(ord);
			normal_order.Remove(ord);
			normal_order_count--;
			//[MA]resets the loop when removing an order to avoid missing orders
			i = -1;
		}
	
	}


}
