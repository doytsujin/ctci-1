// Citc exercise
// 

#include <iostream>
#include <vector>

#include <gtest/gtest.h>
#include "args.h"
#include "macros.h"

using namespace std;

// This is all up to you
class Problem {
    public:
        bool solution(bool throwError) 
        {
            if ( throwError ) {
                throw "No solution found";
            }
            return throwError;
        }
};


TEST(Problem, CorrectTest)
{
    Problem problem;
    bool correct = true;

    try {
        ASSERT_EQ(problem.solution(false), correct);
    } catch (const exception &e) {
        std::cout << "Problem.CorrectTest: Exception - " << e.what() << endl;
    }
}


TEST(Problem, NoSolution)
{
    bool exceptionThrown = false;
    bool ignoreAnswer = true;

    try {
        Problem problem;
        ignoreAnswer = problem.solution(true);
    } catch (const exception &e) {
        exceptionThrown = true;
    }

    ASSERT_EQ(exceptionThrown, true);
}
