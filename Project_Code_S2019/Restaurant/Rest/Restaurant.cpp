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
	for (int i = 0; i < NumberOfRegions; i++) {
		regions[i] = new Region();
	served_FROZ_orders[i]=0;
	served_NORM_orders[i]=0;
	served_VIP_orders[i]=0;
	output[i]="";
	}

}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
		
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		InteractiveMode();
		break;
	case MODE_STEP:
		StepByStepMode();
		break;
	case MODE_SLNT:
		SilentMode();
		break;
	case MODE_DEMO:
		Phase1Sim();

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
		for (int i = 0; i < REG_CNT; i++)
		{
			delete regions[i];
		}
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
	double cost;
	REGION region;
	char regionch;
	int ex_money;

	int vip_speed;
	int frozen_speed;
	int normal_speed;
	int event_count;

    int x;
	char ch;
    ifstream inFile;
    
	//Get the Test file name
	pGUI->PrintMessage("Enter the file name : ");
	string Inputfile = pGUI->GetString();
	Inputfile += ".txt";
	

    inFile.open(Inputfile);
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
	
	int numMotoSpeeds;
	inFile >> x;
	numMotoSpeeds = x;
	int j = 0;
	Motorcycle * Mot;
	for (int i = 0; i < numMotoSpeeds; i++)
	{
		inFile >> x;
		normal_speed = x;
		inFile >> x;
		frozen_speed = x;
		inFile >> x;
		vip_speed = x;
		
		//////////////////
		for (int k = 0; k < NumberOfRegions; k++) {
			inFile >> x;
			for (int i = 0; i < x; i++) {

				Mot = new Motorcycle(j, TYPE_NRM, normal_speed, (REGION)k, IDLE);
				regions[k]->AddMotorcycle(Mot);
				j++;
			}
			inFile >> x;
			for (int i = 0; i < x; i++) {
				Mot = new Motorcycle(j, TYPE_FROZ, frozen_speed, (REGION)k, IDLE);
				regions[k]->AddMotorcycle(Mot);
				j++;
			}
			inFile >> x;
			for (int i = 0; i < x; i++) {
				Mot = new Motorcycle(j, TYPE_VIP, vip_speed, (REGION)k, IDLE);
				regions[k]->AddMotorcycle(Mot);
				j++;
			}
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

			Event*pEv=new ArrivalEvent(time_step,id,type,dist,cost,region);  //casting enums for region and order typech
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

void Restaurant::DelFirst()
{
	for (int k = 0; k < REG_CNT; k++)
	{
		Order* Ord;
		if (!(regions[k]->IsNormalEmpty()))
		{
			regions[k]->AssignNormal(Ord);
			delete Ord;
		}
		if (!(regions[k]->IsFrozenEmpty()))
		{
			regions[k]->AssignFroz(Ord);
			delete Ord;
		}
		if (!(regions[k]->IsVIPEmpty()))
		{
			regions[k]->AssignVIP(Ord);
			delete Ord;
		}
	}
}

Region * Restaurant::get_region(REGION R)
{
	return regions[R];
}

void Restaurant::DrawActiveOrders()
{
	pGUI->ResetDrawingList();
	for (int i = 0; i < REG_CNT; i++)
	{
		regions[i]->AddActiveOrdersToDraw(pGUI);
	}
	pGUI->UpdateInterface();
}

void Restaurant::Phase1Sim()
{
	//initializations
	int CurrentTimeStep = 1;
	//call file loading function to fill events nad motorcycles
	file_loading();
	
	//timerstep = 0 at the beginning
	pGUI->PrintMessage("------------------------------------------------------------------------------");
	//print Data After Loading
	for (int i = 0; i < REG_CNT; i++)
		regions[i]->print(pGUI, i);
	
	//Enter simulation loop
	bool Continue = true;
	while (Continue)
	{
		//To Print Time Step 
		char timestep[10];
		itoa(CurrentTimeStep, timestep, 10);
		pGUI->PrintMessage("------------------------------------------------------------------------------");
		pGUI->PrintTimeStep(timestep);		
		//Execute Events in current time step
		ExecuteEvents(CurrentTimeStep);

		//print the output After Executing current TimeSstep Events
		for (int i = 0; i < REG_CNT; i++)
			regions[i]->print(pGUI, i);
		//Draw orders after execution
		DrawActiveOrders();
		
		Sleep(2000);

		DelFirst();
		//Print the Output after deletion
		pGUI->PrintMessage("------------------------------------------------------------------------------");
		pGUI->PrintTimeStep(timestep);
		for (int i = 0; i < REG_CNT; i++)
			regions[i]->print(pGUI, i);

		//Draw After Deleting
		DrawActiveOrders();
		
		pGUI->waitForClick();

		//To continue if there is any event or any active order in any of the regions
		Continue = !(EventsQueue.isEmpty()) || regions[A_REG]->IsRegionActive() || regions[B_REG]->IsRegionActive() || regions[C_REG]->IsRegionActive() || regions[D_REG]->IsRegionActive();
		CurrentTimeStep++;
	}

	pGUI->PrintMessage("------ End of Simulation ------");
	pGUI->waitForClick();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------PHASE 2 -------------------------------------------------//

void Restaurant::assignOrdtoMoto(Order * Ord, Motorcycle * Moto, int CurrentTimeStep)
{
	int ServTime = ceil((double)Ord->GetDistance() / Moto->GetSpeed()); //Do we need ceil to handle decimal numbers?
	//Calculate the order waiting Time
	int OrdWT = CurrentTimeStep - Ord->GetAT();
	Ord->SetWT(OrdWT);
	//set the order ST
	Ord->SetST(ServTime);
	//Calculate the Finish Time of the order and the Motorcycle
	int OrdFT = CurrentTimeStep + ServTime;
	Ord->SetFT(OrdFT);
	//-------------------Add the order to the in service orders queue with priority = (-1 * FinshTime)
	inServiceOrders.enqueue(Ord,-1 * OrdFT);

	int MotoReturnT = CurrentTimeStep + 2 * ServTime;  //The Motorcycle takes time to reach the destination and return
	Moto->setReturningStep(MotoReturnT);
	ServingMotos.enqueue(Moto, -1 * MotoReturnT); //This priority is to sort the Motos with earlier Finish Time First

	//status bar output
	filling_outputs(Ord,Moto);
}

void Restaurant::ReturnMoto(int currentTimeStep)
{
	//Place Holder for a Motorcycle
	Motorcycle* Moto;
	//Enters if their are Motorcycles that are serving
	//Get a copy of the Motorcycle on top (The first one waiting to return)
	while (ServingMotos.peekFront(Moto))
	{
		//if the Time for returning of the nearest Motorcycle didn't come yet
		if (currentTimeStep < Moto->getReturningStep())
			return;
		//Return the Motorcycle to its Region
		ServingMotos.dequeue(Moto);
		regions[Moto->GetRegion()]->AddMotorcycle(Moto); //[MA] ?? GetRgion should return an int or an enum REGION
		
	}
}

void Restaurant::checkFinishedOrders(int currentTimeStep)
{
	Order* Ord;
	PriorityQueue<Order*> tempQueue;
	while (inServiceOrders.peekFront(Ord))
	{
		if (Ord->GetFT() == currentTimeStep)
		{
			inServiceOrders.dequeue(Ord);
			//served till now
			if(Ord->GetType()==TYPE_FROZ){
			
				served_FROZ_orders[Ord->GetRegion()]++;
			}
			else if(Ord->GetType()==TYPE_VIP){
				served_VIP_orders[Ord->GetRegion()]++;
			}
			else{
				served_NORM_orders[Ord->GetRegion()]++;
			}
			///////////////////////////////////////////
			tempQueue.enqueue(Ord, -1 * Ord->GetST());
		}
		else
			break;

	}
	while (tempQueue.dequeue(Ord))
	{
		finishedOrders.enqueue(Ord);

	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                              SILENT MODE                                                                //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Restaurant::SilentMode()
{
	//initializations
	int CurrentTimeStep = 1;
	//call file loading function to fill events nad motorcycles
	file_loading();
	//timerstep = 0 at the beginning
	

	//Enter simulation loop
	bool Continue = true;
	while (Continue)
	{
		//Execute Events in current time step
		ExecuteEvents(CurrentTimeStep);
		/////////////////////////////////////////////////////////////////////////////////////////////
		//check returning motorcycles
		ReturnMoto(CurrentTimeStep);
		//check finished orders
		checkFinishedOrders(CurrentTimeStep);
		//Check Auto-promoted orders
		for (int i = 0; i < REG_CNT; i++)
		{
			regions[i]->searchForPromotion(CurrentTimeStep, promotion_time);
		}
		
		// Assigning Orders to Motorcycles
		Assign(CurrentTimeStep);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		Continue = (!ServingMotos.isEmpty()) || (! EventsQueue.isEmpty());
		CurrentTimeStep++;
	}

	pGUI->PrintMessage(".......End of Simulation......");
	pGUI->waitForClick();

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                        STEP BY STEP MODE                                                                //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Restaurant::StepByStepMode()
{
	//initializations
	int CurrentTimeStep = 1;
	//call file loading function to fill events nad motorcycles
	file_loading();
	//timerstep = 0 at the beginning
	pGUI->PrintMessage("-------------------------------------------------------------------------------------------------------------------------------------------------------------------");
	//print Data After Loading
	for (int i = 0; i < REG_CNT; i++)
		regions[i]->print(pGUI, i);

	//Enter simulation loop
	bool Continue = true;
	while (Continue)
	{
		//To Print Time Step 
		char timestep[10];
		itoa(CurrentTimeStep, timestep, 10);
		pGUI->PrintMessage("-------------------------------------------------------------------------------------------------------------------------------------------------------------------");
		pGUI->PrintTimeStep(timestep);
		//Execute Events in current time step
		ExecuteEvents(CurrentTimeStep);
		/////////////////////////////////////////////////////////////////////////////////////////////
		
		pGUI->PrintMessage("-------------------------------------------------------------------------------------------------------------------------------------------------------------------");
		//print Data After Execution
		for (int i = 0; i < REG_CNT; i++)
			regions[i]->print(pGUI, i);
		Status_bar_print();
		/////////////////////////////////////////////////////////////////////////////////////////////
		DrawActiveOrders();
		Sleep(400);
		//check returning motorcycles
		ReturnMoto(CurrentTimeStep);
		//check finished orders
		checkFinishedOrders(CurrentTimeStep);
		//Check Auto-promoted orders
		for (int i = 0; i < REG_CNT; i++)
		{
			regions[i]->searchForPromotion(CurrentTimeStep, promotion_time);
		}
		
		// Assigning Orders to Motorcycles
		Assign(CurrentTimeStep);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Printing Status Bar data
		pGUI->PrintMessage("-------------------------------------------------------------------------------------------------------------------------------------------------------------------");
		Status_bar_print();
		for (int i = 0; i < REG_CNT; i++)
			regions[i]->print(pGUI, i);
		//Reset Ouput Strings
		for(int i = 0; i < REG_CNT; i++)
		{
			output[i] = "";
		}

		
		
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		DrawActiveOrders();

		Continue = (!ServingMotos.isEmpty()) || (! EventsQueue.isEmpty());
		CurrentTimeStep++;
		Sleep(1000);
	}
	
	pGUI->PrintMessage(".......End of Simulation......");
	pGUI->waitForClick();

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                         INTERACTIVE MODE                                                                //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Restaurant::InteractiveMode()
{
	//initializations
	int CurrentTimeStep = 1;
	
	//call file loading function to fill events nad motorcycles
	file_loading();
	
	//timerstep = 0 at the beginning
	pGUI->PrintMessage("-------------------------------------------------------------------------------------------------------------------------------------------------------------------");
	//print Data After Loading
	for (int i = 0; i < REG_CNT; i++)
		regions[i]->print(pGUI, i);

	//Enter simulation loop
	bool Continue = true;
	while (Continue)
	{
		//To Print Time Step 
		char timestep[10];
		itoa(CurrentTimeStep, timestep, 10);
		pGUI->PrintMessage("-------------------------------------------------------------------------------------------------------------------------------------------------------------------");
		pGUI->PrintTimeStep(timestep);
		//Execute Events in current time step
		ExecuteEvents(CurrentTimeStep);
		/////////////////////////////////////////////////////////////////////////////////////////////
		
		pGUI->PrintMessage("-------------------------------------------------------------------------------------------------------------------------------------------------------------------");
		//print Data After Execution
		for (int i = 0; i < REG_CNT; i++)
			regions[i]->print(pGUI, i);
		Status_bar_print();
		/////////////////////////////////////////////////////////////////////////////////////////////
		DrawActiveOrders();
		Sleep(400);
		//check returning motorcycles
		ReturnMoto(CurrentTimeStep);
		//check finished orders
		checkFinishedOrders(CurrentTimeStep);
		//Check Auto-promoted orders
		for (int i = 0; i < REG_CNT; i++)
		{
			regions[i]->searchForPromotion(CurrentTimeStep, promotion_time);
		}
		
		// Assigning Orders to Motorcycles
		Assign(CurrentTimeStep);
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//Printing status bar data
		pGUI->PrintMessage("-------------------------------------------------------------------------------------------------------------------------------------------------------------------");
		Status_bar_print();
		for (int i = 0; i < REG_CNT; i++)
			regions[i]->print(pGUI, i);
		//Reset Ouput Strings
		for(int i = 0; i < REG_CNT; i++)
		{
			output[i] = "";
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		DrawActiveOrders();

		Continue = (!ServingMotos.isEmpty()) || (! EventsQueue.isEmpty());
		CurrentTimeStep++;
		pGUI->waitForClick();
	}

	pGUI->PrintMessage(".......End of Simulation......");
	pGUI->waitForClick();

}

void Restaurant::output_file(){
	int sum_WT[4];
	int sum_ST[4];
	
	for(int i=0;i<4;i++){
		sum_WT[i]=0;
		sum_ST[i]=0;
	}
	Order*ord;
	double allOrdersMoney=0;
	double allNormMoney=0;
	double allFrozMoney=0;
	double allVipMoney=0;
	int allOrdersCount=0;
	int allNormOrdersCount=0;
	int allVipOrdersCount=0;
	int allFrozOrdersCount=0;
	int allMotorsCount=0;
	int allNormMotorsCount=0;
	int allVipMotorsCount=0;
	int allFrozMotorsCount=0;
	double all_WT=0;
	double all_ST=0;
        ofstream myfile;
		myfile.open("output.txt");
		myfile << left << setfill(' ');
		myfile<<setw(5)<<"FT";
		myfile <<setw(5)<<"ID";
		myfile <<setw(5)<<"AT";
		myfile <<setw(5)<<"WT";
		myfile <<setw(5)<<"ST";
		myfile<<"\n";
		for (int i =0; i < REG_CNT; i ++){
		allOrdersCount=	allOrdersCount+regions[i]->get_all_count();
		allNormOrdersCount+=regions[i]->get_normal_count();
		allFrozOrdersCount+=regions[i]->get_frozen_count();
		allVipOrdersCount+=regions[i]->get_vip_count();
		allMotorsCount+=regions[i]->get_all_motors_count();
		allNormMotorsCount+=regions[i]->get_normal_motors_count();
		allFrozMotorsCount+=regions[i]->get_frozen_motors_count();
		allVipMotorsCount+=regions[i]->get_vip_motors_count();
		allOrdersMoney+=regions[i]->get_all_money();
		allFrozMoney+=regions[i]->get_FROZ_money();
		allNormMoney+=regions[i]->get_NORM_money();
		allVipMoney+=regions[i]->get_VIP_money();
		}
	for(int i=0;i<allOrdersCount;i++){
	
		finishedOrders.dequeue(ord);
		myfile << left << setfill(' ');
		myfile<<setw(5)<< ord->GetFT();
		myfile<<setw(5)<<ord->GetID();
		myfile<<setw(5)<< ord->GetAT();
		myfile<<setw(5)<<ord->GetWT();
		myfile<<setw(5)<<ord->GetST();
		myfile<<"\n";
		if(ord->GetRegion()==A_REG)
		{
			sum_ST[0]+=ord->GetST();
			sum_WT[0]+=ord->GetWT();
		}
		else if(ord->GetRegion()==B_REG){
			sum_ST[1]+=ord->GetST();
			sum_WT[1]+=ord->GetWT();	
		}
		else if(ord->GetRegion()==C_REG){
		sum_ST[2]+=ord->GetST();
		sum_WT[2]+=ord->GetWT();
		}
		else{
		sum_ST[3]+=ord->GetST();
		sum_WT[3]+=ord->GetWT();
		}
		
		delete ord;
	}

	for(int i=0;i<REG_CNT;i++){
		all_ST+=sum_ST[i];
		all_WT+=sum_WT[i];
	}


	for(int i=0;i<REG_CNT;i++){
		

		myfile<<"\n"<<"Region "<< ((char)(i+65))<<":"<<"\n";
		myfile<<"\t"<<"Orders"<<": ";
		myfile<< regions[i]->get_all_count();
		myfile<<"[Norm:"<<regions[i]->get_normal_count()<<", Froz:"<<regions[i]->get_frozen_count()<<", VIP:"<<regions[i]->get_vip_count()<<"] ";
		myfile<<"\n";
		myfile<<"\t"<<"MotorC: "<<regions[i]->get_all_motors_count();
		myfile<<"[Norm:"<<regions[i]->get_normal_motors_count()<<", Froz"<<regions[i]->get_frozen_motors_count()<<", VIP:"<<regions[i]->get_vip_motors_count()<<" ]";
		if(regions[i]->get_all_count()!=0){
		myfile<<"\n"<<"\t"<<"Avg Wait = "<<((double)sum_WT[i]/regions[i]->get_all_count())<<" , "<<"Avg Serv = "<<((double)sum_ST[i]/regions[i]->get_all_count()); 
	}
		else{
		myfile<<"\n"<<"\t"<<"Avg Wait = "<<"this region hasn't any orders"<<" , "<<"Avg Serv = "<<"this region hasn't any orders";
		}
		myfile<<"\n"<<"\t"<<"Money"<<": ";
		myfile<< regions[i]->get_all_money();
		myfile<<"[Norm:"<<regions[i]->get_NORM_money()<<", Froz:"<<regions[i]->get_FROZ_money()<<", VIP:"<<regions[i]->get_VIP_money()<<"] ";
		myfile<<"\n";
	}

	myfile<<"\n"<<"Resturant : ";
	myfile<<"\n"<<"\t"<<"Orders : "<<allOrdersCount;
	myfile<<"[Norm: "<<allNormOrdersCount<<", Froz: "<<allFrozOrdersCount<<", VIP:"<<allVipOrdersCount<<"] ";
	myfile<<"\n";
	myfile<<"\t"<<"MotorC: "<<allMotorsCount;
	myfile<<"[Norm: "<<allNormMotorsCount<<" Froz: "<<allFrozMotorsCount<<", Vip: "<<allVipMotorsCount<<"] ";
    myfile<<"\n"<<"\t"<<"Avg Wait = "<<(double)(all_WT/allOrdersCount)<<", Avg Serv = "<<(double)(all_ST/allOrdersCount);
	myfile<<"\n"<<"\t"<<"Money : "<<allOrdersMoney;
	myfile<<"[Norm: "<<allNormMoney<<", Froz: "<<allFrozMoney<<", VIP:"<<allVipMoney<<"] ";
	myfile<<"\n";
	myfile.close();

}





void Restaurant::Status_bar_print(){
	served_output = "Served Orders : ";
	char temp[10];
		for(int i=0;i<REG_CNT;i++){
		
		served_output+= "REG[";
		served_output+= (char)(i + 65); //ASCI code for 'A' is 65 in DEC
		served_output+= "] : ";
		itoa(served_VIP_orders[i],temp,10);
		served_output+="VIP: ";
		served_output+=temp;
		served_output+=" || ";

		itoa(served_FROZ_orders[i],temp,10);
		served_output+="F:";
		served_output+=temp;
		served_output+=" || ";

		itoa(served_NORM_orders[i],temp,10);
		served_output+="N:";
		served_output+=temp;
		served_output+=" || ";
		}

		pGUI->printMessageAt(served_output,5);
		for(int i=0;i<REG_CNT;i++){
			pGUI->PrintMessageloc(output[i],i + 1);
		
		}
		
}

void Restaurant::filling_outputs(Order*Ord,Motorcycle*moto){
	char temp[10];
	if(moto->GetType()==TYPE_NRM){
		output[Ord->GetRegion()]+='N';
	}
	else if(moto->GetType()==TYPE_VIP){
		output[Ord->GetRegion()]+='V';
	}
	else{
		output[Ord->GetRegion()]+='F';
	}
	itoa(moto->get_id(),temp,10);
	output[Ord->GetRegion()]+=temp;

	output[Ord->GetRegion()]+="(";

	if(Ord->GetType()==TYPE_NRM){
		output[Ord->GetRegion()]+='N';
	}
	else if(Ord->GetType()==TYPE_VIP){
		output[Ord->GetRegion()]+='V';
	}
	else{
		output[Ord->GetRegion()]+='F';
	}
	itoa(Ord->GetID(),temp,10);
	output[Ord->GetRegion()]+=temp;
	output[Ord->GetRegion()]+=") ";

}

void Restaurant::Assign(int CurrentTimeStep)
{
	//Placeholders for order and motorcycle
	Order* Ord;
	Motorcycle* Moto;
	// Assigning Orders to Motorcycles
	for (int i = 0; i < REG_CNT; i++)
	{
		while (!(regions[i]->IsVIPEmpty()))
		{
			if (!(regions[i]->IsVipMotoEmpty()))
			{
				regions[i]->AssignVIP(Ord);
				regions[i]->sendVIPMoto(Moto);
				assignOrdtoMoto(Ord, Moto, CurrentTimeStep);
			}
			else if (!(regions[i]->IsNormalMotoEmpty()))
			{
				regions[i]->AssignVIP(Ord);
				regions[i]->sendNormalMoto(Moto);
				assignOrdtoMoto(Ord, Moto, CurrentTimeStep);
			}
			else if (!(regions[i]->IsFrozenMotoEmpty()))
			{
				regions[i]->AssignVIP(Ord);
				regions[i]->sendFrozMoto(Moto);
				assignOrdtoMoto(Ord, Moto, CurrentTimeStep);
			}
			else
				break;


		}
		if (regions[i]->IsVIPEmpty())
		{
			while (!(regions[i]->IsFrozenEmpty()))
			{
				if (!(regions[i]->IsFrozenMotoEmpty()))
				{
					regions[i]->AssignFroz(Ord);
					regions[i]->sendFrozMoto(Moto);
					assignOrdtoMoto(Ord, Moto, CurrentTimeStep);

				}
				else
					break;

			}
			while (!(regions[i]->IsNormalEmpty()))
			{
				if (!(regions[i]->IsNormalMotoEmpty()))
				{
					regions[i]->AssignNormal(Ord);
					regions[i]->sendNormalMoto(Moto);
					assignOrdtoMoto(Ord, Moto, CurrentTimeStep);
				}
				else if (!(regions[i]->IsVipMotoEmpty()))
				{
					regions[i]->AssignNormal(Ord);
					regions[i]->sendVIPMoto(Moto);
					assignOrdtoMoto(Ord, Moto, CurrentTimeStep);

				}
				else
					break;
			}

		}

	}
}
