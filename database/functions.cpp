#include "database.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <locale>

using namespace std;

// ������� ��� ���������� ������� � ����
void addBook(int& bookCount, Book books[]) {
    if (bookCount >= MAX_BOOKS) {
        cout << "������: ���� ������ ���������." << endl;
        return;
    }

    Book newBook;

    cout << "������� �������� ������� (�� " << MAX_TITLE_LENGTH << " ��������): ";
    getline(cin, newBook.title);

    cout << "������� ��� ������ (�� " << MAX_AUTHOR_LENGTH << " ��������): ";
    getline(cin, newBook.author);

    cout << "������� ��� ������� (yyyy): ";
    cin >> newBook.year;
    cin.ignore(); // ������� ������ �����

    books[bookCount] = newBook;
    bookCount++;

    cout << "������� ������� ��������� � ����." << endl;
}

// ������� ��� �������� ������� �� ����
void removeBook(int& bookCount, Book books[]) {
    if (bookCount == 0) {
        cout << "������: ���� ������ �����." << endl;
        return;
    }

    string titleToRemove;

    cout << "������� �������� ������� ��� ��������: ";
    getline(cin, titleToRemove);

    // ����� ������� � �������� ���������
    int indexToRemove = -1;
    for (int i = 0; i < bookCount; i++) {
        if (books[i].title == titleToRemove) {
            indexToRemove = i;
            break;
        }
    }

    if (indexToRemove == -1) {
        cout << "������� � ��������� \"" << titleToRemove << "\" �� ������� � ���� ������." << endl;
        return;
    }

    // �������� ������� �� ����
    for (int i = indexToRemove; i < bookCount - 1; i++) {
        books[i] = books[i + 1];
    }
    bookCount--;

    cout << "������� ������� ������� �� ����." << endl;
}

// ������� ��� ��������� ������� � ����
void editBook(int bookCount, Book books[]) {
    if (bookCount == 0) {
        cout << "������: ���� ������ �����." << endl;
        return;
    }

    string titleToEdit;

    cout << "������� �������� ������� ��� ��������������: ";
    getline(cin, titleToEdit);

    // ����� ������� � �������� �
    int indexToEdit = -1;
    for (int i = 0; i < bookCount; i++) {
        if (books[i].title == titleToEdit) {
            indexToEdit = i;
            break;
        }
    }
    if (indexToEdit == -1) {
        cout << "������� � ��������� \"" << titleToEdit << "\" �� ������� � ���� ������." << endl;
        return;
    }

    Book newBook;

    cout << "������� ����� �������� ������� (�� " << MAX_TITLE_LENGTH << " ��������): ";
    getline(cin, newBook.title);

    cout << "������� ����� ��� ������ (�� " << MAX_AUTHOR_LENGTH << " ��������): ";
    getline(cin, newBook.author);

    cout << "������� ����� ��� ������� (yyyy): ";
    cin >> newBook.year;
    cin.ignore(); // ������� ������ �����

    books[indexToEdit] = newBook;

    cout << "������� ������� �������� � ����." << endl;
}
// ������� ��� ���������� ������� �� ��������
void sortBooksByTitle(int bookCount, Book books[]) {
    sort(books, books + bookCount, [](const Book& a, const Book& b) {
        return a.title < b.title;
        });
    cout << "������� ������� ������������� �� ��������." << endl;
}
// ������� ��� ���������� ������� �� ����� ������
void sortBooksByAuthor(int bookCount, Book books[]) {
    sort(books, books + bookCount, [](const Book& a, const Book& b) {
        return a.author < b.author;
        });
    cout << "������� ������� ������������� �� ����� ������." << endl;
}
// ������� ��� ���������� ������� �� ���� �������
void sortBooksByYear(int bookCount, Book books[]) {
    sort(books, books + bookCount, [](const Book& a, const Book& b) {
        return a.year < b.year;
        });
    cout << "������� ������� ������������� �� ���� �������." << endl;
}

