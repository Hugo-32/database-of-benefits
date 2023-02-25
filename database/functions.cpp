#include "database.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <locale>

using namespace std;

// функция для добавления пособия в базу
void addBook(int& bookCount, Book books[]) {
    if (bookCount >= MAX_BOOKS) {
        cout << "Ошибка: база данных заполнена." << endl;
        return;
    }

    Book newBook;

    cout << "Введите название пособия (до " << MAX_TITLE_LENGTH << " символов): ";
    getline(cin, newBook.title);

    cout << "Введите имя автора (до " << MAX_AUTHOR_LENGTH << " символов): ";
    getline(cin, newBook.author);

    cout << "Введите год выпуска (yyyy): ";
    cin >> newBook.year;
    cin.ignore(); // очистка буфера ввода

    books[bookCount] = newBook;
    bookCount++;

    cout << "Пособие успешно добавлено в базу." << endl;
}

// функция для удаления пособия из базы
void removeBook(int& bookCount, Book books[]) {
    if (bookCount == 0) {
        cout << "Ошибка: база данных пуста." << endl;
        return;
    }

    string titleToRemove;

    cout << "Введите название пособия для удаления: ";
    getline(cin, titleToRemove);

    // поиск пособия с заданным названием
    int indexToRemove = -1;
    for (int i = 0; i < bookCount; i++) {
        if (books[i].title == titleToRemove) {
            indexToRemove = i;
            break;
        }
    }

    if (indexToRemove == -1) {
        cout << "Пособие с названием \"" << titleToRemove << "\" не найдено в базе данных." << endl;
        return;
    }

    // удаление пособия из базы
    for (int i = indexToRemove; i < bookCount - 1; i++) {
        books[i] = books[i + 1];
    }
    bookCount--;

    cout << "Пособие успешно удалено из базы." << endl;
}

// функция для изменения пособия в базе
void editBook(int bookCount, Book books[]) {
    if (bookCount == 0) {
        cout << "Ошибка: база данных пуста." << endl;
        return;
    }

    string titleToEdit;

    cout << "Введите название пособия для редактирования: ";
    getline(cin, titleToEdit);

    // поиск пособия с заданным н
    int indexToEdit = -1;
    for (int i = 0; i < bookCount; i++) {
        if (books[i].title == titleToEdit) {
            indexToEdit = i;
            break;
        }
    }
    if (indexToEdit == -1) {
        cout << "Пособие с названием \"" << titleToEdit << "\" не найдено в базе данных." << endl;
        return;
    }

    Book newBook;

    cout << "Введите новое название пособия (до " << MAX_TITLE_LENGTH << " символов): ";
    getline(cin, newBook.title);

    cout << "Введите новое имя автора (до " << MAX_AUTHOR_LENGTH << " символов): ";
    getline(cin, newBook.author);

    cout << "Введите новый год выпуска (yyyy): ";
    cin >> newBook.year;
    cin.ignore(); // очистка буфера ввода

    books[indexToEdit] = newBook;

    cout << "Пособие успешно изменено в базе." << endl;
}
// функция для сортировки пособий по названию
void sortBooksByTitle(int bookCount, Book books[]) {
    sort(books, books + bookCount, [](const Book& a, const Book& b) {
        return a.title < b.title;
        });
    cout << "Пособия успешно отсортированы по названию." << endl;
}
// функция для сортировки пособий по имени автора
void sortBooksByAuthor(int bookCount, Book books[]) {
    sort(books, books + bookCount, [](const Book& a, const Book& b) {
        return a.author < b.author;
        });
    cout << "Пособия успешно отсортированы по имени автора." << endl;
}
// функция для сортировки пособий по году выпуска
void sortBooksByYear(int bookCount, Book books[]) {
    sort(books, books + bookCount, [](const Book& a, const Book& b) {
        return a.year < b.year;
        });
    cout << "Пособия успешно отсортированы по году выпуска." << endl;
}

