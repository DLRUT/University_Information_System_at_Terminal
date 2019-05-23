#ifndef PRESIDENT_H
#define PRESIDENT_H

#include <string>
#include "staff.h"
#include "university.h"

using namespace std;

class president : public staff
{

    public:
        president(string);
        ~president();
        virtual void introduce();
        void addPerson(university*,string,char);
        void removePerson(university*,string,char);
        void addCourse(university*,string);
        void removeCourse(university*,string);
        void addEvent(university*,string,char);
        void removeEvent(university*,string);
        void endEvent(university*,string);
        void joinEvent(university*,string);
        void recordPeople(university*);
        void recordCourses(university*);
        void recordEvents(university*);

    protected:
        string name;
    private:

};


#endif // PRESIDENT_H

