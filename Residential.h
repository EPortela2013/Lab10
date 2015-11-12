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

	/*
	* Constructor
	*
	* Sets all attributes to the passed values, id is set to the next available ID as indicated by the static member of Property "nextID"
	*
	*/
	Residential(const string &newAddress, bool newRentalStatus, double newTaxRate, double newValue, bool newOccupiedStatus);


	/*
	* setOccupiedStatus
	*
	* Sets the occupied status to the argument value
	*
	* Parameter: Bool of occupied status, true if property is occupied, false othersie
	*/
	void setOccupiedStatus(bool newOccupiedStatus);

	/*
	* isOccupied
	*
	* Returns the occupied status of the property
	*/
	bool isOccupied() const;

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
	bool occupiedStatus;			//Set to true if property is occupied, false otherwise

};

#endif