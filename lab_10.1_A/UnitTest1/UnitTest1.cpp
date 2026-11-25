#include "pch.h"
#include "CppUnitTest.h"

#define main LabMain
#include "C:\Users\aizen\Documents\lab c++\Lab_10\lab_10.1_A\lab_10.1_A\lab_10.1_A.cpp"
#undef main

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest101A
{
    TEST_CLASS(UnitTest101A)
    {
    public:
        TEST_METHOD(TestPercentWithoutThrees)
        {
            Student students[2] =
            {
                {"Ivanenko", 1, COMPUTER_SCIENCE, 5, 4, 5},
                {"Petrenko", 1, INFORMATICS, 3, 4, 5}
            };

            Assert::AreEqual(50.0,
                CalcPercentWithoutThrees(students, 2),
                0.001);
        }
    };
}