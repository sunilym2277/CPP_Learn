# 100 OOPs Interview Questions in C++
## 1. Basics of OOP

### 1.1 What is Object-Oriented Programming (OOP)?
Definition:
Object-Oriented Programming (OOP) is a programming paradigm based on the concept of objects.
Objects combine data (attributes) and functions (methods) that operate on that data.
It focuses on modeling real-world entities into software components.

Key features of OOP:
- Encapsulation – Bundling data and functions together inside a class.
- Abstraction – Hiding unnecessary details and showing only essential features.
- Inheritance – Deriving new classes from existing ones to promote code reuse.
- Polymorphism – The ability of the same function to behave differently in different contexts.




### 1.2 What are the main features of OOP?

### 1.3 Explain the difference between procedural programming and OOP.
| Aspect                 | **Procedural Programming**                                                           | **Object-Oriented Programming (OOP)**                                             |
| ---------------------- | ------------------------------------------------------------------------------------ | --------------------------------------------------------------------------------- |
| **Definition**         | Program is structured as a sequence of **functions** (procedures) operating on data. | Program is structured around **objects** that encapsulate both data and behavior. |
| **Focus**              | Focuses on **functions and procedures**.                                             | Focuses on **classes and objects**.                                               |
| **Data Handling**      | Data is **separate from functions** and can be passed around freely.                 | Data is **encapsulated within objects**; only methods can modify it.              |
| **Reusability**        | Code reuse via **functions**.                                                        | Code reuse via **inheritance and polymorphism**.                                  |
| **Security**           | Less secure since data is often **globally accessible**.                             | More secure due to **data hiding and encapsulation**.                             |
| **Real-world Mapping** | Harder to model real-world entities directly.                                        | Maps directly to real-world entities (Car, Employee, BankAccount).                |
| **Examples**           | C, Pascal.                                                                           | C++, Java, Python (OOP part).                                                     |


### 1.4 What is an object in C++?
An object in C++ is an instance of a class that contains both data and methods.
### 1.5 What is a class in C++?
A class in C++ is a user-defined data type that acts as a blueprint or template for creating objects.

- It defines the attributes (data members) and behaviors (member functions) of objects.
- A class itself does not occupy memory (except for static members), but its objects do.
### 1.6 Difference between class and object?

### 1.7 Can we create an object without a class?
Yes, but with conditions:
- You can create objects from structs (since a struct is like a class with default public access).
- You can create objects of built-in types (int x;, double y;) — these are objects but not class-based.
- You can use anonymous classes/structs (not common, but possible in C++).
- You can use union (objects of union type).

### 1.8 What is encapsulation?
Definition:
Encapsulation in C++ is the concept of wrapping data (variables) and functions (methods) into a single unit (class), and restricting direct access to the internal details of that unit.

It ensures that an object’s internal state is hidden from the outside world and can only be accessed through well-defined methods.

Key Points
- Achieved using classes in C++.
- Uses access specifiers: private, protected, public.
- Provides data hiding → prevents unauthorized access.
- Allows changes to internal implementation without affecting external code.
- Makes the code modular, maintainable, and secure.

### 1.9 How does encapsulation help in real-world applications?

### 1.10 What is abstraction?
Definition:
Abstraction in C++ is the process of hiding implementation details and exposing only the essential features of an object.
- It focuses on what an object does, not how it does it.
- The goal is to reduce complexity and increase ease of use.

Key Points

1. Achieved in C++ using:
    - Abstract classes (classes with pure virtual functions).
    - Interfaces (not a keyword in C++, but can be simulated using abstract classes with only pure virtual functions).
    - Access specifiers (public vs private also provide some level of abstraction).

2. Hides unnecessary details from the user.
3. Provides a clear separation between interface (what to do) and implementation (how to do it).
4. Helps in designing scalable and maintainable systems.

### 1.11 What is the difference between encapsulation and abstraction?
| Aspect                   | **Encapsulation**                                                                                   | **Abstraction**                                                                                    |
| ------------------------ | --------------------------------------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------- |
| **Definition**           | Encapsulation is **wrapping data and methods** that operate on the data into a single unit (class). | Abstraction is **hiding implementation details** and exposing only the essential features.         |
| **Focus**                | Focuses on **how data is hidden & controlled**.                                                     | Focuses on **what functionality is exposed**.                                                      |
| **Achieved by**          | Achieved using **classes, access specifiers (private, public, protected)**.                         | Achieved using **abstract classes, interfaces, and pure virtual functions**.                       |
| **Access Control**       | Controls access to data members (e.g., private variables can only be modified via public methods).  | Hides the implementation logic (the “how”) and only shows the required functionality (the “what”). |
| **Example in real life** | A **capsule medicine**: all ingredients are packed inside.                                          | A **car driver only sees steering & pedals**, not engine mechanics.                                |

