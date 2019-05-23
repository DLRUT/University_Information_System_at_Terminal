#include <iostream>
#include <string>
#include "event.h"
#include "person.h"

using namespace std;

template<class T>
event<T>::event() {
    participants = new map<string,T>;
    T *object = new T;
}

template<class T>
event<T>::event(string name, char restriction) {
    this->name = name;
    this->restriction = restriction;
    participants = new map<string,T>;
}

template<class T>
event<T>::~event() {
    delete participants;
}

template<>
event<person>::~event() {
    delete participants;
}


template<class T>
void event<T>::addPerson(string name, T object) {

}

template<>
void event<person>::addPerson(string name, person object) {

}
