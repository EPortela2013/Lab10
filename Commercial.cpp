#include "Commercial.h"
#include <sstream>

using namespace std;

Commercial::Commercial() : Property()
{
	discountRate = 0.0;
}

Commercial::Commercial(const string &newAddress, bool newRentalStatus, double newTaxRate, double newValue, double newDiscountRate) : Property(newAddress, newRentalStatus, newTaxRate, newValue)
{
	discountRate = newDiscountRate;
}


void Commercial::setDiscountRate(double newDiscountRate)
{
	//If passed discount rate is negative, do not update discount rate
	if (newDiscountRate < 0.0) return;

	discountRate = newDiscountRate;
}

double Commercial::getDiscountRate() const
{
	return discountRate;
}

double Commercial::calculateTaxes() const
{
	const double WHOLE_RATE = 1.0;		//100%

	double discountFromWhole = WHOLE_RATE - discountRate;

	return taxRate * value * discountFromWhole;
}


string Commercial::toString() const
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

	//Check if property has a discount rate by checking if the discount rate is a positive number
	if (discountRate > 0.0)
	{
		propertyInfoTemp << " Discounted  Discount " << discountRate;
	}
	else
	{
		propertyInfoTemp << " NOT discounted";
	}

	return propertyInfoTemp.str();
}