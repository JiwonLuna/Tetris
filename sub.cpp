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

// color��� ���� 
#define BLACK 0 
#define BLUE 1 
#define GREEN 2 
#define CYAN 3 
#define RED 4 
#define MAGENTA 5 
#define BROWN 6 
#define LIGHTGRAY 7 
#define DARKGRAY 8 
#define LIGHTBLUE 9 
#define LIGHTGREEN 10 
#define LIGHTCYAN 11 
#define LIGHTRED 12 
#define LIGHTMAGENTA 13 
#define YELLOW 14 
#define WHITE 15 


// �迭���� �������� ǥ���ϰ� �ֱ⿡ �Ϲ����� �׷��Ȱ��� �ٸ��ٴ� ���� �׻� �������.

class Tetris {
    const char* full = "��";
    const char* empty = "��";
    char block_type;
    int core_x;     // ���� �ھ� x��ǥ 1~10 (���� -> ������)
    int core_y;     // ���� �ھ� y��ǥ 1~23 (�� -> �Ʒ�)
    int rotation;   // ȸ�� ���¸� ��Ÿ���� ���� 1~4
    int rotnum;     // �� ���� ���� ������ ȸ���� Ƚ��
    int prohibit;   // ���� �̵������� ��Ÿ���� ����

    int z[2][4] = {0};
    int prev_block[2][4] = {0};

    public:
    Tetris();
    

    int tet[width][height] = { 0 };
    int prev_tet[width][height] = { 0 };
    void save_prev_tet();
    void load_prev_tet();

    void show_stat_num();
    void show_stat_sym();
    void gotoxy(short x, short y);
    void cursor_hide();
    void textcolor(int foreground, int background);
    void block_color();
    void show_video();
    void set_edge();
    void gen_block();
    void set_block();
    void block_switch(int onoff);
    void correction_switch(int onoff);
    
    int check_sum();
    // ���� �����ؾ��ϴ� ����(���)�� width 1~10, height 1~22.
    void up_arrow();
    void down_arrow();
    void left_arrow();
    void right_arrow();
    void down_natural();
    void drop();

    int nextblock;
    int gotonextblock();

    void check_clear_line();

};

Tetris::Tetris() {
    core_x = startx;
    core_y = starty;
    rotation = 0;
    nextblock = 0;
    prohibit = 0;
}

void Tetris::save_prev_tet() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            prev_tet[j][i] = tet[j][i];
        }
    }
}

void Tetris::load_prev_tet() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            tet[j][i] = prev_tet[j][i];
        }
    }

    for(int i = 0; i < height; i++){
        for (int j = 0; j < width; j++) {
            gotoxy(2*j, i);
            if(tet[j][i]==0){
                std::cout << empty;
            }else if(tet[j][i]==1){
                std::cout << full;
            }
        }
    }
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
    for(int i = 0; i < height; i++){
        for (int j = 0; j < width; j++) {
            gotoxy(2*j, i);
            if(tet[j][i]==0){
                std::cout << empty;
            }else if(tet[j][i]==1){
                std::cout << full;
            }
        }
    }
}

void Tetris::gotoxy(short x, short y) {
    //x, y ��ǥ ����
    COORD pos = {x, y};
    //Ŀ�� �̵�
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}    

void Tetris::cursor_hide() {
    CONSOLE_CURSOR_INFO ConsoleCursor;
    // ConsoleCursor.dwSize = 1; //Ŀ�� ���� (1 ~ 100)
    ConsoleCursor.bVisible = false; //Ŀ�� Visible TRUE(����) FALSE(����)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ConsoleCursor);
}

void Tetris::textcolor(int foreground, int background) { 
    int color=foreground+background*16; 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color); 
}

void Tetris::block_color() {
    switch(block_type){
        case 'i':
        textcolor(9, 0);
        break;
        
        case 'o':
        textcolor(14, 0);
        break;

        case 'z':
        textcolor(4, 0);
        break;

        case 's':
        textcolor(10, 0);
        break;

        case 'j':
        textcolor(1, 0);
        break;

        case 'l':
        textcolor(12, 0);
        break;

        case 't':
        textcolor(5, 0);
        break;
    }
}

