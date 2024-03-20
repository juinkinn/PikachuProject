#include "Gameplay.h"
#include "Music.h"

int main() {
    initWindow(1000, 500);

    int status;
    player p;
    
    thread t(playMusic);                    //nhạc
    
    while ((status = mainMenu()) != 2) {
        switch (status)
        {
        case 0: //play
            getPlayerInfo(p);       //input thông tin người chơi
            clearInstruction(p);    //xóa Instructions để vào game
            playGame(p);
            break;
        case 1: //leaderboard
            readLeaderBoard();
            break;
        default: //exit
            break;
        }
    }
}
