#ifndef __ORDER_H_
#define __ORDER_H_

#include "..\Defs.h"

class Order
{

protected:
	int ID;         //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;		//order type: Normal, Frozen, VIP
	REGION Region;  //Region of this order
	int Distance;	//The distance (in meters) between the order location and the resturant 
	                
	double totalMoney;	//Total order money

	int ArrTime, ServTime, FinishTime, WaitingTime;	//arrival, service start, and finish times
	
	
	//
	// TODO: Add More Data Members As Needed
	//

	int Priority;

public:
	Order(int ID, ORD_TYPE r_Type, REGION r_region);
	Order(int iD, ORD_TYPE r_Type, REGION r_region,int dist,double mon,int arrT);
	virtual ~Order();

	int GetID();

	ORD_TYPE GetType() const;
	REGION GetRegion() const;

	void SetDistance(int d);
	int GetDistance() const;

	//
	// TODO: Add More Member Functions As Needed
	//

	void SetPriority(int Pr);
	int GetPriority() const;
	//Setters and Getters for At,ST,FT
	void SetAT(int arrT);
	void SetST(int servT);
	void SetFT(int finT);
	void SetWT(int waitT);
	void SetMoney(double money);
	int GetAT() const;
	int GetST() const;
	int GetFT() const;
	int GetWT() const;

	double get_total_money();    //Ms
	int get_arrival_time();      //MS
	void set_type(ORD_TYPE);

};

#endif