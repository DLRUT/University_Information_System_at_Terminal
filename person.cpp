#include <iostream>
#include <string>
#include "person.h"

using namespace std;

person::person()
{

}

person::person(string name)
{
    this->name = name;
}

person::~person()
{

}

void person::introduce(){
    cout << "I'm a person in this university. My name is " << this->name << "." << endl;
}
