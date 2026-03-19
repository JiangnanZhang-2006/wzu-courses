#include <iostream>
#include <string>
using namespace std;

int main() {
    while (true) {
        string cmd;
        cin >> cmd;
        if (cmd == "Insert") {
            cout << "Insert:" << endl;
        }
        else if (cmd == "List") {
            cout << "List:" << endl;
        }
        else if (cmd == "Find") {
            cout << "Find:" << endl;
        }
        else if (cmd == "Change") {
            cout << "Change:" << endl;
        }
        else if (cmd == "Delete") {
            cout << "Delete:" << endl;
        }
        else if (cmd == "Quit" || cmd == "Exit") {
            cout << "Good bye!" << endl;
            break;
        }
    }
    return 0;
}