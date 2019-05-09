#ifndef __REGION_H
#define __REGION_H_

#include "../Generic_DS/PriorityQueue.h"
#include "..\Generic_DS/Queue.h"
#include "..\Generic_DS/List.h"

#include "..\GUI/GUI.h"

#include "../Rest/Order.h"
#include "../Rest/Motorcycle.h"
#include"..\Events\ArrivalEvent.h"

class Region
{
	PriorityQueue<Motorcycle*> vip_motor;
	PriorityQueue<Motorcycle*> normal_motor;
	PriorityQueue<Motorcycle*> frozen_motor;
	
	PriorityQueue<Order*> vip_order;
	Queue<Order*> frozen_order;
	List<Order*> normal_order;

	//string for printing outputs
	string outputs;

	int normal_order_count;
	int froz_order_count;
	int vip_order_count;

	double normal_orders_money;
	double FROZ_orders_money;
	double VIP_orders_money;

public:
	Region();
	//Takes a Motorcycle and adds it to its Suitable List
	bool AddMotorcycle(Motorcycle * moto);
	//Takes an order and inserts it into its required List
	bool AddOrder(Order* ord);
	//Adds all the waiting Orders in the current region at the end of a TimeStep to the OrdListForDrawing
	//Takes a Pointer to the current GUI
	void AddActiveOrdersToDraw(GUI* pGUI);
	//Cancels a normal order in the normal List
	//Fuctions to get the first order and motorcycle if available to assign them
	// Returns true if the list is empty 
	bool IsNormalEmpty() const;
	bool IsVIPEmpty() const;
	bool IsFrozenEmpty() const;
    // check if there is available Motorcycles
	bool IsNormalMotoEmpty() const;
	bool IsVipMotoEmpty() const;
	bool IsFrozenMotoEmpty() const;
	//Assign orders :Returns the first order to be assigned in a list

	void AssignNormal(Order* &Ord);
	void AssignVIP(Order* &Ord);
	void AssignFroz(Order* &Ord);
	// sending motorcycles
	void sendNormalMoto(Motorcycle* &Moto);
	void sendVIPMoto(Motorcycle* &Moto);
	void sendFrozMoto(Motorcycle* &Moto);
	//Function to show if there are any active orders in cuurent region
	//True if there are any waiting orders
	bool IsRegionActive() const;

	//Takes an ID of a Normal Order ,searches for it in Normal List and removes if found
	//returns true if found , false otherwise
	bool CancelOrder(int ID);

	//Prints Data of the Region
	void print(GUI * pGUI, int i);

	int get_all_count();
	int get_normal_count();
	int get_frozen_count();
	int get_vip_count();


	int get_all_motors_count();
	int get_normal_motors_count();
	int get_frozen_motors_count();
	int get_vip_motors_count();


	double get_all_money();
	double get_NORM_money();
	double get_FROZ_money();
	double get_VIP_money();

	// search for promotion
	void searchForPromotion(int currTimeS,int promotion_time);    //MS
	//promotion function
	bool promoteOrder(int ID,double extMoney);    //MS

	~Region();
};

#endif