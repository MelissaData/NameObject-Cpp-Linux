#include<iostream>

using namespace std;

#ifndef DATACONTAINER_H
#define DATACONTAINER_H

/**
 * Data holder for a single record: carries the input name in and the result codes out.
 */
class DataContainer
{
public:
	// Input: the full name to process.
	char Name[40] = "";

	// Output: comma-separated result codes from GetResults().
	string ResultCodes;

	DataContainer() {};
};

#endif