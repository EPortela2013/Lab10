#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>


using namespace std;

class Property
{
public:
	/*
	*	Default constructor, initializes address to empty string, everything else to 0/false
	*/
	Property();

	/*
	*  Constructor that sets all of the attributes to the given values, id is set to the next available ID as indicated by the static member "nextID"
	*
	* Parameter:  Address of the property
	* Parameter:  Boolean, true if property is rental, false otherwise
	* Parameter:  Tax rate of property
	*/
	Property(const string &newAddress, bool newRentalStatus, double newTaxRate, double newValue);

	/*
	* setAddress	
	*
	*	Sets property's address to the argument value
	*
	* Parameter:  newAddress string of property's address
	*
	*/
	void setAddress(string newAddress);

	/*
	* setID
	*
	*  Sets property's id to the argument value
	*
	* Parameter: New id for property as an int
	*/
	void setID(int newID);

	/*
	* setRental
	*
	* Sets the property's rental status, true if rental, false otherwise
	* 
	* Parameter: Boolean value of the rental status
	*/
	void setRental(bool newRentalStatus);

	/*
	* setTaxRate
	*
	* Sets the property's tax rate to the argument value
	*
	* Parameter: Tax rate as an double
	*/
	void setTaxRate(double newTaxRate);

	/*
	* setValue
	*
	* Sets the property's estimated value to the argument value
	*
	* Parameter: Estimated value as a double as an double
	*/
	void setValue(double newValue);


	/*
	* getAddress
	*
	* Returns property's address as string
	*/
	string getAddress() const;

	/*
	* getID
	*
	* Returns property's id as an int
	*/
	int getID() const;

	/*
	* isRental
	*
	* Returns property's rental status, true if rental, false otherwise
	*/
	bool isRental() const;

	/*
	* getTaxRate
	*
	* Returns property's tax rate as double
	*/
	double getTaxRate() const;

	/*
	* getValue
	*
	* Returns property's estimated value as a double
	*/
	double getValue() const;


	/*
	* toString
	*  Returns information about the property as a string
	*/
	virtual string toString() const;

	/*
	* displayTaxInformation
	*
	*
	* Returns the tax information for the property as a string
	*/
	virtual string getTaxInformation() const;

	/*
	* calculateTaxes
	*  Returns the calculated property tax, pure virtual function
	*/
	virtual double calculateTaxes() const = 0;



protected:
	string address;					//Holds the property's address
	int id;							//Holds the property's id number
	bool rental;					//Set to true if property is rental, false otherwise
	double taxRate;					//Holds the property's tax rate
	double value;					//Holds the property's estimated value
	static int nextID;				//Holds the next available ID



};


#endif
