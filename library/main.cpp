#include "book.h"
#include <iostream>
using namespace std;

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
