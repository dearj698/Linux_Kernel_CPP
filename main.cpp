#include <iostream>

using namespace std;
int main() {
    string name;
    cout << "enter your name: ";
    getline(cin, name);
    std::cout << "Hello! " <<name<< std::endl;
    return 0;
}