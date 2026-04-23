#include <iostream>
using namespace std;

// Implementation interface
class Device {
public:
    virtual bool isEnabled() const = 0;
    virtual void enable() = 0;
    virtual void disable() = 0;
    virtual int getVolume() const = 0;
    virtual void setVolume(int volume) = 0;
    virtual int getChannel() const = 0;
    virtual void setChannel(int channel) = 0;
    virtual ~Device() = default;
};

// Concrete implementation: Radio
class Radio : public Device {
private:
    bool on = false;
    int volume = 30;
    int channel = 1;
public:
    bool isEnabled() const override { return on; }
    void enable() override { on = true; cout << "[Radio] Power ON\n"; }
    void disable() override { on = false; cout << "[Radio] Power OFF\n"; }
    int getVolume() const override { return volume; }
    void setVolume(int v) override { volume = v; cout << "[Radio] Volume set to " << volume << "\n"; }
    int getChannel() const override { return channel; }
    void setChannel(int c) override { channel = c; cout << "[Radio] Channel set to " << channel << "\n"; }
};

// Concrete implementation: TV
class TV : public Device {
private:
    bool on = false;
    int volume = 50;
    int channel = 5;
public:
    bool isEnabled() const override { return on; }
    void enable() override { on = true; cout << "[TV] Power ON\n"; }
    void disable() override { on = false; cout << "[TV] Power OFF\n"; }
    int getVolume() const override { return volume; }
    void setVolume(int v) override { volume = v; cout << "[TV] Volume set to " << volume << "\n"; }
    int getChannel() const override { return channel; }
    void setChannel(int c) override { channel = c; cout << "[TV] Channel set to " << channel << "\n"; }
};

// Abstraction
class Remote {
protected:
    Device *device_;
public:
    Remote(Device* device) : device_(device) { }
    virtual void togglePower() const {
        if (device_->isEnabled()) device_->disable();
        else device_->enable();
    }
    virtual void volumeUp() const {
        device_->setVolume(device_->getVolume() + 10);
    }
    virtual void volumeDown() const {
        device_->setVolume(device_->getVolume() - 10);
    }
    virtual void changeChannel(int channel) const {
        device_->setChannel(channel);
    }
    virtual ~Remote() = default;
};

// Refined Abstraction
class AdvancedRemote : public Remote {
public:
    AdvancedRemote(Device *de) : Remote(de) { }
    void mute() {
        device_->setVolume(0);
        cout << "[Remote] Device muted\n";
    }
};

// Client code
void clientCode(Remote &remote) {
    remote.togglePower();
    remote.changeChannel(10);
    remote.volumeUp();
    remote.volumeDown();
}

int main() {
    Device* tv = new TV;
    Remote* simpleRemote = new Remote(tv);
    cout << "--- Using Simple Remote with TV ---\n";
    clientCode(*simpleRemote);
    delete simpleRemote;
    delete tv;

    cout << "\n--- Using Advanced Remote with Radio ---\n";
    Device* radio = new Radio;
    AdvancedRemote* advRemote = new AdvancedRemote(radio);
    clientCode(*advRemote);
    advRemote->mute();
    delete advRemote;
    delete radio;

    return 0;
}
