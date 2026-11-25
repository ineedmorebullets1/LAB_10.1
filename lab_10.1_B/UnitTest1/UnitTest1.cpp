#include "pch.h"
#include "CppUnitTest.h"

#define main LabMain
#include "C:\Users\aizen\Documents\lab c++\Lab_10\lab_10.1_B\lab_10.1_B\lab_10.1_B.cpp"
#undef main

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest101B
{
    TEST_CLASS(UnitTest101B)
    {
    public:
        TEST_METHOD(TestPercentWithoutThrees)
        {
            Student p[2];

            p[0].specialty = COMPUTER_SCIENCE;
            p[0].physics = 5;
            p[0].math = 4;
            p[0].programming = 5;

            p[1].specialty = INFORMATICS;
            p[1].physics = 4;
            p[1].math = 5;
            p[1].numericalMethods = 3;

            Assert::AreEqual(50.0,
                CalcPercentWithoutThrees(p, 2), 0.001);
        }
    };
}