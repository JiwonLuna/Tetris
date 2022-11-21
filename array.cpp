#include <stdio.h>
#include <iostream>

#define width 12
#define height 22

int main()
{


    string edge[width][height];
    for(int i = 0;i < height; i++){
        edge[0][i] = "■";
        edge[width][i] = "■";
    }
    for(int i = 1; i < (width - 1); i++){
        
        
    }
                                // 2차원 문자배열의 선언과 초기화
    int i;                      // 반복 제어변수
    int count;                  // 문자열의 개수를 저장할 변수
 
    count=sizeof(edge)/sizeof(edge[0]);
    printf("%d\n", sizeof(edge));
    printf("%s\n", edge[0]);
    
    
    
    // 초기화된 문자열의 수 계산
    for(i=0; i<count; i++){
        // 그 개수만큼 반복한다
        printf("%s\n", edge[i]);
        // 저장된 문자열 출력
    }
    return 0;
}

// int main()
// {
//     char animal[][10]={"monkey", "elephant", "dog", "sheep", "pig",
//                         "lion", "tiger", "puma", "turtle", "fox"};
//                                 // 2차원 문자배열의 선언과 초기화
//     int i;                      // 반복 제어변수
//     int count;                  // 문자열의 개수를 저장할 변수
 
//     count=sizeof(animal)/sizeof(animal[0]);
//     printf("%d\n", sizeof(animal));
//     printf("%s\n", animal[0]);
    
    
    
//     // 초기화된 문자열의 수 계산
//     for(i=0; i<count; i++){
//         // 그 개수만큼 반복한다
//         printf("%s\n", animal[i]);
//         // 저장된 문자열 출력
//     }
//     return 0;
// }