void Tetris::show_video() { // ���� ��ǥ�� ����Ű�� ������ ���� ��ȭ�� ��Ȳ�� ǥ�����ش�.
    for(int b = 0; b < 4; b++) {
        gotoxy(2*z[0][b], z[1][b]);
        if(z[0][b] == 0 || z[0][b] == 11 || z[1][b] == height-1){
        }else {
            if(tet[z[0][b]][z[1][b]]==0){
                // textcolor(15, 0);
                std::cout << empty;
            }else if(tet[z[0][b]][z[1][b]]==1){
                // block_color()sub;
                std::cout << full;
            }
        }
    }
    cursor_hide();
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
    int sum = 0;
    for (int b = 0; b<4;b++){
        sum += tet[z[0][b]][z[1][b]];
    }
    if (onoff == On){
        if (sum == 0) {
            for (int b = 0; b<4;b++){
                tet[z[0][b]][z[1][b]] = onoff;
            }
            prohibit = 0;
        }else {
            prohibit = 1;
        }
    }else if(onoff == Off){
        if (sum == 4) {
            for (int b = 0; b<4;b++){
                tet[z[0][b]][z[1][b]] = onoff;
            }
            prohibit = 0;
        }else {
            prohibit = 1;
        }
    }
    // set_edge();
    show_video();
}

void Tetris::correction_switch(int onoff) {
   
    for (int b = 0; b<4;b++){
        if(onoff == On){
            if(tet[z[0][b]][z[1][b]] == Off){
                tet[z[0][b]][z[1][b]] = onoff;
            }
        }else if (onoff == Off){
            if(tet[z[0][b]][z[1][b]] == On){
                tet[z[0][b]][z[1][b]] = onoff;
            }
        }
    }
    set_edge();
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
            if(z[0][b]==z[0][0]-1 && z[1][b] == z[1][0]){   // �ھ� ���� ĭ
                z[0][b]++;
                z[1][b]--;
                //��ǥ�� ������ ���� �̵�
            }else if(z[0][b]==z[0][0] && z[1][b] == z[1][0]-1){  // �ھ� ���� ĭ
                z[0][b]++;
                z[1][b]++;
                //��ǥ�� ������ �Ʒ��� �̵�
            }else if(z[0][b]==z[0][0]+1 && z[1][b] == z[1][0]){  // �ھ� ������ ĭ
                z[0][b]--;
                z[1][b]++;
                //��ǥ�� ������ �Ʒ��� �̵�
            }else if(z[0][b]==z[0][0] && z[1][b] == z[1][0]+1){  // �ھ� �Ʒ��� ĭ
                z[0][b]--;
                z[1][b]--;
                //��ǥ�� ������ �Ʒ��� �̵�
            }
            
            // X-shape
            else if(z[0][b]==z[0][0]-1 && z[1][b] == z[1][0]-1){  // �ھ� ������ ĭ
                z[0][b] += 2;
                // z[1][b]
                //x��ǥ�� ���������� 2ĭ �̵�
            }else if(z[0][b]==z[0][0]+1 && z[1][b] == z[1][0]-1){  // �ھ� �������� ĭ
                // z[0][b] += 2;
                z[1][b] += 2;
                //y��ǥ�� �Ʒ������� 2ĭ �̵�
            }else if(z[0][b]==z[0][0]+1 && z[1][b] == z[1][0]+1){  // �ھ� �����ʾƷ� ĭ
                z[0][b] -= 2;
                // z[1][b]
                //x��ǥ�� �������� 2ĭ �̵�
            }else if(z[0][b]==z[0][0]-1 && z[1][b] == z[1][0]+1){  // �ھ� ���ʾƷ� ĭ
                // z[0][b] += 2;
                z[1][b] -= 2;
                //y��ǥ�� �������� 2ĭ �̵�
            }

            // Just for i-type block
            else if(z[0][b]==z[0][0]-2 && z[1][b] == z[1][0]){  // �ھ� 2ĭ ���� ĭ
                z[0][b] += 2;
                z[1][b] -= 2;
                //x��ǥ�� ���������� 2ĭ �̵�, y��ǥ�� �������� 2ĭ �̵�
            }else if(z[0][b]==z[0][0] && z[1][b] == z[1][0]-2){  // �ھ� 2ĭ ���� ĭ
                z[0][b] += 2;
                z[1][b] += 2;
                //x��ǥ�� ���������� 2ĭ �̵�, y��ǥ�� �Ʒ������� 2ĭ �̵�
            }else if(z[0][b]==z[0][0]+2 && z[1][b] == z[1][0]){  // �ھ� 2ĭ ������ ĭ
                z[0][b] -= 2;
                z[1][b] += 2;
                //x��ǥ�� �������� 2ĭ �̵�, y��ǥ�� �Ʒ������� 2ĭ �̵�
            }else if(z[0][b]==z[0][0] && z[1][b] == z[1][0]+2){  // �ھ� 2ĭ �Ʒ��� ĭ
                z[0][b] -= 2;
                z[1][b] -= 2;
                //x��ǥ�� �������� 2ĭ �̵�, y��ǥ�� �������� 2ĭ �̵�
            }
        }
        block_switch(On);
        
        if (prohibit ==1) {
            for(int b = 0; b < 2; b++) {
                for (int c = 0; c < 4; c++){
                    z[b][c] = save[b][c];
                }
            }
            block_switch(On);
        }
        // if(check != check_sum()) {
        //     correction_switch(Off);
            
        //     for(int b = 0; b < 2; b++) {
        //         for (int c = 0; c < 4; c++){
        //             z[b][c] = save[b][c];
        //         }
        //     }
        //     block_switch(On);
            
        // }
    }
}

