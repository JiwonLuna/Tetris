#include <iostream>
#include <typeinfo>
using namespace std;


int main() {
	int a = 5;
	bool b = false;
	short int c = 15;
	double d = 25.12;
    string e = "��"; //24 ����Ʈ
    string f = "��";

	cout << "a: " << a << ' ' << typeid(a).name() << ' ' << sizeof(int) << "����Ʈ" << endl;
	cout << "b: " << b << ' ' << typeid(b).name() << ' ' << sizeof(bool) << "����Ʈ" << endl;
	cout << "c: " << c << ' ' << typeid(c).name() << ' ' << sizeof(c) << "����Ʈ" << endl;
	cout << "d: " << d << ' ' << typeid(d).name() << ' ' << sizeof(d) << "����Ʈ" << endl;
    cout << "e: " << e << ' ' << typeid(e).name() << ' ' << sizeof(e) << "����Ʈ" << endl;
    cout << "f: " << f << ' ' << typeid(f).name() << ' ' << sizeof(f) << "����Ʈ" << endl;
	return 0;
}