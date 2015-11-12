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
	char sortChoice;							//Will store user's sort preference, 'a' for alphabetical, 't' for tax amount due



	//Populate the properties vector
	populateProperties(properties);

	//Display header for valid properties
	cout << endl << endl << "All valid properties:" << endl << endl;

	//Display the properties
	displayProperties(properties);

	//Prompt user for sort preference
	cout << endl << endl << "How would like like to sort the tax report?" << endl
		<< "Type an 'a' for alphabetical order or a 't' for tax amount due" << endl
		<< "or any other character for no sorting and press enter: ";

	//Store choice
	cin >> sortChoice;

	//Display header for tax report
	cout << endl << endl << "NOW PRINTING TAX REPORT:" << endl << endl;

	//Check user's sort choice
	switch (sortChoice)
	{
	case 'a': 
	case 'A': 
		//Alphabetical Order
		sortAlphabetical(properties);
		break;

	case 't':
	case 'T':
		//Tax amount due
		sortByTaxDue(properties);
		break;

	default:
		//No sort, don't do anything
		break;
	}

	//Display Tax Report
	displayTaxReport(properties);

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
	int tempBoolean;										//Will be used to read boolean value from stream as int
	const int SAFE_NON_BOOLEAN = 2;							//Will be used to reset the tempBoolean variable after testing for valid values
	const int INT_TRUE = 1;								//Integer representation of boolean true
	const int INT_FALSE = 0;							//Integer representation of boolean false
	const double WHOLE_RATE = 1.0;							//100% - Discount rate cannot be bigger than this value
	const double ZERO = 0.0;								//Used for comparisons
	bool propertyRentalStatus;								//Will be set to true if property is a rental, false otherwise
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
				readStream >> tempBoolean;

				//Check for error
				if (readStream.fail() || (tempBoolean > INT_TRUE || tempBoolean < INT_FALSE))
				{
					//Invalid value for rental status, invalid record
					//Output warning message along with bad record
					displayWarning("Ignoring bad COMMERCIAL in input file: ", readLine);

					//Skip rest of iteration
					continue;
				}

				//Update property rental status according to read-in value in tempBoolean

				switch (tempBoolean)
				{
				case INT_FALSE:
					propertyRentalStatus = false;
					break;
				case INT_TRUE:
					propertyRentalStatus = true;
					break;
				}

				//Reset tempBoolean for next read

				tempBoolean = SAFE_NON_BOOLEAN;

				//Read estimated property value
				readStream >> propertyValue;

				//Check for error
				if (readStream.fail() || propertyValue <= ZERO)
				{
					//Invalid value for property value, invalid record
					//Output warning message along with bad record
					displayWarning("Ignoring bad COMMERCIAL in input file: ", readLine);

					//Skip rest of iteration
					continue;
				}

				//Read discount rate status

				readStream >> tempBoolean;

				//Check for error
				if (readStream.fail() || (tempBoolean > INT_TRUE || tempBoolean < INT_FALSE))
				{
					//Invalid value for discount rate status, invalid record
					//Output warning message along with bad record
					displayWarning("Ignoring bad COMMERCIAL in input file: ", readLine);

					//Skip rest of iteration
					continue;
				}

				//Update discount rate status according to read-in value in tempBoolean

				switch (tempBoolean)
				{
				case INT_FALSE:
					discountRateStatus = false;
					break;
				case INT_TRUE:
					discountRateStatus = true;
					break;
				}

				//Reset tempBoolean for next read

				tempBoolean = SAFE_NON_BOOLEAN;


				//Read discount rate

				readStream >> discountRate;

				//Check for error
				if (readStream.fail() || (discountRateStatus == true && discountRate >= WHOLE_RATE) )
				{
					//Invalid value for discount rate, invalid record
					//Output warning message along with bad record
					displayWarning("Ignoring bad COMMERCIAL in input file: ", readLine);

					//Skip rest of iteration
					continue;
				}

				//If discount rate status is false, set discount rate to ZERO
				if (discountRateStatus == false) discountRate = ZERO;

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

				//All of the commercial record was read, create object and push it onto the vector



				//Determine if property is rental as tax rate differs based on this
				if (propertyRentalStatus == true)
				{
					newProperty = new Commercial(propertyAddress, propertyRentalStatus, COM_TAX_RENTAL, propertyValue, discountRate);
				}
				else
				{
					newProperty = new Commercial(propertyAddress, propertyRentalStatus, COM_TAX_NON_RENTAL, propertyValue, discountRate);

				}

				//Push pointer to newly created property onto vector

				properties.push_back(newProperty);


			} 
			else if (propertyType == "Residential")
			{
				//Continue processing file as residential property

				//Read rental status
				readStream >> tempBoolean;

				//Check for error
				if (readStream.fail() || (tempBoolean > INT_TRUE || tempBoolean < INT_FALSE))
				{
					//Invalid value for rental status, invalid record
					//Output warning message along with bad record
					displayWarning("Ignoring bad COMMERCIAL in input file: ", readLine);

					//Skip rest of iteration
					continue;
				}

				//Update property rental status according to read-in value in tempBoolean

				switch (tempBoolean)
				{
				case INT_FALSE:
					propertyRentalStatus = false;
					break;

				case INT_TRUE:
					propertyRentalStatus = true;
					break;
				}

				//Reset tempBoolean for next read
				tempBoolean = SAFE_NON_BOOLEAN;


				//Read estimated property value
				readStream >> propertyValue;

				//Check for error
				if (readStream.fail() || propertyValue <= ZERO)
				{
					//Invalid value for property value, invalid record
					//Output warning message along with bad record
					displayWarning("Ignoring bad RESIDENTIAL in input file: ", readLine);

					//Skip rest of iteration
					continue;
				}

				//Read occupied status

				readStream >> tempBoolean;

				//Check for error
				if (readStream.fail() || (tempBoolean > INT_TRUE || tempBoolean < INT_FALSE))
				{
					//Invalid value for property occupied status, invalid record
					//Output warning message along with bad record
					displayWarning("Ignoring bad COMMERCIAL in input file: ", readLine);

					//Skip rest of iteration
					continue;
				}

				//Update property occupied status according to read-in value in tempBoolean

				switch (tempBoolean)
				{
				case INT_FALSE:
					occupiedStatus = false;
					break;

				case INT_TRUE:
					occupiedStatus = true;
					break;
				}

				//Reset tempBoolean for next read
				tempBoolean = SAFE_NON_BOOLEAN;

				//Read address
				getline(readStream, propertyAddress);

				//Check for error
				if (readStream.fail())
				{
					//Invalid value for property address, invalid record
					//Output warning message along with bad record
					displayWarning("Ignoring bad RESIDENTIAL in input file: ", readLine);

					//Skip rest of iteration
					continue;
				}

				//All of the residential record was read, create object and push it onto the vector



				//Determine if property is occupied as tax rate differs based on this
				if (occupiedStatus == true)
				{
					newProperty = new Residential(propertyAddress, propertyRentalStatus, RES_TAX_OCCUPIED, propertyValue, occupiedStatus);
				}
				else
				{
					newProperty = new Residential(propertyAddress, propertyRentalStatus, RES_TAX_UNOCCUPIED, propertyValue, occupiedStatus);

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
					if (readLine != "") displayWarning("Ignoring unknown types of properties appearing in the input file: ", readLine);
					else displayWarning("Ignoring bad input in input file: ", "");

				}
				else
				{
					//End of file
					//If last line is not empty, display bad record
					if(readLine != "") displayWarning("Ignoring unknown types of properties appearing in the input file: ", readLine);

				}


			}

		}

		//Close file
		fileInput.close();

	}
	else
	{
		//Unable to open file
		//Display error message
		cout << "Unable to open file!" << endl;
	}




}


