#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <unistd.h>
#include <time.h>

using namespace std;

void PressEnterToContinue() {
  int c;
  cout << "Press ENTER to continue...";
  fflush(stdout);
  do c = getchar(); 
  while ((c != '\n') && (c != EOF));
}

void start(vector<vector<bool>> &board, int size, int lives) {
    for (int i = 0; i < size; i++) for (int e = 0; e < size; e++) board[i][e] = false;

    srand(time(NULL));
    vector<pair<int, int>> log;
    for (int i = 0; i < lives; i++) {
        int xcord = rand() % size;
        int ycord = rand() % size;
        if (xcord == size) xcord -= 1;
        if (ycord == size) ycord -= 1;
        board[xcord][ycord] = true;
    }
}

void turn(vector<vector<bool>> &board, int size, int lives) {
    for (int i = 0; i < size; i++) {
        int numlives = 0;
        for (int e = 0; e < size; e++) {
            int neighbors = 0;
            bool corner = false;
            bool side = false;
            bool topbottom = false;

            if ((e == 0 || e == size) && (i == 0 || i == size)) corner = true;
            else if (e == 0 || e == size) topbottom = true;
            else if (i == 0 || i == size) side = true;

            if (corner == false && side == false && topbottom == false) {
                if (board[i-1][e-1] == true) neighbors++;
                if (board[i-1][e] == true) neighbors++;
                if (board[i-1][e+1] == true) neighbors++;
                if (board[i][e-1] == true) neighbors++;
                if (board[i][e+1] == true) neighbors++;
                if (i != size-1) if (board[i+1][e-1] == true) neighbors++;
                if (i != size-1) if (board[i+1][e] == true) neighbors++;
                if (i != size-1) if (board[i+1][e+1] == true) neighbors++;
            }

            else if (corner == true && side == false && topbottom == false) {
                if (i == 0 && e == 0) {
                    if (board[i+1][e] == true) neighbors++;
                    if (board[i+1][e+1] == true) neighbors++;
                    if (board[i][e+1] == true) neighbors++;
                }
                else if (i == 0 && e == size) {
                    if (board[i][e-1] == true) neighbors++;
                    if (board[i+1][e-1] == true) neighbors++;
                    if (board[i+1][e] == true) neighbors++;
                }
                else if (i == size && e == 0) {
                    if (board[i-1][e] == true) neighbors++;
                    if (board[i-1][e+1] == true) neighbors++;
                    if (board[i][e+1] == true) neighbors++;
                }
                else if (i == size && e == size) {
                    if (board[i-1][e] == true) neighbors++;
                    if (board[i-1][e-1] == true) neighbors++;
                    if (board[i][e-1] == true) neighbors++;
                }
            }

            else if (corner == false && side == true && topbottom == false) {
                if (e == 0) {
                    if (board[i-1][e+1] == true) neighbors++;
                    if (board[i][e+1] == true) neighbors++;
                    if (board[i+1][e+1] == true) neighbors++;
                    if (board[i-1][e] == true) neighbors++;
                    if (board[i+1][e] == true) neighbors++;
                }
                else if (e == size) {
                    if (board[i-1][e-1] == true) neighbors++;
                    if (board[i][e-1] == true) neighbors++;
                    if (board[i+1][e-1] == true) neighbors++;
                    if (board[i-1][e] == true) neighbors++;
                    if (board[i+1][e] == true) neighbors++;
                }
            }

            else if (corner == false && side == false && topbottom == true) {
                if (i == 0) {
                    if (board[i+1][e-1] == true) neighbors++;
                    if (board[i+1][e] == true) neighbors++;
                    if (board[i+1][e+1] == true) neighbors++;
                    if (board[i][e-1] == true) neighbors++;
                    if (board[i][e+1] == true) neighbors++;
                }
                else if (i== size) {
                    if (board[i-1][e-1] == true) neighbors++;
                    if (board[i-1][e] == true) neighbors++;
                    if (board[i-1][e+1] == true) neighbors++;
                    if (board[i][e-1] == true) neighbors++;
                    if (board[i][e+1] == true) neighbors++;
                }
            }

            if (board[i][e] == true && (neighbors < 2 || neighbors > 3)) board[i][e] = false;
            else if (board[i][e] == false && neighbors == 3) board[i][e] = true;
        }

        for (int j = 0; j < size; j++) for (int b = 0; b < size; b++) if (board[j][b] == true) numlives++;
        
        if (numlives < 3) {
            cout << "Game Over. ";
            PressEnterToContinue();
            start(board, size, lives);
        }
    }
}

void print(vector<vector<bool>> board, int size) {
    for (int i = 0; i < size; i++) {
        for (int e = 0; e < size; e++) {
            string output;
            if (board[i][e] == true) output = "■ ";
            else output = "  ";
            cout << output;
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    string input;
    cout << "Input Size" << endl;
    cin >> input;

    float size = stoi(input) - 1;
    float startinglives = (size*size) / (17);
    vector<bool> player(size, false);
    vector<vector<bool>> row(size, player);

    start(row, size, startinglives);
    do {
        vector<vector<bool>> temp = row;
        turn(row, size, (startinglives/4));
        if (temp == row) {
            cout << "Game over. ";
            PressEnterToContinue();
            start(row, size, startinglives);
        }
        
        print(row, size);
        usleep(80000);
    } while (true);

    return 0;
}