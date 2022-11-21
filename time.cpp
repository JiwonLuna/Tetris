#include <iostream>
#include <ctime>
using namespace std;
 
int main() {
    clock_t start, finish;
    double duration;
 
    start = clock();
    
    /*실행 시간을 측정하고 싶은 코드*/
 
    finish = clock();
 
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    cout << duration << "초" << endl;
 
    return 0;
}
