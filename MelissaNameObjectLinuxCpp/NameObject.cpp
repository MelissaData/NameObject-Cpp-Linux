#include "NameObject.h"

NameObject::NameObject(string license, string dataPath)
{
	// Set license string and set path to data files
	mdNameObj->SetLicenseString(license.c_str());
	dataFilePath = dataPath;
	mdNameObj->SetPathToNameFiles(dataFilePath.c_str());

	// Load the data files. The returned ProgramStatus reports whether initialization succeeded.
	// If you see a different date than expected, check your license string and either download the new data files
	// or use the Melissa Updater program to update your data files.
	mdName::ProgramStatus pStatus = mdNameObj->InitializeDataFiles();

	// If an issue occurred, please investigate the common causes.
	// Common causes: an invalid/expired license, or missing/wrong-path data files.
	if (pStatus != mdName::ProgramStatus::NoError) 
	{
		cout << "Failed to Initialize Object." << endl;
		cout << pStatus << endl;
		return;
	}

	// Diagnostic information, handy for confirming the object loaded the data you expect:

	// Build date of the data files
	cout << "                DataBase Date: " + string(mdNameObj->GetDatabaseDate()) << endl;

	// When the license stops working
	cout << "              Expiration Date: " + string(mdNameObj->GetLicenseExpirationDate()) << endl;

	/**
	 * This number should match with the file properties of the Melissa Object binary file.
	 * If TEST appears with the build number, there may be a license key issue.
	 */
	cout << "               Object Version: " + string(mdNameObj->GetBuildNumber()) << endl;
}

// This will call the functions to process the input name as well as generate the result codes
void NameObject::ExecuteObjectAndResultCodes(DataContainer& data)
{
	// Reset any state left over from a previous name. Important when reusing the same
	// object across multiple records so fields from a prior name don't bleed into this one.
	mdNameObj->ClearProperties();

	// Supply the raw full-name string to process
	mdNameObj->SetFullName(data.Name);

	// Split it into prefix/first/middle/last/suffix
	mdNameObj->Parse();

	// Infer gender from the parsed first name
	mdNameObj->Genderize();

	// Build a salutation from the parsed components
	mdNameObj->Salutate();

	// Collect the result codes for this run
	// ResultsCodes explain any issues Name Object has with the object.
	// List of result codes for Name Object
	// https://docs.melissa.com/on-premise-api/name-object/result-codes.html
	data.ResultCodes = mdNameObj->GetResults();
}
