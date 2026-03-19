#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Book {
    string id;
    string name;
    string author;
    string type;
    string publisher;
    string date;
    double price;
};

vector<Book> books;

bool compareBooks(const Book& a, const Book& b) {
    if (a.price != b.price) {
        return a.price < b.price;
    }
    return a.id < b.id;
}

int findBookIndex(const string& id) {
    for (int i = 0; i < books.size(); i++) {
        if (books[i].id == id) {
            return i;
        }
    }
    return -1;
}

int main() {
    string command;

    while (cin >> command) {
        if (command == "INSERT") {
            Book book;
            cin >> book.id >> book.name >> book.author >> book.type >> book.publisher >> book.date >> book.price;

            if (findBookIndex(book.id) == -1) {
                books.push_back(book);
                cout << "Inserted" << endl;
            }
            else {
                cout << "Failed" << endl;
            }
        }
        else if (command == "VIEW") {
            string id;
            cin >> id;

            int index = findBookIndex(id);
            if (index != -1) {
                Book& book = books[index];
                cout << book.id << " " << book.name << " " << book.author << " "
                    << book.type << " " << book.publisher << " " << book.date << " "
                    << fixed << setprecision(2) << book.price << endl;
            }
            else {
                cout << "Failed" << endl;
            }
        }
        else if (command == "SORT") {
            vector<Book> sortedBooks = books;
            sort(sortedBooks.begin(), sortedBooks.end(), compareBooks);

            for (const auto& book : sortedBooks) {
                cout << book.id << " " << book.name << " " << book.author << " "
                    << book.type << " " << book.publisher << " " << book.date << " "
                    << fixed << setprecision(2) << book.price << endl;
            }
        }
        else if (command == "FIND") {
            string type, value;
            cin >> type >> value;

            vector<Book> result;
            if (type == "NAME") {
                for (const auto& book : books) {
                    if (book.name == value) {
                        result.push_back(book);
                    }
                }
            }
            else if (type == "AUTHOR") {
                for (const auto& book : books) {
                    if (book.author == value) {
                        result.push_back(book);
                    }
                }
            }

            if (result.empty()) {
                cout << "Failed" << endl;
            }
            else {
                sort(result.begin(), result.end(), compareBooks);
                for (const auto& book : result) {
                    cout << book.id << " " << book.name << " " << book.author << " "
                        << book.type << " " << book.publisher << " " << book.date << " "
                        << fixed << setprecision(2) << book.price << endl;
                }
            }
        }
        else if (command == "DELETE") {
            string id;
            cin >> id;

            int index = findBookIndex(id);
            if (index != -1) {
                books.erase(books.begin() + index);
                cout << "Deleted" << endl;
            }
            else {
                cout << "Failed" << endl;
            }
        }
        else if (command == "CHANGE") {
            string oldId, newId;
            Book book;
            cin >> oldId >> newId >> book.name >> book.author >> book.type >> book.publisher >> book.date >> book.price;
            book.id = newId;

            int oldIndex = findBookIndex(oldId);
            if (oldIndex == -1) {
                cout << "Failed" << endl;
                continue;
            }

            if (oldId != newId && findBookIndex(newId) != -1) {
                cout << "Failed" << endl;
                continue;
            }

            books[oldIndex] = book;
            cout << "Changed" << endl;
        }
        else if (command == "QUIT" || command == "EXIT") {
            cout << "Good bye!" << endl;
            break;
        }
    }

    return 0;
}