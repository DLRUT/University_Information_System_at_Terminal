#include <iostream>
#include <string>
#include "TA.h"

using namespace std;

TA::TA() {

}

TA::TA(string name) : student(name) {
    this->name = name;
}

TA::~TA() {

}

void TA::introduce() {
    cout << "I'm a TA in this university. My name is " << this->name << endl;
}

