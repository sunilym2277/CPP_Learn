//Observer == Subscriber == User
#include <iostream>
#include <list>
#include <string>
using namespace std;

class IObserver {
public:
    virtual ~IObserver() {}
    virtual void Update(const string &msg) = 0;
};

class ISubject {
public:
    virtual ~ISubject() {};
    virtual void Attach(IObserver *observer) = 0;
    virtual void Detach(IObserver *observer) = 0;
    virtual void Notify() = 0;
};

class Subject : public ISubject {
    std::list<IObserver *> list_observer_;
    string message_;
public:
    virtual ~Subject() {
        cout<<"Goodbye, I was the Subject. \n";
    }
    void Attach(IObserver *observer) override {
        list_observer_.push_back(observer);
    }
    void Detach(IObserver *observer) override {
        list_observer_.remove(observer);
    }
    void Notify() override {
       for(auto *observer : list_observer_) {
        observer->Update(message_);
       }
    }

    void CreateMessage(string message = "Empty") {
        this->message_ = message;
        Notify();
    }

    void SomeBusinessLogic() {
        this->message_ = "change message message";
        Notify();
        cout<<"I amd about to do some thing important"<<endl;
    }    
};

class Observer : public IObserver {
string msg_;
Subject &subject_;
static int static_number_;
int number_;
public:
    Observer(Subject &subject) : subject_(subject) {
        this->subject_.Attach(this);
        cout<<"Hi, I'am the Observer \"" <<++Observer::static_number_<<"\".\n";
        this->number_ = Observer::static_number_;
    }
    virtual ~Observer() {
        std::cout << "Goodbye, I was the Observer \"" << this->number_ << "\".\n";
    }
    void Update(const string &msg) override {
        msg_ = msg;
        std::cout << "Observer \"" << this->number_ << "\": a new message is available --> " << this->msg_ << "\n";
    }
    void RemoveMeFromTheList() {
        subject_.Detach(this);
        cout << "Observer \"" << number_ << "\" removed from the list.\n";
    }
};

int Observer::static_number_ = 0;
void ClientCode ()
{
    Subject *subject = new Subject;
    Observer *observer1 = new Observer(*subject);
    Observer *observer2 = new Observer(*subject);
    Observer *observer3 = new Observer(*subject);
    Observer *observer4;
    Observer *observer5;

    subject->CreateMessage("Hello World! : D");
    observer3->RemoveMeFromTheList();

    subject->CreateMessage("The weather is hot today! : p");
    observer4 = new Observer(*subject);

    observer2->RemoveMeFromTheList();
    observer5 = new Observer(*subject);

    subject->CreateMessage("My new car is great! ; )");

    delete observer5;
    delete observer4;
    delete observer3;
    delete observer2;
    delete observer1;
    delete subject;
}

int main()
{
    ClientCode();
    return 0;
}

