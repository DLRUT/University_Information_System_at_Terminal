#ifndef PERSON_H
#define PERSON_H

#include <string>

using namespace std;

class person
{
    public:
        person();
        person(string);
        virtual ~person();
        virtual void introduce();
    protected:
        string name;
    private:
};

#endif // PERSON_H
