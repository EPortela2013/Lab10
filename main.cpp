#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "Property.h"
#include "Residential.h"
#include "Commercial.h"
#include "Helper_Functions.h"


using namespace std;

int main()
{
	Property::nextID = 0;					//Initialize the next available id to 0
	vector<Property *> properties;			//Vector to hold all the valid properties



	//Populate the properties vector
	populateProperties(properties);



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
	double discountRate;									//Will hold the commercial property's discount rate
	double propertyValue;									//Will hold the estimated property value
	
	
	const double RES_TAX_OCCUPIED = 0.006;					//Tax rate for residential, ocuppied properties 0.6%
	const double RES_TAX_UNOCCUPIED = 0.009;				//Tax rate for residential, unocuppied properties 0.9%

	const double COM_TAX_RENTAL = 0.012;					//Tax rate for commercial, rental properties 1.2%
	const double COM_TAX_NON_RENTAL = 0.01;					//Tax rate for commercial, non-rental properties 1%




	ifstream fileInput;			//Stream for the input file
	

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
					printWarning("")
				}
				
			}
			else
			{
				//Property type was neither commercial nor residential, invalid record

				//Output warning message along with bad record
				printWarning("Ignoring bad input in input file: ", readLine);

				//Skip rest of loop
				continue;
			}

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


void printWarning(const string &message, const string &record)
{

}