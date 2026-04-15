//Деятельность хоккейного клуба по учету игроков, у которых
//действующие контракты(вратари, защитники, нападающие).Необходимо
//выдать список игроков заданного амплуа, название которого получено с
//помощью ввода с консоли

#include <iostream>
#include<limits>
#include<string>
#include<vector>
#include<memory>

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
//Basic abstract class: Player
//=================================================
class Player
{
private:
    static int CounterID;
    int PlayerID;
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
        PlayerID = CounterID++;
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
    //Player()
    /*{
        PlayerName = "Ivanov Ivan Ivanych";
        PlayerTeam = "Ack Bars";
        PlayerAge = 18;
        PlayerNumber = 0;
        PlayerSalary = 100000;
        PlayerContractTerm = 1.5;
    }*/

    //virtual deconstructor, because of polymorthism
    virtual ~Player()
    {
        cout << PlayerName << " ended his career!" << endl;
    }

    //getters
    int getPlayerID() const
    {
        return PlayerID;
    }
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

    virtual string getPosition() const = 0;

    virtual void printInfo() const
    {
        cout << "-----------------------------------------------" << endl;
        cout << "|                  Player's Info              |" << endl;
        cout << "-----------------------------------------------" << endl;
        cout << " Name          : " << PlayerName << endl;
        cout << " Team          : " << PlayerTeam << endl;
        cout << " Age           : " << PlayerAge << endl;
        cout << " Number        : " << PlayerNumber << endl;
        cout << " Salary        : " << PlayerSalary << endl;
        cout << " Contract Term : " << PlayerContractTerm << "years" << endl;
    }
};

//static counter inicialization
int Player::CounterID = 1;

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

    string getPosition() const override
    {
        return "Goalie";
    }

    virtual void printInfo() const override
    {
        Player::printInfo();
        cout << " Goalie has " << GoalsLoss << " lost goals, " << SavePercentage << "% of saves, " << Shutouts << " shutouts." << endl;
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

    string getPosition() const override
    {
        return "Defender";
    }

    virtual void printInfo() const override
    {
        Player::printInfo();
        cout << " Defender has " << Goals << " goals, " << Assists << " assists, " << Hits << " hits, " << BlockedShots << " blocked shots." << endl;
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

    string getPosition() const override
    {
        return "Forward";
    }

    virtual void printInfo() const override
    {
        Player::printInfo();
        cout << " Forward has " << Goals << " goals, " << Assists << " assists, " 
            << Benefitial << "% of benefit for team, " << PenaltyMinuts << " min of penalty" << endl;
    }
};

//=================================================
//Array TeamManager
//=================================================
class TeamManager
{
private:
    static const int MAX_Players = 100;
    vector<unique_ptr<Player>> players;
public:
//=================================================
//Functions for working with players data
//=================================================



};


//=================================================
//main function: demonstration of polymorphism
//=================================================

int main()
{
    std::cout << "Hello World!\n";
}
