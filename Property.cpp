#include "Property.h"
#include <sstream>

using namespace std;

Property::Property()
{
	address = "";
	id = 0;
	rental = false;
	taxRate = 0.0;
	value = 0.0;
}


Property::Property(const string &newAddress, int newID, bool newRentalStatus, double newTaxRate, double newValue)
{

	address = newAddress;
	id = newID;
	rental = newRentalStatus;
	taxRate = newTaxRate;

}

void Property::setAddress(string newAddress)
{
	address = newAddress;
}


void Property::setID(int newID)
{
	if (newID < 0) return;  //Only accept non-negative id's, return without making changes otherwise

	id = newID;
	
}

void Property::setRental(bool newRentalStatus)
{
	rental = newRentalStatus;
}


void Property::setTaxRate(double newTaxRate)
{
	taxRate = newTaxRate;
}

void Property::setValue(double newValue)
{
	value = newValue;
}


string Property::getAddress() const
{
	return address;
}

int Property::getID() const
{
	return id;
}

bool Property::isRental() const
{
	return rental;
}

double Property::getTaxRate() const
{
	return taxRate;
}

double Property::getValue() const
{
	return value;
}


string Property::toString() const
{
	ostringstream propertyInfoTemp;			//Stream that will temporarily hold the property's information
	

	propertyInfoTemp << "Property id: " << id << " Address: " << address;

	//Check if property is rental and append appropriate information
	if (rental)
	{
		propertyInfoTemp << " rental";
	}
	else
	{
		propertyInfoTemp << " NOT rental";
	}

	propertyInfoTemp << "Estimated value: " << value;

	propertyInfoTemp << " Tax rate: " << taxRate;

	return propertyInfoTemp.str();

}