### 1.12 Give an example of abstraction in C++.

### 1.13 What is inheritance?
Definition:
Inheritance in C++ is the mechanism by which one class (derived/child class) can acquire properties and behaviors (data members and member functions) of another class (base/parent class).

It allows code reuse, supports hierarchical classification, and enables polymorphism.

Key Points
- Promotes reusability – write once, use in multiple classes.
- Provides IS-A relationship between classes.

Access specifiers in inheritance:
- public → keeps base’s public/protected as public/protected
- protected → base’s public/protected become protected
- private → base’s public/protected become private

### 1.14 Types of inheritance in C++?

### 1.15 Explain multiple inheritance in C++.
Multiple Inheritance is when a class is derived from two or more base classes.

It allows the derived class to inherit features (data + methods) from multiple parent classes.

### 1.16 What is polymorphism?
Polymorphism means "many forms".
In C++, it allows the same function name or operator to behave differently based on the context

### 1.17 Difference between compile-time and runtime polymorphism?
1. Compile-time (Static) Polymorphism
    - Achieved by function overloading and operator overloading.
    - Resolved by the compiler at compile time.
2. Runtime (Dynamic) Polymorphism
    - Achieved by function overriding using virtual functions.
    - Resolved at runtime using vtable & vptr mechanism.

### 1.18 Example of function overloading in C++?
```cpp
#include <iostream>
using namespace std;

class Print {
public:
    void show(int x) { cout << "Integer: " << x << endl; }
    void show(double y) { cout << "Double: " << y << endl; }
};

int main() {
    Print p;
    p.show(10);      // Integer
    p.show(3.14);    // Double
}
```

### 1.19 Example of operator overloading in C++?

```cpp
class Complex {
    public: int real , img;
    Complex(int r ,int  i) : real(r) ,img(i) {}
    Complex operator+ ( Complex &obj) {
        cout<<"real : "<<real<<" img : "<<img<<endl;
        return Complex(real + obj.real , img + obj.img);
    }
};

int main() {
   Complex C1(5,6);
   Complex C2(1,1);
   Complex C3 = C1 + C2; // here this acts as C1 and obj as C2
   cout << "Sum: " << C3.real << " + " << C3.img << "i" << endl;
    return 0;
}
```

### 1.20 What is function overriding?
Function overriding in C++ happens when a derived class provides a new implementation of a function that already exists in its base class (with the same signature).
It is a key feature of runtime polymorphism.

Conditions for Function Overriding:
- The base class function must be virtual (for runtime polymorphism).
- Function name, parameters, and return type must match exactly.
- It occurs in inheritance only.
- Access specifier can change (but visibility rules apply).
```cpp
#include <iostream>
using namespace std;

class Base {
public:
    virtual void display() { cout << "Base class\n"; }
};

class Derived : public Base {
public:
    void display() override { cout << "Derived class\n"; }
};

int main() {
    Base* ptr;
    Derived d;
    ptr = &d;
    ptr->display();   // Calls Derived’s version at runtime
}
```
### 1.21 What is dynamic dispatch?

### 1.22 What is a constructor?
A constructor is a special member function in C++ that is automatically called when an object is created.
Its main job is to initialize the object’s data members.

Key Points:
- Same name as the class.
- Has no return type (not even void).
- Can be overloaded (different constructors with different parameters).
- Can be default, parameterized, or copy constructor.
- If you don’t define any constructor, the compiler provides a default constructor.


### 1.23 Types of constructors in C++?
1. Default Constructor
    - Takes no parameters.
    - Initializes object members with default values.
    - If you don’t write any constructor, C++ provides an implicit default constructor.
2. Parameterized Constructor
    - Takes arguments to initialize objects with custom values.
3. Copy Constructor
    - Creates a new object as a copy of an existing object.
    - Syntax:
    ```cpp
    ClassName(const ClassName &obj);
    ```
    - By default, if you don’t define one, C++ provides a default copy constructor that performs a shallow copy.
    - If you need deep copy, you must write your own copy constructor.
