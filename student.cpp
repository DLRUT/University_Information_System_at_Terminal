#include <iostream>
#include <string>
#include "student.h"
#include "professor.h"

student::student() {
    myCourses = new map<pair<string,string>,pair<char,string>>;
}

student::student(string name) : person(name) {
    this->name = name;
    myCourses = new map<pair<string,string>,pair<char,string>>;
}

student::~student() {
    delete myCourses;
}

void student::takeCourse(university *univ, string courseName, string termName) {
map<string,course*>::iterator courseIter = univ->courseMap->find(courseName);
if (courseIter == univ->courseMap->end()) {
    cout << "This course does not exist! Please try again." << endl;
} else {
    if (myCourses->find(pair<string,string>(courseName,termName)) != myCourses->end()) {
        cout << "You cannot take the same course twice!" << endl;
        return;
    }
    bool found = false;
    course *target = courseIter->second;
    map<string,roster*>::iterator profIter = target->info->begin();
    while (profIter != target->info->end()) {
        roster *tempRoster = profIter->second;
        professor *targetProf = dynamic_cast<professor*>(univ->transferRole('1',profIter->first));
        if (tempRoster->students->find(termName) != tempRoster->students->end()
            && targetProf->isCourseOpen(courseName,termName)) {
            if (!found) {
                cout << "Please type the name of the professor you prefer."
                << " The choice(s) are shown below." << endl;
                found = true;
            }
            cout << profIter->first << endl;
        }
    profIter++;
    }
    if (!found) {
        cout << "Unfortunately, no professor is teaching this course in the specified term." << endl;
        cout << "Please choose another term or another course." << endl;
        return;
    }
    string profName;
    cin.sync();
    getline(cin,profName);
    profIter = target->info->find(profName);
    if (profIter == target->info->end()) {
        cout << "Professor " << profName << " does not exist!" << endl;
    } else { // register course
        roster *targetRoster = profIter->second;
        map<string,map<string,char>*>::iterator studentIter = targetRoster->students->find(termName);
        map<string,char> *targetMap = studentIter->second;
        targetMap->insert(pair<string,char>(this->name,DEFAULT_GRADE));
        myCourses->insert(pair<pair<string,string>,pair<char,string>> \
        (pair<string,string>(courseName,termName),pair<char,string>(DEFAULT_GRADE,profName)));
        cout << "Course " << courseName << " is successfully registered." << endl;
    }
}
}

void student::dropCourse(university *univ, string courseName, string termName) {
map<string,course*>::iterator courseIter = univ->courseMap->find(courseName);
if (courseIter == univ->courseMap->end()) {
    cout << "This course does not exist! Please try again." << endl;
} else {
    map<pair<string,string>,pair<char,string>>::iterator myIter \
    = myCourses->find(pair<string,string>(courseName,termName));
    if (myIter == myCourses->end()) {
        cout << "You didn't take this course!" << endl;
        return;
    }
    course *target = courseIter->second;
    map<string,roster*>::iterator profIter = target->info->find(myIter->second.second);
    if (profIter == target->info->end()) {
        cout << "This professor already quits." << endl;
    } else {
        professor *tempProf = dynamic_cast<professor*>(univ->transferRole('1',profIter->first));
        if (!tempProf->isCourseOpen(courseName,termName)) {
            cout << "You cannot drop an ended course." << endl;
        } else {
            roster *targetRoster = profIter->second;
            map<string,map<string,char>*>::iterator studentIter = targetRoster->students->find(termName);
            map<string,char> *targetMap = studentIter->second;
            targetMap->erase(this->name);
            myCourses->erase(pair<string,string>(courseName,termName));
            cout << "Course " << courseName << " is successfully dropped." << endl;
        }
    }
}
}

void student::joinEvent(university *univ, string name) {
map<string,event<person>*>::iterator eventIter = univ->eventMap->find(name);
if (eventIter == univ->eventMap->end()) {
    cout << "This event does not exist!" << endl;
} else {
    event<person> *targetEvent = eventIter->second;
    bool result = targetEvent->add(this->name,this);
    cout << "Registration " << (result?"successful!":"failed! Permission denied!") << endl;
}
}

void student::viewCourse() {
cout << "You have enrolled " << myCourses->size() << " courses." << endl;
map<pair<string,string>,pair<char,string>>::iterator iter = myCourses->begin();
cout << "Course  Term" << endl;
while (iter != myCourses->end()) {
    cout << iter->first.first  << " " << iter->first.second << endl;
    iter++;
}
}

void student::viewGrade() {
cout << "You have enrolled " << myCourses->size() << " courses." << endl;
map<pair<string,string>,pair<char,string>>::iterator iter = myCourses->begin();
cout << "Course  Grade" << endl;
while (iter != myCourses->end()) {
    cout << iter->first.first  << "   " << iter->second.first << endl;
    iter++;
}
}

void student::introduce() {
    cout << "I'm a student in this university. My name is " << this->name << "." << endl;
}
