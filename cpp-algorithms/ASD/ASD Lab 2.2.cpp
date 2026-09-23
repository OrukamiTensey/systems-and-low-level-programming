#include <iostream>

using namespace std;

// =============================== Task 1 ===============================

//int BaseToBase(int number, int base1 , int base2) 
//{
//    int res = 0;
//    int rest;
//    for (int i = 0; number > 0; i++)
//    {
//        rest = number % base2;
//        number /= base2;
//        res += rest * pow(base1, i);
//    }
//    return res;
//}
//
//int TenToBase(int number , int base) // З десяткової в N-систему числення
//{
//    int res = 0;
//    int rest;
//    for (int i = 0; number > 0; i++)
//    {
//        rest = number % base;
//        number /= base;
//        res += rest * pow(10, i);
//    }
//    return res;
//}
//
//int BaseToTen(int number , int base) // З N-системи числення в десяткову
//{
//    int res = 0;
//    int rest;
//    for (int i = 0; number > 0; i++)
//    {
//        rest = number % 10;
//        number /= 10;
//        res += rest * pow(base, i);
//    }
//    return res; 
//}

int Fibonacci(int n) // Функція знаходження числа Фібоначчі
{
    if (n <= 1) return 0;
    if (n == 2) return 1;

    return Fibonacci(n - 2) + Fibonacci(n - 1);
}

int FibonacciSum(int N, int i = 1, int sum = 0) // Функція знаходження суми перших N чисел 
{                                               // в послідовності Фібоначчі
    if (N < i)
    {
        return sum;
    }
    else
    {
        return FibonacciSum(N, i + 1, sum + Fibonacci(i));
    }
}


int main()
{
    int N;
    cout << "Enter the number of members of the Fibonacci sequence: " << endl;
    cin >> N;
    int result = FibonacciSum(N);
    cout << "Sum of first " << N << " numbers of the Fibonacci sequence: " << result << endl;


    //int num, base;
    //cout << "Enter the NUMBER to convert: " << endl; // Введення числа для конвертації
    //cin >> num;
    //cout << "Enter the BASE to convert to: " << endl; // Введення системи числення в яку конвертувати
    //cin >> base;
    //for (int i = 1; i <= 1000; i++) // Переведення чисел від 1 до 1000 з десяткової 
    //{                               // системи числення в іншу і навпаки
    //    int convertedNum = TenToBase(num, base);
    //    if (BaseToTen(convertedNum, base) != num) // Порівняння введенего числа з двічі конвертованим
    //    {                                         // та зупинення циклу при незбіжності 
    //        cout << "Something Gone wrong!!!" << endl;
    //        break;
    //    }
    //}
    //cout << "Testing completed successufully!" << endl;
}


