#include "Matching.h"

bool checkNext(CELL** board, int y1, int x1, int y2, int x2) {
    if ((y1 == y2 + 1 || y1 == y2 - 1) && (x1 == x2)) {     //Xét hai phần tử kế nhau theo cột
        if (board[y1][x1].c == board[y2][x2].c)
            return true;
    }
    if ((x1 == x2 + 1 || x1 == x2 - 1) && (y1 == y2)) {     //Xét hai phần tử kế nhau theo hàng
        if (board[y1][x1].c == board[y2][x2].c)
            return true;
    }
    return false;
}

bool checkLine(CELL** board, int y1, int x1, int y2, int x2) {
    if (y1 == y2) {
        int y, x, count = 0;
        if (x1 > x2) {
            x = x2;
            y = x1;
        }
        else {
            x = x1;
            y = x2;
        }
        for (int i = x; i <= y; i++) {          //Xét từ ô 1 đến ô 2 tồn tại hơn hoặc bằng 2 ô thì sai
            if (board[y1][i].isValid) {
                count++;
                if (count == 2) return false;
            }
        }
        if ((count == 1) && ((!board[y1][x1].isValid && board[y2][x2].isValid) || (board[y1][x1].isValid && !board[y2][x2].isValid))) {
            return true;        //từ ô 1 đến ô 2 tồn tại duy nhất 1 ô && TH chỉ 1 trong 2 ô tồn tại
        }
        else if (count == 0) {  //TH từ ô 1 đến ô 2 không tồn tại ô nào (bao gồm cả TH cả 2 ô không tồn tại)
            return true;
        }
        return false;
    }
    if (x1 == x2) {
        int x, y, count = 0;
        if (y1 > y2) {
            x = y2;
            y = y1;
        }
        else {
            x = y1;
            y = y2;
        }
        for (int i = x; i <= y; i++) {
            if (board[i][x1].isValid) {
                count++;
                if (count == 2) return false;
            }
        }
        if ((count == 1) && ((!board[y1][x1].isValid && board[y2][x2].isValid) || (board[y1][x1].isValid && !board[y2][x2].isValid))) {
            return true;
        }
        else if (count == 0) {
            return true;
        }
        return false;
    }
    return false;
}

