#include<iostream>
using namespace std;

// The Product interface declares the operations that all concrete products must implement.
class Product {
    public:
        virtual ~Product() {}
        virtual string Operation() const = 0;
};

class ConcreteProductA : public Product {
    public:
        string Operation() const override {
            return "Result of ConcreteProductA";
        }
};

class ConcreteProductB : public Product {
    public:
        string Operation() const override {
            return "Result of ConcreteProductB";
        }
};

// Creator has-a relationship with Product
class Creator {
    public :
        virtual ~Creator() {}
        virtual Product* FactoryMethod() const = 0;
        string SomeOperation() const {
            Product* product = this->FactoryMethod();
            string result = "Creator: The same creator's code has just worked with " + product->Operation();
            delete product;
            return result;
        }
};

class ConcreteCreatorA : public Creator {
    public:
        Product* FactoryMethod() const override {
            return new ConcreteProductA;
        }
};

class ConcreteCreatorB : public Creator {
    public:
        Product* FactoryMethod() const override {
            return new ConcreteProductB;
        }
};


void clientCode(Creator& creator){
    std::cout << "Client: I'm not aware of the creator's class, but it still works.\n"
            << creator.SomeOperation() << std::endl;
}


int main()
{
    cout<<"App launched with ConcreteCreatorA\n";
    Creator* creator1 = new ConcreteCreatorA;
    clientCode(*creator1);
    delete creator1;

    cout<<"App launched with ConcreteCreatorB\n";
    Creator* creator2 = new ConcreteCreatorB;
    clientCode(*creator2);
    delete creator2;

    return 0;
}
