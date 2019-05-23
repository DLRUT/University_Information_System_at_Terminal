#ifndef STAFF_H
#define STAFF_H

#include <string>
#include "person.h"

using namespace std;

class staff : public person
{

    public:
        staff();
        staff(string);
        ~staff();
        virtual void introduce();

    protected:
        string name;
    private:

};


#endif // STAFF_H

