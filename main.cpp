#include <iostream>
#include <map>
#include <exception>
#include "university.h"
#include "president.h"
#include "professor.h"
#include "student.h"
#include "course.h"
#include "event.h"

using namespace std;

enum president_t {CHOOSE, ADD_A_PERSON, REMOVE_A_PERSON, ADD_A_COURSE, \
REMOVE_A_COURSE, ADD_AN_EVENT, REMOVE_AN_EVENT, PARTICIPATE_AN_EVENT, END_AN_EVENT, \
HOLD_A_MEETING, RECORD_PEOPLE, RECORD_COURSES, RECORD_EVENTS, QUIT};

void showNext();
void presidentPanel();
void professorPanel(string);
void studentPanel(string);

int main()
{
    university *univ;
    cout << "Welcome to virtual university system!" << endl;
    cout << "Would you like to start to create a university? y/n" << endl;
    char choice;
    cin >> choice; // no need to catch exception
    if (cin.rdstate() != ios::goodbit || (choice != 'y' && choice != 'Y')) {
        return 0;
    } else {
        univ = new university();
    }

    char nextChoice;
    bool quit = false;
    while(!quit) {
        showNext();
        cin.sync();
        cin.get(nextChoice);
        switch (nextChoice) {
            case '1': // become the president
                {
                bool nextMove = true;
                president *currHead = dynamic_cast<president*>(univ->transferRole('3',""));
                while (nextMove) {
                    presidentPanel();
                    int presidentChoice = 0;
                    cin.sync();
                    cin >> presidentChoice;
                    if (!cin) {
                        cin.clear();
                        cin.sync();
                    }
                    switch (presidentChoice) {
                    case president_t::ADD_A_PERSON: // add a person
                        {
                        string tempName;
                        cout << "Please enter the data of the people you would like to add in " <<
                        "the following format:" << endl;
                        cout << "name(space)number (corresponding to the title)" << endl;
                        cout << "Type \"end\" to end input." << endl;

                        while (tempName != "end") {
                            cin.sync();
                            getline(cin,tempName);
                            if (tempName != "end") {
                                size_t found = tempName.find_last_of("123");
                                char initial = tempName[0];
                                if (found != string::npos && found > 1 && tempName[found-1] == ' '
                                    && ((initial >= 'A' && initial <= 'Z')
                                         || (initial >= 'a' && initial <= 'z'))) {
                                    int length = tempName.length();
                                    string onlyName = tempName.substr(0,length - 2);

                                    currHead->addPerson(univ,onlyName,tempName[found]);

                                } else {
                                    cout << "Input error! Please try again!" << endl;
                                }
                            }
                            cin.clear();
                            cin.sync();
                        }
                        }
                        break;
                    case president_t::REMOVE_A_PERSON: // remove a person
                        {
                        string tempName = "";
                        cout << "Please enter the data of the people you would like to remove in " <<
                        "the following format:" << endl;
                        cout << "name(space)number (corresponding to the title)" << endl;
                        cout << "Type \"end\" to end input." << endl;

                        while (tempName != "end") {
                            cin.sync();
                            getline(cin,tempName);
                            if (tempName != "end") {
                                size_t found = tempName.find_last_of("123");
                                char initial = tempName[0];
                                if (found != string::npos && found > 1 && tempName[found-1] == ' '
                                    && ((initial >= 'A' && initial <= 'Z')
                                         || (initial >= 'a' && initial <= 'z'))) {
                                    int length = tempName.length();
                                    string onlyName = tempName.substr(0,length - 2);

                                    currHead->removePerson(univ,onlyName,tempName[found]);

                                } else {
                                    cout << "Input error! Please try again!" << endl;
                                }
                            }
                            cin.clear();
                            cin.sync();
                        }
                        }
                        break;
                    case president_t::ADD_A_COURSE: // add a course
                        {
                        string tempName;
                        cout << "Please enter the name of the course you would like to add." << endl;
                        cout << "Type \"end\" to end input." << endl;

                        while (tempName != "end") {
                            cin.sync();
                            getline(cin,tempName);
                            if (tempName != "end") {
                                currHead->addCourse(univ,tempName);
                            }
                            cin.clear();
                            cin.sync();
                        }
                        }
                        break;
                    case president_t::REMOVE_A_COURSE: // remove a course
                        {
                        string tempName;
                        cout << "Please enter the name of the course you would like to remove." << endl;
                        cout << "Type \"end\" to end input." << endl;

                        while (tempName != "end") {
                            cin.sync();
                            getline(cin,tempName);
                            if (tempName != "end") {
                                currHead->removeCourse(univ,tempName);
                            }
                            cin.clear();
                            cin.sync();
                        }
                        }
                        break;
                    case president_t::ADD_AN_EVENT: // add an event
                        {
                        string tempName;
                        cout << "Please enter the data of the event you would like to add in " <<
                        "the following format:" << endl;
                        cout << "name(space)number (corresponding to the restriction below)" << endl;
                        cout << "1) All people 2) Professors only 3) Students only" << endl;
                        cout << "Type \"end\" to end input." << endl;

                        while (tempName != "end") {
                            cin.sync();
                            getline(cin,tempName);
                            if (tempName != "end") {
                                size_t found = tempName.find_last_of("123");
                                char initial = tempName[0];
                                if (found != string::npos && found > 1 && tempName[found-1] == ' '
                                    && ((initial >= 'A' && initial <= 'Z')
                                         || (initial >= 'a' && initial <= 'z'))) {
                                    int length = tempName.length();
                                    string onlyName = tempName.substr(0,length - 2);

                                    currHead->addEvent(univ,onlyName,tempName[found]);

                                } else {
                                    cout << "Input error! Please try again!" << endl;
                                }
                            }
                            cin.clear();
                            cin.sync();
                        }
                        }
                        break;
                    case president_t::REMOVE_AN_EVENT: // remove an event
                        {
                        string tempName;
                        cout << "Please enter the name of the event you would like to remove." << endl;
                        cout << "Type \"end\" to end input." << endl;

                        while (tempName != "end") {
                            cin.sync();
                            getline(cin,tempName);
                            if (tempName != "end") {
                                currHead->removeEvent(univ,tempName);
                            }
                            cin.clear();
                            cin.sync();
                        }
                        }
                        break;
                    case president_t::PARTICIPATE_AN_EVENT: // participate an event
                        {
                        string tempName;
                        cout << "Please enter the name of the event you would like to participate." << endl;
                        cout << "Type \"end\" to end input." << endl;

                        while (tempName != "end") {
                            cin.sync();
                            getline(cin,tempName);
                            if (tempName != "end") {
                                currHead->joinEvent(univ,tempName);
                            }
                            cin.clear();
                            cin.sync();
                        }
                        }
                        break;
                    case president_t::END_AN_EVENT: // end an event
                        {
                        string tempName;
                        cout << "Please enter the name of the course you would like to end." << endl;
                        cout << "Type \"end\" to end input." << endl;

                        while (tempName != "end") {
                            cin.sync();
                            getline(cin,tempName);
                            if (tempName != "end") {
                                currHead->endEvent(univ,tempName);
                            }
                            cin.clear();
                            cin.sync();
                        }
                        }
                        break;
                    case president_t::HOLD_A_MEETING: // hold a meeting
                        currHead->introduce();
                        break;
                    case president_t::RECORD_PEOPLE: // record people
                        currHead->recordPeople(univ);
                        break;
                    case president_t::RECORD_COURSES: // record courses
                        currHead->recordCourses(univ);
                        break;
                    case president_t::RECORD_EVENTS: // record events
                        currHead->recordEvents(univ);
                        break;
                    case president_t::QUIT:  // quit
                        nextMove = false;
                        break;
                    default:
                        cout << "Type Error! Please try again!" << endl;
                        break;
                    }
                }
                }
                break;
            case '2': // become a professor
                {
                    bool nextMove = true;
                    cout << "Please type the name of the professor you would like to become." << endl;
                    string tempName;
                    string courseName = "";
                    cin.sync();
                    getline(cin,tempName);
                    if (univ->findPerson(tempName,'1')) {
                        professor *currProf = dynamic_cast<professor*>(univ->transferRole('1',tempName));
                        while (nextMove) {
                            professorPanel(tempName);
                            int professorChoice = 0;
                            cin.sync();
                            try {
                                cin >> professorChoice;
                                if (!cin) {
                                    cin.clear(); // must be included
                                    throw 6.096;
                                }
                                if (professorChoice <= 0 || professorChoice > 7) {
                                    cout << professorChoice << endl;
                                    throw exception();
                                }
                                switch (professorChoice) {
                                    case 1: // teach a course
                                        {
                                        courseName = "";
                                        while (courseName != "end") {
                                            cout << "Please enter the name of the course." << endl;
                                            cout << "You can type \"end\" to quit." << endl;
                                            cin.sync();
                                            getline(cin,courseName);
                                            if (courseName != "end") {
                                                string termName;
                                                cout << "Please enter the semester name of this course "
                                                << "in the following format(e.g.): 2017fall" << endl;
                                                cin.sync();
                                                getline(cin,termName);
                                                currProf->teachCourse(univ,courseName,termName);
                                            }
                                        }
                                        }
                                        break;
                                    case 2: // view all courses
                                        currProf->showAllCourses(univ);
                                        break;
                                    case 3: // view my courses
                                        currProf->showMyCourses();
                                        break;
                                    case 4: // grade a course
                                        {
                                        courseName = "";
                                        while (courseName != "end") {
                                            cout << "Please enter the name of the course." << endl;
                                            cout << "You can type \"end\" to quit." << endl;
                                            cin.sync();
                                            getline(cin,courseName);
                                            if (courseName != "end") {
                                                string termName;
                                                cout << "Please enter the semester name of this course "
                                                << "in the following format(e.g.): 2017fall" << endl;
                                                cin.sync();
                                                getline(cin,termName);
                                                currProf->gradeCourse(univ,courseName,termName);
                                            }
                                        }
                                        }
                                        break;
                                    case 5: // recruit TAs
                                        break;
                                    case 6: // participate an event
                                        {
                                        string tempName;
                                        cout << "Please enter the name of the event you would like to participate." << endl;
                                        cout << "Type \"end\" to end input." << endl;

                                        while (tempName != "end") {
                                            cin.sync();
                                            getline(cin,tempName);
                                            if (tempName != "end") {
                                                currProf->joinEvent(univ,tempName);
                                            }
                                            cin.clear();
                                            cin.sync();
                                        }
                                        }
                                        break;
                                    case 7: // quit
                                        nextMove = false;
                                        break;
                                    default:
                                        break;
                                }
                            } catch (double) {
                                cout << "Input Error! Please try again!" << endl;
                            } catch (...) {
                                cout << "Input out of range! Please try again!" << endl;
                            }
                        }
                    } else {
                        cout << "Person not found! Please try again!" << endl;
                    }
                }
                break;
            case '3': // become a student
                {
                bool nextMove = true;
                    cout << "Please type the name of the student you would like to become." << endl;
                    string tempName;
                    string courseName = "";
                    cin.sync();
                    getline(cin,tempName);
                    if (univ->findPerson(tempName,'2')) {
                        student *currStudent = dynamic_cast<student*>(univ->transferRole('2',tempName));
                        while (nextMove) {
                            studentPanel(tempName);
                            int studentChoice = 0;
                            cin.sync();
                            cin >> studentChoice;
                            if (!cin) { // no need to catch an exception
                                cin.clear();
                                cin.sync();
                            }
                            switch (studentChoice) {
                            case 1: // take a course
                                {
                                courseName = "";
                                    while (courseName != "end") {
                                        cout << "Please enter the name of the course you wish to take." << endl;
                                        cout << "You can type \"end\" to quit." << endl;
                                        cin.sync();
                                        getline(cin,courseName);
                                        if (courseName != "end") {
                                            string termName;
                                            cout << "Please enter the semester name of this course "
                                            << "in the following format(e.g.): 2017fall" << endl;
                                            cin.sync();
                                            getline(cin,termName);
                                            currStudent->takeCourse(univ,courseName,termName);
                                        }
                                    }
                                }
                                break;
                            case 2: // view my courses
                                currStudent->viewCourse();
                                break;
                            case 3: // view my grades
                                currStudent->viewGrade();
                                break;
                            case 4: // drop a course
                                {
                                courseName = "";
                                    while (courseName != "end") {
                                        cout << "Please enter the name of the course you wish to drop." << endl;
                                        cout << "You can type \"end\" to quit." << endl;
                                        cin.sync();
                                        getline(cin,courseName);
                                        if (courseName != "end") {
                                            string termName;
                                            cout << "Please enter the semester name of this course "
                                            << "in the following format(e.g.): 2017fall" << endl;
                                            cin.sync();
                                            getline(cin,termName);
                                            currStudent->dropCourse(univ,courseName,termName);
                                        }
                                    }
                                }
                                break;
                            case 5: // apply to be a TA
                                break;
                            case 6: // participate an event
                                {
                                string tempName;
                                cout << "Please enter the name of the event you would like to participate." << endl;
                                cout << "Type \"end\" to end input." << endl;

                                while (tempName != "end") {
                                    cin.sync();
                                    getline(cin,tempName);
                                    if (tempName != "end") {
                                        currStudent->joinEvent(univ,tempName);
                                    }
                                    cin.clear();
                                    cin.sync();
                                }
                                }
                                break;
                            case 7: // quit
                                nextMove = false;
                                break;
                            default:
                                cout << "Input error! Please try again!" << endl;
                                break;
                            }
                        }
                    } else {
                        cout << "Person not found! Please try again!" << endl;
                    }
                }
                break;
            case '4': // find a person
                {
                string name;
                cout << "Please type the name and job title number separated with a space." << endl;
                cout << "1) professor 2) student 3) staff" << endl;
                cin.sync();
                getline(cin,name);
                int length = name.length();
                univ->displayInformation(name.substr(0, length - 2), name[length - 1]);
                }
                break;
            case '5': // find a course
                {
                string name;
                cout << "Please type the name of the course." << endl;
                cin.sync();
                getline(cin,name);
                if (univ->findCourse(name)) {
                    cout << "Course " << name << " is found!" << endl;
                } else {
                    cout << "Course " << name << " is not found!" << endl;
                }
                }
                break;
            case '6': // find an event
                {
                string name;
                cout << "Please type the name of the event." << endl;
                cin.sync();
                getline(cin,name);
                univ->displayEvent(name);
                }
                break;
            case '7': // set a new president
                {
                    cout << "What's the name of the new president?" << endl;
                    string name;
                    cin.sync();
                    getline(cin,name);
                    univ->changePresident(name);
                }
                break;
            case '8': // quit
                quit = true;
                break;
            default:
                cout << "Type Error! You typed " << nextChoice  << "." << endl;
                break;
        }
    }
    return 0;
}

