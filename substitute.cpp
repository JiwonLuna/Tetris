#include <iostream>

#define width 12
#define height 22

class Tetris {
    const char* full = "бс";
    const char* empty = "бр";

    public:
    int tet[height][width] = { 0 };
    void show_stat_num();
    void show_stat_sym();
    void set_edge();
    void gen_block();

};

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

int main() {
    Tetris tet;
    tet.set_edge();
    tet.show_stat_num();
    tet.show_stat_sym();


    return 0;
    
}