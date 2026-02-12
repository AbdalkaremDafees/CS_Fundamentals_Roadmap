/*
              Problem #48: write a program to read clients file
                    and show them on the screen as follow.
*/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

struct ClientsData {
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
};

// Split words and add them to vector.
vector<string> SplitWords(string S, string delmi = "/##") {
    int pos = 0;
    string sWord = "";
    vector<string> vString;

    while ((pos = S.find(delmi)) != std::string::npos) {
        sWord = S.substr(0, pos);
        if (sWord != "") vString.push_back(sWord);
        S.erase(0, pos + delmi.length());
    }

    if (S != "") vString.push_back(S);
    return vString;
}

// Convert string line to record.
ClientsData ConvertLineToRecord(string S) {
    vector<string> vClient;
    vClient = SplitWords(S);

    ClientsData stClient;
    stClient.AccountNumber = vClient[0];
    stClient.PinCode = vClient[1];
    stClient.Name = vClient[2];
    stClient.Phone = vClient[3];
    to_string(stClient.AccountBalance) = (vClient[4]);
    return stClient;
}

// Get Data from external file and save them in vector.
vector<ClientsData> GetLineFromFile(string FileName) {
    vector<ClientsData> vClients;

    fstream myFile;
    myFile.open(FileName, ios::in);

    if (myFile.is_open()) {

        string Line;
        ClientsData stClient;
        while (getline(myFile, Line)) {
            stClient = ConvertLineToRecord(Line);
            vClients.push_back(stClient);
        }

        myFile.close();
    }
    return vClients;
}

// Print Client Record.
void PrintClientRecord(ClientsData Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

// Print all client data.
void PrintAllClientsData(vector<ClientsData> vClients)
{
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
        cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (ClientsData Client : vClients) {
        PrintClientRecord(Client);
        cout << endl;
    }
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

int main()
{
    vector<ClientsData> vClients = GetLineFromFile("myFile.txt");
    PrintAllClientsData(vClients);
    return 0;
}
