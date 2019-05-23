#include <iostream>
#include <string>
#include "course.h"

using namespace std;

course::course()
{
    this->info = new map<string, roster*>();
}

course::course(string name)
{
    this->name = name;
    this->info = new map<string, roster*>();
}

course::~course()
{
    map<string, roster*>::iterator iter = info->begin();
    while (iter != info->end()) {
        delete iter->second;
        iter++;
    }
    delete info;
}

void course::introduce(){
    cout << "Welcome to course " << this->name << "!" << endl;
}
