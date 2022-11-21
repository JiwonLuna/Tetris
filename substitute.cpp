#include <iostream>

#define width 12
#define height 22

class Tetris {

    public:
    int tet[height][width] = { 0 };
    void show_stat();
    void set_edge();


};

void Tetris::show_stat() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::cout << tet[i][j];
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

int main() {
    Tetris tet;
    tet.set_edge();
    tet.show_stat();


    return 0;
    
}