/*
    Project 3: adding nested classes concept to
    manage basic and detailed laptop specifications
    This program demonstrates nested classes and friend classes
    for laptop information with discount calculation
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
    friend class clsDiscount;
};

// Extends basic info with detailed specifications (weight, warranty, color)
class clsLaptopSpecifications : public clsLaptopStandardInfo
{
private:
    float  _LaptopWeight;
    int    _LaptopWarranty;
    string _LaptopColor;
    float  _DiscountAmount;

public:
    // Nested class for discount functionality
    // This class is defined inside clsLaptopSpecifications to show nested class concept
    class clsDiscount
    {
    private:
        float _DiscountAmount;
        float _LaptopPrice;
        float _Result;

    public:
        clsDiscount(float LaptopPrice, float DiscountAmount = 0)
        {
            _LaptopPrice = LaptopPrice;
            _DiscountAmount = DiscountAmount;
            _Result = _LaptopPrice - _DiscountAmount;
        }

        // Displays the discounted price
        void PrintDiscount()
        {
            cout << "\n\nThe price after discount " << _DiscountAmount << '$'
                 << " is: " << _Result << '$';
        }
    };

    // Nested class object as member
    clsDiscount Discount;

    clsLaptopSpecifications(string LaptopName, string LaptopCode, float LaptopPrice,
        float LaptopWeight, int LaptopWarranty, string LaptopColor, float DiscountAmount = 0)
        : clsLaptopStandardInfo(LaptopName, LaptopCode, LaptopPrice), 
          Discount(LaptopPrice, DiscountAmount)  // Initialize nested object in member initializer list
    {
        _LaptopWeight = LaptopWeight;
        _LaptopWarranty = LaptopWarranty;
        _LaptopColor = LaptopColor;
        _DiscountAmount = DiscountAmount;
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
    // Create and display a sample laptop with discount
    clsLaptopSpecifications Laptop1("Lenovo ThinkPad", "T560", 850.5, 1.8, 2, "Gray", 45.5);
    Laptop1.Print();
    
    // Access nested class method through the outer class object
    Laptop1.Discount.PrintDiscount();

    cout << "\n\n";

    // Create another laptop with different specifications
    clsLaptopSpecifications Laptop2("Dell XPS", "XPS13", 1200.0, 1.2, 3, "Silver", 100.0);
    Laptop2.Print();
    Laptop2.Discount.PrintDiscount();

    return 0;
}