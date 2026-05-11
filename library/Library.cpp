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


// ==================== КЛАСС PUBLISHER ====================
class PublishingHouse
{
protected:
    string name; // название издательства
    string city; // страна издательства
    int foundingYear; // год основания

public:
    PublishingHouse() : name(""), city(""), foundingYear(0) {}
    PublishingHouse(const string& n, const string& c, int year) : name(n), city(c), foundingYear(year) {}
    virtual ~PublishingHouse() {}

    // Геттеры и сеттеры
    void setName(const string& n) { name = n; }
    string getName() const { return name; }

    void setCity(const string& c) { city = c; }
    string getCity() const { return city; }

    void setFoundingYear(int year) { foundingYear = year; }
    int getFoundingYear() const { return foundingYear; }

    // Уникальный метод
    void printHouseInfo() const
    {
        cout << "Publishing house: " << name << ", founded in " << city << " in " << foundingYear << endl;
    }

    // Методы ввода/вывода
    virtual void inputPublisher()
    {
        cout << "Enter publishing house name: ";
        name = safeString();
        cout << "Enter publishing house city: ";
        name = safeString();
        cout << "Enter founding year: ";
        foundingYear = safeInt();
    }

    virtual void outputPublisher() const
    {
        cout << "Publishing house: " << name << ", city: " << city << ", year: " << foundingYear;
    }
};

// ==================== КЛАСС AUTHOR ====================
class Author {
private:
    string fullName;    // Полное имя
    int birthYear;      // Год рождения
    string country;     // Страна

public:
    // Конструкторы
    Author() {
        fullName = "Unknown";
        birthYear = 1970;
        country = "Unknown";
    }

    Author(string name, int year, string cnt) {
        fullName = name;
        birthYear = year;
        country = cnt;
    }

    // Деструктор
    ~Author() {
        cout << "Author \"" << fullName << "\" destroyed" << endl;
    }

    // Ввод данных
    void inputAuthor() {
        cout << "=== Enter Author Info ===" << endl;
        cout << "Author full name: ";
        getline(cin, fullName);
        cout << "Birth year: ";
        cin >> birthYear;
        cin.ignore();
        cout << "Country: ";
        getline(cin, country);
    }

    // Вывод данных
    void outputAuthor() {
        cout << "Author: " << fullName << " (born " << birthYear
            << ", " << country << ")" << endl;
    }

    // Уникальный метод
    int getAge(int currentYear) {
        return currentYear - birthYear;
    }

    // Геттеры
    string getFullName() const { return fullName; }
    int getBirthYear() const { return birthYear; }
    string getCountry() const { return country; }
};

// ==================== КЛАСС BOOK (НАСЛЕДНИК) ====================
class Book : public PublishingHouse, public Author {
private:
    string title;       // Название книги
    string isbn;        // ISBN номер
    int pages;          // Количество страниц

public:
    // Конструктор по умолчанию
    Book() : PublishingHouse(), Author() {
        title = "Unknown";
        isbn = "000-0-00-000000-0";
        pages = 0;
    }

    // Деструктор
    ~Book() {
        cout << "Book \"" << title << "\" destroyed" << endl;
    }

    // Ввод данных
    void inputBook() {
        cout << "\n=== Enter Book Info ===" << endl;
        cout << "Title: ";
        title = safeString();
        cout << "ISBN (format: xxx-x-xx-xxxxxx-x): ";
        getline(cin, isbn);
        cout << "Number of pages: ";
        pages = safeInt();
        cin.ignore();

        cout << "\n";
        inputPublisher();   // Вызов метода родительского класса

        cout << "\n";
        inputAuthor();      // Вызов метода родительского класса
    }

    // Вывод данных
    void outputBook() {
        cout << "\n========================================" << endl;
        cout << "         BOOK INFORMATION" << endl;
        cout << "========================================" << endl;
        cout << "Title:  " << title << endl;
        cout << "ISBN:   " << isbn << endl;
        cout << "Pages:  " << pages << endl;
        cout << "----------------------------------------" << endl;

        outputPublisher();  // Вызов метода родительского класса
        outputAuthor();     // Вызов метода родительского класса

        cout << "----------------------------------------" << endl;
    }

    // Уникальный метод класса Book
    bool isLongBook() {
        return pages > 300;
    }
};

// ==================== ГЛАВНАЯ ФУНКЦИЯ ====================
int main() {
    cout << "╔════════════════════════════════════════╗" << endl;
    cout << "║     LIBRARY MANAGEMENT SYSTEM          ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;

    // Создаём объект книги
    Book myBook;

    // Вводим данные
    myBook.inputBook();

    // Выводим данные
    myBook.outputBook();

    cout << "\nProgram finished successfully!" << endl;

    return 0;
}
