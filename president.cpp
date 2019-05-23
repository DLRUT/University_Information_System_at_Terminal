#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <time.h>
#include "president.h"
#include "university.h"
#include "professor.h"
#include "student.h"
#include "staff.h"
#include "course.h"
#include "event.h"

using namespace std;

president::president(string name) : staff(name) {
    this->name = name;
}

president::~president() {

}

void president::introduce() {
    cout << "I'm the president in this university. My name is " << this->name << "." << endl;
}

void president::addPerson(university * univ, string name, char title) {
pair<map<string,person*>::iterator,bool> insertResult;
if (univ->findPerson(name,title)) {
    cout << "This person already exists!" << endl;
} else {
    switch(title) {
        case '1':
            {
            professor *newProfessor = new professor(name);
            insertResult = univ->personMap->insert(pair<string,person*>(name,newProfessor));
            }
            break;
        case '2':
            {
            student *newStudent = new student(name);
            insertResult = univ->personMap->insert(pair<string,person*>(name,newStudent));
            }
            break;
        case '3':
            {
            staff *newStaff = new staff(name);
            insertResult = univ->personMap->insert(pair<string,person*>(name,newStaff));
            }
            break;
        default:
            cout << "Input error! Please try again!" << endl;
    }
    if (!insertResult.second) {
        cout << "A person with the same name already exists. Please try again." << endl;
    } else {
        cout << name << " is added." << endl;
    }
}
}

void president::removePerson(university *univ, string name, char title) {
if (this->name.compare(name) == 0) {
    cout << "You cannot resign yourself!" << endl;
} else if (!univ->findPerson(name,title)) {
    cout << "This person does not exist!" << endl;
} else {
    string tempName;
    map<string,person*>::iterator iter = univ->personMap->find(name);
    tempName = iter->first;
    delete iter->second;
    univ->personMap->erase(iter);
    cout << tempName << " has been removed!" << endl;
}
}

void president::addCourse(university *univ, string name) {
if (univ->findCourse(name)){
    cout << "This course already exists!" << endl;
} else {
    course *newCourse = new course(name);
    univ->courseMap->insert(pair<string,course*>(name,newCourse));
    cout << "Course " << name << " is added." << endl;
}
}

void president::removeCourse(university *univ, string name) {
if (!univ->findCourse(name)) {
    cout << "This course does not exist!" << endl;
} else {
    //record course in the future
    string tempName;
    map<string,course*>::iterator iter = univ->courseMap->find(name);
    delete iter->second;
    tempName = iter->first;
    univ->courseMap->erase(iter);
    cout << tempName << " has been removed!" << endl;
}
}

void president::addEvent(university* univ, string name, char restriction) {
if (restriction > '5' || restriction < '1') {
    cout << "Input error! Restriction number is out of range." << endl;
} else {
    map<string,event<person>*>::iterator eventIter = univ->eventMap->find(name);
    if (eventIter != univ->eventMap->end()) {
        cout << "This event already exists!" << endl;
    } else {
        event<person> *newEvent = new event<person>(name, restriction);
        univ->eventMap->insert(pair<string,event<person>*>(name,newEvent));
        cout << "Event " << name << " is added." << endl;
    }
}
}

void president::removeEvent(university *univ, string name) {
map<string,event<person>*>::iterator eventIter = univ->eventMap->find(name);
if (eventIter == univ->eventMap->end()) {
    cout << "This event does not exist!" << endl;
} else {
    delete eventIter->second;
}
}

void president::endEvent(university *univ, string name) {
map<string,event<person>*>::iterator eventIter = univ->eventMap->find(name);
if (eventIter == univ->eventMap->end()) {
    cout << "This event does not exist!" << endl;
} else {
    eventIter->second->endEvent();
    cout << "Event " << name << " is now ended." << endl;
}
}

void president::joinEvent(university *univ, string name) {
map<string,event<person>*>::iterator eventIter = univ->eventMap->find(name);
if (eventIter == univ->eventMap->end()) {
    cout << "This event does not exist!" << endl;
} else {
    map<string,person*> *currParticipants = eventIter->second->participants;
    currParticipants->insert(pair<string,person*>(this->name,this));
    cout << "You joined the event " << name << "." << endl;
}
}

