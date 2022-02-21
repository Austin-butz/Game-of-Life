#include <iostream>
#include <string>

using namespace std;

void checkscreensize() {
    for (int i = 1; i < 200; i++) cout << i << endl;
}

void checkinput() {
    int input;
    input = getchar();
    if (input == '\n' || input == EOF) cout << "yes" << endl;
    else cout << "no" << endl;
}

int main() {
    //checkscreensize();
    checkinput();
    return 0;
}