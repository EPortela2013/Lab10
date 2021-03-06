#include "Property.h"
#include <sstream>
#include <iomanip>

using namespace std;

int Property::nextID = 0;					//Initialize the next available id to 0

Property::Property()
{
	address = "";
	id = 0;
	rental = false;
	taxRate = 0.0;
	value = 0.0;
	nextID++;

}


Property::Property(const string &newAddress, bool newRentalStatus, double newTaxRate, double newValue)
{

	address = newAddress;
	id = nextID;
	rental = newRentalStatus;
	taxRate = newTaxRate;
	value = newValue;
	nextID++;

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
		propertyInfoTemp << " Rental";
	}
	else
	{
		propertyInfoTemp << " NOT rental";
	}

	propertyInfoTemp << " Estimated value: " << value;

	propertyInfoTemp << " Tax rate: " << taxRate;

	return propertyInfoTemp.str();

}


string Property::getTaxInformation() const
{
	ostringstream propertyInfoTemp;			//Stream that will temporarily hold the property's tax information

	propertyInfoTemp << "** Taxes due for the property at: " << setw(26) << address << endl
				     << "   Property id:" << setw(45) << id << endl
					 << "   This property has an estimated value of: " << setw(16) << value << endl
					 << "   Taxes due on this property are: " << setw(25) << calculateTaxes() << endl;

	return propertyInfoTemp.str();

}