4. Move Constructor (C++11 onwards)
    - Moves resources from one object to another (instead of copying).
    - Useful for performance optimization when working with temporary objects.
5. Shallow Copy in Constructor
```cpp
class Shallow {
public:
    int* data; 
    Shallow(int val) { data = new int(val); }
    // Default copy constructor → just copies pointer (not value)
};
int main()
{
  Shallow s1(10);
  Shallow s2 = s1;    
  cout<<s2.data<<endl;
  cout<<s1.data<<endl;
}
// Output -> 
// 0x5a57c6a6c2b0
// 0x5a57c6a6c2b0
```
6. Deep Copy in Constructor
```cpp
#include <iostream>
using namespace std;

class Deep {
public:
    int* data;
    // Normal constructor
    Deep(int val) {
        data = new int(val);
    }
    // Deep Copy Constructor
    Deep(const Deep& obj) {
        // allocate new memory and copy the actual value
        data = new int(*obj.data);
        cout << "Deep copy constructor called!" << endl;
    }
    // Destructor
    ~Deep() {
        delete data;
        cout << "Destructor freeing memory!" << endl;
    }
};

int main() {
    Deep d1(10);
    Deep d2 = d1;   // invokes deep copy constructor

    cout << "Address in d1: " << d1.data << " Value: " << *d1.data << endl;
    cout << "Address in d2: " << d2.data << " Value: " << *d2.data << endl;

    *d2.data = 50;  // modify d2’s value

    cout << "After modifying d2:" << endl;
    cout << "d1 Value: " << *d1.data << endl; // still 10
    cout << "d2 Value: " << *d2.data << endl; // 50
}
```
### 1.24 What is a destructor?
A destructor is a special member function of a class that is automatically invoked when an object goes out of scope or is explicitly deleted.
Its purpose is to release resources (like memory, file handles, sockets, etc.) that the object acquired during its lifetime.

### 1.25 Can constructors be virtual in C++?
No, constructors cannot be virtual in C++.
## 2. Constructors & Destructors

### 2.1 Difference between copy constructor and assignment operator?
| Feature                  | Copy Constructor                                              | Assignment Operator                                                |
| ------------------------ | ------------------------------------------------------------- | ------------------------------------------------------------------ |
| **Purpose**              | Initializes a new object as a copy of another                 | Assigns values from one existing object to another existing object |
| **Called when**          | A new object is created from an existing object               | Both objects already exist                                         |
| **Syntax**               | `ClassName(const ClassName &obj);`                            | `obj1 = obj2;`                                                     |
| **Example**              | `ClassB b = a;`                                               | `b = a;`                                                           |
| **Default behavior**     | Member-wise shallow copy                                      | Member-wise shallow copy                                           |
| **Can be overloaded**    | Yes                                                           | Yes                                                                |
| **Memory allocation**    | Usually involves creating new memory if deep copy implemented | Uses existing memory                                               |
| **Called automatically** | When object is declared/initialized from another object       | When `=` operator is used between objects                          |
```cpp
#include <iostream>
using namespace std;

class Demo {
public:
    int* data;

    // Constructor
    Demo(int val) { data = new int(val); }

    // Copy Constructor (deep copy)
    Demo(const Demo &obj) {
        data = new int(*obj.data);
        cout << "Copy constructor called" << endl;
    }

    // Assignment Operator (deep copy)
    Demo& operator=(const Demo &obj) {
        if (this != &obj) {          // self-assignment check
            delete data;             // free old memory
            data = new int(*obj.data);
            cout << "Assignment operator called" << endl;
        }
        return *this;
    }

    ~Demo() { delete data; }
};

int main() {
    Demo a(10);            // Constructor
    Demo b = a;            // Copy constructor
    Demo c(20);
    c = a;                 // Assignment operator
}
```

### 2.2 When is a copy constructor called?
1. When an object is initialized from another object
```cpp
Demo a(10);
Demo b = a;   // Copy constructor called
```
2. When an object is passed by value to a function
```cpp
void func(Demo d) { }

Demo a(10);
func(a);     // Copy constructor called
```
3. When an object is returned by value from a function
```cpp
Demo func() {
    Demo temp(20);
    return temp;  // Copy constructor called
}

Demo b = func();
```
4. When the compiler generates a temporary object
```cpp
Demo b = Demo(10);   // Copy constructor may be called
```

