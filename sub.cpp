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
    int block_type_num;
    char next_block_type;
    int next_block_type_num;
    int core_x;     // ���� �ھ� x��ǥ 1~10 (���� -> ������)
    int core_y;     // ���� �ھ� y��ǥ 1~23 (�� -> �Ʒ�)
    int rotation;   // ȸ�� ���¸� ��Ÿ���� ���� 1~4
    int rotnum;     // �� ���� ���� ������ ȸ���� Ƚ��
    

    int score;

    int z[2][4] = {0};      // ���� ��
    int next_block_z[2][4] = {0};

    public:
    Tetris();
    
    int prohibit;

    int tet[width][height][2] = { 0 };  
    // 3��° �ε����� ���� ���� �����
    // tet[width][height][0] : ���� Ȯ�ο�, tet[width][height][1] : ���� ����(block_type_num) ����.
    int prev_tet[width][height][2] = { 0 };
    void save_prev_tet();
    void load_prev_tet();

    void show_stat_num();
    void show_stat_sym();
    void gotoxy(short x, short y);
    void cursor_hide();
    void textcolor(int foreground, int background);
    void block_color(int type_num);
    void printer();
    void set_edge();
    void gen_first_block();
    void gen_block();
    void set_block();
    void block_switch(int onoff);
    void correction_switch(int onoff);
    void next_block_indicator();
    void next2present();

    int check_sum();
    // ���� �����ؾ��ϴ� ����(���)�� width 1~10, height 1~22.
    void up_arrow();
    void down_arrow();
    void left_arrow();
    void right_arrow();
    void down_natural();
    void drop();

    int next_block_index;
    int gotonextblock();

    void check_clear_line();

    void scorer();
    void control_level();
    int drop_rate;
};

Tetris::Tetris() {
    core_x = startx;
    core_y = starty;
    rotation = 0;
    next_block_index = 0;
    prohibit = 0;
    block_type_num = 0;
    next_block_type_num = 0;
    score = 0;
    drop_rate = 14000;
}

void Tetris::save_prev_tet() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < 2; k++){
                prev_tet[j][i][k] = tet[j][i][k];
            }
        }
    }
}

void Tetris::load_prev_tet() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < 2; k++){
                tet[j][i][k] = prev_tet[j][i][k];
            }
        }
    }

    for(int i = 0; i < height; i++){
        for (int j = 0; j < width; j++) {
            gotoxy(2*j, i);
            if(tet[j][i][0]==0){
                std::cout << empty;
            }else if(tet[j][i][0]==1){
                std::cout << full;
            }
        }
    }
}

void Tetris::show_stat_num() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::cout << tet[j][i][0];
        }
        std::cout << std::endl;
    }
}

