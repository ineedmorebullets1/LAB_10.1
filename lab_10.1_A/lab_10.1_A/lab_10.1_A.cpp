
#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
using namespace std;

enum Specialty
{
    COMPUTER_SCIENCE, INFORMATICS, MATH_ECONOMICS,
    PHYSICS_INFORMATICS, LABOR_TRAINING
};

struct Student
{
    string surname;
    int course = 0;
    Specialty specialty = COMPUTER_SCIENCE;
    int physics = 0;
    int math = 0;
    int informatics = 0;
};

string GetSpecialtyName(Specialty s)
{
    switch (s)
    {
    case COMPUTER_SCIENCE: return "Комп'ютерні науки";
    case INFORMATICS: return "Інформатика";
    case MATH_ECONOMICS: return "Математика та економіка";
    case PHYSICS_INFORMATICS: return "Фізика та інформатика";
    case LABOR_TRAINING: return "Трудове навчання";
    }
    return "";
}

bool Create(Student* p, int n)
{
    for (int i = 0; i < n; i++)
    {
        int spec = 0;

        cout << "\nСтудент №" << i + 1 << endl;
        cout << "Прізвище: ";
        getline(cin >> ws, p[i].surname);

        cout << "Курс (1-6): "; cin >> p[i].course;

        cout << "0 - Комп'ютерні науки\n"
            << "1 - Інформатика\n"
            << "2 - Математика та економіка\n"
            << "3 - Фізика та інформатика\n"
            << "4 - Трудове навчання\n";

        cout << "Спеціальність: "; cin >> spec;

        if (!cin || spec < 0 || spec > 4)
            return false;

        p[i].specialty = static_cast<Specialty>(spec);

        cout << "Оцінка з фізики: "; cin >> p[i].physics;
        cout << "Оцінка з математики: "; cin >> p[i].math;
        cout << "Оцінка з інформатики: "; cin >> p[i].informatics;

        if (!cin || p[i].course < 1 || p[i].course > 6 ||
            p[i].physics < 2 || p[i].physics > 5 ||
            p[i].math < 2 || p[i].math > 5 ||
            p[i].informatics < 2 || p[i].informatics > 5)
            return false;
    }
    return true;
}

void Print(const Student* p, int n)
{
    cout << "\nСПИСОК СТУДЕНТІВ\n";
    cout << string(95, '=') << endl;

    cout << "| " << setw(3) << left << "№"
        << " | " << setw(16) << "Прізвище"
        << " | " << setw(4) << "Курс"
        << " | " << setw(23) << "Спеціальність"
        << " | " << setw(6) << "Фізика"
        << " | " << setw(10) << "Математика"
        << " | " << setw(11) << "Інформатика" << " |\n";

    cout << string(95, '-') << endl;

    for (int i = 0; i < n; i++)
    {
        cout << "| " << setw(3) << right << i + 1
            << " | " << setw(16) << left << p[i].surname
            << " | " << setw(4) << right << p[i].course
            << " | " << setw(23) << left
            << GetSpecialtyName(p[i].specialty)
            << " | " << setw(6) << right << p[i].physics
            << " | " << setw(10) << p[i].math
            << " | " << setw(11) << p[i].informatics
            << " |\n";
    }

    cout << string(95, '=') << endl;
}

double CalcPercentWithoutThrees(const Student* p, int n)
{
    int k = 0;

    for (int i = 0; i < n; i++)
        if (p[i].physics >= 4 && p[i].math >= 4 &&
            p[i].informatics >= 4)
            k++;

    return n > 0 ? 100.0 * k / n : 0.0;
}

void PrintSurnamesWithHighPhysics(const Student* p, int n)
{
    cout << "\nСтуденти з оцінкою 5 або 4 з фізики:\n";

    for (int i = 0; i < n; i++)
        if (p[i].physics == 5 || p[i].physics == 4)
            cout << p[i].surname << endl;
}

int main()
{
    if (!SetConsoleCP(1251) || !SetConsoleOutputCP(1251))
        return 1;

    int n = 0;
    cout << "Кількість студентів: "; cin >> n;

    if (!cin || n <= 0)
        return 1;

    Student* p = new Student[n];

    if (!Create(p, n))
    {
        cout << "Некоректні дані!" << endl;
        delete[] p;
        return 1;
    }

    Print(p, n);

    cout << fixed << setprecision(2);
    cout << "\nВідсоток студентів без трійок: "
        << CalcPercentWithoutThrees(p, n) << "%\n";

    PrintSurnamesWithHighPhysics(p, n);

    delete[] p;
    return 0;
}
