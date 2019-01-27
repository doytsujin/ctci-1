// 7.2 Call Center: Imagine you have a call center with three levels of employees

#include <iostream>
#include <vector>

#include <gtest/gtest.h>
#include "args.h"
#include "macros.h"

using namespace std;

namespace callcenter {

    struct Name {
        string first;
        string last;
    };

    class Employee 
    {
        public:
            Employee(Name name, string id, Employee *manager=nullptr) 
                : _name(name), _id(id), _manager(manager) 
            {
                _available = true;
            }

            Name getName(void) const {return _name;}
            string getId(void) const {return _id;}
            bool getAvailability(void) const {return _available;}
            Employee *getManager(void) const {return _manager;}

            void setAvailability(bool available) {_available = available;}

        protected:
            Name _name;
            string _id;
            bool _available;
            Employee *_manager;
    };

    class Respondent : public Employee
    {
        public:
            using Employee::Employee;
    };

    class Manager : public Employee
    {
        public:
            using Employee::Employee;
    };

    class Director : public Employee
    {
        public:
            using Employee::Employee;
    };

    class CallCenter
    {
        public: 
            Employee *dispatchCall(map<string, Employee *> employees) {
                map<string, Employee *> managers;
                Employee *employee = nullptr;

                for (auto &e: employees) {
                    if ( e.second->getAvailability() ) {
                        e.second->setAvailability(false);
                        employee = e.second;
                        break;
                    } else if ( e.second->getManager() ) {
                        managers[e.second->getManager()->getId()] = e.second->getManager();
                    }
                }

                if ( !employee && managers.size() ) {
                    employee = dispatchCall(managers);
                }

                return employee;
            }
    };


};

using namespace callcenter;

TEST(CallCenter, Test)
{
    Name respondent1Name = {"Emplo", "Yee"};
    string respondent1Id = "e1";

    Name respondent2Name = {"Emp", "Lyee"};
    string respondent2Id = "e2";

    Name respondent3Name = {"Emp", "Loyee"};
    string respondent3Id = "e3";

    Name manager1Name = {"Mana", "Ger"};
    string manager1Id = "m1";

    Name manager2Name = {"Man", "Ager"};
    string manager2Id = "m2";

    Name directorName = {"Dir", "Ector"};
    string directorId = "d1";

    Director director(directorName, directorId);
    Manager manager1(manager1Name, manager1Id, &director);
    Manager manager2(manager2Name, manager2Id, &director);
    Respondent respondent1(respondent1Name, respondent1Id, &manager1);
    Respondent respondent2(respondent2Name, respondent2Id, &manager2);
    Respondent respondent3(respondent3Name, respondent3Id, &manager2);

    map<string, Employee *> respondents;
    respondents[respondent1Id] = &respondent1;
    respondents[respondent2Id] = &respondent2;
    respondents[respondent3Id] = &respondent3;

    CallCenter callCenter;

    ASSERT_EQ(callCenter.dispatchCall(respondents), &respondent1);
    ASSERT_EQ(callCenter.dispatchCall(respondents), &respondent2);
    ASSERT_EQ(callCenter.dispatchCall(respondents), &respondent3);

    ASSERT_EQ(callCenter.dispatchCall(respondents), &manager1);
    ASSERT_EQ(callCenter.dispatchCall(respondents), &manager2);

    ASSERT_EQ(callCenter.dispatchCall(respondents), &director);
    ASSERT_EQ(callCenter.dispatchCall(respondents), nullptr);

    respondent2.setAvailability(true);
    ASSERT_EQ(callCenter.dispatchCall(respondents), &respondent2);
}