### 2.3 What is a move constructor in C++11?
A move constructor is a special constructor that transfers resources from a temporary (rvalue) object to a new object instead of copying them.

This improves performance by avoiding unnecessary deep copies.

Introduced in C++11.
```cpp
#include <iostream>
using namespace std;

class Demo {
public:
    int* data;

    // Normal constructor
    Demo(int val) { 
        data = new int(val); 
        cout << "Constructor called\n"; 
    }

    // Move constructor
    Demo(Demo&& obj) noexcept {
        data = obj.data;   // steal the resource
        obj.data = nullptr; // leave source in safe state
        cout << "Move constructor called\n";
    }

    ~Demo() { 
        delete data; 
        cout << "Destructor called\n"; 
    }
};

int main() {
    Demo d1(10);           // Constructor
    Demo d2 = std::move(d1); // Move constructor called

    cout << "d1.data = " << d1.data << endl; // nullptr
    cout << "d2.data = " << *d2.data << endl; // 10
}
```

### 2.4 Difference between shallow copy and deep copy?

### 2.5 Can destructor be overloaded?
No, destructors cannot be overloaded in C++.
1. Destructor has a fixed signature:
- Name = ~ClassName
- Takes no arguments
- Returns nothing

2. Automatic invocation by compiler:
- Destructor is called automatically when an object goes out of scope.
- If you had multiple destructors (overloading), the compiler wouldn’t know which one to call automatically.

3. No arguments allowed
- Overloading requires different parameter lists, which destructors cannot have.
### 2.6 Order of constructor and destructor calls in inheritance hierarchy?
| Event              | Order          |
| ------------------ | -------------- |
| Object creation    | Base → Derived |
| Object destruction | Derived → Base |


### 2.7 What happens if we make destructor private?
If a class has a private destructor, objects of that class cannot be destroyed outside the class.
1. Stack objects cannot be created:
```cpp
class Demo {
private:
    ~Demo() {}   // private destructor
};

int main() {
    Demo d;  // ❌ Error: destructor is private
}
```
2. Heap objects can be created via new, but cannot delete them outside the class:
```cpp
Demo* d = new Demo();
delete d;  // ❌ Error: destructor is private
```

Key Points:
- Private destructor → prevents automatic deletion from outside scope.
- Useful for Singletons or classes managing their own memory.
- Works only if class methods handle object destruction internally.
### 2.8 Can we have a virtual constructor?
No, C++ does not allow constructors to be virtual.

1. Vtable is not yet created
- Virtual functions rely on the vtable to resolve the correct function at runtime.
- During constructor execution, the vtable for that object is not fully set up yet.
- So making a constructor virtual cannot work, because the object’s type is still being initialized.

2. Construction order
- In inheritance, base constructors are always called before derived constructors.
- Allowing a virtual constructor would create ambiguity about which constructor to call first.
### 2.9 What is the use of explicit constructor?
The explicit keyword in C++ is used to prevent implicit conversions by constructors that take a single argument.
- By default, single-argument constructors can be used by the compiler to perform implicit type conversions.
- explicit stops the compiler from doing that automatically.
1. Example Without explicit:
```cpp
#include <iostream>
using namespace std;

class Demo {
public:
    Demo(int x) { cout << "Constructor called with " << x << endl; }
};

void func(Demo d) { }

int main() {
    func(10);  // Implicit conversion from int → Demo
}
```
2. Example With explicit:
```cpp
#include <iostream>
using namespace std;

class Demo {
public:
    explicit Demo(int x) { cout << "Constructor called with " << x << endl; }
};

void func(Demo d) { }

int main() {
    func(10);    // ❌ Compilation error: cannot convert int → Demo
    func(Demo(10)); // ✅ Works fine
}
```
### 2.10 Difference between default constructor and parameterized constructor?

## 3. Inheritance

