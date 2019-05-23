#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include "university.h"
#include "professor.h"
#include "person.h"
#include "student.h"
#include "course.h"

using namespace std;

professor::professor() {
    myCourses = new list<string>();
    courseStatus = new map<pair<string,string>,bool>();
}

professor::professor(string name) : person(name) {
    this->name = name;
    myCourses = new list<string>();
    courseStatus = new map<pair<string,string>,bool>();
}

professor::~professor() {
    delete myCourses;
    delete courseStatus;
}

void professor::showAllCourses(university *univ) {
map<string,course*>::iterator iter = univ->courseMap->begin();
while (iter != univ->courseMap->end()) {
    cout << iter->first << endl;
    iter++;
}
cout << "There are " << univ->courseMap->size() << " courses in total." << endl;
}

void professor::showMyCourses() {
list<string>::iterator iter = myCourses->begin();
while (iter != myCourses->end()) {
    cout << *iter << endl;
    iter++;
}
cout << "There are "  << myCourses->size() << " courses." << endl;
}

bool professor::isCourseOpen(string courseName, string termName) {
bool result = false;
map<pair<string,string>,bool>::iterator iter = courseStatus->find(pair<string,string>(courseName,termName));
if (iter != courseStatus->end()) {
    result = iter->second;
} else {
    cout << "The course of this term does not exist." << endl;
}
return result;
}

void professor::endCourse(string courseName, string termName) {
map<pair<string,string>,bool>::iterator iter = courseStatus->find(pair<string,string>(courseName,termName));
if (iter != courseStatus->end()) {
    iter->second = false;
} else {
    cout << "The course of this term does not exist." << endl;
}
}

void professor::gradeCourse(university *univ, string courseName, string termName) {
map<string,course*>::iterator courseIter = univ->courseMap->find(courseName);
if (courseIter == univ->courseMap->end()) {
    cout << "This course does not exist! Please try again." << endl;
} else {
    course *target = courseIter->second;
    map<string,roster*>::iterator infoIter = target->info->find(this->name);
    if (infoIter == target->info->end()) {
        cout << "You didn't teach this course. Please try again." << endl;
    } else {
        map<pair<string,string>,bool>::iterator endStatusIter
        = courseStatus->find(pair<string,string>(courseName,termName));
        if (endStatusIter == courseStatus->end()) {
            cout << "You didn't teach this term. Please try again." << endl;
        } else if (!endStatusIter->second) {
            cout << "You have ended this course. It's read-only now." << endl;
        } else {
            roster *tempRoster = infoIter->second;
            map<string,map<string,char>*>::iterator gradeIter = tempRoster->students->find(termName);
            if (gradeIter != tempRoster->students->end()) {
                cout << "Please type a letter grade for each student." << endl;
                cout << "To keep the current letter grade, type K." << endl;
                map<string,char> *grades = gradeIter->second;
                cout << "There are " << grades->size() << " students in this class." << endl;
                map<string,char>::iterator iter = grades->begin();
                char tempGrade;
                while (iter != grades->end()) {
                    cout << "Name: " << iter->first << " Grade: " << iter->second << endl;
                    cin.sync();
                    cin >> tempGrade;
                    if (tolower(tempGrade) != 'k') {
                        iter->second = toupper(tempGrade);
                        // edit student grade map for each student
                        student *currStudent = dynamic_cast<student*>(univ->transferRole('2',iter->first));
                        map<pair<string,string>,pair<char,string>>::iterator studentIter =
                        currStudent->myCourses->find(pair<string,string>(courseName,termName));
                        studentIter->second.first = tempGrade;
                    }
                    iter++;
                }
                cout << "Would you like to end this course? y/n" << endl;
                char endChoice;
                cin.sync();
                cin >> endChoice;
                if (endChoice == 'y' || endChoice == 'Y') {
                    endCourse(courseName,termName);
                }
            } else {
                cout << "This course is not available at the specified term." << endl;
            }
        }
    }
}
}

void professor::teachCourse(university *univ, string courseName, string termName) {
if (!univ->findCourse(courseName)) {
    cout << "This course does not exist! Please try again." << endl;
} else {
    map<string,course*>::iterator courseIter = univ->courseMap->find(courseName);
    course *target = courseIter->second;
    map<string,roster*>::iterator infoIter = target->info->find(this->name);
    map<string,char> *studentMap = new map<string,char>();
    map<string,double> * TAMap = new map<string,double>();
    if (infoIter == target->info->end()) { // create a new roster
        roster *newRoster = new roster();
        newRoster->students->insert(pair<string,map<string,char>*>(termName,studentMap));
        newRoster->TAs->insert(pair<string,map<string,double>*>(termName,TAMap));
        target->info->insert(pair<string,roster*>(this->name,newRoster));

        list<string>::iterator listIter = find(myCourses->begin(),myCourses->end(),courseName);
        if (listIter == myCourses->end()) {
            myCourses->push_back(courseName);
        }
        courseStatus->insert(pair<pair<string,string>,bool>(pair<string,string>(courseName,termName),true));

        cout << "Term " << termName << " has been created for course " << courseName << "." << endl;
    } else { // add a new semester to the roster
        roster *tempRoster = infoIter->second;
        if (tempRoster->students->find(termName) == tempRoster->students->end()) {
            tempRoster->students->insert(pair<string,map<string,char>*>(termName,studentMap));
            tempRoster->TAs->insert(pair<string,map<string,double>*>(termName,TAMap));

            list<string>::iterator listIter = find(myCourses->begin(),myCourses->end(),courseName);
            if (listIter == myCourses->end()) {
                myCourses->push_back(courseName);
            }
            courseStatus->insert(pair<pair<string,string>,bool>(pair<string,string>(courseName,termName),true));

            cout << "Term " << termName << " has been created for course " << courseName << "." << endl;
        } else {
            cout << "The specified term for this course already exists!" << endl;
        }
    }
}
}

void professor::joinEvent(university *univ, string name) {
map<string,event<person>*>::iterator eventIter = univ->eventMap->find(name);
if (eventIter == univ->eventMap->end()) {
    cout << "This event does not exist!" << endl;
} else {
    event<person> *targetEvent = eventIter->second;
    bool result = targetEvent->add(this->name,this);
    cout << "Registration " << (result?"successful!":"failed! Permission denied!") << endl;
}
}

void professor::introduce() {
    cout << "I'm a professor in this university. My name is " << this->name << "." << endl;
}
