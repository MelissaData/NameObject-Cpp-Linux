#include<iostream>
#include <string>

#include "mdName.h"
#include "DataContainer.h"

using namespace std;

#ifndef NAMEOBJECT_H
#define NAMEOBJECT_H

class NameObject
{
public:
	// Path to Name Object data files (.dat, etc)
	string dataFilePath;

	// Create instance of Melissa Name Object
	mdName* mdNameObj = new mdName;

	NameObject(string license, string dataPath);

	// This will call the functions to process the input name as well as generate the result codes
	void ExecuteObjectAndResultCodes(DataContainer& data);
};

#endif