// функция для поиска пособия по названию
void searchByTitle(int bookCount, Book books[]) {
    if (bookCount == 0) {
        cout << "Ошибка: база данных пуста." << endl;
        return;
    }
    string titleToSearch;

    cout << "Введите название пособия для поиска: ";
    getline(cin, titleToSearch);

    int count = 0;
    for (int i = 0; i < bookCount; i++) {
        if (books[i].title == titleToSearch) {
            cout << "Название: " << books[i].title << endl;
            cout << "Автор: " << books[i].author << endl;
            cout << "Год выпуска: " << books[i].year << endl;
            cout << endl;
            count++;
        }
    }

    if (count == 0) {
        cout << "Пособие с названием \"" << titleToSearch << "\" не найдено в базе данных." << endl;
    }
    else {
        cout << "Найдено " << count << " пособий с названием \"" << titleToSearch << "\"." << endl;
    }
}

// функция для поиска пособия по автору
void searchByAuthor(int bookCount, Book books[]) {
    if (bookCount == 0) {
        cout << "Ошибка: база данных пуста." << endl;
        return;
    }

    string authorToSearch;

    cout << "Введите имя автора для поиска: ";
    getline(cin, authorToSearch);

    int count = 0;
    for (int i = 0; i < bookCount; i++) {
        if (books[i].author == authorToSearch) {
            cout << "Название: " << books[i].title << endl;
            cout << "Автор: " << books[i].author << endl;
            cout << "Год выпуска: " << books[i].year << endl;
            cout << endl;
            count++;
        }
    }

    if (count == 0) {
        cout << "Пособия автора \"" << authorToSearch << "\" не найдены в базе данных." << endl;
    }
    else {
        cout << "Найдено " << count << " пособий автора \"" << authorToSearch << "\"." << endl;
    }
}

// функция для поиска пособия по году выпуска
void searchByYear(int bookCount, Book books[]) {
    if (bookCount == 0) {
        cout << "Ошибка: база данных пуста." << endl;
        return;
    }
    int yearToSearch;

    cout << "Введите год выпуска для поиска: ";
    cin >> yearToSearch;
    cin.ignore();

    int count = 0;
    for (int i = 0; i < bookCount; i++) {
        if (books[i].year == yearToSearch) {
            cout << "Название: " << books[i].title << endl;
            cout << "Автор: " << books[i].author << endl;
            cout << "Год выпуска: " << books[i].year << endl;
            cout << endl;
            count++;
        }
    }

    if (count == 0) {
        cout << "Пособия, выпущенные в " << yearToSearch << " году, не найдены в базе данных." << endl;
    }
    else {
        cout << "Всего найдено пособий, выпущенных в " << yearToSearch << " году: " << count << endl;
    }
}

// функция для вывода отчета о базе данных
void printReport(int bookCount, Book books[]) {
    cout << "Количество книг в базе: " << bookCount << endl;
    string authors[MAX_BOOKS];
    int authorCount = 0;
    for (int i = 0; i < bookCount; i++) {
        bool found = false;
        for (int j = 0; j < authorCount; j++) {
            if (authors[j] == books[i].author) {
                found = true;
                break;
            }
        }
        if (!found) {
            authors[authorCount] = books[i].author;
            authorCount++;
        }
    }

    cout << "Количество авторов в базе: " << authorCount << endl;

    cout << "Список авторов в базе:" << endl;
    for (int i = 0; i < authorCount; i++) {
        cout << "- " << authors[i] << endl;
    }
}

// функция для сохранения базы данных в файл
void saveToFile(int bookCount, Book books[], string filename) {
    ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        cout << "Ошибка: не удалось открыть файл \"" << filename << "\"." << endl;
        return;
    }

    for (int i = 0; i < bookCount; i++) {
        outputFile << books[i].title << endl;
        outputFile << books[i].author << endl;
        outputFile << books[i].year << endl;
    }

    outputFile.close();

    cout << "База данных успешно сохранена в файл \"" << filename << "\"." << endl;
}

// функция для вывода всех книг в базе
void printAllBooks(int bookCount, Book books[]) {
    if (bookCount == 0) {
        cout << "База данных пуста." << endl;
        return;
    }

    cout << "Список всех книг в базе:" << endl << endl;
    for (int i = 0; i < bookCount; i++) {
        cout << "Название: " << books[i].title << endl;
        cout << "Автор: " << books[i].author << endl;
        cout << "Год выпуска: " << books[i].year << endl;
        cout << endl;
    }
}