#include <iostream>
#include <string>
using namespace std;

// ==================== КЛАСС PUBLISHER ====================
class Publisher {
private:
    string name;        // Название издательства
    string city;        // Город
    int foundingYear;   // Год основания

public:
    // Конструкторы
    Publisher() {
        name = "Unknown";
        city = "Unknown";
        foundingYear = 2000;
    }

    Publisher(string n, string c, int year) {
        name = n;
        city = c;
        foundingYear = year;
    }

    // Деструктор
    ~Publisher() {
        cout << "Publisher \"" << name << "\" destroyed" << endl;
    }

    // Ввод данных
    void inputPublisher() {
        cout << "=== Enter Publisher Info ===" << endl;
        cout << "Publisher name: ";
        getline(cin, name);
        cout << "City: ";
        getline(cin, city);
        cout << "Founding year: ";
        cin >> foundingYear;
        cin.ignore(); // очищаем буфер после cin
    }

    // Вывод данных
    void outputPublisher() {
        cout << "Publisher: " << name << ", " << city
            << " (founded " << foundingYear << ")" << endl;
    }

    // Уникальный метод
    void printCopyright() {
        cout << "Copyright © " << foundingYear << " by " << name << endl;
    }

    // Геттеры
    string getName() const { return name; }
    string getCity() const { return city; }
    int getFoundingYear() const { return foundingYear; }
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
class Book : public Publisher, public Author {
private:
    string title;       // Название книги
    string isbn;        // ISBN номер
    int pages;          // Количество страниц

public:
    // Конструктор по умолчанию
    Book() : Publisher(), Author() {
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
        getline(cin, title);
        cout << "ISBN (format: xxx-x-xx-xxxxxx-x): ";
        getline(cin, isbn);
        cout << "Number of pages: ";
        cin >> pages;
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

        // Демонстрация уникальных методов
        printCopyright();                                  // Из Publisher
        cout << "Author's age in 2024: " << getAge(2024) << endl;  // Из Author
        cout << "Long book? " << (isLongBook() ? "Yes (more than 300 pages)" : "No") << endl;
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