void Tetris::show_stat_sym() {
    for(int i = 0; i < height; i++){
        for (int j = 0; j < width; j++) {
            gotoxy(2*j, i);
            if(tet[j][i][0]==0){
                block_color(tet[j][i][1]);
                std::cout << empty;
            }else if(tet[j][i][0] == 1){
                block_color(tet[j][i][1]);
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

void Tetris::block_color(int type_num) {
    switch(type_num){
        case 0: // ����
        textcolor(7, 0);
        break;
        
        case 1: //'i'
        textcolor(9, 0);
        break;
        
        case 2: // 'o'
        textcolor(14, 0);
        break;

        case 3: //'z'
        textcolor(4, 0);
        break;

        case 4: //'s'
        textcolor(10, 0);
        break;

        case 5: //'j'
        textcolor(1, 0);
        break;

        case 6: //'l'
        textcolor(12, 0);
        break;

        case 7: //'t'
        textcolor(5, 0);
        break;
    }
}

void Tetris::printer() { // ��ǥ�� ����Ű�� ������ ���� ��ȭ�� ��Ȳ�� ǥ�����ش�.
    for(int b = 0; b < 4; b++) {
        gotoxy(2*z[0][b], z[1][b]);
        if(z[0][b] == 0 || z[0][b] == 11 || z[1][b] == height-1){
        }else {
            if(tet[z[0][b]][z[1][b]][0]==0){
                block_color(tet[z[0][b]][z[1][b]][1]);
                std::cout << empty;
            }else if(tet[z[0][b]][z[1][b]][0]==1){
                block_color(tet[z[0][b]][z[1][b]][1]);
                std::cout << full;
            }
        }
    }
    cursor_hide();
}

void Tetris::set_edge() {
    for (int i = 0; i < width; i++) {
        tet[i][height-1][0] = On;
    }
    for (int i = 0; i < height; i++) {
        tet[0][i][0] = On;
        tet[width-1][i][0] = On;
    }
}

void Tetris::gen_first_block() {
    srand(time(NULL));
    int a = rand() % 7;
    char types[7] = {'i', 'o', 'z', 's', 'j', 'l', 't'};
    block_type = types[a];
    block_type_num = a + 1;
    // std::cout << block_type << std::endl;
    rotation = 0;
    rotnum = 0;
}

void Tetris::gen_block() {

    srand(time(NULL));
    int a = rand() % 7;
    char types[7] = {'i', 'o', 'z', 's', 'j', 'l', 't'};
    next_block_type = types[a];
    next_block_type_num = a + 1;
    // std::cout << block_type << std::endl;
    rotation = 0;
    rotnum = 0;
}

void Tetris::next2present() {
    block_type = next_block_type;
    block_type_num = next_block_type_num;
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
        sum += tet[z[0][b]][z[1][b]][0];
    }
    if (onoff == On){
        if (sum == 0) {
            for (int b = 0; b<4;b++){
                tet[z[0][b]][z[1][b]][0] = onoff;
                tet[z[0][b]][z[1][b]][1] = block_type_num;
            }
            prohibit = 0;
        }else {
            prohibit = 1;
        }
    }else if(onoff == Off){
        if (sum == 4) {
            for (int b = 0; b<4;b++){
                tet[z[0][b]][z[1][b]][0] = onoff;
                tet[z[0][b]][z[1][b]][1] = 0;
            }
            prohibit = 0;
        }else {
            prohibit = 1;
        }
    }
    // set_edge();
    printer();
}

void Tetris::correction_switch(int onoff) {
   
    for (int b = 0; b<4;b++){
        if(onoff == On){
            if(tet[z[0][b]][z[1][b]][0] == Off){
                tet[z[0][b]][z[1][b]][0] = onoff;
            }
        }else if (onoff == Off){
            if(tet[z[0][b]][z[1][b]][0] == On){
                tet[z[0][b]][z[1][b]][0] = onoff;
            }
        }
    }
    set_edge();
    printer();
}

void Tetris::next_block_indicator(){
    int start_line = 3;
    gotoxy(34, start_line);
    printf("���� Next");
    for(int i = 0; i<9; i++) printf("��");
    printf("��");
    for(int i = 0; i<7; i++){
        gotoxy(34, i+start_line+1);
        printf("��");
        for(int j = 0; j<15; j++) printf(" ");
        printf("��");
    }
    gotoxy(34, start_line+8);
    printf("��");
    for(int i = 0; i<15; i++) printf("��");
    printf("��");

    int indi_coord_x = 21;
    int indi_coord_y = 7;
    switch(next_block_type) {
            
        case 'i': 
        next_block_z[0][0] = indi_coord_x;
        next_block_z[1][0] = indi_coord_y;
        next_block_z[0][1] = indi_coord_x;
        next_block_z[1][1] = indi_coord_y-1;
        next_block_z[0][2] = indi_coord_x;
        next_block_z[1][2] = indi_coord_y+1;
        next_block_z[0][3] = indi_coord_x;
        next_block_z[1][3] = indi_coord_y+2;

        break;
        
        case 'o': 
        next_block_z[0][0] = indi_coord_x;
        next_block_z[1][0] = indi_coord_y;
        next_block_z[0][1] = indi_coord_x+1;
        next_block_z[1][1] = indi_coord_y;
        next_block_z[0][2] = indi_coord_x;
        next_block_z[1][2] = indi_coord_y-1;
        next_block_z[0][3] = indi_coord_x+1;
        next_block_z[1][3] = indi_coord_y-1;
        break;
        

        case 'z': 
        next_block_z[0][0] = indi_coord_x;
        next_block_z[1][0] = indi_coord_y;
        next_block_z[0][1] = indi_coord_x-1;
        next_block_z[1][1] = indi_coord_y;
        next_block_z[0][2] = indi_coord_x;
        next_block_z[1][2] = indi_coord_y+1;
        next_block_z[0][3] = indi_coord_x+1;
        next_block_z[1][3] = indi_coord_y+1;
        break;
        

        case 's': 
        next_block_z[0][0] = indi_coord_x;
        next_block_z[1][0] = indi_coord_y;
        next_block_z[0][1] = indi_coord_x+1;
        next_block_z[1][1] = indi_coord_y;
        next_block_z[0][2] = indi_coord_x;
        next_block_z[1][2] = indi_coord_y+1;
        next_block_z[0][3] = indi_coord_x-1;
        next_block_z[1][3] = indi_coord_y+1;
        break;
        
        case 'j':
        next_block_z[0][0] = indi_coord_x;
        next_block_z[1][0] = indi_coord_y;
        next_block_z[0][1] = indi_coord_x;
        next_block_z[1][1] = indi_coord_y-1;
        next_block_z[0][2] = indi_coord_x;
        next_block_z[1][2] = indi_coord_y+1;
        next_block_z[0][3] = indi_coord_x-1;
        next_block_z[1][3] = indi_coord_y+1;
        break;

        case 'l':            
        next_block_z[0][0] = indi_coord_x;
        next_block_z[1][0] = indi_coord_y;
        next_block_z[0][1] = indi_coord_x;
        next_block_z[1][1] = indi_coord_y-1;
        next_block_z[0][2] = indi_coord_x;
        next_block_z[1][2] = indi_coord_y+1;
        next_block_z[0][3] = indi_coord_x+1;
        next_block_z[1][3] = indi_coord_y+1;
        break;

        case 't':
        next_block_z[0][0] = indi_coord_x;
        next_block_z[1][0] = indi_coord_y;
        next_block_z[0][1] = indi_coord_x;
        next_block_z[1][1] = indi_coord_y-1;
        next_block_z[0][2] = indi_coord_x-1;
        next_block_z[1][2] = indi_coord_y;
        next_block_z[0][3] = indi_coord_x+1;
        next_block_z[1][3] = indi_coord_y;
        break;
    }
    for(int b = 0; b < 4; b++) {
        gotoxy(2*next_block_z[0][b], next_block_z[1][b]);
        block_color(next_block_type_num);
        std::cout << full;
    }
    textcolor(7, 0);
    cursor_hide();
}


int Tetris::check_sum() {
    int sum = 0;
    for(int i = 0; i < height-1; i++) {
        for(int j = 1; j < width-1; j++) {
            sum += tet[j][i][0];
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
    next_block_index = 0;
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
    next_block_index = 0;
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
        next_block_index++;
        for(int b = 0; b<4; b++){
        z[1][b]--;
        }
        block_switch(On);
    }

    // if(check != check_sum()) {
    //     next_block_index++;
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
        next_block_index = 0;
    }
    down_natural();
}

int Tetris::gotonextblock() {
    return next_block_index;
}

void Tetris::check_clear_line() {
    int sum[height] = {0};
    
    for (int j = 0; j < height-1; j++) {
        for(int i = 1; i < width-1; i++){
            sum[j] += tet[i][j][0];
        }    
    }
    for(int j = 0; j < height-1; j++) {
        if (sum[j] == 10){ // �� ���� �� á�ٸ�, �� ���� ����� �� �� ���� �ִ� ��� ���� �� ĭ �Ʒ��� ������.
            score += 10;
            for(int b = j; b > 0; b--){
                for(int i = 1; i < width-1; i++){
                    tet[i][b][0] = 0;
                    tet[i][b][0] = tet[i][b-1][0];
                    tet[i][b][1] = tet[i][b-1][1];
                }
            }
        }
    }
}

void Tetris::scorer(){
    int start_line = 13;
    gotoxy(34, start_line);
    printf("���� Score");
    for(int i = 0; i<8; i++) printf("��");
    printf("��");

    gotoxy(34, start_line+1);
    printf("��");
    for(int j = 0; j<15; j++) printf(" ");
    printf("��");

    gotoxy(34, start_line+2);
    printf("��%15d��", score);
    

    gotoxy(34, start_line+3);
    printf("��");
    for(int j = 0; j<15; j++) printf(" ");
    printf("��");


    gotoxy(34, start_line+4);
    printf("��");
    for(int i = 0; i<15; i++) printf("��");
    printf("��");
}

void Tetris::control_level() {
    if(score < 80){
        drop_rate = 10000;
    }else if(80<=score && score < 150){
        drop_rate = 8000;
    }else if(150<=score && score < 250){
        drop_rate = 5000;
    }else if (250<=score && score < 400){
        drop_rate = 4000;
    }else if (400<=score){
        drop_rate = 3000;
    }
}


int main() {

    Tetris tet;
    system("cls");
    tet.gen_first_block();
    nextblock:   
    tet.set_edge();
    tet.set_block();
    tet.gen_block();
    tet.show_stat_sym();
    tet.scorer();
    tet.control_level();
    tet.next_block_indicator();
    tet.save_prev_tet();
    tet.block_switch(On);

    

    if (tet.prohibit == 1) {
        // goto GameOver;
        system("cls");
        tet.textcolor(7, 0);
        std::cout << "GAME OVER" << std::endl;
        return 0;
    }
    

    int input;
    int down_time = (unsigned)time(NULL);
    down_time += 1; // 1��

    int down_num = 0;

    while(true) {
        // system("cls");
        down_num++;

        if(kbhit()) {
            input = getch();
            
            switch(input) {
                case 72:
                    // ���� ����Ű, ȸ��
                    tet.up_arrow();
                    break;

                case 80:
                    // �Ʒ��� ����Ű, ������ �ϰ�
                    down_num--;
                    tet.down_natural();
                    break;

                case 75:
                    // ���� ����Ű, �������� �̵�
                    tet.left_arrow();
                    break;

                case 77:
                    // ������ ����Ű, ���������� �̵�
                    tet.right_arrow();
                    break;
                
                case ' ':
                    tet.drop();
                    break;

                default:
                    break;
                }
        }

        if(down_num==tet.drop_rate){
            tet.down_natural();
            down_num = 0;
        }

        if(tet.next_block_index == 2) {
            tet.next_block_index = 0;
            tet.check_clear_line();
            tet.next2present();
            goto nextblock;
        }

        
    }

// GameOver: 
//     system("cls");
//     std::cout << "GAME OVER" << std::endl;


    return 0;
}