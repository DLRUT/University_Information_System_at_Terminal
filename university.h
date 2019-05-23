#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include <map>
#include <string>
#include "person.h"
#include "course.h"
#include "event.h"

using namespace std;

class university
{
    friend class president;
    friend class professor;
    friend class student;
    public:
        university();
        ~university();
        bool findPerson(string,char);
        bool findCourse(string);
        void displayEvent(string);
        void displayInformation(string,char);
        void changePresident(string);
        person* transferRole(char,string);
    protected:
    private:
        map<string,person*> *personMap;
        map<string,course*> *courseMap;
        map<string,event<person>*> *eventMap;
        string name;
        string realTitle(string,char);
};

#endif // UNIVERSITY_H
