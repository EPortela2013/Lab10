#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

/*
* populateProperties
*
* Prompts user for file to read and populates given properties vector
*
* Parameter: Vector of properties
*/
void populateProperties(vector<Property *> &properties);


/*
* displayProperties
*
* Displays all of the properties in the given vector
*
* Parameter: Vector of properties
*/
void displayProperties(const vector<Property *> &properties);

/*
* displayTaxReport
*
* Displays the tax due information for all properties in vector
*
* Parameter: Vector of properties
*/
void displayTaxReport(const vector<Property *> &properties);

/*
* displayWarning
*
* Displays warning message and misformed record
*
* Parameter: Warning message
* Parameter: Misformed record
*/
void displayWarning(const string &message, const string &record);



/*
* deleteProperties
*
* Frees memory taken by objects in properties vector
*
* Parameter: Vector of properties
*/
void deleteProperties(vector<Property *> &properties);


/*
* sortAlphabetical
*
* Sorts the properties in the given vector by alphabetical order
*
* Parameter: Vector of properties
*/
void sortAlphabetical(vector<Property *> &properties);

/*
* sortByTaxDue
*
* Sorts the properties in the given vector by increasing tax due amount
*
* Parameter: Vector of properties
*/
void sortByTaxDue(vector<Property *> &properties);

#endif