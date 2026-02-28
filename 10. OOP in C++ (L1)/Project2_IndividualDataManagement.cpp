/*
            Poject 2: Individual Data and Contact Management System
                        with Communication Features
*/
#include <iostream>
using namespace std;

// Represents a person with basic contact information and communication capabilities
class clsPerson
{

private:
    int _ID;                    // Unique identifier for the person (read-only)
    string _FirstName, _LastName, _Email, _Phone;

public:
    // Constructor: Initializes a new person with provided details
    clsPerson(int ID, string FirstName, string LastName, string Email, string Phone)
    {
        _ID = ID;
        _FirstName = FirstName;
        _LastName = LastName;
        _Email = Email;
        _Phone = Phone;
    }

    // ID property - read-only (no setter provided)
    int ID() {
        return _ID;
    }

    // FirstName property with getter and setter
    void setFirstName(string FirstName)
    {
        _FirstName = FirstName;
    }
    string FirstName()
    {
        return _FirstName;
    }

    // LastName property with getter and setter
    void setLastName(string LastName)
    {
        _LastName = LastName;
    }
    string LastName()
    {
        return _LastName;
    }

    // Email property with getter and setter
    void setEmail(string Email)
    {
        _Email = Email;
    }
    string Email()
    {
        return _Email;
    }

    // Phone property with getter and setter
    void setPhone(string Phone)
    {
        _Phone = Phone;
    }
    string Phone()
    {
        return _Phone;
    }

    // Returns the person's full name by combining first and last name
    string FullName()
    {
        return _FirstName + ' ' + _LastName;
    }

    // Simulates sending an email to the person
    void SendEmail(string Subject, string Body)
    {
        cout << "\nThe following message sent successfully to email: " << _Email;
        cout << "\nSubject: " << Subject;
        cout << "\nBody: " << Body;
    }

    // Simulates sending an SMS to the person's phone
    void SendSMS(string Message)
    {
        cout << "\n\nThe following SMS sent successfully to Phone: " << _Phone;
        cout << '\n' << Message;
    }

    // Displays all person information in a formatted output
    void Print()
    {
        cout << "\nInfo: ";
        cout << "\n_________________________";
        cout << "\nID        :" << _ID;
        cout << "\nFirstName :" << _FirstName;
        cout << "\nLastName  :" << _LastName;
        cout << "\nFullName  :" << FullName();
        cout << "\nEmail     :" << _Email;
        cout << "\nPhone     :" << _Phone;
        cout << "\n_________________________\n";
    }
};

int main()
{
    // Create and test a Person object with sample data
    clsPerson Person1(10, "PersonFirst", "PersonLast", "my@gmail.com", "00966886688");
    Person1.Print();

    // Test communication methods
    Person1.SendEmail("Hi", "How are you?");
    Person1.SendSMS("How are you?");

    system("pause>0");
    return 0;
}