#pragma once  // Ensures this header file is included only once during compilation
#include <iostream>
#include <string>
#include "clsPerson.h"   // Base class for person info (name, email, phone)
#include "clsString.h"
#include <vector>
#include <fstream>

using namespace std;

// Bank client class that inherits from clsPerson
class clsBankClient : public clsPerson
{
private:
	// Mode of the object: empty (no data) or update (loaded/existing client)
	enum enMode { EmptyMode = 0, UpdateMode = 1 };
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;      
	float _AccountBalance;

public:

	// Constructor: initializes the client with all details
	// Passes personal info to the base class clsPerson
	clsBankClient(enMode Mode, string FirstName, string LastName,
		string Email, string Phone, string AccountNumber, string PinCode,
		float AccountBalance) :
		clsPerson(FirstName, LastName, Email, Phone)

	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;

	}

	// Checks if the object is empty (no client data)
	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}


	// Returns the account number (read-only)
	string AccountNumber()
	{
		return _AccountNumber;
	}

	// Sets a new PIN code
	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	// Returns the current PIN code
	string GetPinCode()
	{
		return _PinCode;
	}
	// Property to access PinCode like a variable (get/set)
	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	// Sets a new account balance
	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	// Returns the current account balance
	float GetAccountBalance()
	{
		return _AccountBalance;
	}
	// Property to access AccountBalance like a variable (get/set)
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

	// Prints all client details
	void Print()
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << FirstName;       // Inherited from clsPerson
		cout << "\nLastName    : " << LastName;        // Inherited from clsPerson
		cout << "\nFull Name   : " << FullName();      // Inherited method from clsPerson
		cout << "\nEmail       : " << Email;           // Inherited from clsPerson
		cout << "\nPhone       : " << Phone;           // Inherited from clsPerson
		cout << "\nAcc. Number : " << _AccountNumber;
		cout << "\nPassword    : " << _PinCode;
		cout << "\nBalance     : " << _AccountBalance;
		cout << "\n___________________\n";

	}
};