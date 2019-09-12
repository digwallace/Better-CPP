// Compile with -std=c++11

#include<iostream>
#include<memory>    // C++11 header for smart pointer method.

class DummyClass{};

class ConstructorAllocatingClass{
    public:
        ConstructorAllocatingClass(DummyClass copy); 
    private:
        // Incorrect vs. Correct manner of handling.
        DummyClass incorrect;
        std::unique_ptr<DummyClass> correct;
};

ConstructorAllocatingClass::ConstructorAllocatingClass(DummyClass copy){
        incorrect = copy;                   // Leaks memory if object fails.
        correct   = std::unique_ptr<DummyClass>(new DummyClass(copy));   // Deletes object when out of scope.
}

// Pre-C++11 Method using a Try-Catch.
class OldMethodClass{
    public:
        OldMethodClass(DummyClass copy);
    private:
        DummyClass  old_method_object;
};

OldMethodClass::OldMethodClass(DummyClass copy){
    old_method_object = copy;
    if(&old_method_object != &copy){
        throw "Failed to copy!\n";
    }
}

int main(){

    DummyClass                  class_to_copy;
    ConstructorAllocatingClass  example(class_to_copy);

    try{
        OldMethodClass              old_example(class_to_copy);    
    }catch(const char* msg){
        std::cout << msg;
    }
    
    return 0;
}
