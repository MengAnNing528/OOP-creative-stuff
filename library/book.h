#ifndef BOOK_H
#define BOOK_H

#include "publisher.h"
#include "author.h"
#include <string>

// Множественное наследование
class Book : public Publisher, public Author {
private:
    std::string title;      // Название книги
    std::string isbn;       // ISBN номер
    int pages;              // Количество страниц
    
public:
    // Конструкторы
    Book();
    Book(std::string t, std::string i, int p,
         std::string pubName, std::string pubCity, int pubYear,
         std::string authName, int authYear, std::string authCountry);
    
    // Деструктор
    ~Book();
    
    // Методы ввода/вывода
    void inputBook();
    void outputBook();
    
    // Уникальный метод
    bool isLongBook();
};

#endif
