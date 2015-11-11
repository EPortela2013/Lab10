#ifndef RESIDENTIAL_H
#define RESIDENTIAL_H

#include "Property.h"

class Residential : public Property
{
public:
	/*
	* Default Constructor
	*
	* Sets address to empty string, everything else to 0/false
	*/
	Residential();

	Residential(const string &newAddress, int newID, bool newRentalStatus, double newTaxRate, double newValue);


	virtual double calculateTaxes();

};

#endif