#include <iostream>
#include <typeinfo>
using namespace std;


int main() {
	int a = 5;
	bool b = false;
	short int c = 15;
	double d = 25.12;
    string e = "■"; //24 바이트
    string f = "□";

	cout << "a: " << a << ' ' << typeid(a).name() << ' ' << sizeof(int) << "바이트" << endl;
	cout << "b: " << b << ' ' << typeid(b).name() << ' ' << sizeof(bool) << "바이트" << endl;
	cout << "c: " << c << ' ' << typeid(c).name() << ' ' << sizeof(c) << "바이트" << endl;
	cout << "d: " << d << ' ' << typeid(d).name() << ' ' << sizeof(d) << "바이트" << endl;
    cout << "e: " << e << ' ' << typeid(e).name() << ' ' << sizeof(e) << "바이트" << endl;
    cout << "f: " << f << ' ' << typeid(f).name() << ' ' << sizeof(f) << "바이트" << endl;
	return 0;
}