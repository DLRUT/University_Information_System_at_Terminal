#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include "person.h"

using namespace std;

template <class T>
class event
{
    public:
        friend class president;
        event();
        event<T>(string, char);
        ~event();
        bool isOpen() const {return state;};
        bool add(string, T*);

    protected:
    private:
        string name;
        bool state;
        char restriction;
        map<string,T*> *participants;
        void endEvent(){state = false;};
};

template<class T>
event<T>::event() {
    state = true;
    participants = new map<string,T*>;
}

template<class T>
event<T>::event(string name, char restriction) {
    this->name = name;
    this->restriction = restriction;
    state = true;
    participants = new map<string,T*>;
}

template<class T>
event<T>::~event() {
    delete participants;
}

template<class T>
bool event<T>::add(string name, T *object) {
if (!state) {
    cout << "This event has ended!" << endl;
    return false;
}
bool result = false;
typename map<string,T*>::iterator iter = participants->find(name);
pair< typename map<string,T*>::iterator,bool> insertResult;
switch (restriction) {
case '1':
    {
    if (iter != participants->end()) {
        cout << "You already registered this event!" << endl;
    } else {
        insertResult = participants->insert(pair<string,T*>(name,object));
        if (insertResult.second) result = true;
    }
    }
    break;
case '2':
    {
    string typeName = typeid(*object).name();
    if (typeName.find("professor") != string::npos) {
        insertResult = participants->insert(pair<string,T*>(name,object));
        if (insertResult.second) result = true;
    }
    }
    break;
case '3':
    {
    string typeName = typeid(*object).name();
    if (typeName.find("student") != string::npos) {
        insertResult = participants->insert(pair<string,T*>(name,object));
        if (insertResult.second) result = true;
    }
    }
    break;
default:
    cout << "Something is wrong with restriction setting." << endl;
    break;
}
return result;
}

#endif // EVENT_H
