#include <iostream>
#include <conio.h>
#include <Windows.h>

#define width 12
#define height 26
#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
#define On 1
#define Off 0
#define startx 5
#define starty 2


// 배열에서 움직임을 표현하고 있기에 일반적인 그래픽과는 다르다는 점을 항상 명심하자.

class Tetris {
    const char* full = "■";
    const char* empty = "□";
    char block_type;
    int core_x;     // 블럭의 코어 x좌표 1~10 (왼쪽 -> 오른쪽)
    int core_y;     // 블럭의 코어 y좌표 1~23 (위 -> 아래)
    int rotation;   // 회전 상태를 나타내는 인자 1~4
    int rotnum;     // 한 블럭이 낙하 전까지 회전한 횟수

    public:
    Tetris();
    
    int tet[width][height] = { 0 };
    void show_stat_num();
    void show_stat_sym();
    void set_edge();
    void gen_block(char type);
    void block(int onoff);
    
    int check_sum();
    // 블럭이 존재해야하는 공간(경계)은 width 1~10, height 1~22.
    void up_arrow();
    void down_arrow();
    void left_arrow();
    void right_arrow();
    void down_natural();
};

Tetris::Tetris() {
    core_x = 5;
    core_y = 2;
    rotation = 0;
}

void Tetris::show_stat_num() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::cout << tet[j][i];
        }
        std::cout << std::endl;
    }
}

void Tetris::show_stat_sym() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if(tet[j][i]==1){
                std::cout << full;
            }
            else if(tet[j][i]==0) {
                std::cout << empty;
            }
        }
        
        std::cout << std::endl;
    }
}

void Tetris::set_edge() {
    for (int i = 0; i < width; i++) {
        tet[i][height-1] = On;
    }
    for (int i = 0; i < height; i++) {
        tet[0][i] = On;
        tet[width-1][i] = On;
    }
}

void Tetris::gen_block(char type) {
    block_type = type;
    core_x = startx;
    core_y = starty;
    rotation = 0;
    rotnum = 0;
}

void Tetris::block(int onoff) {
    
    int l;
    int r;
    int u;
    int d;
    int x = core_x;
    int y = core_y;
    int rot = rotnum % 4;
    
    if(onoff == On){
        tet[x][y] = onoff;

        switch(block_type) {
            
            case 'i':
            tet[x][y-1] = onoff;
            tet[x][y+1] = onoff;
            tet[x][y+2] = onoff;
            break;

            case 'o':
            tet[x+1][y] = onoff;
            tet[x][y-1] = onoff;
            tet[x+1][y-1] = onoff;
            break;

            case 'z':
            tet[x-1][y] = onoff;
            tet[x][y+1] = onoff;
            tet[x+1][y+1] = onoff;
            break;

            case 's':
            tet[x+1][y] = onoff;
            tet[x][y+1] = onoff;
            tet[x-1][y+1] = onoff;
            break;
            
            case 'j':
            tet[x][y-1] = onoff;
            tet[x][y+1] = onoff;
            tet[x-1][y+1] = onoff;
            break;

            case 'l':
            tet[x][y-1] = onoff;
            tet[x][y+1] = onoff;
            tet[x+1][y+1] = onoff;
            break;

            case 't':
            tet[x][y-1] = onoff;
            tet[x-1][y] = onoff;
            tet[x+1][y] = onoff;
            break;
        }
        for(int i = 0; i< rot; i++) {
            // + change
            int first = tet[x][y+1];
            tet[x][y+1] = tet[x+1][y];
            tet[x+1][y] = tet[x][y-1];
            tet[x][y-1] = tet[x-1][y];
            tet[x-1][y] = first;

            // X change
            int second = tet[x-1][y-1];
            tet[x-1][y-1] = tet[x-1][y+1];
            tet[x-1][y+1] = tet[x+1][y+1];
            tet[x+1][y+1] = tet[x+1][y-1];
            tet[x+1][y-1] = second;

        }
    }else if (onoff == Off){
        for(int i = x-1; i<=x+1;i++){
            for(int j = y-1; j <= y+1; j++){
                if(tet[i][j] == 1) {
                    tet[i][j] = 0;
                }
            }
        }
    }
    rotation = rot;
}

