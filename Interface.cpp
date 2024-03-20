#include "Interface.h"
#include "Gameplay.h"
#include <iostream>
#include<conio.h>

void readLeaderBoard() {
    //ghi 2 đề mục leaderboard,name và point
    goToXY(60, 5);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << "LEADERBOARD";
    goToXY(30, 6);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    cout << "NAME";
    goToXY(100, 6);
    cout << "POINT";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    goToXY(30, 7);
    for (int i = 0; i < 75; i++) {
        cout << "=";
    }

    fstream f;
    f.open("LeaderBoard.bin", ios::binary | ios::in);
    if (f.is_open()) {
        player p;

        int i = 0;
        while (f.read(reinterpret_cast<char*>(&p.name), sizeof(p.name))) { // readname
            f.read(reinterpret_cast<char*>(&p.point), sizeof(p.point)) >> p.point; //read point
            goToXY(30, 7 + i);
            for (int j = 0; j < 75; j++) {
                cout << "=";
            }
            if (i <= 4) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4 - i / 2);
            goToXY(30, 8 + i);
            cout << p.name; //write name
            goToXY(100, 8 + i);
            cout << p.point; // write point
            if (i <= 4) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            i += 2;
        }
        f.close();
    }
    _getch();
    system("cls");
}// read file leaderboard

void writeLeaderBoard(player p) {
    fstream f;
    f.open("LeaderBoard.bin", ios::binary | ios::in);
    if (f.is_open()) {
        player* list = new player[10];
        int no_player = 0;
        string s;

        while (f.read(reinterpret_cast<char*>(&s), sizeof(s))) {
            list[no_player].name = s;           //write player's name
            f.write(reinterpret_cast<char*>(&list[no_player].point), sizeof(list[no_player].point));       //write player's point                      
            no_player++;                        //increase number of players
        }

        int index = no_player - 1;
        for (index; index >= 0; index--) {
            if (p.point <= list[index].point) {
                break;
            }
        }

        if (no_player < 10) {
            for (int i = no_player; i > index + 1; i--) {
                list[i] = list[i - 1];
            }
            list[index + 1] = p;
            no_player++;
        }
        else {
            if (index != no_player - 1) {
                for (int i = no_player - 1; i > index + 1; i--) {
                    list[i] = list[i - 1];
                }
                list[index + 1] = p;
            }
        }//sắp xếp lại info theo point
        f.close();

        f.open("LeaderBoard.bin", ios::binary | ios::in);

        for (int i = 0; i < no_player; i++) {
            f.write(reinterpret_cast<char*>(&list[i].name), sizeof(list[i].name));
            f.write(reinterpret_cast<char*>(&list[i].point), sizeof(list[i].point));
        }

        f.close();

        delete[]list;
    }
    else { 
        f.open("LeaderBoard.bin", ios::binary | ios::in);
        f.write(reinterpret_cast<char*>(&p.name), sizeof(p.name));
        f.write(reinterpret_cast<char*>(&p.point), sizeof(p.point));
        f.close();
    }
}  //ghi info vào leaderboard 

void getPlayerInfo(player& p) {
    //22127478 code(line 106 ->113)--------------
    goToXY(0, 26);
    for (int i = 0; i < 120; i++)
        cout << "*";
    goToXY(0, 0);
    for (int i = 0; i < 120; i++)
        cout << "*";
    displayInstruction(p);
    //-------------------------------------------
    goToXY(50, 12);
    cout << "Enter player name: ";
    cin >> p.name;
    cin.ignore();
    p.life = 3;
    p.point = 0;
}//input info nguoi choi

