#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <locale>
#include "database.h"

using namespace std;

int loadFromFile(Book books[], string filename) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Ошибка: не удалось открыть файл \"" << filename << "\"." << endl;
        return 0;
    }

    int bookCount = 0;
    string title, author, yearString;

    while (getline(inputFile, title) && getline(inputFile, author) && getline(inputFile, yearString)) {
        Book newBook;
        newBook.title = title;
        newBook.author = author;
        newBook.year = stoi(yearString);
        books[bookCount] = newBook;
        bookCount++;
    }

    inputFile.close();

    cout << "База данных успешно загружена из файла \"" << filename << "\"." << endl;

    return bookCount;
}

int main() {
    setlocale(LC_ALL, "Russian");
    int bookCount = 0;
    Book books[MAX_BOOKS];
    bookCount = loadFromFile(books, "books.txt");
    int choice;
    while (true) {
        // вывод меню
        cout << endl;
        cout << "Меню:" << endl;
        cout << "1. Добавить пособие в базу" << endl;
        cout << "2. Удалить пособие из базы" << endl;
        cout << "3. Редактировать пособие из базы" << endl;
        cout << "4. Сортировать пособия по названию" << endl;
        cout << "5. Сортировать пособия по автору" << endl;
        cout << "6. Сортировать пособия по году выпуска" << endl;
        cout << "7. Отчет по базе данных" << endl;
        cout << "8. Поиск пособия по названию" << endl;
        cout << "9. Поиск пособия по автору" << endl;
        cout << "10. Поиск пособия по году" << endl;
        cout << "11. Список всех пособий в базе." << endl;
        cout << "12. Сохранить базу данных в файл" << endl;
        cout << "0. Выход из программы" << endl;
        cout << endl;
        cout << "Выберите пункт меню: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 1:
            addBook(bookCount, books);
            break;
        case 2:
            removeBook(bookCount, books);
            break;
        case 3:
            editBook(bookCount, books);
            break;
        case 4:
            sortBooksByTitle(bookCount, books);
            break;
        case 5:
            sortBooksByAuthor(bookCount, books);
            break;
        case 6:
            sortBooksByYear(bookCount, books);
            break;
        case 7:
            printReport(bookCount, books);
            break;
        case 8:
            searchByTitle(bookCount, books);
            break;
        case 9:
            searchByAuthor(bookCount, books);
            break;
        case 10:
            searchByYear(bookCount, books);
            break;
        case 11:
            printAllBooks(bookCount, books);
            break;
        case 12:
            saveToFile(bookCount, books, "books.txt");
            cout << "База данных успешно сохранена в файл." << endl;
            break;
        case 0:
            cout << "Выход из программы." << endl;
            return 0;
        default:
            cout << "Ошибка: неверный пункт меню." << endl;
            break;
        }
    }
}