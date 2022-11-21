#include <iostream>
#include <chrono>
#include <Windows.h>
 
using namespace std;
 
// C++ 프로그램의 경과 시간을 측정하는 메인 함수
// 크로노 라이브러리 사용
int main()
{
    auto start = chrono::steady_clock::now();
 
    // 여기에서 몇 가지 작업을 수행합니다.
    Sleep(300);
 
    auto end = chrono::steady_clock::now();
 
    cout << "Elapsed time in nanoseconds: "
        << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
        << " ns" << endl;
 
    cout << "Elapsed time in microseconds: "
        << chrono::duration_cast<chrono::microseconds>(end - start).count()
        << " ?s" << endl;
 
    cout << "Elapsed time in milliseconds: "
        << chrono::duration_cast<chrono::milliseconds>(end - start).count()
        << " ms" << endl;
 
    cout << "Elapsed time in seconds: "
        << chrono::duration_cast<chrono::seconds>(end - start).count()
        << " sec";
 
    return 0;
}