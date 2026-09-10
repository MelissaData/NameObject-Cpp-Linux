/**
 * @file Main.cpp
 * @brief Name Object automates the handling of name data, making it simple to send
 * personalized business mail, tailored specifically to the gender of the people in
 * your mailing list, while screening out vulgar or obviously false names.
 *
 * High-level flow of this sample:
 *   1. SETUP     - create an mdName instance, hand it the license string and the
 *                  path to the data files, then InitializeDataFiles() (one time).
 *   2. INPUT     - feed a full name in with SetFullName().
 *   3. PROCESS   - Parse() splits the name; Genderize() and Salutate() derive the
 *                  gender and salutation from the parsed result.
 *   4. READ      - pull the individual fields back out with the Get* getters
 *                  (GetFirstName, GetLastName, GetGender, GetSalutation, ...).
 *   5. INTERPRET - GetResults() returns comma-separated result codes describing
 *                  what the object did/found; each code has a human description.
 *
 * The pieces of this sample map onto that flow:
 *   - main / ParseArguments / RunAsConsole : console harness (argument parsing + the interactive loop).
 *   - NameObject      : thin wrapper around mdName that owns setup + the call sequence.
 *   - DataContainer   : plain holder for one record's input and output.
 *
 * Where mdName comes from:
 *   There is no generated wrapper source for C++. mdName.h and
 *   mdNameEnums.h declare the API, and libmdName.so carries the implementation. The
 *   accompanying MelissaNameObjectLinuxCpp.sh script downloads all three on every run.
 *
 * Reference:
 *   Quickstart    : https://docs.melissa.com/on-premise-api/name-object/name-object-quickstart.html
 *   Release notes : https://releasenotes.melissa.com/on-premise-api/name-object/
 *   Result codes  : https://docs.melissa.com/on-premise-api/name-object/result-codes.html
 */

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

/**
 * Entry point. Reads the optional command-line arguments, then hands control to
 * RunAsConsole, which performs the actual Name Object setup and processing.
 *
 * @param argc The count of command-line arguments.
 * @param argv The raw command-line arguments.
 */
int main(int argc, char* argv[])
{
	// Populated by ParseArguments below.
	string license = "";
	string testName = "";
	string dataPath = "";

	ParseArguments(license, testName, dataPath, argc, argv);
	RunAsConsole(license, testName, dataPath);

	return 0;
}

/**
 * Reads the supported command-line options into the reference parameters.
 *
 * Recognized flags (each followed by its value, e.g. "--name Ray Melissa"):
 *   --license / -l   : the Melissa license string
 *   --dataPath / -d  : path to the Name Object data files
 *   --name / -n      : a name to test in one-shot mode
 *
 * @param license  Receives the Melissa license string.
 * @param testName Receives the name to test in one-shot mode.
 * @param dataPath Receives the path to the Name Object data files.
 * @param argc     The count of command-line arguments to parse.
 * @param argv     The raw command-line arguments to parse.
 */
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

/**
 * Sets up the Name Object once, then drives the input -> process -> output cycle.
 *
 * In interactive mode (no --name) it loops, asking for a new name each pass until
 * the user answers "N". In one-shot mode (--name supplied) it runs a single pass
 * on testName and exits.
 *
 * @param license  The Melissa license string used to initialize the object.
 * @param testName A name to process in one-shot mode; if empty, the program prompts interactively.
 * @param dataPath Path to the Name Object data files.
 */
void RunAsConsole(string license, string testName, string dataPath)
{
	cout << "\n============= WELCOME TO MELISSA NAME OBJECT LINUX C++ =============\n"	<< endl;
	
	// Construct the wrapper. This is where the object is licensed, pointed at the
	// data files, and initialized (see the NameObject constructor below).
	NameObject* nameObject = new NameObject(license, dataPath);

	bool shouldContinueRunning = true;

	while (shouldContinueRunning)
	{
		// Holder for this pass's input and result codes.
		DataContainer dataContainer = DataContainer();

		if (testName.empty())
		{
			// Interactive mode: prompt the user for a name.
			cout << "\nFill in each value to see the Name Object results" << endl;
			cout << "Name: ";

			string input;
			getline(cin, input);

			strcpy(dataContainer.Name, input.c_str());
		}
		else
		{
			// One-shot mode: use the name passed on the command line.
			strcpy(dataContainer.Name, testName.c_str());
		}

		// Print user input
		cout << "\n============================== INPUTS ==============================\n" << endl;
		cout << "\t                 Name: " + string(dataContainer.Name)                   << endl;

		// Execute Name Object
		// Runs the parse/genderize/salutate sequence and stores the result codes on dataContainer
		nameObject->ExecuteObjectAndResultCodes(dataContainer);

		// Print output
		// Each Get* getter below returns one component the object produced for the most
		// recently processed name. These read directly from the mdName instance, which
		// still holds the results from the Execute call above. Prefix/First/Middle/Last/Suffix
		// come from Parse(), Gender from Genderize(), and Salutation from Salutate().
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

		// Result codes come back as a single comma-separated string (e.g. "NS01,NS02").
		// Split it and ask the object for a readable description of each code.
		// ResultCodeDescriptionLong requests the long-form text; a short form is also
		// available via ResultCodeDescriptionShort.
		list<string> rs = SplitResultCodes(dataContainer.ResultCodes, ",");
		list<string>::iterator it;

		for (it = rs.begin(); it != rs.end(); it++)
		{
			printf("        %s: %s", it->c_str(), nameObject->mdNameObj->GetResultCodeDescription(it->c_str(), nameObject->mdNameObj->ResultCodeDescriptionLong));
			cout << endl;
		}

		bool isValid = false;

		// In one-shot mode there is nothing more to do after a single pass: mark the
		// input handled and stop the outer loop.
		if (!testName.empty()) 
		{
			isValid = true;
			shouldContinueRunning = false;
		}

		// Interactive mode: ask whether to process another name. Keep prompting until
		// we get a valid Y/N. "N" ends the program; "Y" falls through to another pass.
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

/**
 * Splits the comma-separated result-code string into individual codes.
 *
 * @param s         The result-code string (e.g. "NS01,NS02").
 * @param delimiter The delimiter string to split on.
 * @return A list holding each individual result code.
 */
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
