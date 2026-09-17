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

// Asks for an existing account number, lets the user edit its info, then saves it.
void UpdateClient()
{
	string AccountNumber = "";

	cout << "\nPlease enter client account number: ";
	AccountNumber = clsInputValidate::ReadString();

	while (!clsBankClient::IsClientExist(AccountNumber))
	{
		cout << "\nAccount number is not found, choose another one: ";
		AccountNumber = clsInputValidate::ReadString();
	}

	clsBankClient Client1 = clsBankClient::Find(AccountNumber);
	Client1.Print();

	cout << "\nUpdate client info: ";
	cout << "\n___________________\n";

	ReadClientInfo(Client1);

	clsBankClient::enSaveResults SaveResult;

	SaveResult = Client1.Save();

	switch (SaveResult)
	{
	case clsBankClient::enSaveResults::svSucceeded:
		cout << "\nAccount Updated Succeesfully :)";
		Client1.Print();
		break;
	case clsBankClient::enSaveResults::svFaildEmptyObject:
		cout << "\nError account was not saved because it's empty.";
		break;
	}
}

int main()
{
	UpdateClient();
	
	return 0;
}

