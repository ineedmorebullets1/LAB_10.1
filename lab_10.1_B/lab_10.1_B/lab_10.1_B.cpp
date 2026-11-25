
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

    union
    {
        int programming = 0;
        int numericalMethods;
        int pedagogy;
    };
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
        int spec = 0, grade = 0;

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

        switch (p[i].specialty)
        {
        case COMPUTER_SCIENCE:
            cout << "Оцінка з програмування: "; break;
        case INFORMATICS:
            cout << "Оцінка з чисельних методів: "; break;
        default:
            cout << "Оцінка з педагогіки: "; break;
        }

        cin >> grade;

        if (!cin || p[i].course < 1 || p[i].course > 6 ||
            p[i].physics < 2 || p[i].physics > 5 ||
            p[i].math < 2 || p[i].math > 5 ||
            grade < 2 || grade > 5)
            return false;

        switch (p[i].specialty)
        {
        case COMPUTER_SCIENCE: p[i].programming = grade; break;
        case INFORMATICS: p[i].numericalMethods = grade; break;
        default: p[i].pedagogy = grade; break;
        }
    }
    return true;
}

int GetThirdGrade(const Student& s)
{
    switch (s.specialty)
    {
    case COMPUTER_SCIENCE: return s.programming;
    case INFORMATICS: return s.numericalMethods;
    default: return s.pedagogy;
    }
}

void Print(const Student* p, int n)
{
    cout << "\nСПИСОК СТУДЕНТІВ\n";
    cout << string(128, '=') << endl;

    cout << "| " << setw(3) << left << "№"
        << " | " << setw(16) << "Прізвище"
        << " | " << setw(4) << "Курс"
        << " | " << setw(23) << "Спеціальність"
        << " | " << setw(6) << "Фізика"
        << " | " << setw(10) << "Математика"
        << " | " << setw(13) << "Програмування"
        << " | " << setw(15) << "Чисельні методи"
        << " | " << setw(10) << "Педагогіка" << " |\n";

    cout << string(128, '-') << endl;

    for (int i = 0; i < n; i++)
    {
        const Student& s = p[i];

        cout << "| " << setw(3) << right << i + 1
            << " | " << setw(16) << left << s.surname
            << " | " << setw(4) << right << s.course
            << " | " << setw(23) << left << GetSpecialtyName(s.specialty)
            << " | " << setw(6) << right << s.physics
            << " | " << setw(10) << s.math
            << " | " << setw(13)
            << (s.specialty == COMPUTER_SCIENCE ? to_string(s.programming) : "")
            << " | " << setw(15)
            << (s.specialty == INFORMATICS ? to_string(s.numericalMethods) : "")
            << " | " << setw(10)
            << (s.specialty != COMPUTER_SCIENCE && s.specialty != INFORMATICS
                ? to_string(s.pedagogy) : "") << " |\n";
    }

    cout << string(128, '=') << endl;
}

double CalcPercentWithoutThrees(const Student* p, int n)
{
    int k = 0;
    for (int i = 0; i < n; i++)
        if (p[i].physics >= 4 && p[i].math >= 4 &&
            GetThirdGrade(p[i]) >= 4)
            k++;

    return n > 0 ? 100.0 * k / n : 0.0;
}

void PrintSurnamesWithHighPhysics(const Student* p, int n)
{
    cout << "\nСтуденти з оцінкою 5 або 4 з фізики:\n";

    for (int i = 0; i < n; i++)
        if (p[i].physics == 4 || p[i].physics == 5)
            cout << p[i].surname << endl;
}

int main()
{
    if (!SetConsoleCP(1251) || !SetConsoleOutputCP(1251))
        return 1;

    int n = 0;
    cout << "Кількість студентів: ";
    cin >> n;

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
