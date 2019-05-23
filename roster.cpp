#include <iostream>
#include <string>
#include "roster.h"

using namespace std;

roster::roster()
{
    this->students = new map<string, map<string, char>*>();
    this->TAs = new map<string, map<string, double>*>();
}

roster::roster(roster &other) {
    this->students = new map<string, map<string, char>*>();
    this->TAs = new map<string, map<string, double>*>();
    map<string, map<string, char>*>::iterator studentIter;
    for (studentIter = (other.students)->begin();studentIter != (other.students)->end();studentIter++) {
        map<string, char> *tempRecord = new map<string, char>();
        map<string, char>::iterator recordIter;
        string otherString = studentIter->first;
        map<string, char> *otherRecord = studentIter->second;
        for (recordIter = otherRecord->begin();recordIter != otherRecord->end();recordIter++) {
            tempRecord->insert(pair<string,char>(recordIter->first,recordIter->second));
        }
        students->insert(pair<string,map<string,char>*>(otherString,tempRecord));
    } // copy students map
    map<string, map<string, double>*>::iterator TAIter;
    for (TAIter = other.TAs->begin();TAIter != other.TAs->end();TAIter++) {
        map<string, double> *tempRecord = new map<string, double>();
        map<string, double>::iterator recordIter;
        string otherString = TAIter->first;
        map<string, double> *otherRecord = TAIter->second;
        for (recordIter = otherRecord->begin();recordIter != otherRecord->end();recordIter++) {
            tempRecord->insert(pair<string,double>(recordIter->first,recordIter->second));
        }
        TAs->insert(pair<string,map<string,double>*>(otherString,tempRecord));
    } // copy students map
}

roster::~roster()
{
    map<string, map<string, char>*>::iterator studentIter;
    for (studentIter = students->begin();studentIter != students->end();studentIter++) {
        delete studentIter->second;
    }
    delete students;
    map<string, map<string, double>*>::iterator TAIter;
    for (TAIter = TAs->begin();TAIter != TAs->end();TAIter++) {
        delete TAIter->second;
    }
    delete TAs;
}

void roster::introduce(){
    cout << "This is a roster." << endl;
}

