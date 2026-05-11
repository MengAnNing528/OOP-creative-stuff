#include <iostream>
#include <string>
#include <limits>

using namespace std;

//Безопасный ввод
string safeString()
{
    string line;
    getline(cin, line);
    while (line.empty())
    {
        cout << "String can't be empty. Try again: ";
        getline(cin, line);
    }
    return line;
}

int safeInt()
{
    int value;
    while (true)
    {
        cin >> value;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error. Enter number: ";
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

double safeDouble()
{
    double value;
    while (true)
    {
        cin >> value;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error. Enter number: ";
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

//Класс "Издательство"
class PublishingHouse
{
protected:
    string name; // название издательства
    int foundingYear; // год основания

public:
    PublishingHouse() : name(""), foundingYear(0) {}
    PublishingHouse(const string& n, int year) : name(n), foundingYear(year) {}
    virtual ~PublishingHouse() {}

    // Геттеры и сеттеры
    void setName(const string& n) { name = n; }
    string getName() const { return name; }

    void setFoundingYear(int year) { foundingYear = year; }
    int getFoundingYear() const { return foundingYear; }

    // Уникальный метод
    void printHouseInfo() const
    {
        cout << "Publishing house: " << name << ", founded in " << foundingYear << endl;
    }

    // Методы ввода/вывода
    virtual void input()
    {
        cout << "Enter publishing house name: ";
        name = safeString();
        cout << "Enter founding year: ";
        foundingYear = safeInt();
    }

    virtual void output() const
    {
        cout << "Publishing house: " << name << ", year: " << foundingYear;
    }
};