### 3.1 What is virtual inheritance?
Virtual inheritance is a C++ technique used to prevent multiple “copies” of a base class when using multiple inheritance, particularly in the diamond problem scenario.
- Without virtual inheritance, the derived class may end up with duplicate base class sub-objects.
- Virtual inheritance ensures that there is only one shared instance of the base class, even if it is inherited multiple times indirectly.
```css
       A
      / \
     B   C
      \ /
       D
```
- Classes B and C inherit from A.
- Class D inherits from both B and C.
- Without virtual inheritance, D would contain two separate copies of A → ambiguity when accessing A members.
- Only one copy of A exists in D due to virtual keyword.
- Without virtual, obj.x would be ambiguous (compiler error).
soultion : Virtual Inheritance
```cpp
#include <iostream>
using namespace std;

class A {
public:
    int x;
};

class B : virtual public A { };  // virtual inheritance
class C : virtual public A { };

class D : public B, public C { };

int main() {
    D obj;
    obj.x = 10;  // No ambiguity!
    cout << obj.x << endl;
}
```
### 3.2 Diamond problem in C++ and how to solve it?

### 3.3 Can we override a private method in derived class?
Yes, but with some nuances.
- A private method in the base class cannot be accessed directly in the derived class.
- However, the derived class can define a method with the same name.
- If the base method is virtual, the derived method overrides it, even if the base method is private.
```cpp
#include <iostream>
using namespace std;

class Base {
private:
    virtual void show() { cout << "Base show\n"; }
public:
    void callShow() { show(); }  // calls the private virtual function
};

class Derived : public Base {
private:
    void show() override { cout << "Derived show\n"; }  // overrides Base::show
};

int main() {
    Derived d;
    d.callShow();  // prints "Derived show"
}
```
### 3.4 Can constructor be inherited?
Yes, starting from C++11, constructors can be inherited from a base class using the using keyword.

By Default (pre-C++11)
- Constructors are not inherited automatically.
- You have to explicitly define constructors in the derived class.
```cpp
#include <iostream>
using namespace std;

class Base {
public:
    Base(int x) { cout << "Base constructor: " << x << endl; }
};

class Derived : public Base {
    // No constructor defined → Base constructor not inherited
};

int main() {
    // Derived d(10);  ❌ Compilation error: no matching constructor
}
```
With using C++11
- You can inherit base constructors in derived class:
- Only constructors can be inherited with using.
- Destructor is never inherited.
- If the derived class defines its own constructor, inherited constructors are not automatically used unless explicitly called.
- Useful to avoid boilerplate when derived class has no additional members.
### 3.5 Difference between protected and private inheritance?

### 3.6 How do access specifiers change in different types of inheritance?

### 3.7 What is the order of constructor calls in multiple inheritance?

### 3.8 How to call base class constructor explicitly?
In C++, a derived class can explicitly call a base class constructor to initialize the base part of the object.
- This is done using the member initializer list.
- Base(base_args) calls the base class constructor with arguments.
- This happens before the derived class constructor body executes.
```cpp
class Derived : public Base {
public:
    Derived(args) : Base(base_args) {
        // derived constructor body
    }
};
```
Example :
```cpp
#include <iostream>
using namespace std;

class Base {
public:
    Base(int x) { cout << "Base constructor: " << x << endl; }
};

class Derived : public Base {
public:
    Derived(int x, int y) : Base(x) {  // explicit call to Base constructor
        cout << "Derived constructor: " << y << endl;
    }
};

int main() {
    Derived d(10, 20);
}
```
### 3.9 Can we prevent class from being inherited?
Yes, in C++11 and later, we can prevent a class from being inherited by using the final keyword.
```cpp
class Base final {   // cannot be inherited
    // class body
};
```
### 3.10 Difference between IS-A and HAS-A relationship?
| Feature            | IS-A Relationship (Inheritance)                         | HAS-A Relationship (Composition/Aggregation)             |
| ------------------ | ------------------------------------------------------- | -------------------------------------------------------- |
| **Definition**     | Represents **“is a”** relationship.                     | Represents **“has a”** relationship.                     |
| **Implementation** | Implemented using **inheritance** (`: public Base`).    | Implemented using **member objects / pointers**.         |
| **Example**        | `class Car : public Vehicle { }` → Car **is a** Vehicle | `class Car { Engine e; }` → Car **has an** Engine        |
| **Code Reuse**     | Enables **code reuse via inheritance**                  | No code reuse automatically; uses object’s functionality |
| **Flexibility**    | Less flexible if hierarchy changes                      | More flexible; can replace components easily             |
| **Coupling**       | Tightly coupled (inheritance)                           | Loosely coupled (composition/aggregation)                |

Example of HAS-A
```cpp
class Engine {
public:
    void start() { cout << "Engine starts\n"; }
};

class Car {
private:
    Engine engine;  // Car HAS-A Engine
public:
    void startCar() { engine.start(); }
};

int main() {
    Car c;
    c.startCar();
}
```
## 4. Polymorphism

