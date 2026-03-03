/*
            Poject 2: Improving the project by applying the OOP inheritance principle
                        by inheriting the person class to employee class.
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

// applying the OOP inheritance principle by inheriting the person class to employee class.
class clsEmployee : public clsPerson
{

private:
    string _Title, _Department;
    float _Salary;

public:
    // Constructor: Initializes a new Employee with provided details
    clsEmployee(int ID, string FirstName, string LastName, string Email, string Phone, string Title, string Department, float Salary)
        : clsPerson(ID, FirstName, LastName, Email, Phone)
    {
        _Title = Title;
        _Department = Department;
        _Salary = Salary;
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

    // Applying function overriding
    void Print() {
        cout << "\nInfo: ";
        cout << "\n_________________________";
        cout << "\nID        : " << ID();
        cout << "\nFirstName : " << FirstName();
        cout << "\nLastName  : " << LastName();
        cout << "\nFullName  : " << FullName();
        cout << "\nEmail     : " << Email();
        cout << "\nPhone     : " << Phone();

        cout << "\nTitle     : " << _Title;
        cout << "\nDepartment: " << _Department;
        cout << "\nSalary    : " << _Salary << '$';

        cout << "\n_________________________\n";
    }
};

int main()
{
    clsEmployee Employee1(10, "EmployeeFirst", "EmployeeLast", "a@a.com", "0968686868", "AI Engineer", "IT Department", 9000);
 
    Employee1.Print();

    system("pause>0");
    return 0;
}