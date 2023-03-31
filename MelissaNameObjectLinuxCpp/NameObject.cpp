#include "NameObject.h"

NameObject::NameObject(string license, string dataPath)
{
	// Set license string and set path to data files (.dat, etc)
	mdNameObj->SetLicenseString(license.c_str());
	dataFilePath = dataPath;
	mdNameObj->SetPathToNameFiles(dataFilePath.c_str());

	// If you see a different date than expected, check your license string and either download the new data files or use the Melissa Updater program to update your data files.  
	mdName::ProgramStatus pStatus = mdNameObj->InitializeDataFiles();

	// If an issue occurred while initializing the data files, this will throw
	if (pStatus != mdName::ProgramStatus::NoError) 
	{
		cout << "Failed to Initialize Object." << endl;
		cout << pStatus << endl;
		return;
	}

	cout << "                DataBase Date: " + string(mdNameObj->GetDatabaseDate()) << endl;
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
	mdNameObj->ClearProperties();

	mdNameObj->SetFullName(data.Name);
	mdNameObj->Parse();
	mdNameObj->Genderize();
	mdNameObj->Salutate();

	data.ResultCodes = mdNameObj->GetResults();

	// ResultsCodes explain any issues Name Object has with the object.
	// List of result codes for Name Object
	// https://wiki.melissadata.com/?title=Result_Code_Details#Name_Object
}
