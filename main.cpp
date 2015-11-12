#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "Property.h"
#include "Residential.h"
#include "Commercial.h"
#include "Helper_Functions.h"


using namespace std;

int main()
{

	vector<Property *> properties;				//Vector to hold all the valid properties



	//Populate the properties vector
	populateProperties(properties);

	//Display header for valid properties
	cout << endl << endl << "All valid properties:" << endl << endl;

	//Display the properties
	displayProperties(properties);

	//Display Tax Report
	displayTaxReport(properties);

	system("pause");

	//Program terminating, unallocate memory
	deleteProperties(properties);

	return 0;
}


void populateProperties(vector<Property *> &properties)
{
	string fileName;										//Will store the file name of the file to be read
	string readLine;										//Will temporarily store each read line
	string propertyType;									//Will hold the type of property, valid values are "Commercial" or "Residential"
	string propertyAddress;									//Will hold the property address
	bool propertyRental;									//Will be set to true if property is a rental, false otherwise
	bool occupiedStatus;									//Will be set to true if the residential property is occupied, false otherwise
	bool discountRateStatus;								//Will be set to true if the commercial property has a tax discount rate
	double discountRate;									//Will hold the commercial property's discount rate
	double propertyValue;									//Will hold the estimated property value

	Property *newProperty;									//Property pointer to temporarily hold pointer to newly created properties
	
	const double RES_TAX_OCCUPIED = 0.006;					//Tax rate for residential, occupied properties 0.6%
	const double RES_TAX_UNOCCUPIED = 0.009;				//Tax rate for residential, unoccupied properties 0.9%

	const double COM_TAX_RENTAL = 0.012;					//Tax rate for commercial, rental properties 1.2%
	const double COM_TAX_NON_RENTAL = 0.01;					//Tax rate for commercial, non-rental properties 1%
	
	ifstream fileInput;										//Stream for the input file
	


	//Prompt user for the file name
	cout << "From where should I read the data? ";

	//Store response
	getline(cin, fileName);

	//Open the file
	fileInput.open(fileName.c_str());

	//Check if file was opened successfully
	if (fileInput.fail() == false)
	{
		//File open did not fail, read file contents

		//Loop through all the records
		while (fileInput.eof() == false)
		{
			//Reinitialize property type to empty string
			propertyType = "";

			//Read line and store it
			getline(fileInput, readLine);

			//Create string stream and populate it using the read line
			istringstream readStream(readLine);

			//Read property type and store it
			readStream >> propertyType;

			//Check if propertyType is valid
			if (propertyType == "Commercial")
			{
				//Continue processing file as commercial property

				//Read rental status
				readStream >> propertyRental;

				//Check for error
				if (readStream.fail())
				{
					//Invalid value for rental status, invalid record
					//Output warning message along with bad record, if it's not the end of the file
					if(fileInput.get() == false) displayWarning("Ignoring bad COMMERCIAL in input file: ", readLine);

					//Skip rest of iteration
					continue;
				}

				//Read estimated property value
				readStream >> propertyValue;

				//Check for error
				if (readStream.fail())
				{
					//Invalid value for rental status, invalid record
					//Output warning message along with bad record
					displayWarning("Ignoring bad COMMERCIAL in input file: ", readLine);

					//Skip rest of iteration
					continue;
				}

				//Read discount rate status

				readStream >> discountRateStatus;

				//Check for error
				if (readStream.fail())
				{
					//Invalid value for rental status, invalid record
					//Output warning message along with bad record
					displayWarning("Ignoring bad COMMERCIAL in input file: ", readLine);

					//Skip rest of iteration
					continue;
				}

				//Read discount rate

				readStream >> discountRate;

				//Check for error
				if (readStream.fail())
				{
					//Invalid value for rental status, invalid record
					//Output warning message along with bad record
					displayWarning("Ignoring bad COMMERCIAL in input file: ", readLine);

					//Skip rest of iteration
					continue;
				}

				//If discount rate status is false, set discount rate to 0.0
				if (discountRateStatus == false) discountRate = 0.0;

				//Read address
				getline(readStream, propertyAddress);

				//Check for error
				if (readStream.fail())
				{
					//Invalid value for rental status, invalid record
					//Output warning message along with bad record
					displayWarning("Ignoring bad COMMERCIAL in input file: ", readLine);

					//Skip rest of iteration
					continue;
				}

				//All of the record was read, create object and push it onto the vector



				//Determine if property is rental as tax rate differs based on this
				if (propertyRental == true)
				{
					newProperty = new Commercial(propertyAddress, propertyRental, COM_TAX_RENTAL, propertyValue, discountRate);
				}
				else
				{
					newProperty = new Commercial(propertyAddress, propertyRental, COM_TAX_NON_RENTAL, propertyValue, discountRate);

				}

				//Push pointer to newly created property onto vector

				properties.push_back(newProperty);


			} 
			else if (propertyType == "Residential")
			{
				//Continue processing file as residential property

				//Read rental status
				readStream >> propertyRental;

				//Check for error
				if (readStream.fail())
				{
					//Invalid value for rental status, invalid record
					//Output warning message along with bad record
					displayWarning("Ignoring bad RESIDENTIAL in input file: ", readLine);

					//Skip rest of iteration
					continue;
				}

				//Read estimated property value
				readStream >> propertyValue;

				//Check for error
				if (readStream.fail())
				{
					//Invalid value for rental status, invalid record
					//Output warning message along with bad record
					displayWarning("Ignoring bad RESIDENTIAL in input file: ", readLine);

					//Skip rest of iteration
					continue;
				}

				//Read occupied status

				readStream >> occupiedStatus;

				//Check for error
				if (readStream.fail())
				{
					//Invalid value for rental status, invalid record
					//Output warning message along with bad record
					displayWarning("Ignoring bad RESIDENTIAL in input file: ", readLine);

					//Skip rest of iteration
					continue;
				}

				//Read address
				getline(readStream, propertyAddress);

				//Check for error
				if (readStream.fail())
				{
					//Invalid value for rental status, invalid record
					//Output warning message along with bad record
					displayWarning("Ignoring bad RESIDENTIAL in input file: ", readLine);

					//Skip rest of iteration
					continue;
				}

				//All of the record was read, create object and push it onto the vector



				//Determine if property is occupied as tax rate differs based on this
				if (occupiedStatus == true)
				{
					newProperty = new Residential(propertyAddress, propertyRental, RES_TAX_OCCUPIED, propertyValue, occupiedStatus);
				}
				else
				{
					newProperty = new Residential(propertyAddress, propertyRental, RES_TAX_UNOCCUPIED, propertyValue, occupiedStatus);

				}

				//Push pointer to newly created property onto vector

				properties.push_back(newProperty);
				
				
			}
			else
			{
				//Property type was neither commercial nor residential, invalid record

				//Check for end of file
				if (fileInput.eof() == false)
				{
					//Output warning message along with bad record
					displayWarning("Ignoring unknown types of properties appearing in the input file: ", readLine);

				}
				else
				{
					//End of file
					//If last line is not empty, display bad record
					if(readLine != "") displayWarning("Ignoring unknown types of properties appearing in the input file: ", readLine);

				}


			}

		}

	}




}


