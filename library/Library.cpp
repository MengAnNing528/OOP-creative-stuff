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
private:
    string name; // название издательства
    int foundingYear; // год основания

public:
    PublishingHouse() : name(""), foundingYear(0) {}
    PublishingHouse(const string& n, int year) {
        name = n;
        foundingYear = year;
    }
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
    virtual void inputPublisher()
    {
        cout << "=== Enter Publishing House Info ===" << endl;
        cout << "Enter publishing house name: ";
        name = safeString();
        cout << "Enter founding year: ";
        foundingYear = safeInt();
    }

    virtual void outputPublisher() const
    {
        cout << "Publishing house: " << name << ", year: " << foundingYear << endl;
    }
};

// ==================== КЛАСС AUTHOR ====================
class Author {
private:
    string  AuthorName; // имя автора
    string AuthorCountry; // страна автора

public:
    // Конструкторы
    Author() : AuthorName("-"), AuthorCountry("-") {}
    Author(const string& AN, const string& AC) {
        AuthorName = AN;
        AuthorCountry = AC;
    }
    virtual ~Author() {}

    void setName(const string& AN) { AuthorName = AN; }
    string getName() const { return AuthorName; }

    void setCountry(const string& AC) { AuthorCountry = AC; }
    string getCountry() const { return AuthorCountry; }

    void printInfoAthor() const {
        cout << "Author name:" << AuthorName << " from: " << AuthorCountry << endl;
    }

    // Ввод данных
    virtual void inputAuthor() {
        cout << "=== Enter Author Info ===" << endl;
        cout << "Author full name: ";
        AuthorName = safeString();
        cout << "Country: ";
        AuthorCountry = safeString();
    }

    // Вывод данных
    virtual void outputAuthor() const {
        cout << "Author: " << AuthorName << " from " << AuthorCountry << endl;
    }
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

        //outputPublisher();  // Вызов метода родительского класса
        //outputAuthor();     // Вызов метода родительского класса

        printHouseInfo();
        printInfoAthor();
        cout << "----------------------------------------" << endl;
    }

    // Уникальный метод класса Book
    bool isLongBook() {
        return pages > 300;
    }
};

// ==================== ГЛАВНАЯ ФУНКЦИЯ ====================
int main() {
    cout << "==========================================" << endl;
    cout << "|     LIBRARY MANAGEMENT SYSTEM          |" << endl;
    cout << "==========================================" << endl;

    // Создаём объект книги
    Book myBook;

    // Вводим данные
    myBook.inputBook();

    // Выводим данные
    myBook.outputBook();

    cout << "\nProgram finished successfully!" << endl;

    return 0;
}
