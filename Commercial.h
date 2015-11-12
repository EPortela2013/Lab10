#ifndef COMMERCIAL_H
#define COMMERCIAL_H

#include "Property.h"

class Commercial : public Property
{
public:
	/*
	* Default Constructor
	*
	* Sets address to empty string, everything else to 0/false
	*/
	Commercial();

	/*
	* Constructor
	*
	* Sets all attributes to the passed values, id is set to the next available ID as indicated by the static member of Property "nextID"
	*
	*/
	Commercial(const string &newAddress, bool newRentalStatus, double newTaxRate, double newValue, double newDiscountRate);


	/*
	* setDiscountRate
	*
	* Sets the discount rate to the argument value
	*
	* Parameter: New discount rate as a double
	*/
	void setDiscountRate(double newDiscountRate);

	/*
	* getDiscountRate
	*
	* Returns the property's discount rate as a double
	*/
	double getDiscountRate() const;

	/*
	*
	* calculateTaxes
	*
	* Calculates the property taxes and returns it as a double
	*
	*/
	virtual double calculateTaxes() const;

	/*
	* toString
	*  Returns information about the property as a string
	*/
	virtual string toString() const;

private:
	double discountRate;			//Will hold the property's discount rate

};

#endif