#include <stdio.h>
#include <iostream>

#define width 12
#define height 22

int main()
{


    string edge[width][height];
    for(int i = 0;i < height; i++){
        edge[0][i] = "��";
        edge[width][i] = "��";
    }
    for(int i = 1; i < (width - 1); i++){
        
        
    }
                                // 2���� ���ڹ迭�� ����� �ʱ�ȭ
    int i;                      // �ݺ� �����
    int count;                  // ���ڿ��� ������ ������ ����
 
    count=sizeof(edge)/sizeof(edge[0]);
    printf("%d\n", sizeof(edge));
    printf("%s\n", edge[0]);
    
    
    
    // �ʱ�ȭ�� ���ڿ��� �� ���
    for(i=0; i<count; i++){
        // �� ������ŭ �ݺ��Ѵ�
        printf("%s\n", edge[i]);
        // ����� ���ڿ� ���
    }
    return 0;
}

// int main()
// {
//     char animal[][10]={"monkey", "elephant", "dog", "sheep", "pig",
//                         "lion", "tiger", "puma", "turtle", "fox"};
//                                 // 2���� ���ڹ迭�� ����� �ʱ�ȭ
//     int i;                      // �ݺ� �����
//     int count;                  // ���ڿ��� ������ ������ ����
 
//     count=sizeof(animal)/sizeof(animal[0]);
//     printf("%d\n", sizeof(animal));
//     printf("%s\n", animal[0]);
    
    
    
//     // �ʱ�ȭ�� ���ڿ��� �� ���
//     for(i=0; i<count; i++){
//         // �� ������ŭ �ݺ��Ѵ�
//         printf("%s\n", animal[i]);
//         // ����� ���ڿ� ���
//     }
//     return 0;
// }