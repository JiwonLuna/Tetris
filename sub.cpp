#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

#define width 12
#define height 26
#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
#define On 1
#define Off 0
#define startx 5
#define starty 3


// 배열에서 움직임을 표현하고 있기에 일반적인 그래픽과는 다르다는 점을 항상 명심하자.

class Tetris {
    const char* full = "■";
    const char* empty = "□";
    char block_type;
    int core_x;     // 블럭의 코어 x좌표 1~10 (왼쪽 -> 오른쪽)
    int core_y;     // 블럭의 코어 y좌표 1~23 (위 -> 아래)
    int rotation;   // 회전 상태를 나타내는 인자 1~4
    int rotnum;     // 한 블럭이 낙하 전까지 회전한 횟수
    

    int z[2][4] = {0};


    public:
    Tetris();
    

    int tet[width][height] = { 0 };
    void show_stat_num();
    void show_stat_sym();
    void gotoxy(short x, short y);
    void show_video();
    void set_edge();
    void gen_block();
    void set_block();
    void block_switch(int onoff);
    
    int check_sum();
    // 블럭이 존재해야하는 공간(경계)은 width 1~10, height 1~22.
    void up_arrow();
    void down_arrow();
    void left_arrow();
    void right_arrow();
    void down_natural();
};

Tetris::Tetris() {
    core_x = startx;
    core_y = starty;
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

void Tetris::gotoxy(short x, short y) {
    //x, y 좌표 설정
    COORD pos = {x, y};
    //커서 이동
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}    

void Tetris::show_video() {
    for(int b = 0; b < 4; b++) {
        gotoxy(2*z[0][b], z[1][b]);
        if(z[0][b] == 0 || z[0][b] == 11 || z[1][b] == height-1){
        }else {
            if(tet[z[0][b]][z[1][b]]==0){
            std::cout << "□";
            }else if(tet[z[0][b]][z[1][b]]==1){
                std::cout << "■";
            }
        }
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

void Tetris::gen_block() {
    srand(time(NULL));
    int a = rand() % 7;
    char types[7] = {'i', 'o', 'z', 's', 'j', 'l', 't'};
    block_type = types[a];
    // std::cout << block_type << std::endl;
    rotation = 0;
    rotnum = 0;
}

void Tetris::set_block() {
    switch(block_type) {
            
            case 'i': 
            z[0][0] = core_x;
            z[1][0] = core_y;
            z[0][1] = core_x;
            z[1][1] = core_y-1;
            z[0][2] = core_x;
            z[1][2] = core_y+1;
            z[0][3] = core_x;
            z[1][3] = core_y+2;

            break;
            
            case 'o': 
            z[0][0] = core_x;
            z[1][0] = core_y;
            z[0][1] = core_x+1;
            z[1][1] = core_y;
            z[0][2] = core_x;
            z[1][2] = core_y-1;
            z[0][3] = core_x+1;
            z[1][3] = core_y-1;
            break;
            

            case 'z': 
            z[0][0] = core_x;
            z[1][0] = core_y;
            z[0][1] = core_x-1;
            z[1][1] = core_y;
            z[0][2] = core_x;
            z[1][2] = core_y+1;
            z[0][3] = core_x+1;
            z[1][3] = core_y+1;
            break;
            

            case 's': 
            z[0][0] = core_x;
            z[1][0] = core_y;
            z[0][1] = core_x+1;
            z[1][1] = core_y;
            z[0][2] = core_x;
            z[1][2] = core_y+1;
            z[0][3] = core_x-1;
            z[1][3] = core_y+1;
            break;
            
            case 'j':
            z[0][0] = core_x;
            z[1][0] = core_y;
            z[0][1] = core_x;
            z[1][1] = core_y-1;
            z[0][2] = core_x;
            z[1][2] = core_y+1;
            z[0][3] = core_x-1;
            z[1][3] = core_y+1;
            break;

            case 'l':            
            z[0][0] = core_x;
            z[1][0] = core_y;
            z[0][1] = core_x;
            z[1][1] = core_y-1;
            z[0][2] = core_x;
            z[1][2] = core_y+1;
            z[0][3] = core_x+1;
            z[1][3] = core_y+1;
            break;

            case 't':
            z[0][0] = core_x;
            z[1][0] = core_y;
            z[0][1] = core_x;
            z[1][1] = core_y-1;
            z[0][2] = core_x-1;
            z[1][2] = core_y;
            z[0][3] = core_x+1;
            z[1][3] = core_y;
            break;
        }
}

void Tetris::block_switch(int onoff) {
    int x = core_x;
    int y = core_y;
    int rot = rotation;
            
    for (int b = 0; b<4;b++){
        tet[z[0][b]][z[1][b]] = onoff;
    }
    show_video();
}

int Tetris::check_sum() {
    int sum = 0;
    for(int i = 0; i < height-1; i++) {
        for(int j = 1; j < width-1; j++) {
            sum += tet[j][i];
        }
    }
    return sum;
}

void Tetris::up_arrow() {   // rotation
    if(block_type != 'o'){
        int check = check_sum();
        block_switch(Off);
        
        int save[2][4]={0};

        for(int b = 0; b < 2; b++) {
            for (int c = 0; c < 4; c++){
                save[b][c] = z[b][c];
            }
        }
        for (int b = 1; b<4;b++){
            // + -shape
            if(z[0][b]==z[0][0]-1 && z[1][b] == z[1][0]){   // 코어 왼쪽 칸
                z[0][b]++;
                z[1][b]--;
                //좌표값 오른쪽 위로 이동
            }else if(z[0][b]==z[0][0] && z[1][b] == z[1][0]-1){  // 코어 위쪽 칸
                z[0][b]++;
                z[1][b]++;
                //좌표값 오른쪽 아래로 이동
            }else if(z[0][b]==z[0][0]+1 && z[1][b] == z[1][0]){  // 코어 오른쪽 칸
                z[0][b]--;
                z[1][b]++;
                //좌표값 왼쪽쪽 아래로 이동
            }else if(z[0][b]==z[0][0] && z[1][b] == z[1][0]+1){  // 코어 아래쪽 칸
                z[0][b]--;
                z[1][b]--;
                //좌표값 오른쪽 아래로 이동
            }
            
            // X-shape
            else if(z[0][b]==z[0][0]-1 && z[1][b] == z[1][0]-1){  // 코어 왼쪽위 칸
                z[0][b] += 2;
                // z[1][b]
                //x좌표값 오른쪽으로 2칸 이동
            }else if(z[0][b]==z[0][0]+1 && z[1][b] == z[1][0]-1){  // 코어 오른쪽위 칸
                // z[0][b] += 2;
                z[1][b] += 2;
                //y좌표값 아래쪽으로 2칸 이동
            }else if(z[0][b]==z[0][0]+1 && z[1][b] == z[1][0]+1){  // 코어 오른쪽아래 칸
                z[0][b] -= 2;
                // z[1][b]
                //x좌표값 왼쪽으로 2칸 이동
            }else if(z[0][b]==z[0][0]-1 && z[1][b] == z[1][0]+1){  // 코어 왼쪽아래 칸
                // z[0][b] += 2;
                z[1][b] -= 2;
                //y좌표값 위쪽으로 2칸 이동
            }

            // Just for i-type block
            else if(z[0][b]==z[0][0]-2 && z[1][b] == z[1][0]){  // 코어 2칸 왼쪽 칸
                z[0][b] += 2;
                z[1][b] -= 2;
                //x좌표값 오른쪽으로 2칸 이동, y좌표값 위쪽으로 2칸 이동
            }else if(z[0][b]==z[0][0] && z[1][b] == z[1][0]-2){  // 코어 2칸 위쪽 칸
                z[0][b] += 2;
                z[1][b] += 2;
                //x좌표값 오른쪽으로 2칸 이동, y좌표값 아래쪽으로 2칸 이동
            }else if(z[0][b]==z[0][0]+2 && z[1][b] == z[1][0]){  // 코어 2칸 오른쪽 칸
                z[0][b] -= 2;
                z[1][b] += 2;
                //x좌표값 왼쪽으로 2칸 이동, y좌표값 아래쪽으로 2칸 이동
            }else if(z[0][b]==z[0][0] && z[1][b] == z[1][0]+2){  // 코어 2칸 아래쪽 칸
                z[0][b] -= 2;
                z[1][b] -= 2;
                //x좌표값 왼쪽으로 2칸 이동, y좌표값 위쪽으로 2칸 이동
            }
        }
        block_switch(On);
        
        if(check != check_sum()) {
            block_switch(Off);
            
            for(int b = 0; b < 2; b++) {
                for (int c = 0; c < 4; c++){
                    z[b][c] = save[b][c];
                }
            }
            block_switch(On);
            
        }
    }
}

void Tetris::down_arrow() {

}

void Tetris::left_arrow() {
    int check = check_sum();
    block_switch(Off);
    
    for(int b = 0; b<4; b++){
        z[0][b]--;
    }
    block_switch(On);
    
    if(check != check_sum()) {
        block_switch(Off);
        
        for(int b = 0; b<4; b++){
        z[0][b]++;
        }
        set_edge();
        block_switch(On);
        
    }
    
    
}

void Tetris::right_arrow() {
    int check = check_sum();
    block_switch(Off);
    for(int b = 0; b<4; b++){
        z[0][b]++;
    }
    
    block_switch(On);
    if(check != check_sum()) {
        block_switch(Off);
        for(int b = 0; b<4; b++){
        z[0][b]--;
        }
        set_edge();
        block_switch(On);
    }
    
}

void Tetris::down_natural() {
    int check = check_sum();
    block_switch(Off);
    for(int b = 0; b<4; b++){
        z[1][b]++;
    }
    block_switch(On);
    
    if(check != check_sum()) {
        block_switch(Off);
        for(int b = 0; b<4; b++){
        z[1][b]--;
        }
        set_edge();
        block_switch(On);
    }
    
}

int main() {
    system("cls");
    Tetris tet;
    tet.set_edge();
    tet.gen_block();
    tet.set_block();
    tet.show_stat_sym();
    tet.block_switch(On);

    int input;
    int down_time = (unsigned)time(NULL);
    down_time += 1; // 1초

    int down_num = 0;

    while(true) {
        // system("cls");
        down_num++;


        if(kbhit()) {
            input = _getch();
            

            if (input ==224){
                
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
        }

        if(down_num==20000){
            
            tet.down_natural();

            down_num = 0;

        }

        
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