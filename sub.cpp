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


// �迭���� �������� ǥ���ϰ� �ֱ⿡ �Ϲ����� �׷��Ȱ��� �ٸ��ٴ� ���� �׻� �������.

class Tetris {
    const char* full = "��";
    const char* empty = "��";
    char block_type;
    int core_x;     // ���� �ھ� x��ǥ 1~10 (���� -> ������)
    int core_y;     // ���� �ھ� y��ǥ 1~23 (�� -> �Ʒ�)
    int rotation;   // ȸ�� ���¸� ��Ÿ���� ���� 1~4


    public:
    Tetris();
    
    int tet[width][height] = { 0 };
    void show_stat_num();
    void show_stat_sym();
    void set_edge();
    void gen_block(char type);
    void block(int rot, int onoff);
    
    int check_sum();
    // ���� �����ؾ��ϴ� ����(���)�� width 1~10, height 1~22.
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
    for (int i = 4; i < height-1; i++) {
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
        tet[i][height-2] = On;
    }
    for (int i = 0; i < (height-1); i++) {
        tet[0][i] = On;
        tet[width-1][i] = On;
    }
}

void Tetris::gen_block(char type) {
    block_type = type;
    core_x = startx;
    core_y = starty;
    rotation = 0;
}

void Tetris::block(int rot, int onoff) {
    
    rotation = rot;
    tet[core_x][core_y] = onoff;

    switch(block_type) {
        
        case 'i':
        tet[core_x][core_y-1] = onoff;
        tet[core_x][core_y+1] = onoff;
        tet[core_x][core_y+2] = onoff;
        break;

        case 'o':
        tet[core_x+1][core_y] = onoff;
        tet[core_x][core_y-1] = onoff;
        tet[core_x+1][core_y-1] = onoff;
        break;

        case 'z':
        tet[core_x-1][core_y] = onoff;
        tet[core_x][core_y+1] = onoff;
        tet[core_x+1][core_y+1] = onoff;
        break;

        case 's':
        tet[core_x+1][core_y] = onoff;
        tet[core_x][core_y+1] = onoff;
        tet[core_x-1][core_y+1] = onoff;
        break;
        
        case 'j':
        tet[core_x][core_y-1] = onoff;
        tet[core_x][core_y+1] = onoff;
        tet[core_x-1][core_y+1] = onoff;
        break;

        case 'l':
        tet[core_x][core_y-1] = onoff;
        tet[core_x][core_y+1] = onoff;
        tet[core_x+1][core_y+1] = onoff;
        break;

        case 't':
        tet[core_x][core_y-1] = onoff;
        tet[core_x-1][core_y] = onoff;
        tet[core_x+1][core_y] = onoff;
        break;
    }

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
    
}

void Tetris::down_arrow() {

}

void Tetris::left_arrow() {
    int check = check_sum();
    block(rotation, Off);
    core_x -= 1;
    block(rotation, On);
    if(check != check_sum()) {
        block(rotation,Off);
        core_x +=1;
    }
    block(rotation, On);
    
}

void Tetris::right_arrow() {
    int check = check_sum();
    block(rotation, Off);
    core_x += 1;
    block(rotation, On);
    if(check != check_sum()) {
        block(rotation, Off);
        core_x -=1;
    }
    block(rotation, On);
}

void Tetris::down_natural() {
    int check = check_sum();
    block(rotation, Off);
    core_y += 1;
    block(rotation, On);
    if(check != check_sum()) {
        block(rotation, Off);
        core_y -=1;
    }
    block(rotation, On);
}

int main() {
    system("cls");
    Tetris tet;
    tet.set_edge();
    tet.show_stat_sym();
    tet.gen_block('j');
    tet.block(0,On);

    int input;

    while(true) {
        
        input = _getch();

        if (input ==224){
            system("cls");
            input = _getch();
        }
        if (input == UP){
            
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
    //                 // ���� ����Ű, ȸ��
    //                 currentPosY -= 1;
    //                 setCursorPos(currentPosX, currentPosY);
    //                 printf("��");
    //                 break;

    //             case 80:
    //                 // �Ʒ��� ����Ű, ������ �ϰ�(�ð��� �պ����ϳ�...)
    //                 currentPosY += 1;
    //                 setCursorPos(currentPosX, currentPosY);
    //                 printf("��");
    //                 break;

    //             case 75:
    //                 // ���� ����Ű, �������� �̵�
    //                 currentPosX -= 2;
    //                 setCursorPos(currentPosX, currentPosY);
    //                 printf("��");
    //                 break;

    //             case 77:
    //                 // ������ ����Ű, ���������� �̵�
    //                 currentPosX += 2;
    //                 setCursorPos(currentPosX, currentPosY);
    //                 printf("��");
    //                 break;

    //             default:
    //                 break;
    //             }
    //     }
    // }
    return 0;
}