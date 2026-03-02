/*
            Poject 2: Employee Data and Contact Management System
                        with Communication Features
*/
#include <iostream>
using namespace std;

// Represents an employee with basic contact information and communication capabilities
class clsEmployee
{

private:
    int _ID;                    // Unique identifier for the person (read-only)
    string _FirstName, _LastName, _Title, _Email, _Phone, _Department;
    float _Salary;

public:
    // Constructor: Initializes a new person with provided details
    clsEmployee(int ID, string FirstName, string LastName, string Title, string Email, string Phone, float Salary, string Department)
    {
        _ID = ID;
        _FirstName = FirstName;
        _LastName = LastName;
        _Title = Title;
        _Email = Email;
        _Phone = Phone;
        _Salary = Salary;
        _Department = Department;
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

    // Title property with getter and setter
    void setTitle(string Title)
    {
        _Title = Title;
    }
    string Title()
    {
        return _Title;
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

    // Salary property with getter and setter
    void setSalary(float Salary)
    {
        _Salary = Salary;
    }
    float Salary()
    {
        return _Salary;
    }

    // Department property with getter and setter
    void setDepartment(string Department)
    {
        _Department = Department;
    }
    string Department()
    {
        return _Department;
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
        cout << "\nID        : " << _ID;
        cout << "\nFirstName : " << _FirstName;
        cout << "\nLastName  : " << _LastName;
        cout << "\nFullName  : " << FullName();
        cout << "\nTitle     : " << _Title;
        cout << "\nEmail     : " << _Email;
        cout << "\nPhone     : " << _Phone;
        cout << "\nSalary    : " << _Salary << '$';
        cout << "\nDepartment: " << _Department;
        cout << "\n_________________________\n";
    }
};

int main()
{
    // Create and test a Employee object with sample data
    clsEmployee Employee1(10, "EmployeeFirst", "EmployeeLast", "AI Engineer", "my@gmail.com", "00966886688", 9000, "IT Department");
    Employee1.Print();

    // Test communication methods
    Employee1.SendEmail("Hi", "How are you?");
    Employee1.SendSMS("How are you?");

    system("pause>0");
    return 0;
}