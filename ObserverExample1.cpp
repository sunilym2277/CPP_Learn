#include <iostream>
#include <list>
#include <memory>
using namespace std;

class ISubscriber {
public:
    virtual void notify(string msg) = 0;
};

class User : public ISubscriber {
        int userId;
    public:
        User(int userId) { this->userId = userId; }
        void notify(string msg) override{
            cout<<"User :" <<userId<<" recived msg"<<msg<<endl;
        }
};

class Group {
private:
    list<shared_ptr<ISubscriber>> users;
public:
    void subscribe(shared_ptr<ISubscriber> user) { users.push_back(user); }
    void unsubscribe(shared_ptr<ISubscriber> user) { users.remove(user); }
    void notify(string msg) {
        for(auto user: users) {
            user->notify(msg);
        }
    }
};
int main() {
    Group* group = new Group;
    shared_ptr<User> user1 = make_shared<User>(1);
    shared_ptr<User> user2 = make_shared<User>(2);
    shared_ptr<User> user3 = make_shared<User>(3);

    group->subscribe(user1);
    group->subscribe(user2);
    group->subscribe(user3);
    group->notify(" new msg");

    group->unsubscribe(user1);
    group->notify(" new new msg");


    return 0;
}