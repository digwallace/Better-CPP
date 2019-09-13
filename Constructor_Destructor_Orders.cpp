#include<iostream>

class Base{

  public:
    Base()
    { std::cout << "\t>Base Constructor called!\n"; }
    
    virtual ~Base()
    { std::cout << "\t>Base Destructor Called!\n"; }

};

class Derived : Base{
  public:
    Derived()
    { std::cout << "\t>Derived Constructor called!\n"; }

    // PRO-TIP: Always make a destructor in the derived if you have 
    //          a virtual destructor, even if it's empty.
    ~Derived()
    { std::cout << "\t>Derived Destructor called!\n"; }
};

int main(){

  std::cout << "  Create new Derived object:\n";
  Derived *constructor_order_example  = new Derived();

  std::cout << "  Delete Derived object:\n"; 
  delete constructor_order_example;

  std::cout << "  New Derived object via pointer\n";
  Derived *derived                                    = new Derived();
  
  std::cout << "**Reference from Derived assigned to a Base pointer!**\n";
  Base    *derived_deleted_via_base_pointer_example   = (Base*)derived;

  std::cout << "  Delete via Base pointer:\n";
  delete derived_deleted_via_base_pointer_example;

  return 0;
}
