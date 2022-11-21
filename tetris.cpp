#include <iostream>

// 함수의 특징을 잘 활용해봐라.


class Tetris{


};

// ■    □


int main() {
    std::cout << "Let's play Tetris!!" << std::endl;
    std::cout << std::endl;
    for (int i = 0; i < 12; i++) printf("■");
    printf("\n");
    for (int i = 0; i < 23; i++) {
        printf("■");
        for (int i = 0; i < 10; i++) printf("□");
        printf("■\n");
    }
    for (int i = 0; i < 12; i++) printf("■");
    printf("\n");

    printf("\u2103\n");


    return 0;
}