// Prototype is a creational design pattern that allows you copy existing objects without making your code dependent on their classes.
#include <iostream>
#include <unordered_map>
using namespace std;

enum Type {
    PROTOTYPE_1 = 0,
    PROTOTYPE_2 = 1,
    PROTOTYPE_3,
    PROTOTYPE_4
};

class Prototype {
protected:
    string name_;
    float field_;
public:
    Prototype(string name ,float field) : name_(name) , field_(field){}
    virtual Prototype *Clone() const = 0;
    virtual void Method(float field){
        this->field_ = field;
        cout<<"Call Method from "<<name_<<" with field :"<<field_<<endl;
    }
};

class ConcretePrototype1 : public Prototype {
private:
    //float concrete_prototype_field1_;
public:
    ConcretePrototype1(string name,float concrete_prototype_field1) : Prototype(name,concrete_prototype_field1){}
    Prototype *Clone() const override {
        return new ConcretePrototype1(*this);
    }
};

class ConcretePrototype2 : public Prototype {
    private:
        float concrete_prototype_field2_;
    public:
        ConcretePrototype2(string name,float concrete_prototype_field2) : Prototype(name,concrete_prototype_field2) {}
        Prototype *Clone() const override {
            return new ConcretePrototype2(*this);
        }
};

class PrototypeFactory {
private:
    std::unordered_map<int, Prototype*> prototypes_;
public:
    PrototypeFactory() {
        prototypes_[Type::PROTOTYPE_1] = new ConcretePrototype1("Prototype_1" ,50.0);
        prototypes_[Type::PROTOTYPE_2] = new ConcretePrototype2("Prototype_2",60.0);
        prototypes_[Type::PROTOTYPE_3] = new ConcretePrototype1("Prototype_3" ,50.0);
        prototypes_[Type::PROTOTYPE_4] = new ConcretePrototype2("Prototype_4",60.0);
    }

    ~PrototypeFactory()
    {
        delete prototypes_[Type::PROTOTYPE_1];
        delete prototypes_[Type::PROTOTYPE_2];
        delete prototypes_[Type::PROTOTYPE_3];
        delete prototypes_[Type::PROTOTYPE_4];
    }

    Prototype *CreatePrototype(Type type) {
        return prototypes_[type]->Clone();
    }
};
void Client(PrototypeFactory &prototype_factory)
{
    Prototype *prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_1);
    prototype->Method(0.0);
    delete prototype;

    cout<<endl;

    prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_2);
    prototype->Method(10.0);
    delete prototype;

    cout<<endl;

    prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_3);
    prototype->Method(20.0);
    delete prototype;

    cout<<endl;

    prototype = prototype_factory.CreatePrototype(Type::PROTOTYPE_4);
    prototype->Method(30.0);
    delete prototype;
}

int main() {
    PrototypeFactory *prototype_factory = new PrototypeFactory();
    Client(*prototype_factory);
    delete prototype_factory;

    return 0;
}