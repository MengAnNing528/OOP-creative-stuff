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
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
using namespace std;

// Функция для очистки буфера ввода
void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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
class Goalie;
class Defender;
class Forward;
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

   // virtual string getPosition() const = 0;

   // virtual void printInfo() const
    virtual void getResults()
    {
        cout << "All Players are qualified" << endl;
    }

    virtual void printInfo()
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
//int Player::CounterID = 1;

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
//Вызываем конструктор родительского класса Player, чтобы заполнить общие поля игрока
    Goalie(string name, string team, int age, int number,
        int salary, double contr_term)
        : Player(name, team, age, number, salary, contr_term)
    {
        GoalsLoss = 0;
        SavePercentage = 0;
        Shutouts = 0;
    }

    void getResults() override //Переопределяем виртуальный метод родительского класса, чтобы выводить специфичную для вратаря информацию.
    {
        cout << " Position: Goalkeeper" << endl;
    }
};

    //string getPosition() const override
    //{
        //return "Goalie";
    //}

    //virtual void printInfo() const override
    //{
        //Player::printInfo();
        //cout << " Goalie has " << GoalsLoss << " lost goals, " << SavePercentage << "% of saves, " << Shutouts << " shutouts." << endl;
    //}
//};

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
        cout << " Position: Defender" << endl;
    }
};

    //string getPosition() const override
    //{
        //return "Defender";
    //}

    //virtual void printInfo() const override
    //{
        //Player::printInfo();
        //cout << " Defender has " << Goals << " goals, " << Assists << " assists, " << Hits << " hits, " << BlockedShots << " blocked shots." << endl;
    //}
//};

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
        cout << " Position: Forward" << endl;
    }
};

    //string getPosition() const override
    //{
        //return "Forward";
    //}

    //virtual void printInfo() const override
    //{
        //Player::printInfo();
        //cout << " Forward has " << Goals << " goals, " << Assists << " assists, " 
            //<< Benefitial << "% of benefit for team, " << PenaltyMinuts << " min of penalty" << endl;
    //}
//};

//=================================================
//Array TeamManager
//=================================================
//class TeamManager
//{
//private:
  //  static const int MAX_Players = 100;
    //vector<unique_ptr<Player>> players;
//public:
//=================================================
//Functions for working with players data
//=================================================



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//=================================================
// Global storage for players
//=================================================
vector<Player> allPlayers; //Хранит всех игроков в одной коллекции

//=================================================
// Функция для проверки, занят ли номер
//=================================================
bool isNumberTaken(int number) //объявляем функцию
{
    for (int i = 0; i < allPlayers.size(); i++) //берем значения от 0 и до конечного числа игроков, сохраненных в векторе 
    {
        if (allPlayers[i].getPlayerNumber() == number) //берем игрока по индексу и проверяем, совпадает ли какой из них с введенным номером
        {
            return true;
        }
    }
    return false;
}

//=================================================
// Функция для показа доступных номеров
//=================================================
void showAvailableNumbers() //показывает номера, которые еще не заняты 
{
    cout << "Свободные номера: ";
    int count = 0;
    for (int num = 1; num <= 99; num++)
    {
        if (!isNumberTaken(num)) //если номер занят, то выводим те, что свободны
        {
            cout << num << " ";
            count++;
        
        }
    }
    if (count == 0) //случай, когда свободные номера закончились 
    {
        cout << "Нет свободных номеров";
    }
    cout << endl;
}

