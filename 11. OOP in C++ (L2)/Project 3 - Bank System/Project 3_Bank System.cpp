#include <iostream>
#include "clsBankClient.h"
using namespace std;

// Delete client object from the 'Clients.txt' file.
void DeleteClient()
{
	string AccountNumber = "";

	cout << "\nPlease enter account number: ";
	AccountNumber = clsInputValidate::ReadString();

	while (!clsBankClient::IsClientExist(AccountNumber))
	{
		cout << "\nClient is not exist! try again: ";
		AccountNumber = clsInputValidate::ReadString();
	}

	clsBankClient Client1 = clsBankClient::Find(AccountNumber);
	Client1.Print();

	cout << "\nAre you sure you want to delete this client (y/n): ";

	char Answer = 'n';
	cin >> Answer;

	if (Answer == 'y' || Answer == 'Y')
	{
		if (Client1.Delete())
		{
			cout << "\nClient deleted successfully.\n";

			Client1.Print();
		}
		else
		{
			cout << "\nError! Client was not deleted.\n";
		}
	}
}

int main()
{	
	DeleteClient();

	return 0;
}

