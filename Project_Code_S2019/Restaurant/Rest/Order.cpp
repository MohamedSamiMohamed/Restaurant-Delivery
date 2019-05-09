#include "Order.h"

Order::Order(int id, ORD_TYPE r_Type, REGION r_region)
{
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	type = r_Type;
	Region = r_region;

	Priority = -1; //-1 till assigned for VIP orders
}

Order::Order(int iD, ORD_TYPE r_Type, REGION r_region, int dist, double mon, int arrT)
{
	ID = iD;
	type = r_Type;
	Region = r_region;
	Distance = dist;
	totalMoney = mon;
	ArrTime = arrT;
	if (type == TYPE_VIP) {
		Priority = 5 * totalMoney - (20*Distance *ArrTime);//temporary
	
	}
	else {
		Priority = -1;
	}
}

Order::~Order()
{
}

int Order::GetID()
{
	return ID;
}


ORD_TYPE Order::GetType() const
{
	return type;
}

REGION Order::GetRegion() const
{
	return Region;
}

void Order::SetDistance(int d)
{
	Distance = d>0?d:0;
}

int Order::GetDistance() const
{
	return Distance;
}

void Order ::  SetPriority(int Pr)
{
	Priority = Pr;
}

int Order ::  GetPriority() const
{
	return Priority;
}

void Order::SetAT(int arrT)
{
	ArrTime = arrT;
}

void Order::SetST(int servT)
{
	ServTime = servT;
}

void Order::SetFT(int finT)
{
	FinishTime = finT;
}

void Order::SetWT(int waitT)
{
	WaitingTime = waitT;
}

int Order::GetAT() const
{
	return ArrTime;
}

int Order::GetST() const
{
	return ServTime;
}

int Order::GetFT() const
{
	return FinishTime;
}

int Order::GetWT() const
{
	return WaitingTime;
}

double Order::get_total_money(){
	return totalMoney;

}

int Order::get_arrival_time(){
	return ArrTime;
}

void Order::set_type(ORD_TYPE ord_type){
	type=ord_type;

}

void Order::SetMoney(double mon){
	totalMoney= mon;
}
