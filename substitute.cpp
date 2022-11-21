#include <iostream>
#include <conio.h>
#include <Windows.h>

#define width 12
#define height 23
#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75

// 배열에서 움직임을 표현하고 있기에 일반적인 그래픽과는 다르다는 점을 항상 명심하자.

class Tetris {
    const char* full = "■";
    const char* empty = "□";
    int core_x;     // 블럭의 코어 x좌표 1~10 (왼쪽 -> 오른쪽)
    int core_y;     // 블럭의 코어 y좌표 23~1 (위 -> 아래)
    int rotation;   // 회전 상태를 나타내는 인자 1~4

    public:
    Tetris();
    int tet[height][width] = { 0 };
    void show_stat_num();
    void show_stat_sym();
    void set_edge();
    void gen_block();

    // 블럭이 존재해야하는 공간(경계)은 width 1~10, height 1~22.
    void up_arrow();
    void down_arrow();
    void left_arrow();
    void right_arrow();
    void down_natural();
};

Tetris::Tetris() {
    core_x = 5;
    core_y = 23;
    rotation = 1;
}

void Tetris::show_stat_num() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::cout << tet[i][j];
        }
        std::cout << std::endl;
    }
}

void Tetris::show_stat_sym() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if(tet[i][j]==1){
                std::cout << full;
            }
            else if(tet[i][j]==0) {
                std::cout << empty;
            }
        }
        
        std::cout << std::endl;
    }
}

void Tetris::set_edge() {
    for (int i = 0; i < width; i++) {
        tet[height-1][i] = 1;
        tet[0][i] = 1;
    }
    for (int i = 1; i < (height-1); i++) {
        tet[i][0] = 1;
        tet[i][width-1] = 1;
    }
}

void Tetris::gen_block() {
    
}

void Tetris::up_arrow() {

}

void Tetris::down_arrow() {

}

void Tetris::left_arrow() {

}

void Tetris::right_arrow() {

}

void Tetris::down_natural() {

}

int main() {
    Tetris tet;
    tet.set_edge();
    
    tet.show_stat_num();
    tet.show_stat_sym();
    
    while(true) {
        if(kbhit()) {
            int pressed_key = getch();
            switch(pressed_key) {
                case 72:
                    // 위쪽 방향키, 회전
                    currentPosY -= 1;
                    setCursorPos(currentPosX, currentPosY);
                    printf("■");
                    break;

                case 80:
                    // 아래쪽 방향키, 빠르게 하강(시간을 손봐야하나...)
                    currentPosY += 1;
                    setCursorPos(currentPosX, currentPosY);
                    printf("■");
                    break;

                case 75:
                    // 왼쪽 방향키, 왼쪽으로 이동
                    currentPosX -= 2;
                    setCursorPos(currentPosX, currentPosY);
                    printf("■");
                    break;

                case 77:
                    // 오른쪽 방향키, 오른쪽으로 이동
                    currentPosX += 2;
                    setCursorPos(currentPosX, currentPosY);
                    printf("■");
                    break;

                default:
                    break;
                }
        }
    }
    return 0;
}