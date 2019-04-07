#ifndef __REGION_H
#define __REGION_H_

#include "../Generic_DS/PriorityQueue.h"
#include "..\Generic_DS/Queue.h"
#include "..\Generic_DS/List.h"

#include "..\GUI/GUI.h"

#include "../Rest/Order.h"
#include "../Rest/Motorcycle.h"
#include "../Defs.h"

class Region
{
	PriorityQueue<Motorcycle*> vip_motor;
	PriorityQueue<Motorcycle*> normal_motor;
	PriorityQueue<Motorcycle*> frozen_motor;
	
	PriorityQueue<Order*> vip_order;
	Queue<Order*> frozen_order;
	List<Order*> normal_order;

	
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

	//Assign orders :Returns the first order to be assigned in a list
	void AssignNormal(Order* &Ord);
	void AssignVIP(Order* &Ord);
	void AssignFroz(Order* &Ord);

	//Function to show if there are any active orders in cuurent region
	//True if there are any waiting orders
	bool IsRegionActive() const;
	void print(GUI * pGUI, int i);
	
	~Region();
};

#endif