bool checkImatching(CELL** board, int y1, int x1, int y2, int x2) {
    if (y1 == y2) {
        int y, x;
        if (x1 > x2) {
            x = x2;
            y = x1;
        }
        else {
            x = x1;
            y = x2;
        }
        for (int i = x + 1; i < y; i++) {       //check giữa ô 1 và ô 2 có tồn tại ô nào không, nếu có thì sai
            if (board[y1][i].isValid) {
                return false;
            }
        }
        return true;
    }
    if (x1 == x2) {
        int x, y;
        if (y1 > y2) {
            x = y2;
            y = y1;
        }
        else {
            x = y1;
            y = y2;
        }
        for (int i = x + 1; i < y; i++) {
            if (board[i][x1].isValid) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool checkLmatching(CELL** board, int y1, int x1, int y2, int x2) {
    if (y1 == y2 || x1 == x2) {     //TH hai ô cùng nằm trên một hàng (cột) -> không tạo chữ L
        return false;
    }
    bool c1, c2;
    if (!board[y1][x2].isValid) {
        c1 = checkLine(board, y1, x1, y1, x2);      //check từ ô kế ô 1 đến ô là góc của hình chữ L xem có tồn tại ô nào nữa không nếu có thì sai
        c2 = checkLine(board, y2, x2, y1, x2);      //check từ ô góc chữ L đến trước ô 2
        if (c1 && c2) {
            return true;
        }
    }
    if (!board[y2][x1].isValid) {
        c1 = checkLine(board, y1, x1, y2, x1);
        c2 = checkLine(board, y2, x2, y2, x1);
        if (c1 && c2) {
            return true;
        }
    }
    return false;
}

bool checkZmatching(CELL** board, int y1, int x1, int y2, int x2) {
    if (y1 == y2 || x1 == x2) {     //TH hai ô cùng nằm trên một hàng (cột) -> không tạo chữ Z
        return false;
    }
    bool c1, c2, c3;
    int x, y;
    if (x2 < x1) {
        x = x2;
        y = x1;
    }
    else {
        x = x1;
        y = x2;
    }
    for (int i = x + 1; i < y; i++) {
        c3 = checkLine(board, y1, i, y2, i);        //Check xem có cột nào trống hoàn toàn trong phạm vi hình chữ nhật từ ô 1 đến ô 2 không
        if (c3) {
            c1 = checkLine(board, y1, x1, y1, i);   //check xem có đường ra từ ô 1 đến cột đã check không
            c2 = checkLine(board, y2, x2, y2, i);   //check xem có đường ra từ ô 2 đến cột đã check không
            if (c1 && c2)
                return true;
        }
    }
    if (y2 < y1) {
        x = y2;
        y = y1;
    }
    else {
        x = y1;
        y = y2;
    }
    for (int i = x + 1; i < y; i++) {
        c3 = checkLine(board, i, x1, i, x2);
        if (c3) {
            c1 = checkLine(board, y1, x1, i, x1);
            c2 = checkLine(board, y2, x2, i, x2);
            if (c1 && c2)
                return true;
        }
    }
    return false;
}

bool checkUmatching(CELL** board, int y1, int x1, int y2, int x2) {
    if (((y1 == y2) && (y1 == 0 || y1 == BOARDHEIGHT - 1) || ((x1 == x2) && (x1 == 0 || x2 == BOARDWIDTH - 1)))) {
        return true;        //Check các phần tử ngoài rìa của bảng
    }       
    bool c1, c2, c3;
    int x, y;
    if (x2 < x1) {
        x = x2;
        y = x1;
    }
    else {
        x = x1;
        y = x2;
    }
    for (int i = 0; i < BOARDWIDTH; i++) {
        if (i <= x || i >= y) {
            c3 = checkLine(board, y1, i, y2, i);        //Check xem có cột nào trống hoàn toàn không
            if (c3) {
                c1 = checkLine(board, y1, x1, y1, i);   //Check xem có đường ra từ ô 1 đến cột đã check không
                c2 = checkLine(board, y2, x2, y2, i);   //Check xem có đường ra từ ô 2 đến cột đã check không
                if (c1 && c2) {
                    return true;
                }
            }
            else if (i == 0 || i == (BOARDWIDTH - 1)) { //Check TH xét cột đầu và cột cuối nếu từ ô 1, ô 2 đến cột đó có đường đi thì đúng
                c1 = checkLine(board, y1, x1, y1, i);
                c2 = checkLine(board, y2, x2, y2, i);
                if ((c1 && c2) || (c1 && x2 == i) || (x1 == i && c2)) {
                    return true;
                }
            }
        }
    }

    if (y2 < y1) {
        x = y2;
        y = y1;
    }
    else {
        x = y1;
        y = y2;
    }
    for (int i = 0; i < BOARDHEIGHT; i++) {
        if (i <= x || i >= y) {
            c3 = checkLine(board, i, x1, i, x2);
            if (c3) {
                c1 = checkLine(board, y1, x1, i, x1);
                c2 = checkLine(board, y2, x2, i, x2);
                if (c1 && c2) {
                    return true;
                }
            }
            else if (i == 0 || i == (BOARDHEIGHT - 1)) {
                c1 = checkLine(board, y1, x1, i, x1);
                c2 = checkLine(board, y2, x2, i, x2);
                if ((c1 && c2) || (c1 && y2 == i) || (y1 == i && c2)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool checkAll(CELL** board, int y1, int x1, int y2, int x2) {//kiểm tra tất cả các trường hợp matching có hợp lệ
    if (checkNext(board, y1, x1, y2, x2)) {
        return true;
    }
    else if (checkImatching(board, y1, x1, y2, x2)) {
        return true;
    }
    else if (checkLmatching(board, y1, x1, y2, x2)) {
        return true;
    }
    else if (checkZmatching(board, y1, x1, y2, x2)) {
        return true;
    }
    else if (checkUmatching(board, y1, x1, y2, x2)) {
        return true;
    }
    return false;
}

bool checkValidPairs(CELL** board) { //kiểm tra 2 ô đã chọn có kí tự giống nhau không
    char check = 'A';
    while (check >= 'A' && check <= 'Z') {
        int count = 0;
        int* pos = new int[BOARDHEIGHT * BOARDWIDTH];
        for (int i = 0; i < BOARDHEIGHT; i++) {
            for (int j = 0; j < BOARDWIDTH; j++) {
                if (board[i][j].c == check && board[i][j].isValid) {
                    pos[count++] = i;
                    pos[count++] = j;
                }
            }
        }
        for (int i = 0; i < count - 2; i += 2) {
            for (int j = i + 2; j < count; j += 2) {
                if (checkAll(board, pos[i], pos[i + 1], pos[j], pos[j + 1])) {
                    delete[] pos;
                    return true;
                }
            }
        }
        check++;
        delete[] pos;
    }
    return false;
}