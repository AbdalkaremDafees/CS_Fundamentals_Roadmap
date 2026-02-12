/*
         Problem #46: Write a program to convert one string line data
                           to record and print it.
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct ClientData {
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
};

// Dividing the text into parts and place them in a vector
vector<string> SplitWords(string S, string delmi = "/##") {
    int pos = 0; 
    string sWord;
    vector<string> vString;

    while ((pos = S.find(delmi)) != std::string::npos) {
        sWord = S.substr(0, pos);
        if (sWord != "") vString.push_back(sWord);
        S.erase(0, pos + delmi.length());
    }

    if (S != "") vString.push_back(S);      // for last elemnt.
    return vString;
}

// Converting parts of string into their specific place in the struct.
ClientData ConvertLineToRecord(string S) {
    ClientData Client;
    vector<string> vClientData;

    vClientData = SplitWords(S);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);//cast string to double

    return Client;
}

// Print client data recorf
void printRecord(ClientData Client) {
    cout << "\nAccount Number: " << Client.AccountNumber;
    cout << "\nAccount Number: " << Client.PinCode;
    cout << "\nAccount Number: " << Client.Name;
    cout << "\nAccount Number: " << Client.Phone;
    cout << "\nAccount Number: " << Client.AccountBalance;
}

int main() {
    cout << "Line Record Is:";
    string S = "A150/##1234/##User Name/##056123456/##500.80";
    cout << '\n' << S;

    ClientData Client;
    Client = ConvertLineToRecord(S);

    cout << "\n\nThe Followin Is The Extracted Client Record: \n";
    printRecord(Client);

    return 0;
}