void displayProperties(const vector<Property *> &properties)
{
	int vectorSize = properties.size();				//Store the vector size

	//Iterate through the whole vector
	for (int i = 0; i < vectorSize; i++)
	{
		//Check if current pointer is not null
		if(properties[i] != NULL)
		{
			//Display current property's information
			cout << properties[i]->toString() << endl;
		}
	}
}

void displayTaxReport(const vector<Property *> &properties)
{
	int vectorSize = properties.size();				//Store the vector size

	//Iterate through the whole vector
	for (int i = 0; i < vectorSize; i++)
	{
		//Check if current pointer is not null
		if (properties[i] != NULL)
		{
			//Display current property's tax due information
			cout << "** Taxes due for the property at: " << properties[i]->getAddress() << endl
				 << "   Property id:" << setw(20) << properties[i]->getID() << endl
				 << "   This property has an estimated value of: "
			cout << properties[i]->toString() << endl;
		}
	}
}


void deleteProperties(vector<Property *> &properties)
{
	int vectorSize = properties.size();			//Store vector size

	//Loop through all the members of the vector
	for (int i = 0; i < vectorSize; i++)
	{
		//Unallocate the memory space
		delete properties[i];
	}
}


void displayWarning(const string &message, const string &record)
{
	cout << endl << message << record;
}