int Tetris::check_sum() {
    int sum = 0;
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            sum += tet[j][i];
        }
    }
    return sum;
}

void Tetris::up_arrow() {   // rotation
    block(Off);
    rotnum++;
    // int check = check_sum();
    // int subtet[width][height];
    // for(int i = 0; i < height; i++) {
    //     for(int j = 0; j < width; j++) {
    //         subtet[j][i] = tet[j][i];    
    //     }
    // }
    block(On);
    // if(block_type = 'i') {

    // }
    // // + change
    // int first = tet[core_x][core_y+1];
    // tet[core_x][core_y+1] = tet[core_x+1][core_y];
    // tet[core_x+1][core_y] = tet[core_x][core_y-1];
    // tet[core_x][core_y-1] = tet[core_x-1][core_y];
    // tet[core_x-1][core_y] = first;

    // // X change
    // int second = tet[core_x-1][core_y-1];
    // tet[core_x-1][core_y-1] = tet[core_x-1][core_y+1];
    // tet[core_x-1][core_y+1] = tet[core_x+1][core_y+1];
    // tet[core_x+1][core_y+1] = tet[core_x+1][core_y-1];
    // tet[core_x+1][core_y-1] = second;
    
    
    // if(check != check_sum()) {
    //     block(Off);
    //     for(int i = 0; i < height; i++) {
    //         for(int j = 0; j < width; j++) {
    //             tet[j][i] = subtet[j][i];    
    //         }
    //     }
    //     block(On);
    // }
    
    

}

void Tetris::down_arrow() {

}

void Tetris::left_arrow() {
    int check = check_sum();
    block(Off);
    core_x -= 1;
    block(On);
    if(check != check_sum()) {
        block(Off);
        core_x +=1;
        block(On);
    }
    
    
}

void Tetris::right_arrow() {
    int check = check_sum();
    block(Off);
    core_x += 1;
    block(On);
    if(check != check_sum()) {
        block(Off);
        core_x -=1;
        block(On);
    }
    
}

void Tetris::down_natural() {
    int check = check_sum();
    block(Off);
    core_y += 1;
    block(On);
    if(check != check_sum()) {
        block(Off);
        core_y -=1;
        block(On);
    }
    
}

int main() {
    system("cls");
    Tetris tet;
    tet.set_edge();
    tet.gen_block('j');
    tet.block(On);
    tet.show_stat_sym();

    int input;

    while(true) {
        
        input = _getch();

        if (input ==224){
            system("cls");
            input = _getch();
        }
        if (input == UP){
            tet.up_arrow();
        }
        else if (input == DOWN) {
            tet.down_natural();
        }
        else if (input == RIGHT) {
            tet.right_arrow();
        }
        else if (input == LEFT) {
            tet.left_arrow();
        }
        tet.set_edge();
        tet.show_stat_sym();
    }
    

    // while(true) {
    //     if(kbhit()) {
    //         int pressed_key = getch();
    //         switch(pressed_key) {
    //             case 72:
    //                 // 위쪽 방향키, 회전
    //                 currentPosY -= 1;
    //                 setCursorPos(currentPosX, currentPosY);
    //                 printf("■");
    //                 break;

    //             case 80:
    //                 // 아래쪽 방향키, 빠르게 하강(시간을 손봐야하나...)
    //                 currentPosY += 1;
    //                 setCursorPos(currentPosX, currentPosY);
    //                 printf("■");
    //                 break;

    //             case 75:
    //                 // 왼쪽 방향키, 왼쪽으로 이동
    //                 currentPosX -= 2;
    //                 setCursorPos(currentPosX, currentPosY);
    //                 printf("■");
    //                 break;

    //             case 77:
    //                 // 오른쪽 방향키, 오른쪽으로 이동
    //                 currentPosX += 2;
    //                 setCursorPos(currentPosX, currentPosY);
    //                 printf("■");
    //                 break;

    //             default:
    //                 break;
    //             }
    //     }
    // }
    return 0;
}