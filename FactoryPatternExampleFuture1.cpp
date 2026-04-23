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

class ScrollBar {
public:
    virtual ~ScrollBar() {}
    virtual string Operation() const = 0;
};

class WindowsScrollBar : public ScrollBar {
public:
    string Operation() const override {
        return "Windows ScrollBar";
    }
};

class LinuxScrollBar : public ScrollBar {
public:
    string Operation() const override {
        return "Linux ScrollBar";
    }
};

class MacOSScrollBar : public ScrollBar {
public:
    string Operation() const override {
        return "MacOS ScrollBar";
    }
};

class AndroidScrollBar : public ScrollBar {
public:
    string Operation() const override {
        return "Android ScrollBar";
    }
};

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
    virtual ScrollBar* createScrollBar() const = 0;

    string performButtonOperation() const {
        Button* button = createButton();
        string result = "System: " + button->Operation();
        delete button;
        return result;
    }
    
    string performScrollBarOperation() const {
        ScrollBar* scrollBar = createScrollBar();
        string result = "System: " + scrollBar->Operation();
        delete scrollBar;
        return result;
    }
};

class WindowsSystem : public System {
public:
    Button* createButton() const override {
        return new WindowsButton;
    }
    ScrollBar* createScrollBar() const override {
        return new WindowsScrollBar;
    }
};

class LinuxSystem : public System {
public:
    Button* createButton() const override {
        return new LinuxButton;
    }
    ScrollBar* createScrollBar() const override {
        return new LinuxScrollBar;
    }
};

class MacOSSystem : public System {
public:
    Button* createButton() const override {
        return new MacOSButton;
    }
    ScrollBar* createScrollBar() const override {
        return new MacOSScrollBar;
    }
};


class AndroidSystem : public System {
public:
    Button* createButton() const override {
        return new AndroidButton;
    }
    ScrollBar* createScrollBar() const override {
        return new AndroidScrollBar;
    }
};

void clientCode(System& system) {
    cout << system.performButtonOperation() << endl;
    cout << system.performScrollBarOperation() << endl;
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
