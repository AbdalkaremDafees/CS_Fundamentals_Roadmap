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
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;

	static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
	{
		vector<string> vClientData;
		vClientData = clsString::Split(Line, Seperator);

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
			vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	// Loads all clients from the hardcoded "Clients.txt" file into a vector.
	static vector<clsBankClient> _LoadClientsFromFile()
	{
		vector<clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLinetoClientObject(Line);
				vClients.push_back(Client);
			}

			MyFile.close();
		}

		return vClients;
	}

	// Converts a client object into a single delimited line for file storage.
	static string _ConvertClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
	{
		string stClientRecord = "";

		stClientRecord += Client.FirstName + Seperator;
		stClientRecord += Client.LastName + Seperator;
		stClientRecord += Client.Email + Seperator;
		stClientRecord += Client.Phone + Seperator;
		stClientRecord += Client.AccountNumber() + Seperator;
		stClientRecord += Client.PinCode + Seperator;
		stClientRecord += to_string(Client.AccountBalance);

		return stClientRecord;
	}

	// Overwrites "Clients.txt" with the given vector of clients.
	static void _SaveClientsDataToFile(vector<clsBankClient> vClients)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);

		string DataLine;

		if (MyFile.is_open())
		{
			for (clsBankClient& C : vClients)
			{
				DataLine = _ConvertClientObjectToLine(C);
				MyFile << DataLine << endl;
			}

			MyFile.close();
		}
	}

	// Add new client to the file.
	void _AddNewClientToFile(string stDataLine)
	{
		fstream MyFile;
		MyFile.open("Client.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;

			MyFile.close();
		}
	}

	// Updates the current client's record in the file.
	void _Update()
	{
		vector<clsBankClient> _vClients;
		_vClients = _LoadClientsFromFile();

		for (clsBankClient& C : _vClients)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		}

		_SaveClientsDataToFile(_vClients);
	}

	// Add new client information to the file
	void _AddNew()
	{
		_AddNewClientToFile(_ConvertClientObjectToLine(*this));
	}

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

	static clsBankClient Find(string AccountNumber)
	{
		vector <clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLinetoClientObject(Line);
				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}

				MyFile.close();
			}

			return _GetEmptyClientObject();
		}
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		vector <clsBankClient> vClients;

		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLinetoClientObject(Line);
				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
				{
					MyFile.close();
					return Client;
				}

				MyFile.close();
			}

			return _GetEmptyClientObject();
		}
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };

	// Saves the current client depending on the object's mode.
	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
			return enSaveResults::svFaildEmptyObject;

		case enMode::UpdateMode:

			_Update();

			return enSaveResults::svSucceeded;
			break;
		}
		case enMode::AddNewMode:
			if (clsBankClient::IsClientExist(_AccountNumber))
			{
				return enSaveResults::svFaildAccountNumberExists;
			}
			else
			{
				_AddNew();

				return enSaveResults::svSucceeded;
			}
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client = clsBankClient::Find(AccountNumber);

		return (!Client.IsEmpty());
	}

	// Generate Object for adding new client.
	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}
};