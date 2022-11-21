#include <iostream>
#include <conio.h>
#include <Windows.h>

#define width 12
#define height 23
#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75

// �迭���� �������� ǥ���ϰ� �ֱ⿡ �Ϲ����� �׷��Ȱ��� �ٸ��ٴ� ���� �׻� �������.

class Tetris {
    const char* full = "��";
    const char* empty = "��";
    int core_x;     // ���� �ھ� x��ǥ 1~10 (���� -> ������)
    int core_y;     // ���� �ھ� y��ǥ 23~1 (�� -> �Ʒ�)
    int rotation;   // ȸ�� ���¸� ��Ÿ���� ���� 1~4

    public:
    Tetris();
    int tet[height][width] = { 0 };
    void show_stat_num();
    void show_stat_sym();
    void set_edge();
    void gen_block();

    // ���� �����ؾ��ϴ� ����(���)�� width 1~10, height 1~22.
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
                    // ���� ����Ű, ȸ��
                    currentPosY -= 1;
                    setCursorPos(currentPosX, currentPosY);
                    printf("��");
                    break;

                case 80:
                    // �Ʒ��� ����Ű, ������ �ϰ�(�ð��� �պ����ϳ�...)
                    currentPosY += 1;
                    setCursorPos(currentPosX, currentPosY);
                    printf("��");
                    break;

                case 75:
                    // ���� ����Ű, �������� �̵�
                    currentPosX -= 2;
                    setCursorPos(currentPosX, currentPosY);
                    printf("��");
                    break;

                case 77:
                    // ������ ����Ű, ���������� �̵�
                    currentPosX += 2;
                    setCursorPos(currentPosX, currentPosY);
                    printf("��");
                    break;

                default:
                    break;
                }
        }
    }
    return 0;
}