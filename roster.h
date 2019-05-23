#ifndef ROSTER_H
#define ROSTER_H

#include <string>
#include <map>

using namespace std;

class roster
{
    friend class president;
    friend class professor;
    friend class student;
    public:
        virtual ~roster();
        virtual void introduce();
    protected:
    private:
        map<string, map<string, char>*> *students;
        map<string, map<string, double>*> *TAs;
        roster();
        roster(roster&);
};

#endif // ROSTER_H