//=================================================
// Функция для добавления игрока
//=================================================
void Add_Player() 
{
    string name, team;
    int age, number;
    int salary = 5000;
    double contractTerm = 1.5;

    clearInput();
    
    cout << "Введите информацию о новом игроке: " << endl;
    cout << "ФИО: ";
    getline(cin, name);
    
    cout << "Введите название команды игрока: ";
    getline(cin, team);
    
    // Проверка возраста
    bool validAge = false;
    do {                                        //прописываем через  do/while
        cout << "Введите возраст игрока: ";
        cin >> age;
        if (age >= 18 && age <= 55)
        {
            validAge = true;
        }
        else
        {
            cout << "Your age is unsuitable. Able age 18-55" << endl;
            cout << "Попробуйте снова" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    } while (!validAge);
    
    // Проверка номера
    bool validNumber = false;
    do {
        cout << "Введите желаемый номер игрока (1-99): ";
        cin >> number;
        
        if (number < 1 || number > 99)
        {
            cout << "Номер должен быть в диапазоне от 1 до 99!" << endl;
            cout << "Попробуйте снова" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
        else if (isNumberTaken(number))
        {
            cout << "Номер " << number << " уже занят!" << endl;
            showAvailableNumbers();
            cout << "Попробуйте снова" << endl;
        }
        else
        {
            validNumber = true;
        }
    } while (!validNumber);
    
    // Выбор позиции
    cout << "\n--- ВЫБОР ПОЗИЦИИ ---" << endl;
    cout << "1. Вратарь" << endl;
    cout << "2. Защитник" << endl;
    cout << "3. Нападающий" << endl;
    cout << "Выберите позицию (1-3): ";
    int posChoice;
    cin >> posChoice;
    
    // Создаём игрока в зависимости от выбранной позиции
    if (posChoice == 1) 
    {
        Goalie newPlayer(name, team, age, number, salary, contractTerm);
        allPlayers.push_back(newPlayer);           //добавляем в конец нашего созданного игрока (в вектор )
        cout << "\n ВРАТАРЬ УСПЕШНО ДОБАВЛЕН!" << endl;
    }
    else if (posChoice == 2) 
    {
        Defender newPlayer(name, team, age, number, salary, contractTerm);
        allPlayers.push_back(newPlayer);
        cout << "\n ЗАЩИТНИК УСПЕШНО ДОБАВЛЕН!" << endl;
    }
    else if (posChoice == 3) 
    {
        Forward newPlayer(name, team, age, number, salary, contractTerm);
        allPlayers.push_back(newPlayer);
        cout << "\n НАПАДАЮЩИЙ УСПЕШНО ДОБАВЛЕН!" << endl;
    }
    else
    {
        cout << "Неверный выбор позиции! Игрок не будет добавлен." << endl;
        return;
    }

    cout << "====================================" << endl;
    cout << "Игрок: " << name << endl;
    cout << "Возраст: " << age << " лет" << endl;
    cout << "Номер: " << number << endl;
    cout << "Команда: " << team << endl;
    cout << "====================================" << endl;
    cout << "Всего игроков в системе: " << allPlayers.size() << endl;
}

//=================================================
// Функция для показа всех игроков
//=================================================
void ShowAllPlayers() 
{
    if (allPlayers.size() == 0) 
    {
        cout << "\n Список игроков пуст!" << endl;
        return;
    }
    
    cout << "\n=== СПИСОК ВСЕХ ИГРОКОВ ===" << endl;
    cout << "=================================" << endl;
    
    for (int i = 0; i < allPlayers.size(); i++) 
    {
        cout << i + 1 << ". " 
             << allPlayers[i].getPlayerName() << " | "
             << allPlayers[i].getPlayerAge() << " лет | "
             << "Номер: " << allPlayers[i].getPlayerNumber() << " | "
             << "Команда: " << allPlayers[i].getPlayerTeam() << endl;
    }
}

//=================================================
// Функция для удаления игрока по имени
//=================================================
void DeletePlayerByName()
{
    if (allPlayers.empty())
    {
        cout << "\nСписок игроков пуст! Некого удалять." << endl;
        return;
    }
    
    cout << "\n=== УДАЛЕНИЕ ИГРОКА ===" << endl;
    cout << "Введите ФИО игрока, которого хотите удалить: ";
    clearInput();
    string name;
    getline(cin, name);
    
    bool found = false;
    for (int i = 0; i < allPlayers.size(); i++)
    {
        if (allPlayers[i].getPlayerName() == name)
        {
            cout << "\nНайден игрок:" << endl;
            cout << "   ФИО: " << allPlayers[i].getPlayerName() << endl;
            cout << "   Команда: " << allPlayers[i].getPlayerTeam() << endl;
            cout << "   Возраст: " << allPlayers[i].getPlayerAge() << endl;
            cout << "   Номер: " << allPlayers[i].getPlayerNumber() << endl;
            
            cout << "\nВы уверены, что хотите удалить этого игрока? (y/n): ";
            char confirm;
            cin >> confirm;
            
            if (confirm == 'y' || confirm == 'Y')
            {
                allPlayers.erase(allPlayers.begin() + i);
                cout << " Игрок успешно удалён!" << endl;
            }
            else
            {
                cout << " Удаление отменено." << endl;
            }
            found = true;
            break;
        }
    }
    
    if (!found)
    {
        cout << " Игрок с именем \"" << name << "\" не найден!" << endl;
    }
}

//=================================================
// main function
//=================================================
int main()
{
    int choice;
    
    do {
        cout << "\n=======================================================" << endl;
        cout << "           ХОККЕЙНЫЙ КЛУБ - ГЛАВНОЕ МЕНЮ         " << endl;
        cout << "=================================================" << endl;
        cout << " 1. Добавить игрока                              " << endl;
        cout << " 2. Показать всех игроков                        " << endl;
        cout << " 3. Удалить игрока                               " << endl;
        cout << " 4. Выйти                                        " << endl;
        cout << "========================================================" << endl;
        cout << "Ваш выбор: ";
        cin >> choice;
        
        switch(choice)
        {
            case 1:
                Add_Player();
                break;
            case 2:
                ShowAllPlayers();
                break;
            case 3:
                DeletePlayerByName();
                break;
            case 4:
                cout << "\n До свидания!" << endl;
                break;
            default:
                cout << "\n Неверный выбор!" << endl;
        }
    } while (choice != 4);
    
    return 0;
}
