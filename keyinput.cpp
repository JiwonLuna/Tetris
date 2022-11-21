#include <iostream>
#include <conio.h>
#include <Windows.h>

#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75

void gotoXY(int, int);

int main() {
    
    int input;
    int x = 0;
    int y = 0;

    while(true){
        system("cls");
        gotoXY(x, y);
        std::cout << "@";
        
        input = _getch();


        if (input ==224){
            input = _getch();
        }
        if (input == UP){
            y -= 1;
            if (y < 1) {
                y = 0;
            }
        }
        else if (input == DOWN) {
            y += 1;
            if(y < 1) {
                y = 0;
            }
        }
        else if (input == RIGHT) {
            x += 1;
            if (x < 1) {
                x = 0;
            }
        }
        else if (input == LEFT) {
            x -= 1;
            if (x < 1) {
                x = 0;
            }
        }
        // input = _getch();
        // std::cout << input << std::endl;
    }
    return 0;
}


void gotoXY(int x, int y) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}


