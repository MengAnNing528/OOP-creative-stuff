//Деятельность хоккейного клуба по учету игроков, у которых
//действующие контракты(вратари, защитники, нападающие).Необходимо
//выдать список игроков заданного амплуа, название которого получено с
//помощью ввода с консоли

#include <iostream>
#include<string>

using namespace std;

//=================================================
//Secure input helper features
//=================================================
string safeString()
{
    string line;
    getline(cin, line);
    while (line.empty())
    {
        cout << "String can't be empty. Try again: ";
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
            cin.ignore(numeric_limits <streamsize> ::max(), '\n');
            cout << "Error. Enter number: ";
        }
        else
        {
            cin.ignore(numeric_limits <streamsize> ::max(), '\n');
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
            cout << "Error. Enter number: ";
        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

//=================================================
//Basic abstract class: MusicTrack
//=================================================
class Player
{
private:
    string PlayerName;
    string PlayerTeam;
    int PlayerAge;
    int PlayerNumber;
    int PlayerSalary;
    double PlayerContractTerm;
public:
    //constructor with parameters
    Player(string name, string team, int age, int number, int salary, double contr_term)
    {
        PlayerName = name;
        PlayerTeam = team;

        if (age >= 18 && age <= 55)
        {
            PlayerAge = age;
        }
        else
        {
            age = 0;
            cout << "Player should be older than 18 y/o" << endl;
        }

        if (number >= 0 && number <= 99)
        {
            PlayerNumber = number;
        }
        else
        {
            number = 0;
            cout << "Number cannot be negative" << endl;
        }

        if (salary >= 0)
        {
            PlayerSalary = salary;
        }
        else
        {
            salary = 0;
            cout << "Salary cannot be negative" << endl;
        }
    }

    //default constructor
    Player()
    {
        PlayerName = "Ivanov Ivan Ivanych";
        PlayerTeam = "Ack Bars";
        PlayerAge = 18;
        PlayerNumber = 0;
        PlayerSalary = 100000;
        PlayerContractTerm = 1.5;
    }

    //virtual deconstructor, because of polymorthism
    virtual ~Player()
    {
        cout << PlayerName << " ended his career!" << endl;
    }

    //getters
    string getPlayerName()
    {
        return PlayerName;
    }
    string getPlayerTeam()
    {
        return PlayerTeam;
    }
    int getPlayerAge()
    {
        return PlayerAge;
    }
    int getPlayerNumber()
    {
        return PlayerNumber;
    }
    int getPlayerSalary()
    {
        return PlayerSalary;
    }
    double getPlayerContractTerm()
    {
        return PlayerContractTerm;
    }

    //setters
    void setPlayerName(string name)
    {
        PlayerName = name;
    }
    void setPlayerTeam(string team)
    {
        PlayerTeam = team;
    }
    void setPlayerAge(int age)
    {
        PlayerAge = age;
    }
    void setPlayerNumber(int number)
    {
        PlayerNumber = number;
    }
    void setPlayerSalary(int salary)
    {
        PlayerSalary = salary;
    }
    void setPlayerContractTerm(double contr_term)
    {
        PlayerContractTerm = contr_term;
    }

    virtual void getResults()
    {
        cout << "All Players are qualified" << endl;
    }

    virtual void printInfo()
    {
        cout << "-----------------------------------------------" << endl;
        cout << "|                  Player's Info              |" << endl;
        cout << "-----------------------------------------------" << endl;
        cout << " Name         : " << PlayerName << endl;
        cout << " Team         : " << PlayerTeam << endl;
        cout << " Age          : " << PlayerAge << endl;
        cout << " Number       : " << PlayerNumber << endl;
        cout << " Salary       : " << PlayerSalary << endl;
        cout << " Contract Term: " << PlayerContractTerm << "years" << endl;
        cout << "-----------------------------------------------" << endl;
    }
};

//=================================================
//Derived class: Goalie
//=================================================
class Goalie : public Player
{ 
private:
    int GoalsLoss;
    double SavePercentage;
    int Shutouts;
public:
    Goalie(string name, string team, int age, int number,
        int salary, double contr_term,
        int goalsLoss, double saved, int shutouts)
        : Player(name, team, age, number, salary, contr_term)
    {
        if (goalsLoss >= 0)
        {
            GoalsLoss = goalsLoss;
        }
        else
        {
            GoalsLoss = 0;
            cout << "Incorrect number of goals!" << endl;
        }

        if (saved >= 0)
        {
            SavePercentage = saved;
        }
        else
        {
            SavePercentage = 0;
            cout << "Incorrect percentage of saved goals!" << endl;
        }

        if (shutouts >= 0)
        {
            Shutouts = shutouts;
        }
        else
        {
            Shutouts = 0;
            cout << "Incorrect number of shutouts!" << endl;
        }
    }

    void getResults() override
    {
        cout << "-----------------------------------------------" << endl;
        cout << "|               Player's Results              |" << endl;
        cout << "-----------------------------------------------" << endl;
        cout << " Player           : " << getPlayerName() << endl;
        cout << " Team             : " << getPlayerTeam() << endl;
        cout << " Age              : " << getPlayerAge() << endl;
        cout << " Number           : " << getPlayerNumber() << endl;
        cout << " Goal loss        : " << GoalsLoss << endl;
        cout << " Saved percentage : " << SavePercentage << "%" << endl;
        cout << " Shutout games    : " << Shutouts << endl;
        cout << "-----------------------------------------------" << endl;
    }
};

//=================================================
//Derived class: Defender
//=================================================
class Defender : Player
{ 
private:
    int Goals;
    int Assists;
    int Hits;
    int BlockedShots;
public:
    Defender(string name, string team, int age, int number,
        int salary, double contr_term,
        int goals, int assists, int hits, int blocked)
        : Player(name, team, age, number, salary, contr_term)
    {
        if (goals >= 0)
        {
            Goals = goals;
        }
        else
        {
            Goals = 0;
            cout << "Incorrect number of goals!" << endl;
        }

        if (assists >= 0)
        {
            Assists = assists;
        }
        else
        {
            Assists = 0;
            cout << "Incorrect number of assists!" << endl;
        }

        if (hits >= 0)
        {
            Hits = hits;
        }
        else
        {
            Hits = 0;
            cout << "Incorrect number of hits!" << endl;
        }

        if (blocked >= 0)
        {
            BlockedShots = blocked;
        }
        else
        {
            BlockedShots = 0;
            cout << "Incorrect number of blocked shots!" << endl;
        }
    }

    void getResults() override
    {
        cout << "-----------------------------------------------" << endl;
        cout << "|               Player's Results              |" << endl;
        cout << "-----------------------------------------------" << endl;
        cout << " Player        : " << getPlayerName() << endl;
        cout << " Team          : " << getPlayerTeam() << endl;
        cout << " Age           : " << getPlayerAge() << endl;
        cout << " Number        : " << getPlayerNumber() << endl;
        cout << " Goals         : " << Goals << endl;
        cout << " Assists       : " << Assists << endl;
        cout << " Hits          : " << Hits << endl;
        cout << " Blocked Shots : " << BlockedShots << endl;
        cout << "-----------------------------------------------" << endl;
    }
};

//=================================================
//Derived class: Forward
//=================================================
class Forward : public Player
{ 
private:
    int Goals;
    int Assists;
    int Benefitial;
    int PenaltyMinuts;
public:
    Forward(string name, string team, int age, int number,
        int salary, double contr_term,
        int goals, int assists, int benifit, int min)
        : Player(name, team, age, number, salary, contr_term)
    {
        if (goals >= 0)
        {
            Goals = goals;
        }
        else
        {
            Goals = 0;
            cout << "Incorrect number of goals!" << endl;
        }

        if (assists >= 0)
        {
            Assists = assists;
        }
        else
        {
            Assists = 0;
            cout << "Incorrect number of assists!" << endl;
        }

        if (benifit >= 0)
        {
            Benefitial = benifit;
        }
        else
        {
            Benefitial = 0;
            cout << "Incorrect percentage of benefitial or player is not useful!" << endl;
        }

        if (min >= 0)
        {
            PenaltyMinuts = min;
        }
        else
        {
            PenaltyMinuts = 0;
            cout << "Incorrect number of penalty minuts!" << endl;
        }
    }

    void getResults() override
    {
        cout << "-----------------------------------------------" << endl;
        cout << "|               Player's Results              |" << endl;
        cout << "-----------------------------------------------" << endl;
        cout << " Player           : " << getPlayerName() << endl;
        cout << " Team             : " << getPlayerTeam() << endl;
        cout << " Age              : " << getPlayerAge() << endl;
        cout << " Number           : " << getPlayerNumber() << endl;
        cout << " Goals            : " << Goals << endl;
        cout << " Assists          : " << Assists << endl;
        cout << " Benefit for team : " << Benefitial << endl;
        cout << " Penalty minuts   : " << PenaltyMinuts << endl;
        cout << "-----------------------------------------------" << endl;
    }
};

    


//=================================================
//Functions for working with players data
//=================================================


//=================================================
//main function: demonstration of polymorphism
//=================================================

int main()
{
    std::cout << "Hello World!\n";
}
