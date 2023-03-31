#include <iostream>
#include <cstring>
#include <cstdlib>
#include <list>

#include "mdName.h"
#include "NameObject.h"
#include "DataContainer.h"

using namespace std;

// function declarations
void ParseArguments(string& license, string& testName, string& dataPath, int argc, char** argv);
void RunAsConsole(string license, string testName, string dataPath);
list<string> SplitResultCodes(string s, string delimiter);

int main(int argc, char* argv[])
{
	// Variables
	string license = "";
	string testName = "";
	string dataPath = "";

	ParseArguments(license, testName, dataPath, argc, argv);
	RunAsConsole(license, testName, dataPath);

	return 0;
}

void ParseArguments(string& license, string& testName, string& dataPath, int argc, char* argv[])
{
	for (int i = 1; i < argc; i++)
	{
		if (string(argv[i]) == "--license" || string(argv[i]) == "-l")
		{
			if (argv[i + 1] != NULL)
			{
				license = argv[i + 1];
			}
		}
		if (string(argv[i]) == "--name" || string(argv[i]) == "-n")
		{
			if (argv[i + 1] != NULL)
			{
				testName = argv[i + 1];
			}
		}
		if (string(argv[i]) == "--dataPath" || string(argv[i]) == "-d")
		{
			if (argv[i + 1] != NULL)
			{
				dataPath = argv[i + 1];
			}
		}
	}
}

void RunAsConsole(string license, string testName, string dataPath)
{
	cout << "\n============= WELCOME TO MELISSA NAME OBJECT LINUX C++ =============\n"	<< endl;
	
	NameObject* nameObject = new NameObject(license, dataPath);

	bool shouldContinueRunning = true;

	while (shouldContinueRunning)
	{
		DataContainer dataContainer = DataContainer();

		if (testName.empty())
		{
			cout << "\nFill in each value to see the Name Object results" << endl;
			cout << "Name: ";

			string input;
			getline(cin, input);

			strcpy(dataContainer.Name, input.c_str());
		}
		else
		{
			strcpy(dataContainer.Name, testName.c_str());
		}

		// Print user input
		cout << "\n============================== INPUTS ==============================\n" << endl;
		cout << "\t                 Name: " + string(dataContainer.Name)                   << endl;

		// Execute Name Object
		nameObject->ExecuteObjectAndResultCodes(dataContainer);

		// Print output
		cout << "\n============================== OUTPUT ==============================\n"      << endl;
		cout << "\n\tName Object Information:"                                                  << endl;
		cout << "\t               Prefix: " + string(nameObject->mdNameObj->GetPrefix())        << endl;
		cout << "\t           First Name: " + string(nameObject->mdNameObj->GetFirstName())     << endl;
		cout << "\t          Middle Name: " + string(nameObject->mdNameObj->GetMiddleName())    << endl;
		cout << "\t            Last Name: " + string(nameObject->mdNameObj->GetLastName())      << endl;
		cout << "\t               Suffix: " + string(nameObject->mdNameObj->GetSuffix())        << endl;
		cout << "\t               Gender: " + string(nameObject->mdNameObj->GetGender())        << endl;
		cout << "\t           Salutation: " + string(nameObject->mdNameObj->GetSalutation())    << endl;
		cout << "\t         Result Codes: " + dataContainer.ResultCodes                         << endl;

		list<string> rs = SplitResultCodes(dataContainer.ResultCodes, ",");
		list<string>::iterator it;

		for (it = rs.begin(); it != rs.end(); it++)
		{
			printf("        %s: %s", it->c_str(), nameObject->mdNameObj->GetResultCodeDescription(it->c_str(), nameObject->mdNameObj->ResultCodeDescriptionLong));
			cout << endl;
		}

		bool isValid = false;
		if (!testName.empty()) 
		{
			isValid = true;
			shouldContinueRunning = false;
		}
		while (!isValid)
		{
			string testAnotherResponse;

			cout << "\nTest another name? (Y/N)" << endl;
			getline(cin, testAnotherResponse);

			if (!testAnotherResponse.empty())
			{
				if (testAnotherResponse == "y" || testAnotherResponse == "Y")
				{
					isValid = true;
				}
				else if (testAnotherResponse == "n" || testAnotherResponse == "N")
				{
					isValid = true;
					shouldContinueRunning = false;
				}
				else
				{
					cout << "Invalid Response, please respond 'Y' or 'N'" << endl;
				}
			}
		}
	}
	cout << "\n=============== THANK YOU FOR USING MELISSA C++ OBJECT =============\n" << endl;
}

/// <summary>
/// This function splits the resultCodes based on a delimiter
/// </summary>
/// <param name="s">the resultCode string</param>
/// <param name="delimiter"the delimiter string></param>
/// <returns></returns>
list<string> SplitResultCodes(string s, string delimiter) {
	list<string> resultCodes;

	size_t pos = 0;
	string token;

	while ((pos = s.find(delimiter)) != string::npos) {
		token = s.substr(0, pos);
		resultCodes.push_back(token);
		s.erase(0, pos + delimiter.length());
	}

	// push back the last resultCode
	resultCodes.push_back(s);

	return resultCodes;
}
