#include <iostream>
using namespace std;

class Button {
public:
    virtual ~Button() {}
    virtual string Operation() const = 0; 
};

class WindowsButton : public Button {
public:
    string Operation() const override {
        return "Creating a new Windows Button";
    }
};

class LinuxButton : public Button {
public:
    string Operation() const override {
        return "Creating a new Linux Button";
    }
};

// This class will be added in future without touching the existing ones
class MacOSButton : public Button {
public:
    string Operation() const override {
        return "Creating a new MacOS Button";
    }
};

class AndroidButton : public Button {
public:
    string Operation() const override {
        return "Creating a new Android Button";
    }
};

class System {
public:
    virtual ~System() {}
    virtual Button* createButton() const = 0;

    string performOperation() const {
        Button* button = this->createButton();
        string result = "System: Working with " + button->Operation();
        delete button;
        return result;
    }
};

class WindowsSystem : public System {
public:
    Button* createButton() const override {
        return new WindowsButton;
    }
};

class LinuxSystem : public System {
public:
    Button* createButton() const override {
        return new LinuxButton;
    }
};

// This class will be added in future without touching the existing ones
class MacOSSystem : public System {
public:
    Button* createButton() const override {
        return new MacOSButton;
    }
};


class AndroidSystem : public System {
public:
    Button* createButton() const override {
        return new AndroidButton;
    }
};

// Client code works with any System subclass via the System interface.
void clientCode(System& system) {
    cout << "Client: Not aware of the system class, but it works:\n"<< system.performOperation() << endl;
}

int main() {
    cout << "App launched with WindowsSystem\n";
    System* system1 = new WindowsSystem;
    clientCode(*system1);
    delete system1;

    cout << "\nApp launched with LinuxSystem\n";
    System* system2 = new LinuxSystem;
    clientCode(*system2);
    delete system2;

    cout << "\nApp launched with MacOSSystem\n";
    System* system3 = new MacOSSystem;
    clientCode(*system3);
    delete system3;

    cout << "\nApp launched with AndroidSystem\n";
    System* system4 = new AndroidSystem;
    clientCode(*system4);
    delete system4;

    return 0;
}
