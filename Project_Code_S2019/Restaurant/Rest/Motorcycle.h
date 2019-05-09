#ifndef __MOTORCYCLE_H_
#define __MOTORCYCLE_H_


#include "..\Defs.h"

#pragma once
class Motorcycle	
{
	int ID;
	ORD_TYPE type;	//for each order type there is a corresponding motorcycle type 
	int speed;		//meters it can move in one clock tick (in one timestep)
	REGION	region;	//region of the motorcycle
	STATUS	status;	//idle or in-service
	//---------------------------------------------------------------------------------------------//
	int ServingReturnTimeStep;//Time Step it returns from serving an order(FT+ST of an order)
	int ReturningPri; //The earlier the return ,the higher the priority {1000 - ServingReturnTimeStep}

public:
	Motorcycle();
	Motorcycle(int, ORD_TYPE, int, REGION, STATUS);
	virtual ~Motorcycle();
	//--------------------------------------------------------------------------------------------//
	ORD_TYPE GetType() const;
	int GetSpeed() const;
	void setSpeed(int speed_fn);
	void setType(ORD_TYPE type_fn);
	int get_id();

	void setReturningStep(int RTimeStep);
	int getReturningStep() const;
	int GetRegion() const;
};

#endif