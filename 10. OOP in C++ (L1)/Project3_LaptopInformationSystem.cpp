/*
            Project 3: adding friend classes concept to
          manage basic and detailed laptop specifications    
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

    // Allows clsLaptopSpecifications to access private members
    friend class clsLaptopSpecifications;
};

// Extends basic info with detailed specifications (weight, warranty, color)
class clsLaptopSpecifications : public clsLaptopStandardInfo
{
private:
    float  _LaptopWeight;
    int _LaptopWarranty;
    string _LaptopColor;

public:
    clsLaptopSpecifications(string LaptopName, string LaptopCode, float LaptopPrice,
        float LaptopWeight, int LaptopWarranty, string LaptopColor)
        : clsLaptopStandardInfo(LaptopName, LaptopCode, LaptopPrice)
    {
        _LaptopWeight = LaptopWeight;
        _LaptopWarranty = LaptopWarranty;
        _LaptopColor = LaptopColor;
    }

    // Displays complete laptop information including all specifications
    void Print()
    {
        cout << "========Laptop Standard Info========";
        cout << "\nLaptop Name : " << _LaptopName;
        cout << "\nLaptop Code : " << _LaptopCode;
        cout << "\nLaptop Price: " << _LaptopPrice << '$';
        cout << "\n\n========Laptop Specifications========";
        cout << "\nLaptop Weight  : " << _LaptopWeight << " Kg";
        cout << "\nLaptop Warranty: " << _LaptopWarranty << " Years";
        cout << "\nLaptop Color   : " << _LaptopColor;
    }
};

int main()
{
    // Create and display a sample laptop
    clsLaptopSpecifications Laptop1("Lenovo ThinkPad", "T560", 850.5, 1.8, 2, "Gray");
    Laptop1.Print();

    return 0;
}