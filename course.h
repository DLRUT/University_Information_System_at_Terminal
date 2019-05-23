#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <map>
#include "roster.h"

using namespace std;

class course
{
    friend class president;
    friend class professor;
    friend class student;
    public:
        course();
        course(string);
        virtual ~course();
        virtual void introduce();
    protected:
        string name;
    private:
        map<string, roster*> *info;
};

#endif // COURSE_H
