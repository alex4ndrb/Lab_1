#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>


using namespace std;

void drawMap(char array[]);
bool userWon(char array[]);
bool aiWon(char array[]);
bool mapIsFull(char array[]);
int miniMax(char array[], string nextUser);


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    system("mode con cols=30 lines=10");
    char map[9] = { ' ',' ',' ',' ',' ',' ',' ',' ',' ' };
    const int KEY_ESC = 27;
    while (true) {
        string player;
        drawMap(map);
        int userStep;
        int indexToKnow = 0;
        cout << "Выберите клетку от 1 to 9" << endl;
        cin >> userStep;
        map[userStep - 1] = 'O';

        if (userWon(map) || mapIsFull(map)) {
            if (userWon(map)) {
                drawMap(map);
                cout << "С победой" << endl;
                cout << "Нажмите escape для выхода" << endl;
                while (_getch() != KEY_ESC);
                return 0;
            }
            else {
                drawMap(map);
                cout << "Ничья" << endl;
                cout << "Нажмите escape для выхода" << endl;
                while (_getch() != KEY_ESC);    
                return 0;
            }
            break;
        }

        player = "user";
        int score = -10;
        for (int i = 0; i < 9; i++) {
            if (map[i] == ' ') {
                map[i] = 'X';
                int minmaxRes = miniMax(map, player);
                map[i] = ' ';
                if (minmaxRes > score) {
                    score = minmaxRes;
                    indexToKnow = i;
                }
            }
        }


        map[indexToKnow] = 'X';

        if (aiWon(map) || mapIsFull(map)) {
            if (aiWon(map)) {
                drawMap(map);
                cout << "Вы проиграли" << endl;
                cout << "Нажмите escape для выхода" << endl;
                while (_getch() != KEY_ESC);         
                return 0;

            }
            else {
                drawMap(map);
                cout << "Ничья" << endl;
                cout << "Нажмите escape для выхода" << endl;
                while (_getch() != KEY_ESC);        
                return 0;
            }
            return 0;
        }

    }
    return 0;
}


int miniMax(char array[9], string nextUser)
{
    int minmaxScore;
    if (aiWon(array) == true) { return 10; }
    else if (userWon(array) == true) { return -10; }
    else if (mapIsFull(array) == true) { return 0; }

    if (nextUser == "ai") {
        minmaxScore = -10;
        for (int i = 0; i < 9; i++) {
            int score;
            if (array[i] == ' ') {
                array[i] = 'X';
                nextUser = "user";
                score = miniMax(array, nextUser);
                array[i] = ' ';
                if (minmaxScore < score) {
                    minmaxScore = score;
                }
            }
        }
        return minmaxScore;
    }

    if (nextUser == "user") {
        minmaxScore = 10;
        for (int i = 0; i < 9; i++) {
            int score;
            if (array[i] == ' ') {
                array[i] = 'O';
                nextUser = "ai";
                score = miniMax(array, nextUser);
                array[i] = ' ';
                if (minmaxScore > score) {
                    minmaxScore = score;
                }
            }
        }
        return minmaxScore;
    }
}

void drawMap(char array[9])
{
    system("cls");
    cout << endl;
    cout << array[0] << "|" << array[1] << "|" << array[2] << endl;
    cout << "-----" << endl;
    cout << array[3] << "|" << array[4] << "|" << array[5] << endl;
    cout << "-----" << endl;
    cout << array[6] << "|" << array[7] << "|" << array[8] << endl;
}

bool userWon(char array[])
{
    for (int i = 0; i < 9; i += 3)
    {
        if ((array[i] == array[i + 1]) && (array[i + 1] == array[i + 2]) && (array[i] == 'O'))
            return true;
    }
    for (int i = 0; i < 3; i++)
    {
        if ((array[i] == array[i + 3]) && (array[i + 3] == array[i + 6]) && (array[i] == 'O'))
            return true;
    }
    if ((array[0] == array[4]) && (array[4] == array[8]) && (array[0] == 'O'))
    {
        return true;
    }
    if ((array[2] == array[4]) && (array[4] == array[6]) && (array[2] == 'O'))
    {
        return true;
    }
    return false;
}

bool aiWon(char array[])
{
    for (int i = 0; i < 9; i += 3)
    {
        if ((array[i] == array[i + 1]) && (array[i + 1] == array[i + 2]) && (array[i] == 'X'))
            return true;
    }
    for (int i = 0; i < 3; i++)
    {
        if ((array[i] == array[i + 3]) && (array[i + 3] == array[i + 6]) && (array[i] == 'X'))
            return true;
    }
    if ((array[0] == array[4]) && (array[4] == array[8]) && (array[0] == 'X'))
    {
        return true;
    }
    if ((array[2] == array[4]) && (array[4] == array[6]) && (array[2] == 'X'))
    {
        return true;
    }
    return false;
}
bool mapIsFull(char array[])
{
    for (int i = 0; i < 9; i++)
    {
        if (array[i] != 'X' && array[i] != 'O')
        {
            return false;
        }
    }
    return true;
}
