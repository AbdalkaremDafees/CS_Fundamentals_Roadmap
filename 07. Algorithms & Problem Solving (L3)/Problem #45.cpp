/*
            Write a program to read banck client data record
                       and convert it to one line
*/

#include <iostream>
#include <string>
using namespace std;

// Struct to organize all client data.
struct ClientData {
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
};

// Get all Data from the client (user).
ClientData GetClientData() {
    ClientData Client;

    cout << "\nEnter Account Number: ";
    getline(cin, Client.AccountNumber);

    cout << "\nEnter Pin Code: ";
    getline(cin, Client.PinCode);

    cout << "\nEnter Name: ";
    getline(cin, Client.Name);

    cout << "\nEnter Phone Number: ";
    getline(cin, Client.Phone);

    cout << "\nEnter Account Balance: ";
    cin >> Client.AccountBalance;

    return Client;
}

// Convert the client data record to one string line with seperator.
string ConvertRecordToOneLine(ClientData Client, string seperat = "/##") {
    string OneLine;
    OneLine += Client.AccountNumber + seperat;
    OneLine += Client.PinCode       + seperat;
    OneLine += Client.Name          + seperat;
    OneLine += Client.Phone         + seperat;
    OneLine += to_string(Client.AccountBalance);

    return OneLine;
}

int main() {

    cout << "Please Enter Client Data: \n";
    ClientData Client;
    Client = GetClientData();

    cout << "\n\nClient Record for Saving is: \n";
    string OneLine;
    OneLine = ConvertRecordToOneLine(Client);
    cout << OneLine;

    return 0;
}
