// Bridge is a structural design pattern that divides business logic or huge class into seprate class hierarchies that can be developed independently
#include <iostream>
using namespace std;

class Implementation {
public:
    virtual string OperationImplementation() const = 0;
};

class ConcreteImplementationA : public Implementation {
public:
    string OperationImplementation() const override {
        return "ConcreteImplementationA : Here's the result on the platform A. \n";
    }
};

class ConcreteImplementationB : public Implementation {
public:
    string OperationImplementation() const override {
        return "ConcreteImplementationB : Here's the result on the platform B. \n";
    }
};

class Abstraction {
protected:
    Implementation *implementation_;
public:
    Abstraction(Implementation* implementation) : implementation_(implementation) { }
    virtual string Operation() const {
        return "Abstraction : Base Operation with:\n" + implementation_->OperationImplementation();
    }
};

class ExtendAbstraction : public Abstraction {
public:
    ExtendAbstraction(Implementation *implementation) : Abstraction(implementation) { }
    string Operation() const override {
        return "ExtendedAbstraction : Extended operation with : \n" + implementation_->OperationImplementation();
    }
};

void clientCode(const Abstraction &abstraction) {
    cout<<abstraction.Operation();
} 

int main() {
    Implementation* implementation = new ConcreteImplementationA;
    Abstraction *abstraction = new Abstraction(implementation);
    clientCode(*abstraction);
    delete implementation;
    delete abstraction;

    implementation = new ConcreteImplementationB;
    abstraction = new ExtendAbstraction(implementation);
    clientCode(*abstraction);
    delete implementation;
    delete abstraction;

    return 0;

}