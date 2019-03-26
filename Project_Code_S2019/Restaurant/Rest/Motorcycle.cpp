#include "Motorcycle.h"


Motorcycle::Motorcycle()
{
}


Motorcycle::~Motorcycle()
{
}

ORD_TYPE Motorcycle::GetType() const
{
	return type;
}

void Motorcycle::setType(ORD_TYPE type_fn) {
	type = type_fn;
}

int Motorcycle::GetSpeed() const
{
	return speed;
}
void Motorcycle::setSpeed(int speed_fn) {
	speed = speed_fn;
}