#include <iostream>

using namespace std;

int TenToEight(int number)
{
    int res = 0;
    if (number == 0)
    {
        return res;
    }
    int a = number / 8;
    cout << a;
    /*int q = number % 8;
    for (int i = 0;a > 0; i++)
    {
        res += q * pow(10, i);
        q = a % 8;
        a /= 8;
    }
    return res;*/
}

int main()
{
    int res = TenToEight(73);
    cout << res << endl;

    
    
}

