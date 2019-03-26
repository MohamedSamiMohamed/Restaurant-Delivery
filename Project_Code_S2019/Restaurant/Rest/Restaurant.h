#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Events\Event.h"
#include"..\Generic_DS\PriorityQueue.h"
#include"../Generic_DS/List.h"
#include"Motorcycle.h"
#include "Order.h"
#include "Region.h"

#include"..\Events\cancelationEvent.h"
#include"..\Events\promotionEvent.h"

// it is the maestro of the project
class Restaurant  
{	
private:
	int promotion_time;

	GUI *pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file
	
								//---------------------------------------------------------------------------------------------------//
	//Restaurant Branch A
	//Motorcycle Queues
	PriorityQueue<Motorcycle*> vip_motor_A;
	PriorityQueue<Motorcycle*> normal_motor_A;
	PriorityQueue<Motorcycle*> frozen_motor_A;
	//Order Queues
	PriorityQueue<Order*> vip_order_A;
	Queue<Order*> frozen_order_A;
	List<Order*> normal_order_A;
	//---------------------------------------------------------------------------------------------------//
	//Restaurant Branch B
	//Motorcycle Queues
	PriorityQueue<Motorcycle*> vip_motor_B;
	PriorityQueue<Motorcycle*> normal_motor_B;
	PriorityQueue<Motorcycle*> frozen_motor_B;
	//Order Queues
	PriorityQueue<Order*> vip_order_B;
	Queue<Order*> frozen_order_B;
	List<Order*> normal_order_B;
	//---------------------------------------------------------------------------------------------------//
	//Restaurant Branch 
	//Motorcycle Queues
	PriorityQueue<Motorcycle*> vip_motor_C;
	PriorityQueue<Motorcycle*> normal_motor_C;
	PriorityQueue<Motorcycle*> frozen_motor_C;
	//Order Queues
	PriorityQueue<Order*> vip_order_C;
	Queue<Order*> frozen_order_C;
	List<Order*> normal_order_C;
	//---------------------------------------------------------------------------------------------------//
	//Restaurant Branch D
	//Motorcycle Queues
	PriorityQueue<Motorcycle*> vip_motor_D;
	PriorityQueue<Motorcycle*> normal_motor_D;
	PriorityQueue<Motorcycle*> frozen_motor_D;
	//Order Queues
	PriorityQueue<Order*> vip_order_D;
	Queue<Order*> frozen_order_D;
	List<Order*> normal_order_D;
	

	//new method
	Region*region_A;
	Region*region_B;
	Region*region_C;
	Region*region_D;
	//---------------------------------------------------------------------------------------------------//
	//Serving Motorcycles
	//---------------------------------------------------------------------------------------------------//

	/// ==> 
	//	DEMO-related members. Should be removed in phases 1&2
	Queue<Order*> DEMO_Queue;	//Important: This is just for demo
	/// ==>
	
	//
	// TODO: Add More Data Members As Needed
	//

public:
	
	Restaurant();
	~Restaurant();
	void AddEvent(Event* pE);	//adds a new event to the queue of events
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();

	/// ==> 
	///  DEMO-related functions. Should be removed in phases 1&2
	void Just_A_Demo();	//just to show a demo and should be removed in phase1 1 & 2
	void AddtoDemoQueue(Order* po);	//adds an order to the demo queue
	Order* getDemoOrder();			//return the front order from demo queue
	/// ==> 


	//
	// TODO: Add More Member Functions As Needed
	//

	//**************************************file loading function*****************************

	void file_loading();

};

#endif