### 4.1 What is virtual function?
A virtual function is a member function in a base class that can be overridden in derived classes, and whose call is resolved at runtime (dynamic dispatch) rather than compile time.
- Enables runtime polymorphism.
- Declared using the virtual keyword in the base class.
### 4.2 What is pure virtual function?
A pure virtual function is a virtual function with no definition in the base class, forcing derived classes to provide an implementation.
- Declared using = 0 syntax.
- Makes the class abstract, i.e., it cannot be instantiated.
### 4.3 Difference between virtual and pure virtual function?
| Feature                    | Virtual Function                                           | Pure Virtual Function                                               |
| -------------------------- | ---------------------------------------------------------- | ------------------------------------------------------------------- |
| **Definition**             | A member function that can be overridden in derived class. | A virtual function with no definition in the base class (`= 0`).    |
| **Implementation in Base** | Can have a body (definition) in base class.                | No body (definition) in base class.                                 |
| **Class Type**             | Base class can be instantiated.                            | Base class becomes abstract → cannot instantiate.                   |
| **Purpose**                | Allows runtime polymorphism optionally.                    | Forces derived classes to implement the function.                   |
| **Syntax**                 | `virtual void func() { /*...*/ }`                          | `virtual void func() = 0;`                                          |
| **Overriding Requirement** | Optional in derived class.                                 | Mandatory in derived class (unless derived class is also abstract). |
| **Use Case**               | Provide default behavior that can be overridden.           | Define interface-like behavior in base class.                       |



### 4.4 What is an abstract class?
An abstract class is a class that cannot be instantiated and is meant to provide a base for other classes.
- Contains at least one pure virtual function.
- Can also have normal member functions.
### 4.5 Can we create object of abstract class?

### 4.6 What is vtable (virtual table)?
A vtable is a lookup table created by the compiler to support runtime (dynamic) polymorphism in C++.
- Stores addresses of virtual functions of a class.
- Each class with virtual functions has its own vtable.
- Allows base class pointers/references to call the correct derived class function at runtime.
How it Works:
- Each object of a class with virtual functions contains a hidden pointer called vptr.
    - Points to the vtable of that class.
- When a virtual function is called through a base pointer, the compiler uses the vptr → vtable → function address to resolve the correct function.

### 4.7 What is vptr (virtual pointer)?
A vptr is a hidden pointer inside each object of a class with virtual functions.
- Points to the vtable (virtual table) of the class.
- Used by the compiler to resolve virtual function calls at runtime (dynamic dispatch).

### 4.8 How does C++ implement runtime polymorphism internally?
C++ implements runtime (dynamic) polymorphism using virtual functions, which rely on:
- vtable (virtual table) – a table of function pointers.
- vptr (virtual pointer) – a hidden pointer in each object pointing to the vtable.

### 4.9 Can destructor be pure virtual?

### 4.10 Can static functions be virtual?
No, static member functions cannot be virtual in C++.
- Virtual functions require a vptr (per-object pointer) to resolve the function at runtime.
- Static functions are class-level, not object-level → they do not have a vptr.
- Therefore, runtime polymorphism is not possible for static functions.
### 4.11 Why do we need virtual destructor?
When a base class pointer points to a derived class object, and you delete the pointer:
- If the destructor is non-virtual, only the base class destructor is called.
- Derived class destructor is skipped, leading to resource/memory leaks
### 4.12 Can constructor be virtual?
No, constructors cannot be virtual in C++
### 4.13 Difference between virtual function and function overloading?

### 4.14 What is covariant return type?

### 4.15 What happens if base class and derived class have same function signature but without virtual keyword?
- No virtual keyword → No runtime polymorphism.
- Function call is resolved at compile-time (static binding) based on the type of the pointer/reference, not the actual object.
- Derived class function hides the base class function if accessed via a derived object.


## 5. Advanced OOP & C++ Concepts

