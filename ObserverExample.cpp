//Observer == Subscriber == User
#include <iostream>
#include <list>
#include <string>
using namespace std;

class EventListners {
public:
    virtual ~EventListners() {}
    virtual void Update(const string &msg) = 0;
};

class IEventManager {
public:
    virtual ~IEventManager() {};
    virtual void subscribe(EventListners *observer) = 0;
    virtual void unsubscribe(EventListners *observer) = 0;
    virtual void Notify() = 0;
};

class EventManager : public IEventManager {
    std::list<EventListners *> listners;
    string message_;
public:
    virtual ~EventManager() {
        cout<<"Goodbye, I was the EventManager. \n";
    }
    void subscribe(EventListners *listner) override {
        listners.push_back(listner);
    }
    void unsubscribe(EventListners *listner) override {
        listners.remove(listner);
    }
    void Notify() override {
       for(auto *listner : listners) {
        listner->Update(message_);
       }
    }
    void CreateMessage(string message = "Empty") {
        this->message_ = message;
        Notify();
    }   
};

class EmailAlertsListener : public EventListners {
    string msg_;
    EventManager &subject_;
    static int static_number_;
    int number_;
public:
    EmailAlertsListener(EventManager &subject) : subject_(subject) {
        this->subject_.subscribe(this);
        cout<<"Hi, I'am the EmailAlertsListener \"" <<++EmailAlertsListener::static_number_<<"\".\n";
        this->number_ = EmailAlertsListener::static_number_;
    }
    virtual ~EmailAlertsListener() {
        std::cout << "Goodbye, I was the EmailAlertsListener \"" << this->number_ << "\".\n";
    }
    void Update(const string &msg) override {
        msg_ = msg;
        std::cout << "EmailAlertsListener \"" << this->number_ << "\": a new message is available --> " << this->msg_ << "\n";
    }
    void RemoveMeFromTheList() {
        subject_.unsubscribe(this);
        cout << "EmailAlertsListener \"" << number_ << "\" removed from the list.\n";
    }
};

class LoggingListner : public EventListners {
    string msg_;
    EventManager &subject_;
    static int static_number_;
    int number_;
public:
    LoggingListner(EventManager &subject) : subject_(subject) {
        this->subject_.subscribe(this);
        cout<<"Hi, I'am the LoggingListner \"" <<++LoggingListner::static_number_<<"\".\n";
        this->number_ = LoggingListner::static_number_;
    }
    virtual ~LoggingListner() {
        std::cout << "Goodbye, I was the LoggingListner \"" << this->number_ << "\".\n";
    }
    void Update(const string &msg) override {
        msg_ = msg;
        std::cout << "LoggingListner \"" << this->number_ << "\": a new message is available --> " << this->msg_ << "\n";
    }
    void RemoveMeFromTheList() {
        subject_.unsubscribe(this);
        cout << "LoggingListner \"" << number_ << "\" removed from the list.\n";
    }
};

int LoggingListner::static_number_ = 0;
int EmailAlertsListener::static_number_ = 0;
class Editor
{
    EventManager events;
    public:
    EventManager &GetEventManager() {
        return events;
    }

    void OpenFile(const string &filename) {
        cout << "Editor: Opening file " << filename << "\n";
        events.CreateMessage("File opened: " + filename);
    }

    void SaveFile(const string &filename) {
        cout << "Editor: Saving file " << filename << "\n";
        events.CreateMessage("File saved: " + filename);
    }
};

int main()
{
    Editor editor;
    EventManager &eventManager = editor.GetEventManager();

    EmailAlertsListener *emailListener1 = new EmailAlertsListener(eventManager);
    EmailAlertsListener *emailListener2 = new EmailAlertsListener(eventManager);
    LoggingListner loggingListener(eventManager);

    editor.OpenFile("document.txt");
    editor.SaveFile("document.txt");

    emailListener1->RemoveMeFromTheList();
    editor.SaveFile("another.txt");

    return 0;
}

