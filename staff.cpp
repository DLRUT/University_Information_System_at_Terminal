#include <iostream>
#include <string>
#include "staff.h"

using namespace std;

staff::staff() {

}

staff::staff(string name) : person(name) {
    this->name = name;
}

staff::~staff() {

}

void staff::introduce() {
    cout << "I'm a staff in this university. My name is " << this->name << "." << endl;
}
