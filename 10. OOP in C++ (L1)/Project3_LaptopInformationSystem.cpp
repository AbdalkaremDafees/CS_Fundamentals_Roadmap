/*
            Project 3: simple laptop information system using
                        abstract interface concept    
*/
#include <iostream>
using namespace std;

// Abstract interface defining essential laptop properties
class clsLaptops
{
    virtual string LaptopName() = 0;
    virtual string LaptopCode() = 0;
    virtual float  LaptopPrice() = 0;
};

// Handles basic laptop information (name, code, price)
class clsLaptopStandardInfo
{
private:
    string _LaptopName;
    string _LaptopCode;
    float  _LaptopPrice;

public:
    clsLaptopStandardInfo(string LaptopName, string LaptopCode, float LaptopPrice)
    {
        _LaptopName = LaptopName;
        _LaptopCode = LaptopCode;
        _LaptopPrice = LaptopPrice;
    }

    string LaptopName()
    {
        return _LaptopName;
    }

    string LaptopCode()
    {
        return _LaptopCode;
    }

    float LaptopPrice()
    {
        return _LaptopPrice;
    }

};

int main()
{
    // Create and display a sample laptop
    clsLaptopStandardInfo Laptop1("Lenovo ThinkPad", "T560", 850.5);
    cout << "\nLaptop Name:  " << Laptop1.LaptopName();
    cout << "\nLaptop Code:  " << Laptop1.LaptopCode();
    cout << "\nLaptop Price: " << Laptop1.LaptopPrice() << '$';

    return 0;
}