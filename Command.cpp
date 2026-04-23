#include <iostream>
#include <memory>
using namespace std;

//1. Command Interface
class Command {
public:
    virtual void execute() = 0;
    virtual ~Command() { }
};

//2. Reciver
class Light {
public:
    void turnOn() { cout<<" Light is ON"<<endl;}
    void turnOff() { cout << "Light is OFF\n"; }
};

//3. Concrete Commands
class TurnOnCommand : public Command {
    Light* light;
public:
    TurnOnCommand(Light *l): light(l) {}
    void execute() override { light->turnOn(); }
};

class TurnOffCommand : public Command {
   Light* light;
public:
    TurnOffCommand(Light *l): light(l) {}
    void execute() override { light->turnOff(); }
};

//4. Invoker
class RemoteControl {
    Command* command;
public:
    void setCommand(Command *cmd) {
        command = cmd;
    }
    void pressButton() {
        if(command) command->execute();
    }
};

//5. Client
int main() {
    Light livingRoomLight;

    TurnOnCommand on(&livingRoomLight);
    TurnOffCommand off(&livingRoomLight);

    RemoteControl remote;
    remote.setCommand(&on);
    remote.pressButton();

    remote.setCommand(&off);
    remote.pressButton();

    return 0;
}