#include <cstdlib>
#include <time.h>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"



Restaurant::Restaurant() 
{
	pGUI = NULL;
}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
		
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		break;
	case MODE_STEP:
		break;
	case MODE_SLNT:
		break;
	case MODE_DEMO:
		Just_A_Demo();

	};

}



//////////////////////////////////  Event handling functions   /////////////////////////////
void Restaurant::AddEvent(Event* pE)	//adds a new event to the queue of events
{
	EventsQueue.enqueue(pE);
}

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while( EventsQueue.peekFront(pE) )	//as long as there are more events
	{
		if(pE->getEventTime() > CurrentTimeStep )	//no more events at current time
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}


Restaurant::~Restaurant()
{
		delete pGUI;
}




////////////////////////////////////////////////////////////////////////////////
/// ==> 
///  DEMO-related functions. Should be removed in phases 1&2

//This is just a demo function for project introductory phase
//It should be removed starting phase 1
void Restaurant::Just_A_Demo()
{
	
	//
	// THIS IS JUST A DEMO FUNCTION
	// IT SHOULD BE REMOVED IN PHASE 1 AND PHASE 2
	
	int EventCnt;	
	Order* pOrd;
	Event* pEv;
	srand(time(NULL));

	pGUI->PrintMessage("Just a Demo. Enter EVENTS Count(next phases should read I/P filename):");
	EventCnt = atoi(pGUI->GetString().c_str());	//get user input as a string then convert to integer

	pGUI->UpdateInterface();

	pGUI->PrintMessage("Generating orders randomly... In next phases, orders should be loaded from a file");
		
	int EvTime = 0;
	
	//Create Random events
	//All generated event will be "ArrivalEvents" for the demo
	for(int i=0; i<EventCnt; i++)
	{
		int O_id = i+1;
		
		//Rendomize order typech
		int OType;
		if(i<EventCnt*0.2)	//let 1st 20% of orders be VIP (just for sake of demo)
			OType = TYPE_VIP;
		else if(i<EventCnt*0.5)	
			OType = TYPE_FROZ;	//let next 30% be Frozen
		else
			OType = TYPE_NRM;	//let the rest be normal

		
		int reg = rand()% REG_CNT;	//randomize regionch


		//Randomize event time
		EvTime += rand()%4;
		pEv = new ArrivalEvent(EvTime,O_id,(ORD_TYPE)OType,(REGION)reg);
		AddEvent(pEv);

	}	

	int CurrentTimeStep = 1;
	//as long as events queue is not empty yet
	while(!EventsQueue.isEmpty())
	{
		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep,timestep,10);	
		pGUI->PrintMessage(timestep);


		ExecuteEvents(CurrentTimeStep);	//execute all events at current time step
		//The above line may add new orders to the DEMO_Queue

		//Let's draw all arrived orders by passing them to the GUI to draw

		while(DEMO_Queue.dequeue(pOrd))
		{
			pGUI->AddOrderForDrawing(pOrd);
			pGUI->UpdateInterface();
		}
		Sleep(1000);
		CurrentTimeStep++;	//advance timestep
	}


	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();

	
}
////////////////

void Restaurant::AddtoDemoQueue(Order *pOrd)
{
	DEMO_Queue.enqueue(pOrd);
}