### 5.1 Difference between composition and aggregation?
| Feature                 | Composition                                                                               | Aggregation                                                                                |
| ----------------------- | ----------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------ |
| **Definition**          | A **strong “has-a” relationship** where the part **cannot exist without the whole**.      | A **weak “has-a” relationship** where the part **can exist independently**.                |
| **Lifetime Management** | Whole (owner) manages the lifetime of the part. If whole is destroyed, part is destroyed. | Part can exist independently of the whole. Destruction of whole does not destroy the part. |
| **Ownership**           | Strong ownership.                                                                         | Weak ownership.                                                                            |
| **Example in C++**      | `class Car` has `Engine` as a member object (by value).                                   | `class Car` has `Wheel*` pointer (could be shared elsewhere).                              |
| **Implementation**      | Member object (by value).                                                                 | Pointer or reference to object.                                                            |
| **Dependency**          | Part **cannot exist** without whole.                                                      | Part **can exist** without whole.                                                          |

Composition (Strong Relationship)
```cpp
#include <iostream>
using namespace std;

class Engine {
public:
    Engine() { cout << "Engine created\n"; }
    ~Engine() { cout << "Engine destroyed\n"; }
};

class Car {
    Engine engine;  // Composition: Engine is part of Car
public:
    Car() { cout << "Car created\n"; }
    ~Car() { cout << "Car destroyed\n"; }
};

int main() {
    Car c;
}
```
Aggregation (Weak Relationship)
```cpp
#include <iostream>
using namespace std;

class Wheel {
public:
    Wheel() { cout << "Wheel created\n"; }
    ~Wheel() { cout << "Wheel destroyed\n"; }
};

class Car {
    Wheel* wheel;  // Aggregation: Car uses Wheel, but doesn't own it
public:
    Car(Wheel* w) : wheel(w) { cout << "Car created\n"; }
    ~Car() { cout << "Car destroyed\n"; }
};

int main() {
    Wheel w;
    Car c(&w);
}
```
- Wheel exists independently of Car → weak ownership.
### 5.2 Example of HAS-A relationship in C++?

### 5.3 What is object slicing?

### 5.4 What is friend function? Pros/cons?

### 5.5 What is friend class?

### 5.6 Can a friend function be virtual?

### 5.7 Difference between static function and non-static function?
| Feature               | Static Function                                | Non-Static Function                               |
| --------------------- | ---------------------------------------------- | ------------------------------------------------- |
| **Belongs To**        | Class itself (class-level)                     | Object of the class (instance-level)              |
| **Access to Members** | Can access **only static members**             | Can access **both static and non-static members** |
| **Called Using**      | Class name (`ClassName::func()`) or object     | Object (`obj.func()`)                             |
| **`this` Pointer**    | Does **not have** `this` pointer               | Has `this` pointer (points to current object)     |
| **Polymorphism**      | Cannot be **virtual**, no runtime polymorphism | Can be virtual, supports runtime polymorphism     |
| **Memory Allocation** | Single copy exists for the class               | Each object has its own copy                      |
| **Use Case**          | Utility functions, counters, shared data       | Behavior specific to object instances             |

### 5.8 Can static functions access non-static members?
No, static functions cannot access non-static members directly.
Reason:
- Static functions belong to the class, not any object.
- Non-static members belong to specific objects.
- Static functions do not have a this pointer, so they cannot refer to instance variables.

### 5.9 What are static data members? Use case?
A static data member is a class-level variable that is shared by all objects of the class.
- Declared inside the class with the keyword static.
- Exists only once in memory, regardless of the number of objects.
- Can be accessed using the class name or object.

### 5.10 Lifetime of static data members?
The lifetime of a static data member is the entire duration of the program.
- They are created when the program starts and destroyed when the program ends.
- Unlike non-static members, their lifetime is independent of any object.

### 5.11 Can static variables be inherited?
Yes, static data members can be inherited by derived classes.
- Derived class can access static members of base class.
- Static member exists only once, shared across base and derived classes

### 5.12 What is const member function?

### 5.13 Difference between const object and const member function?
| Feature                     | Const Object                                                           | Const Member Function                                                 |
| --------------------------- | ---------------------------------------------------------------------- | --------------------------------------------------------------------- |
| **Definition**              | An object declared with `const` keyword.                               | A member function declared with `const` keyword after parameter list. |
| **Modification of Members** | Cannot call **non-const member functions** or modify members directly. | Cannot modify the object’s non-mutable members when called.           |
| **Call Restrictions**       | Can only call **const member functions**.                              | Can be called on **both const and non-const objects**.                |
| **Declaration Example**     | `const Box b;`                                                         | `int getWidth() const;`                                               |
| **Purpose**                 | Make **the entire object read-only**.                                  | Ensure **function does not alter object’s state**.                    |
| **Compiler Enforcement**    | Compiler forbids modification via object.                              | Compiler forbids modification inside function.                        |
| **Usage Scenario**          | Protect object from being modified accidentally.                       | Protect function from changing object state, e.g., getters.           |

