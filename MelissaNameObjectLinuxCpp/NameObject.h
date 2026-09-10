#include<iostream>
#include <string>

#include "mdName.h"
#include "DataContainer.h"

using namespace std;

#ifndef NAMEOBJECT_H
#define NAMEOBJECT_H

/**
 * Wrapper that owns a single Melissa Name Object instance and encapsulates the two
 * things every Melissa object needs: one-time setup (license + data files) and the
 * per-record processing sequence. Reuse one instance across many names; do NOT
 * re-initialize per name.
 */
class NameObject
{
public:
	// Path to the Name Object data files.
	string dataFilePath;

	// The underlying Melissa Name Object instance.
	mdName* mdNameObj = new mdName;

	/**
	 * Performs the mandatory one-time setup, in this required order:
	 *   1. SetLicenseString    - authorize the object.
	 *   2. SetPathToNameFiles  - tell it where the data files live.
	 *   3. InitializeDataFiles - load the data into memory.
	 *
	 * @param license  The Melissa license string used to authorize the object.
	 * @param dataPath Path to the folder containing the Name Object data files.
	 */
	NameObject(string license, string dataPath);

	/**
	 * Runs the full Name Object processing sequence for one name and captures its
	 * result codes. This is the canonical per-record call pattern to copy into your
	 * own application:
	 *   ClearProperties -> SetFullName -> Parse -> Genderize -> Salutate -> GetResults
	 *
	 * @param data The record to process. Its Name is read as input, and ResultCodes is
	 *             populated with this run's result codes.
	 */
	void ExecuteObjectAndResultCodes(DataContainer& data);
};

#endif
