/*
            Problem #47: write a progrma to ask you to enter clients 
                    and save them to file using fstream
*/

#include <iostream>
#include <string>
#include <fstream>
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
    getline(cin >> ws, Client.AccountNumber);

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
    OneLine += Client.PinCode + seperat;
    OneLine += Client.Name + seperat;
    OneLine += Client.Phone + seperat;
    OneLine += to_string(Client.AccountBalance);

    return OneLine;
}

// Save the data string line to external file (.txt)
void SaveDataToFile(string FileName, string DataToAdd) {
    fstream myFile;
    myFile.open(FileName, ios::out | ios::app);
    if (myFile.is_open()) {
        myFile << DataToAdd << endl;
        myFile.close();
    }
}

// Get new client data and save them to file
void AddNewClient() {
    cout << "Please Enter Client Data: \n";
    ClientData Client;
    Client = GetClientData();

    cout << "\n\nClient Record for Saving is: \n";
    string OneLine;
    OneLine = ConvertRecordToOneLine(Client);
    
    SaveDataToFile("MyFile.txt", OneLine);
}

// Ask user to add more clients
void addClients() {
    char choice = 'Y';
    do {
        system("cls");
        AddNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients ? Y / N ? ";
        cin >> choice;
    } while (toupper(choice) == 'Y');
}

int main() {

    addClients();

    return 0;
}