void presidentPanel() {
    cout << endl;
    cout << "You are the president. What would you like to do? Please type a number." << endl;
    cout << "1) Add a person 2) Remove a person 3) Add a course 4) Remove a course" << endl;
    cout << "5) Add an event 6) Remove an event 7) Participate an event 8) End an event" << endl;
    cout << "9) Hold a meeting 10) Record people 11) Record courses 12) Record events" << endl;
    cout << "13) Quit" << endl;
}

void professorPanel(string name) {
    cout << endl;
    cout << "You are professor " << name << ". What would you like to do? Please type a number." << endl;
    cout << "1) Teach a course 2) View all courses 3) View my courses" << endl;
    cout << "4) Grade a course 5) Recruit TAs 6) Participate an event" << endl;
    cout << "7) Quit" << endl;
}

void studentPanel(string name) {
    cout << endl;
    cout << "You are student " << name << ". What would you like to do? Please type a number." << endl;
    cout << "1) Take a course 2) View my courses 3) View my grades" << endl;
    cout << "4) Drop a course 5) Apply to be a TA 6) Participate an event" << endl;
    cout << "7) Quit" << endl;
}

void showNext() {
    cout << endl;
    cout << "What would you like to do now? Please type a number." << endl;
    cout << "1) Become the president 2) Become a professor 3) Become a student" << endl;
    cout << "4) Find a person 5) Find a course 6) Find an event" << endl;
    cout << "7) Set a new president 8) Quit" << endl;
}
