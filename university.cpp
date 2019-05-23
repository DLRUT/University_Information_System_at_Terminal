#include <iostream>
#include "university.h"
#include "person.h"
#include "staff.h"
#include "president.h"
#include "professor.h"
#include "student.h"
#include <string>
#include <typeinfo>
#include <map>

using namespace std;

university::university()
{
    string tempName;
    cout << "A university has been created!" << endl;
    cout << "Please give the university a name." << endl;
    cin.sync();
    getline(cin, this->name);
    personMap = new map<string, person*>;
    cout << "A university needs a president. Please provide a name." << endl;
    getline(cin, tempName);
    staff *head = new president(tempName);
    personMap->insert(pair<string,person*>(tempName, head));

    cout << "Now start by creating people! A person can be 1) a professor, 2) a student or 3) a staff." << endl;
    cout << "Please enter data in the following format: name(space)number(corresponding to the title)" << endl;
    cout << "Type \"end\" to end input." << endl;

    while (tempName != "end") {
        getline(cin,tempName);
        if (tempName != "end") {
            size_t found = tempName.find_last_of("123");
            if (found != string::npos) {
                int length = tempName.length();
                string onlyName = tempName.substr(0,length - 2);
                pair<map<string,person*>::iterator,bool> insertResult;
                switch (tempName[found]){
                    case '1':
                        {
                            professor *newProfessor = new professor(onlyName);
                            insertResult = personMap->insert(pair<string,person*>(onlyName,newProfessor));
                        }
                        break;
                    case '2':
                        {
                            student *newStudent = new student(onlyName);
                            insertResult = personMap->insert(pair<string,person*>(onlyName,newStudent));
                        }
                        break;
                    case '3':
                        {
                            staff *newStaff = new staff(onlyName);
                            insertResult = personMap->insert(pair<string,person*>(onlyName,newStaff));
                        }
                        break;
                    default:
                        cout << "Input error! Please try again!" << endl;
                        break;
                }
                if (!insertResult.second) {
                    cout << "A person with the same name already exists. Please try again." << endl;
                }
            } else {
                cout << "Input error! Please try again!" << endl;
            }
        }
        cin.clear();
        cin.sync();
    }
    cin.sync();

    courseMap = new map<string, course*>;
    eventMap = new map<string, event<person>*>;
}

university::~university()
{
    map<string,person*>::iterator personIter;
    for (personIter = personMap->begin(); personIter != personMap->end(); personIter++) {
        delete personIter->second;
    }
    delete personMap;

    map<string,course*>::iterator courseIter;
    for (courseIter = courseMap->begin(); courseIter != courseMap->end(); courseIter++) {
        delete courseIter->second;
    }
    delete courseMap;

    map<string,event<person>*>::iterator eventIter;
    for (eventIter = eventMap->begin(); eventIter != eventMap->end(); eventIter++) {
        delete eventIter->second;
    }
    delete eventMap;
}

bool university::findPerson(string name, char title) {
bool result = true;
map<string,person*>::iterator iter = personMap->find(name);
if (iter == personMap->end()) {
    result = false;
} else {
    string actualTitle = typeid(*(iter->second)).name();
    size_t found;
    switch (title) {
        case '1':
            {
                found = actualTitle.find(realTitle(name,title));
            }
            break;
        case '2':
            {
                found = actualTitle.find(realTitle(name,title));
            }
            break;
        case '3':
            {
                found = actualTitle.find(realTitle(name,title));
                if (found == string::npos) {
                    found = actualTitle.find("president");
                }
            }
            break;
        default:
            found = string::npos;
    }
    if (found == string::npos) {
        result = false;
    }
}

return result;
}

bool university::findCourse(string name) {
bool result = true;
map<string,course*>::iterator iter = courseMap->find(name);
if (iter == courseMap->end()) {
    result = false;
}
return result;
}

void university::displayEvent(string name) {
map<string,event<person>*>::iterator iter = eventMap->find(name);
if (iter == eventMap->end()) {
    cout << "Event " << name << " is not found." << endl;
} else {
    cout << "Event " << name << " is found." << endl;
    bool isEnded = iter->second->isOpen();
    cout << "This event is" << (isEnded?" not ":" ") << "ended." << endl;
}
}

void university::displayInformation(string name, char title) {
if (findPerson(name, title)) {
    map<string,person*>::iterator iter = personMap->find(name);
    cout << "Name: " << iter->first << " Identity: " << realTitle(name,title) << endl;
} else {
    cout << "Person not found!" << endl;
}
}

string university::realTitle(string name, char title) {
switch (title) {
case '1':
    return "professor";
case '2':
    return "student";
case '3':
    return "staff";
default:
    return "error";
}
}

void university::changePresident(string name) {
    map<string,person*>::iterator iter;
    for (iter = personMap->begin(); iter != personMap->end();iter++) {
        string type = typeid(*(iter->second)).name();
        if (type.find("president") != string::npos) {
            delete iter->second;
            personMap->erase(iter);
            break;
        }
    }
    staff *head = new president(name);
    personMap->insert(pair<string,person*>(name,head));
}

person* university::transferRole(char title, string name) {
person *result;
switch (title) {
    case '1':
        {
        map<string,person*>::iterator iter = personMap->find(name);
        if (iter != personMap->end()) {
            string typeName = typeid(*(iter->second)).name();
            if (typeName.find("professor") != string::npos) {
                result = iter->second;
            }
        }
        }
        break;
    case '2':
        {
        map<string,person*>::iterator iter = personMap->find(name);
        if (iter != personMap->end()) {
            string typeName = typeid(*(iter->second)).name();
            if (typeName.find("student") != string::npos) {
                result = iter->second;
            }
        }
        }
        break;
    case '3':
        {
        map<string,person*>::iterator iter;
            for (iter = personMap->begin(); iter != personMap->end();iter++) {
                string type = typeid(*(iter->second)).name();
                if (type.find("president") != string::npos) {
                    result = iter->second;
                    break;
                }
            }
        }
        break;
}
return result;
}
