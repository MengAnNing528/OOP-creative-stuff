#include <iostream>
#include <string>
#include <limits>

using namespace std;

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

class Athor
{
private:
    string  AthorName;
    string AthorCountry;

public:
    Athor(): AthorName("-"), AthorCountry("-") {}
    Athor(const string& AN, const string& AC) {
        AthorName = AN;
        AthorCountry = AC;
    }
    virtual ~ Athor() {}
     
    void setName(const string& AN) {AthorName = AN;}
    string getName() const {return AthorName;}

    void setCountry(const string& AC) {AthorCountry = AC;}
    string getCountry() const {return AthorCountry;}

    void PrintInfoAthor() {
        cout<<"ФИО автора:"<< AthorName << ", страна :" << AthorCountry << endl;
    }

    virtual void InInfo() {
        cout << "Введите ФИО автора:"<< endl;
        AthorName = safeString();
        cout <<"Введити родную страну автора:"<<endl;
        AthorCountry = safeString();
    }

    virtual void OutInfo() {
        cout << "---Информация об авторе--" <<endl;
        cout<<"ФИО:"<<AthorName<<endl;
        cout<<"Родная страна"<<AthorCountry<<endl;
    }
}
