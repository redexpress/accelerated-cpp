#include <iostream>

using std::cout;
using std::endl;

int next(int n)
{
    return n + 1;
}

int main()
{
    int x = 5;
    int* p = &x;
    cout << "x=" << x << endl;
    *p = 6;
    cout << "x=" << x << endl;

    int (*fp)(int) = &next;
    int i = (*fp)(3);
    cout << "i=" << i << endl;
    i = fp(6);
    cout << "i=" << i << endl;

    int (*fp2)(int) = next;
    i = fp2(6);
    cout << "i=" << i << endl;

    int (*fp3)(int);
    fp3 = next;
    i = fp3(6);
    cout << "i=" << i << endl;

    return 0;
}