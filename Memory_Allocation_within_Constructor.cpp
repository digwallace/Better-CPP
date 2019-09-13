// Compile with -std=c++11

#include<iostream>
#include<memory>    // C++11 header for smart pointer method.

class Dummy{};

class ModernMethod
{
    public:
        ModernMethod(Dummy copy); 
    private:
        // Incorrect vs. Correct manner of handling.
        Dummy incorrect;
        std::unique_ptr<Dummy> correct;
};

ModernMethod::ModernMethod(Dummy copy){
        incorrect = copy;   // Leaks memory if object fails.
        correct   = std::unique_ptr<Dummy>(new Dummy(copy));   
}

// Pre-C++11 Method using a Try-Catch.
class OldMethod
{
    public:
        OldMethod(Dummy copy);
    private:
        Dummy  old_dummy;
};

OldMethod::OldMethod(Dummy copy){
    old_dummy = copy;
    if(&old_dummy != &copy){
        throw "Failed to copy!\n";
    }
}

int main(){

    Dummy           class_to_copy;
    ModernMethod    modern_example(class_to_copy);

    try{
        OldMethod               old_example(class_to_copy);    
    }catch(const char* msg){
        std::cout << msg;
    }
    
    return 0;
}
