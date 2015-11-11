#include "Property.h"
#include "Residential.h"
#include "Commercial.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<Property *> properties;

	properties.push_back(new Residential("45 Address Way", 0, true, 1.8, 28000, false));

	properties.push_back(new Commercial("800 Industrial Park", 1, false, 3.0, 800000, 0.2));

	cout << properties[0].toString() << endl << endl;

	cout << properties[1].toString() << endl << endl;

	delete properties[0];
	delete properties[1];

	return 0;
}