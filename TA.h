#ifndef TA_H
#define TA_H

#include <string>
#include "student.h"

using namespace std;

class TA : public student
{
    public:
        TA();
        TA(string);
        virtual ~TA();
        virtual void introduce();
    protected:
        string name;
    private:
};

#endif // TA_H