void president::recordPeople(university *univ) {
fstream peopleFile("people.txt", ios_base::in|ios_base::out|ios_base::trunc);
if (!peopleFile.is_open()) {
    cout << "Cannot open file people.txt." << endl;
} else {
    // write this file
    int max_name_length = 15;
    map<string,person*>::iterator personIter = univ->personMap->begin();
    while (personIter != univ->personMap->end()) {
        if (personIter->first.size() > max_name_length) max_name_length = personIter->first.size();
        personIter++;
    }
    time_t timeStamp = time(0);
    string currTime = asctime(localtime(&timeStamp)); // get time in week month day time(00:00:00) year
    peopleFile << univ->name << " Affiliated People" << endl << endl;
    peopleFile << "Recorded by " << currTime << endl; // currTime contains an endl so only one is required
    peopleFile << "Name" << setw(max_name_length + 2 - 4 + 13) << "Registered As" << endl << endl;
    string tempName, tempTitle, typeName;
    for (personIter = univ->personMap->begin(); personIter != univ->personMap->end(); personIter++) {
        tempName = personIter->first;
        typeName = typeid(*(personIter->second)).name();
        if (typeName.find("professor") != string::npos) {
            tempTitle = "Professor";
        } else if (typeName.find("student") != string::npos) {
            tempTitle = "Student";
        } else if (typeName.find("staff") != string::npos) {
            tempTitle = "Staff";
        } else if (typeName.find("president") != string::npos) {
            tempTitle = "President";
        } else {
            tempTitle = "Unknown";
        }
        peopleFile << tempName
        << setw(max_name_length + 2 - tempName.size() + tempTitle.size()) << tempTitle << endl;
    }
    peopleFile << endl;
    peopleFile.close();

    // print the content in people.txt
    peopleFile.open("people.txt", ios_base::in);
    cout << "The following is printed in people.txt:" << endl;
    char currChar;
    while (peopleFile.get(currChar)) {
        cout << currChar;
    }
    cout << endl;
    peopleFile.close();
}
}

void president::recordCourses(university *univ) {
fstream courseFile("courses.txt", ios_base::in|ios_base::out|ios_base::trunc);
if (!courseFile.is_open()) {
    cout << "Cannot open file courses.txt." << endl;
} else {
    int max_name_length = 15; // calculate maximum of name size
    map<string,person*>::iterator personIter = univ->personMap->begin();
    while (personIter != univ->personMap->end()) {
        if (personIter->first.size() > max_name_length) max_name_length = personIter->first.size();
        personIter++;
    }

    time_t timeStamp = time(0); // print current time
    string currTime = asctime(localtime(&timeStamp));
    courseFile << univ->name << " Affiliated Courses" << endl << endl;
    courseFile << "Recorded by " << currTime << endl;

    map<string,course*>::iterator courseIter = univ->courseMap->begin();
    while (courseIter != univ->courseMap->end()) {
        courseFile << courseIter->first << endl;
        courseFile << "Professor" << setw(max_name_length + 1 - 9) << " " << "Terms" << endl;
        map<string,roster*>::iterator rosterIter = courseIter->second->info->begin();
        string tempName, termName;
        while (rosterIter != courseIter->second->info->end()) {
            tempName = rosterIter->first;
            courseFile << tempName << setw(max_name_length + 1 - tempName.size()) << " ";
            map<string,map<string,char>*>::iterator termIter = rosterIter->second->students->begin();
            while (termIter != rosterIter->second->students->end()) {
                termName = termIter->first;
                courseFile << termName
                << (++termIter == rosterIter->second->students->end()?"":", ");
            }
            courseFile << endl;
            rosterIter++;
        }
        courseFile << endl;
        courseIter++;
    }

    courseFile.close();

    // print the content in course.txt
    courseFile.open("courses.txt", ios_base::in);
    cout << "The following is printed in courses.txt:" << endl;
    char currChar;
    while (courseFile.get(currChar)) {
        cout << currChar;
    }
    cout << endl;
    courseFile.close();
}
}

void president::recordEvents(university *univ) {
fstream eventFile("events.txt", ios_base::in|ios_base::out|ios_base::app);
if (!eventFile.is_open()) {
    cout << "Cannot open file events.txt." << endl;
} else {
    int max_name_length = 15;
    map<string,event<person>*>::iterator eventIter = univ->eventMap->begin();
    while (eventIter != univ->eventMap->end()) {
        if (eventIter->first.size() > max_name_length) max_name_length = eventIter->first.size();
        eventIter++;
    }

    time_t timeStamp = time(0);
    string currTime = asctime(localtime(&timeStamp));
    eventFile << univ->name << " Affiliated Events" << endl << endl;
    eventFile << "Recorded by " << currTime << endl;
    eventFile << "Event Name" << setw(max_name_length + 1 - 10) << " " << "Type" << endl << endl;

    string tempName, tempRestriction;
    for (eventIter = univ->eventMap->begin(); eventIter != univ->eventMap->end(); eventIter++) {
        tempName = eventIter->first;
        tempRestriction = eventIter->second->restriction;
        eventFile << tempName
        << setw(max_name_length + 1 - tempName.size()) << " " << tempRestriction << endl;
    }
    eventFile << endl;
    eventFile.close();

    // print the content in events.txt
    eventFile.open("events.txt", ios_base::in);
    cout << "The following is printed in events.txt:" << endl;
    char currChar;
    while (eventFile.get(currChar)) {
        cout << currChar;
    }
    cout << endl;
    eventFile.close();
}
}