### 5.14 Can we overload const and non-const member functions?

### 5.15 Can we declare a constructor as const?

### 5.16 What is mutable keyword in C++?
The mutable keyword allows a class member to be modified even if it is part of a const object or inside a const member function.
- Normally, const objects or const member functions cannot modify data members.
- Declaring a member as mutable overrides this restriction.
```cpp
#include <iostream>
using namespace std;

class Box {
    int width;
    mutable int accessCount; // Can be modified in const functions
public:
    Box(int w) : width(w), accessCount(0) {}

    int getWidth() const {
        accessCount++;  // ✅ Allowed because accessCount is mutable
        return width;
    }

    int getAccessCount() const { return accessCount; }
};

int main() {
    const Box b(10);       // Const object
    cout << b.getWidth() << endl;      // Modifies accessCount
    cout << b.getAccessCount() << endl; // Shows updated accessCount
}
```
### 5.17 Difference between deep copy and shallow copy with example?

### 5.18 What is multiple dispatch? Is it supported in C++?

### 5.19 Explain Rule of 3 / Rule of 5 in C++.
#### Rule of Three:
- If a class requires any one of the following three special functions, it probably requires all three:
1. Destructor (~ClassName())
2. Copy constructor (ClassName(const ClassName&))
3. Copy assignment operator (ClassName& operator=(const ClassName&))

Reason:
- If your class manages resources (like dynamic memory, file handles, or sockets), the compiler-generated versions may lead to shallow copies, dangling pointers, or double deletion.
```cpp
#include <iostream>
using namespace std;

class Deep {
    int* data;
public:
    Deep(int val) { data = new int(val); }  // Constructor
    ~Deep() { delete data; }                // Destructor

    // Copy constructor
    Deep(const Deep& other) {
        data = new int(*other.data);
    }

    // Copy assignment operator
    Deep& operator=(const Deep& other) {
        if (this != &other) {
            delete data;
            data = new int(*other.data);
        }
        return *this;
    }

    void print() { cout << *data << endl; }
};

int main() {
    Deep d1(10);
    Deep d2 = d1;  // Calls copy constructor
    d2.print();
}
```
Rule of Five (C++11 onwards):
- Adds two more functions for move semantics, to optimize temporary objects:
4. Move constructor (ClassName(ClassName&&))
5. Move assignment operator (ClassName& operator=(ClassName&&))

Reason:
- Efficiently transfer resources from temporary objects without deep copying.
```cpp
class Deep {
    int* data;
public:
    // Existing: Constructor, Destructor, Copy constructor, Copy assignment

    // Move constructor
    Deep(Deep&& other) noexcept : data(other.data) {
        other.data = nullptr;
    }

    // Move assignment operator
    Deep& operator=(Deep&& other) noexcept {
        if (this != &other) {
            delete data;
            data = other.data;
            other.data = nullptr;
        }
        return *this;
    }
};
```

### 5.20 What is object slicing in polymorphism?

## 6. Templates & OOP

### 6.1 Difference between class template and function template?

### 6.2 Can we have virtual functions in templates?

### 6.3 How templates support polymorphism?

### 6.4 What is CRTP (Curiously Recurring Template Pattern)?

### 6.5 Difference between templates and inheritance for polymorphism?

### 6.6 Can constructor be template?

### 6.7 What is specialization in templates?

### 6.8 What is type erasure?

## 7. Design Patterns & OOP Applications

### 7.1 Explain Singleton pattern in C++.
done
### 7.2 How to implement Factory pattern?
done
### 7.3 Explain Strategy pattern with example.
done
### 7.4 What is Observer pattern? Example in C++.
done
### 7.5 Explain Adapter design pattern.
done
### 7.6 Difference between composition and inheritance (which to prefer)?

### 7.7 What is dependency inversion principle?

### 7.8 What is SOLID principle in OOP?

### 7.9 Example of real-world polymorphism in C++.
done
### 7.10 Example of encapsulation in real project.
done
### 7.11 Why multiple inheritance is avoided in real-world projects?

### 7.12 How do you decide between inheritance and interfaces in design?