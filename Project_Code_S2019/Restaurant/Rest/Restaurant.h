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

#define NumberOfRegions 4
// it is the maestro of the project
class Restaurant  
{	
private:
	int promotion_time;
	int served_VIP_orders[4];
	int served_NORM_orders[4];
	int served_FROZ_orders[4];
	string output[4];
	string served_output;

	GUI *pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file
	
	//Array for the four regions
	Region* regions[REG_CNT];

	//---------------------------------------------------------------------------------------------------//
	//Serving Motorcycles
	PriorityQueue<Motorcycle*> ServingMotos;

	//---------------------------------------------------------------------------------------------------//
	//Serving Orders
	PriorityQueue<Order*> inServiceOrders;
	Queue<Order*> finishedOrders;
	 
	//	DEMO-related members. Should be removed in phases 1&2
	Queue<Order*> DEMO_Queue;	//Important: This is just for demo
	
	
		
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
	//[MA]Simulation Auxilary functions
	void DelFirst();
	Region* get_region(REGION R);
	void DrawActiveOrders(); //Function to fill ordlist for drawing and draw on GUI
	
	//phase 1 Simulation Function
	void Phase1Sim();

	//[MA] Phase 2 Simulation Functions
	//This Function Takes an Ord and a Moto to assign them to each other calculating their data and moving them to their assign Lists
	void assignOrdtoMoto(Order* Ord, Motorcycle* Moto, int CurrentTimeStep);
	//Returns motorcycle to their list When they finish serving an order 
	//called Every Time Step to check returning Motos
	void ReturnMoto(int currentTimeStep);
	//arrange orders having same FT by ST  then add them to finishedOrders queue
	void checkFinishedOrders(int currentTimeStep);

	//SIMULATION FUNCTIONS
	void StepByStepMode();
	//Interactive Mode
	void InteractiveMode();

	void SilentMode();

	void output_file();

	void Status_bar_print();

	void filling_outputs(Order*Ord,Motorcycle *moto);
	//Responsible for assigning Orders to motorcycles every time step
	void Assign(int CurrentTimeStep);
	
};

#endif