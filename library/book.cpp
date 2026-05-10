#include "book.h"
#include <iostream>
using namespace std;

// Конструктор по умолчанию
Book::Book() : Publisher(), Author() {
    title = "Unknown";
    isbn = "000-0-00-000000-0";
    pages = 0;
}

// Конструктор с параметрами
Book::Book(string t, string i, int p,
           string pubName, string pubCity, int pubYear,
           string authName, int authYear, string authCountry)
    : Publisher(pubName, pubCity, pubYear),
      Author(authName, authYear, authCountry) {
    title = t;
    isbn = i;
    pages = p;
}

// Деструктор
Book::~Book() {
    cout << "Book \"" << title << "\" destroyed" << endl;
}

// Ввод данных
void Book::inputBook() {
    cout << "\n=== Enter Book Info ===" << endl;
    cout << "Title: ";
    cin.ignore();
    getline(cin, title);
    cout << "ISBN (format: xxx-x-xx-xxxxxx-x): ";
    getline(cin, isbn);
    cout << "Number of pages: ";
    cin >> pages;
    
    // Ввод данных об издательстве
    cout << "\n";
    inputPublisher();
    
    // Ввод данных об авторе
    cout << "\n";
    inputAuthor();
}

// Вывод данных
void Book::outputBook() {
    cout << "\n╔════════════════════════════════════════╗" << endl;
    cout << "║         BOOK INFORMATION               ║" << endl;
    cout << "╚════════════════════════════════════════╝" << endl;
    cout << "Title:  " << title << endl;
    cout << "ISBN:   " << isbn << endl;
    cout << "Pages:  " << pages << endl;
    cout << "-----------------------------------------" << endl;
    
    // Вывод издательства
    outputPublisher();
    
    // Вывод автора
    outputAuthor();
    
    cout << "-----------------------------------------" << endl;
    
    // Демонстрация уникальных методов
    printCopyright();                                          // Из Publisher
    cout << "Author's age in 2024: " << getAge(2024) << endl;  // Из Author
    cout << "Long book? " << (isLongBook() ? "Yes ⚠️" : "No ✅") << endl;
}

// Уникальный метод книги
bool Book::isLongBook() {
    return pages > 300;
}