// ������� ��� ������ ������� �� ��������
void searchByTitle(int bookCount, Book books[]) {
    if (bookCount == 0) {
        cout << "������: ���� ������ �����." << endl;
        return;
    }
    string titleToSearch;

    cout << "������� �������� ������� ��� ������: ";
    getline(cin, titleToSearch);

    int count = 0;
    for (int i = 0; i < bookCount; i++) {
        if (books[i].title == titleToSearch) {
            cout << "��������: " << books[i].title << endl;
            cout << "�����: " << books[i].author << endl;
            cout << "��� �������: " << books[i].year << endl;
            cout << endl;
            count++;
        }
    }

    if (count == 0) {
        cout << "������� � ��������� \"" << titleToSearch << "\" �� ������� � ���� ������." << endl;
    }
    else {
        cout << "������� " << count << " ������� � ��������� \"" << titleToSearch << "\"." << endl;
    }
}

// ������� ��� ������ ������� �� ������
void searchByAuthor(int bookCount, Book books[]) {
    if (bookCount == 0) {
        cout << "������: ���� ������ �����." << endl;
        return;
    }

    string authorToSearch;

    cout << "������� ��� ������ ��� ������: ";
    getline(cin, authorToSearch);

    int count = 0;
    for (int i = 0; i < bookCount; i++) {
        if (books[i].author == authorToSearch) {
            cout << "��������: " << books[i].title << endl;
            cout << "�����: " << books[i].author << endl;
            cout << "��� �������: " << books[i].year << endl;
            cout << endl;
            count++;
        }
    }

    if (count == 0) {
        cout << "������� ������ \"" << authorToSearch << "\" �� ������� � ���� ������." << endl;
    }
    else {
        cout << "������� " << count << " ������� ������ \"" << authorToSearch << "\"." << endl;
    }
}

// ������� ��� ������ ������� �� ���� �������
void searchByYear(int bookCount, Book books[]) {
    if (bookCount == 0) {
        cout << "������: ���� ������ �����." << endl;
        return;
    }
    int yearToSearch;

    cout << "������� ��� ������� ��� ������: ";
    cin >> yearToSearch;
    cin.ignore();

    int count = 0;
    for (int i = 0; i < bookCount; i++) {
        if (books[i].year == yearToSearch) {
            cout << "��������: " << books[i].title << endl;
            cout << "�����: " << books[i].author << endl;
            cout << "��� �������: " << books[i].year << endl;
            cout << endl;
            count++;
        }
    }

    if (count == 0) {
        cout << "�������, ���������� � " << yearToSearch << " ����, �� ������� � ���� ������." << endl;
    }
    else {
        cout << "����� ������� �������, ���������� � " << yearToSearch << " ����: " << count << endl;
    }
}

// ������� ��� ������ ������ � ���� ������
void printReport(int bookCount, Book books[]) {
    cout << "���������� ���� � ����: " << bookCount << endl;
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

    cout << "���������� ������� � ����: " << authorCount << endl;

    cout << "������ ������� � ����:" << endl;
    for (int i = 0; i < authorCount; i++) {
        cout << "- " << authors[i] << endl;
    }
}

// ������� ��� ���������� ���� ������ � ����
void saveToFile(int bookCount, Book books[], string filename) {
    ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        cout << "������: �� ������� ������� ���� \"" << filename << "\"." << endl;
        return;
    }

    for (int i = 0; i < bookCount; i++) {
        outputFile << books[i].title << endl;
        outputFile << books[i].author << endl;
        outputFile << books[i].year << endl;
    }

    outputFile.close();

    cout << "���� ������ ������� ��������� � ���� \"" << filename << "\"." << endl;
}

// ������� ��� ������ ���� ���� � ����
void printAllBooks(int bookCount, Book books[]) {
    if (bookCount == 0) {
        cout << "���� ������ �����." << endl;
        return;
    }

    cout << "������ ���� ���� � ����:" << endl << endl;
    for (int i = 0; i < bookCount; i++) {
        cout << "��������: " << books[i].title << endl;
        cout << "�����: " << books[i].author << endl;
        cout << "��� �������: " << books[i].year << endl;
        cout << endl;
    }
}