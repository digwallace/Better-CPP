#include<memory>    // Used for unique_ptr.

class DummyClass{};

// Note: Must be compiled using a c++11 compiler.
//       (i.e. You may need to use the -std=c++11 flag.)
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
        correct  = std::unique_ptr<DummyClass>(new DummyClass(copy));   // Deletes object when out of scope.
}

// ************************ OLD METHOD *****************************
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
        throw "Failed to copy!";
    }

}

// ********************* END OF OLD METHOD *************************

int main(){

    DummyClass                 class_to_copy;
    ConstructorAllocatingClass example(class_to_copy);

    // Old Method.
    try{
        OldMethodClass              old_example(class_to_copy);    
    }catch(const char* msg){

    }  // End of Old Method.

    return 0;
}