void displayProperties(const vector<Property *> &properties)
{
	int vectorSize = properties.size();				//Store the vector size

	//Check if vector is empty
	if (vectorSize == 0)
	{
		//Vector is empty, display message and return
		cout << "There are no valid properties to display " << endl;
		
	}

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

	//Check if vector is empty
	if (vectorSize == 0)
	{
		//Vector is empty, display message and return
		cout << "There are no valid properties to display " << endl;

	}

	//Iterate through the whole vector
	for (int i = 0; i < vectorSize; i++)
	{
		//Check if current pointer is not null
		if (properties[i] != NULL)
		{
			//Display current property's tax due information
			cout << "** Taxes due for the property at: " << setw(26) <<  properties[i]->getAddress() << endl
				<< "   Property id:" << setw(45) << properties[i]->getID() << endl
				<< "   This property has an estimated value of: " << setw(16) << properties[i]->getValue() << endl
				<< "   Taxes due on this property are: " << setw(25) << properties[i]->calculateTaxes() << endl << endl;

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


void sortAlphabetical(vector<Property *> &properties)
{

	int vectorSize = properties.size();						//Store vector size
	bool sorted;											//Set to true if properties are in sorted order
	Property * temp;										//Will temporarily hold a pointed to be moved

    //If vector is empty return
	if (vectorSize == 0) return;

	//Loop until all are sorted
	do
	{
		// Reset sort flag to true for each iteration
		sorted = true;

		//Iterate through all of the properties
		//Stop at vectorSize - 1 to avoid accessing outside vector limits
		for (int i = 0; i < vectorSize - 1; i++)
		{
			//Check to make sure neither pointer points to NULL
			if (properties[i] != NULL && properties[i + 1] != NULL)
			{
				//Create string streams to extract numeric part of addresses
				istringstream addressStream1(properties[i]->getAddress());
				istringstream addressStream2(properties[i + 1]->getAddress());

				//Create integers to hold numeric part of addresses
				int numAddress1;
				int numAddress2;

				//Create strings to hold the remainder of the addresses
				string address1;
				string address2;

				//Store numeric parts
				addressStream1 >> numAddress1;
				addressStream2 >> numAddress2;

				//Store remainder parts
				getline(addressStream1, address1);
				getline(addressStream2, address2);

				//Compare current item with next item
				if (numAddress2 < numAddress1)
				{
					//Switch pointer positions
					temp = properties[i];
					properties[i] = properties[i + 1];
					properties[i + 1] = temp;

					//Set flag to do outer loop once more
					sorted = false;
				}
				else if (numAddress1 == numAddress2)
				{
					//Numeric parts are identical, compare using remainder of addresses
					if (address2 < address1)
					{
						//Switch pointer positions
						temp = properties[i];
						properties[i] = properties[i + 1];
						properties[i + 1] = temp;

						//Set flag to do outer loop once more
						sorted = false;
					}
				}

			}


		}

	} while (!sorted);

}

void sortByTaxDue(vector<Property *> &properties)
{
	int vectorSize = properties.size();						//Store vector size
	bool sorted;											//Set to true if properties are in sorted order
	Property * temp;										//Will temporarily hold a pointed to be moved

	//If vector is empty return
	if (vectorSize == 0) return;

	//Loop until all are sorted
	do
	{
		// Reset sort flag to true for each iteration
		sorted = true;

		//Iterate through all of the properties
		//Stop at vectorSize - 1 to avoid accessing outside vector limits
		for (int i = 0; i < vectorSize - 1; i++)
		{
			//Check to make sure neither pointer points to NULL
			if (properties[i] != NULL && properties[i + 1] != NULL)
			{
				//Compare current item with next item
				if (properties[i]->calculateTaxes() > properties[i + 1]->calculateTaxes())
				{
					//Switch pointer positions
					temp = properties[i];
					properties[i] = properties[i + 1];
					properties[i + 1] = temp;

					//Set flag to do outer loop once more
					sorted = false;
				}
			}


		}

	} while (!sorted);

}