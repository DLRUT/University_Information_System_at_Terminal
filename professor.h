#ifndef PROFESSOR_H
#define PROFESSOR_H

#include <string>
#include <list>
#include "person.h"
#include "university.h"

#define DEFAULT_GRADE '#'

class professor : public person
{
    public:
        professor();
        professor(string);
        ~professor();
        void showAllCourses(university*);
        void showMyCourses();
        bool isCourseOpen(string,string);
        void endCourse(string,string);
        void gradeCourse(university*, string, string);
        void teachCourse(university*, string, string);
        void joinEvent(university*, string);
        virtual void introduce();
    protected:
        string name;
    private:
        list<string> *myCourses;
        map<pair<string,string>,bool> *courseStatus;
};


#endif // PROFESSOR_H
