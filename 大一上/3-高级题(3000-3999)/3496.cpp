#include <bits/stdc++.h>
using namespace std;

int main() {
    int invalid_person_count = 0, invalid_object_count = 0, person_total, invalid_object_total;
    cin >> person_total >> invalid_object_total;
    unordered_set<string> invalid_objects;
    for (int i = 0; i < invalid_object_total; ++i) {
        string obj;
        cin >> obj;
        invalid_objects.insert(obj);
    }
    for (int i = 0; i < person_total; ++i) {
        string person_name;
        int object_count;
        cin >> person_name >> object_count;
        bool is_invalid_person = false;
        for (int j = 0; j < object_count; ++j) {
            string obj;
            cin >> obj;
            if (invalid_objects.find(obj) != invalid_objects.end()) {
                invalid_object_count++;
                if (!is_invalid_person) cout << person_name << ": " << obj;
                else cout << ' ' << obj;
                is_invalid_person = true;
            }
        }
        if (is_invalid_person) {
            cout << '\n';
            ++invalid_person_count;
        }
    }
    cout << invalid_person_count << ' ' << invalid_object_count << '\n';
}