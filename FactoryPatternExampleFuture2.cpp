#include <iostream>
#include <memory>  // For unique_ptr
using namespace std;

class Button {
public:
    virtual ~Button() = default;
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

class System {
public:
    virtual ~System() = default;

    virtual unique_ptr<Button> createButton() const = 0;

    string performButtonOperation() const {
        unique_ptr<Button> button = createButton();
        return "System: " + button->Operation();
    }
};

class WindowsSystem : public System {
public:
    unique_ptr<Button> createButton() const override {
        unique_ptr<Button> button = make_unique<WindowsButton>();
        return button;
    }
};

class LinuxSystem : public System {
public:
    unique_ptr<Button> createButton() const override {
        unique_ptr<Button> button = make_unique<LinuxButton>();
        return button;
    }
};

void clientCode(System& system) {
    cout << system.performButtonOperation() << endl;
}

int main() {
    cout << "App launched with WindowsSystem\n";
    WindowsSystem winSystem;
    clientCode(winSystem);

    cout << "\nApp launched with LinuxSystem\n";
    LinuxSystem linuxSystem;
    clientCode(linuxSystem);

    return 0;
}