Order* Restaurant::getDemoOrder()
{
	Order* pOrd;
	DEMO_Queue.dequeue(pOrd);
	return pOrd;

}
void Restaurant::file_loading(){
	
	int time_step;
	char typech;
	ORD_TYPE type; //casting typech to type enum
	int id;
	int dist;
	int cost;
	char regionch;
	REGION region;
	int ex_money;

	int vip_speed;
	int frozen_speed;
	int normal_speed;
	int event_count;

    int x;
	char ch;
    ifstream inFile;
    
    inFile.open("test.txt");
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
	
	inFile>>x;
	normal_speed=x;
	inFile>>x;
	frozen_speed=x;
	inFile>>x;
	vip_speed=x;
	for(int i=0;i<4;i++){
		switch (i){
		case 0:{
			inFile >> x;
			Motorcycle * Mot;
			for (int i = 0; i < x; i++) {
				Mot = new Motorcycle();
				Mot->setSpeed(normal_speed);
				Mot->setType(TYPE_NRM);
				normal_motor_A.enqueue(Mot,Mot->GetSpeed());
			}
			inFile >> x;
			for (int i = 0; i < x; i++) {
				Mot = new Motorcycle();
				Mot->setSpeed(frozen_speed);
				Mot->setType(TYPE_FROZ);
				frozen_motor_A.enqueue(Mot, Mot->GetSpeed());
			}
			inFile >> x;
			for (int i = 0; i < x; i++) {
				Mot = new Motorcycle();
				Mot->setSpeed(vip_speed);
				Mot->setType(TYPE_VIP);
				vip_motor_A.enqueue(Mot, Mot->GetSpeed());
			}
			   }break;
		case 1:{
			inFile >> x;
			Motorcycle * Mot;
			for (int i = 0; i < x; i++) {
				Mot = new Motorcycle();
				Mot->setSpeed(normal_speed);
				Mot->setType(TYPE_NRM);
				normal_motor_B.enqueue(Mot, Mot->GetSpeed());
			}
			inFile >> x;
			for (int i = 0; i < x; i++) {
				Mot = new Motorcycle();
				Mot->setSpeed(frozen_speed);
				Mot->setType(TYPE_FROZ);
				frozen_motor_B.enqueue(Mot, Mot->GetSpeed());
			}
			inFile >> x;
			for (int i = 0; i < x; i++) {
				Mot = new Motorcycle();
				Mot->setSpeed(vip_speed);
				Mot->setType(TYPE_VIP);
				vip_motor_B.enqueue(Mot, Mot->GetSpeed());
			}
			   }break;
		case 2:{inFile >> x;
			Motorcycle * Mot;
			for (int i = 0; i < x; i++) {
				Mot = new Motorcycle();
				Mot->setSpeed(normal_speed);
				Mot->setType(TYPE_NRM);
				normal_motor_C.enqueue(Mot, Mot->GetSpeed());
			}
			inFile >> x;
			for (int i = 0; i < x; i++) {
				Mot = new Motorcycle();
				Mot->setSpeed(frozen_speed);
				Mot->setType(TYPE_FROZ);
				frozen_motor_C.enqueue(Mot, Mot->GetSpeed());
			}
			inFile >> x;
			for (int i = 0; i < x; i++) {
				Mot = new Motorcycle();
				Mot->setSpeed(vip_speed);
				Mot->setType(TYPE_VIP);
				vip_motor_C.enqueue(Mot, Mot->GetSpeed());
			}
			}break;
		case 3:{inFile >> x;
			Motorcycle * Mot;
			for (int i = 0; i < x; i++) {
				Mot = new Motorcycle();
				Mot->setSpeed(normal_speed);
				Mot->setType(TYPE_NRM);
				normal_motor_D.enqueue(Mot, Mot->GetSpeed());
			}
			inFile >> x;
			for (int i = 0; i < x; i++) {
				Mot = new Motorcycle();
				Mot->setSpeed(frozen_speed);
				Mot->setType(TYPE_FROZ);
				frozen_motor_D.enqueue(Mot, Mot->GetSpeed());
			}
			inFile >> x;
			for (int i = 0; i < x; i++) {
				Mot = new Motorcycle();
				Mot->setSpeed(vip_speed);
				Mot->setType(TYPE_VIP);
				vip_motor_D.enqueue(Mot, Mot->GetSpeed());
			}
			}break;
		}
	}
	inFile>>x;
	promotion_time=x;
	inFile>>x;
	event_count=x;

	for(int i=0;i<event_count;i++){
		inFile>>ch;
	
		if(ch=='R'){
		
		inFile>>time_step;
		inFile>>typech;

		switch (typech)
		{
		case('N'):
			type = TYPE_NRM;
			break;
		case('V'):
			type = TYPE_VIP;
			break;
		case('F'):
			type = TYPE_FROZ;
			break;
		}

		inFile>>id;
		inFile>>dist;
		inFile>>cost;
		inFile>>regionch;

		switch (regionch)
		{
		case('A'):
			region = A_REG;
			break;
		case('B'):
			region = B_REG;
			break;
		case('C'):
			region = C_REG;
			break;
		case('D'):
			region = D_REG;
			break;
		}

			Event*pEv=new ArrivalEvent(time_step,id,type,region);  //casting enums for region and order typech
			AddEvent(pEv);
		
		}

		else if(ch=='X'){
		inFile>>time_step;
			inFile>>id;
			Event*pEv=new cancelationEvent(time_step,id);
			AddEvent(pEv);
		}
		else if(ch=='P'){
			inFile>>time_step;
			inFile>>id;
			inFile>>ex_money;
			Event*pEv= new promotionEvent(time_step,id,ex_money);
			AddEvent(pEv);
		
		}
	
	
	}
    inFile.close();
	



}

/// ==> end of DEMO-related function