void displayStatus(bool win) {
    if (win) {//Winning verify
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
        goToXY(50, 10);
        cout << "__  ______  __  __  _      ______  _  __";
        goToXY(50, 11);
        cout << "\\ \\/ / __ \\/ / / / | | /| / / __ \\/ |/ /";
        goToXY(50, 12);
        cout << " \\  / /_/ / /_/ /  | |/ |/ / /_/ /    /";
        goToXY(50, 13);
        cout << " /_/\\____/\\____/   |__/|__/\\____/_/|_/";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        goToXY(58, 16);
        cout << "THANK YOU FOR PLAYING!";
    }
    else {//Losing verify
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
        goToXY(50, 10);
        cout << "__  ______  __  __  __   ____  ________";
        goToXY(50, 11);
        cout << "\\ \\/ / __ \\/ / / / / /  / __ \\/ __/ __/";
        goToXY(50, 12);
        cout << " \\  / /_/ / /_/ / / /__/ /_/ /\\ \\/ _/";
        goToXY(50, 13);
        cout << " /_/\\____/\\____/ /____/\\____/___/___/";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        goToXY(58, 16);
        cout << "TRY AGAIN NEXT TIME";
    }
}//game finish verify

void getBackground(char bg[][41]) {
    ifstream fin("pika.txt");
    if (fin) {
        for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 41; j++)
            {
                bg[i][j] = fin.get();
            }
            fin.ignore();
        }
        fin.close();
    }
    else {
        memset(bg, ' ', sizeof(bg));
    }
}//read file and display background game

void displayBackground(char bg[][41], int x, int y) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 11; j++) {
            goToXY((x + 1) * 10 + j, (y + 1) * 4 + i);
            cout << bg[y * 4 + i][x * 10 + j];
        }
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

int mainMenu() { // display menu
    int choice[3] = { 0,0,0 }, temp, key, curChoice = 0;

    goToXY(48, 2);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "          _                              ";
    goToXY(45, 3);
    cout << " _ __   ___ | | _____ _ __ ___   ___  _ __  ";
    goToXY(45, 4);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
    cout << "| '_ \\ / _ \\| |/ / _ \\ '_ ` _ \\ / _ \\| '_ \\ ";
    goToXY(45, 5);
    cout << "| |_) | (_) |   <  __/ | | | | | (_) | | | |";
    goToXY(45, 6);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
    cout << "|.__ / \\___/|_|\\_\\___|_| |_| |_|\\___/|_| |_|";
    goToXY(45, 7);
    cout << "|_|                                         ";
    // print Title
    while (1) {

        choice[curChoice] = 1;

        if (choice[0]) {// PLAY option
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112); // 112 = background_color * 16 (WHITE = 7)

            for (int i = 0; i < 3; i++) {
                goToXY(60, 13 + i);
                cout << "               ";
            }

            goToXY(65, 14);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112 + 2); // 112 = background_color * 16 + text_color
            cout << "PLAY";
        }
        else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

            for (int i = 0; i < 3; i++) {
                goToXY(60, 13 + i);
                cout << "               ";
            }

            goToXY(65, 14);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
            cout << "PLAY";
        }

        if (choice[1]) {//LEADERBOARD OPTION
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);

            for (int i = 0; i < 3; i++) {
                goToXY(60, 16 + i);
                cout << "               ";
            }

            goToXY(62, 17);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112 + 6);
            cout << "LEADERBOARD";
        }
        else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

            for (int i = 0; i < 3; i++) {
                goToXY(60, 16 + i);
                cout << "               ";
            }

            goToXY(62, 17);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
            cout << "LEADERBOARD";
        }

        if (choice[2]) {// EXIT OPTION
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);

            for (int i = 0; i < 3; i++) {
                goToXY(60, 19 + i);
                cout << "               ";
            }

            goToXY(65, 20);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112 + 4);
            cout << "EXIT";
        }
        else {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

            for (int i = 0; i < 3; i++) {
                goToXY(60, 19 + i);
                cout << "               ";
            }

            goToXY(65, 20);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            cout << "EXIT";
        }
        
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

        if (temp = _getch()) {
            if (temp != 224 && temp)
            {
                if (temp == ENTER_KEY) {
                    system("cls");
                    return curChoice;
                }
            }
            else {
                key = _getch();
                switch (key)
                {
                case KEY_UP:
                    choice[curChoice] = 0;
                    if (curChoice > 0) curChoice--;
                    else curChoice = 2;
                    break;
                case KEY_DOWN:
                    choice[curChoice] = 0;
                    if (curChoice < 2) curChoice++;
                    else curChoice = 0;
                default:
                    break;
                }
            }
        }
    }
}