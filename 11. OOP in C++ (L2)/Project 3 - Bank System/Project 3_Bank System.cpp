#include <iostream>
#include "clsBankClient.h"
using namespace std;

// Reads client fields from the user and fills the given client object.
void ReadClientInfo(clsBankClient& Client)
{
	cout << "\nEnter first name: ";
	Client.FirstName = clsInputValidate::ReadString();

	cout << "\nEnter last name: ";
	Client.LastName = clsInputValidate::ReadString();

	cout << "\nEnter email: ";
	Client.Email = clsInputValidate::ReadString();

	cout << "\nEnter phone: ";
	Client.Phone = clsInputValidate::ReadString();

	cout << "\nEnter pin code: ";
	Client.PinCode = clsInputValidate::ReadString();

	cout << "\nEnter account balance: ";
	Client.AccountBalance = clsInputValidate::ReadFloatNumber();
}

// Add new client object to the 'Clients.txt' file.
void AddNewClient()
{
	string AccountNumber = "";

	cout << "\nPlease enter account number: ";
	AccountNumber = clsInputValidate::ReadString();

	while (clsBankClient::IsClientExist(AccountNumber))
	{
		cout << "\nClient is exist! try again";
		AccountNumber = clsInputValidate::ReadString();
	}

	clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);

	ReadClientInfo(NewClient);

	clsBankClient::enSaveResults SaveResult;

	SaveResult = NewClient.Save();

	switch (SaveResult)
	{
	case clsBankClient::enSaveResults::svSucceeded:
		cout << "\nAdded Succeesfully.";
		NewClient.Print();
		break;

	case clsBankClient::enSaveResults::svFaildEmptyObject:
		cout << "\nFaild! Empty Object!";
		break;

	case clsBankClient::enSaveResults::svFaildAccountNumberExists:
		cout << "\nFaild! Account Number is exists!";
		break;
	}
}

int main()
{
	AddNewClient();
	
	return 0;
}

