#include "Residential.h"
#include <sstream>

using namespace std;

Residential::Residential() : Property()
{
	occupiedStatus = false;
}

Residential::Residential(const string &newAddress, bool newRentalStatus, double newTaxRate, double newValue, bool newOccupiedStatus) : Property(newAddress, newRentalStatus, newTaxRate, newValue)
{
	occupiedStatus = newOccupiedStatus;
}


void Residential::setOccupiedStatus(bool newOccupiedStatus)
{
	occupiedStatus = newOccupiedStatus;
}

bool Residential::isOccupied() const
{
	return occupiedStatus;
}

double Residential::calculateTaxes() const
{
	return taxRate * value;
}


string Residential::toString() const
{
	ostringstream propertyInfoTemp;			//Stream that will temporarily hold the property's information


	propertyInfoTemp << "Property id: " << id << " Address: " << address;

	//Check if property is rental and append appropriate information
	if (rental)
	{
		propertyInfoTemp << " Rental";
	}
	else
	{
		propertyInfoTemp << " NOT rental";
	}

	propertyInfoTemp << " Estimated value: " << value;

	//Check if property is occupied and append appropriate information
	if (occupiedStatus)
	{
		propertyInfoTemp << " occupied";
	}
	else
	{
		propertyInfoTemp << " NOT occupied";
	}

	return propertyInfoTemp.str();
}