void Tetris::down_arrow() {

}

void Tetris::left_arrow() {
    nextblock = 0;
    int check = check_sum();
    block_switch(Off);
    
    for(int b = 0; b<4; b++){
        z[0][b]--;
    }
    
    block_switch(On);
    if (prohibit ==1) {
        for(int b = 0; b<4; b++){
        z[0][b]++;
        }
        block_switch(On);
    }
    // if(check != check_sum()) {
    //     correction_switch(Off);
    //     load_prev_tet();
    //     for(int b = 0; b<4; b++){
    //     z[0][b]++;
    //     }
    //     set_edge();
    //     block_switch(On);
        
    // }
    
    
}

void Tetris::right_arrow() {
    nextblock = 0;
    int check = check_sum();
    block_switch(Off);
    for(int b = 0; b<4; b++){
        z[0][b]++;
    }
    
    block_switch(On);
    if(prohibit ==1) {
        for(int b = 0; b<4; b++){
        z[0][b]--;
        }
        block_switch(On);
    }

    // if(check != check_sum()) {
    //     correction_switch(Off);
    //     load_prev_tet();
    //     for(int b = 0; b<4; b++){
    //     z[0][b]--;
    //     }
    //     set_edge();
    //     block_switch(On);
    // }
    
}

void Tetris::down_natural() {
    int check = check_sum();
    block_switch(Off);
    for(int b = 0; b<4; b++){
        z[1][b]++;
    }
    block_switch(On);
    
    if (prohibit ==1) {
        nextblock++;
        for(int b = 0; b<4; b++){
        z[1][b]--;
        }
        block_switch(On);
        gotonextblock();
    }

    // if(check != check_sum()) {
    //     nextblock++;
    //     correction_switch(Off);
    //     load_prev_tet();
    //     for(int b = 0; b<4; b++){
    //     z[1][b]--;
    //     }
    //     set_edge();
    //     block_switch(On);
    //     gotonextblock();
    // }
    
}

void Tetris::drop() {       //�ݺ��� Ȫ���� ���� ������ ���� ������ �ʿ䰡 ����.
//�ϰ� ������ ���� �ݺ�Ƚ���� �����ϸ� ���� ��.
    for (int i = 0; i < 22; i++) {
        down_natural();
        nextblock = 0;
    }
    down_natural();
}

int Tetris::gotonextblock() {
    return nextblock;
}

void Tetris::check_clear_line() {
    int sum[height] = {0};
    
    for (int j = 0; j < height-1; j++) {
        for(int i = 1; i < width-1; i++){
            sum[j] += tet[i][j];
        }    
    }
    for(int j = 0; j < height-1; j++) {
        if (sum[j] == 10){ // �� ���� �� á�ٸ�, �� ���� ����� �� �� ���� �ִ� ��� ���� �� ĭ �Ʒ��� ������.
            for(int b = j; b > 0; b--){
                for(int i = 1; i < width-1; i++){
                    tet[i][b] = 0;
                    tet[i][b] = tet[i][b-1];
                }
            }
        }
    }
}

int main() {

    Tetris tet;
    system("cls");
    
    nextblock:   
    tet.set_edge();
    tet.gen_block();
    tet.set_block();
    tet.show_stat_sym();
    tet.save_prev_tet();
    tet.block_switch(On);

    int input;
    int down_time = (unsigned)time(NULL);
    down_time += 1; // 1��

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
                down_num--;
                tet.down_natural();
            }
            else if (input == RIGHT) {
                tet.right_arrow();
            }
            else if (input == LEFT) {
                tet.left_arrow();
            }

            if(getch()==' ') {
                tet.drop();
            }
        }


        if(down_num==10000){
            tet.down_natural();
            down_num = 0;
        }

        if(tet.nextblock == 1) {
            tet.nextblock = 0;
            tet.check_clear_line();
            // system("cls");
            goto nextblock;
        }

        
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