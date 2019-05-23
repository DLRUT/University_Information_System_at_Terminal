#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include "person.h"
#include "course.h"
#include "roster.h"
#include "university.h"

using namespace std;

class student : public person
{

    public:
        friend class professor;
        student();
        student(string);
        ~student();
        void takeCourse(university*,string,string);
        void dropCourse(university*,string,string);
        void joinEvent(university*,string);
        void viewCourse();
        void viewGrade();
        virtual void introduce();

    protected:
        string name;
    private:
        map<pair<string,string>,pair<char,string>> *myCourses;
};


#endif // STUDENT_H



