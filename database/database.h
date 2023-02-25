#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <locale>

using namespace std;

const int MAX_BOOKS = 1000; // ������������ ���������� �������
const int MAX_TITLE_LENGTH = 100; // ������������ ����� ��������
const int MAX_AUTHOR_LENGTH = 50; // ������������ ����� ����� ������

struct Book {
    string title; // �������� �������
    string author; // ����� �������
    int year; // ��� ������� �������
};

void addBook(int& bookCount, Book books[]);
void removeBook(int& bookCount, Book books[]);
void editBook(int bookCount, Book books[]);
void sortBooksByTitle(int bookCount, Book books[]);
void sortBooksByAuthor(int bookCount, Book books[]);
void sortBooksByYear(int bookCount, Book books[]);
void searchByTitle(int bookCount, Book books[]);
void searchByAuthor(int bookCount, Book books[]);
void searchByYear(int bookCount, Book books[]);
void printReport(int bookCount, Book books[]);
void saveToFile(int bookCount, Book books[], string filename);
int loadFromFile(Book* books[], string filename);
void printAllBooks(int bookCount, Book books[]);
