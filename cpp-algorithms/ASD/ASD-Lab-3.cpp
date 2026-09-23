#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cfloat>

using namespace std;
// Task 1
void BubbleSort(int* array, int size)
{
    int pastElem;
    for (int i = 0; i < size - 1; i++)
    { 
        for (int r = 0; r < size - i - 1; r++)
        {
            if (array[r] > array[r + 1])
            {
                pastElem = array[r];
                array[r] = array[r + 1];
                array[r + 1] = pastElem;
            } 
        }
    }
} 

int LinearSearch(int* array, int size, int num)
{
    for (int i = 0; i < size; i++)
    {
        if (array[i] == num)
        {
            return array[i];
        }
    }
    return -1;
} 

int BinarySearch(int* array, int size, int num)
{
    int low = 0, high = size - 1, mid;
    while (low <= high)
    {
        mid = low + (high - low) / 2;
        if (array[mid] > num)
        {
            high = mid - 1;
        }
        else if (array[mid] < num)
        {
            low = mid + 1;
        }
        else return array[mid];
    }
    return -1;  
}
// Task 2
void RandomPermutation(int* array, int size)
{
    int r, Elem; 
    for (int i = 0; i < size; i++)
    {
        r = rand() % (size - i);
        Elem = array[size - i - 1];
        array[size - i - 1] = array[r];
        array[r] = Elem;
    }
}

void SelectionSort(int* array, int size)
{
    int min, Elem; 
    for (int i = 0; i < size - 1; i++)
    {
        min = i;
        for (int r = i + 1; r < size; r++)  
        {
            if ((array[r] % 7) < (array[min] % 7))  
            {
                min = r;
            }
            else if ((array[r] % 7) == (array[min] % 7))
            {
                if (array[r] < array[min])
                {
                    min = r;
                }
            }
        }
        Elem = array[min]; 
        array[min] = array[i];
        array[i] = Elem;
    }
}

void CoutArray(int* array, int size)
{
    for (int i = 0; i < size; i++) 
    {
        cout << array[i] << " ";
    }
    cout << "\n\n";
}
// Task 3
double MathFunc(double a, double b, double x)
{
    return x * x + a * x + b;
}

double TernarySearchMin(double left, double right, double eps, double a, double b)
{
    double m1, m2;
    while (right - left > eps)
    {
        m1 = left + (right - left) / 3;
        m2 = right - (right - left) / 3;
        if (MathFunc(a, b, m1) < MathFunc(a, b, m2))
        {
            right = m2;
        }
        else
        {
            left = m1;
        }
    }
    return (left + right) / 2;
}

double GoldenRatioSearch(double left, double right, double eps, double a, double b) 
{ 
    const double goldenRatio = (1 + sqrt(5)) / 2;

    double x1 = right - (right - left) / goldenRatio;  
    double x2 = left + (right - left) / goldenRatio;

    double f1 = MathFunc(a, b, x1);
    double f2 = MathFunc(a, b, x2);

    while (fabs(right - left) > eps) { 
        if (f1 < f2)   
        {
            right = x2; 
            x2 = x1; 
            f2 = f1;
            x1 = right - (right - left) / goldenRatio; 
            f1 = MathFunc(a, b, x1);  
        }
        else 
        { 
            left = x1; 
            x1 = x2; 
            f1 = f2;
            x2 = left + (right - left) / goldenRatio;   
            f2 = MathFunc(a, b, x2);  
        }
    }
    // Повертаємо середнє значення
    return (left + right) / 2;
}

int main()
{
    srand(time(NULL));

    // ========================== Task 1 ===========================
    const int size = 1000;
    int array[size]{};

    for (int i = 0; i < size; i++) // Заповнення масиву ввипадковими числами в діапазоні від -2000 до 2000 
    {
        array[i] = rand() % 4001 - 2000;  
    }
    BubbleSort(array, size); // Виклик Функції сортування масиву "Бульбашкою" 
   
    int res1, res2, NumberToFind;
    double time1 = 0, time2 = 0;
    for (int t = 0; t < 100000; t++) // Обгортка для коректного заміру часу
    {
        NumberToFind = rand() % 4001 - 2000; // Генерація випадково числа для пошуку

        clock_t startTime1 = clock(); // Замір часу виконання лінійного пошуку
        res1 = LinearSearch(array, size, NumberToFind); 
        clock_t endTime1 = clock();
        double seconds1 = (double(endTime1 - startTime1)) / CLOCKS_PER_SEC;   
        time1 += seconds1;

        clock_t startTime2 = clock(); // Замір часу виконання бінарного пошуку
        res2 = BinarySearch(array, size, NumberToFind);  
        clock_t endTime2 = clock();
        double seconds2 = (double(endTime2 - startTime2)) / CLOCKS_PER_SEC;  
        time2 += seconds2;
        if (res1 != res2)
        {
            cout << "MISTAKE!!!";
            break;
        }
    }

    cout << "Time of the linear search: " << time1 << " seconds" << endl; 
    cout << "Time of the binary search: " << time2 << " seconds" << endl; 

    // ========================== Task 2 ===========================
    cout << "\n=========== Task 2 ============\n\n";
    const int size_2 = 200; 
    int array_2[size_2]{};  

    for (int i = 0; i < size_2; i++) // Заповнення масиву послідовними числами від 1 до 200
    {
        array_2[i] = i + 1;
    }
    RandomPermutation(array_2, size_2); // Виклик функції перетасовки 
    cout << "Permutated Array:\n";
    CoutArray(array_2, size_2);

    SelectionSort(array_2, size_2); 
    cout << "Array sorted by criteria:\n";
    CoutArray(array_2, size_2);

    // ========================== Task 3 ===========================
    cout << "\n=========== Task 3 ============\n\n";
    double eps, a, b, left, right;
    cout << "Enter for precision of x (eps): "; cin >> eps; 
    cout << "Enter for a: "; cin >> a;
    cout << "Enter for b: "; cin >> b;
    cout << "Enter for left limit: "; cin >> left;
    cout << "enter for right limit: "; cin >> right; cout << "\n";

    clock_t startTime1 = clock(); // Замір часу виконання тернарного пошуку  
    for (int t = 0; t < 100000; t++)
    {
        double result = TernarySearchMin(left, right, eps, a, b);   
        if (t == 0)
        {
            cout << "Minimum value with Ternary search: " << result << endl;  
        }
    }
    clock_t endTime1 = clock(); 
    double seconds1 = (double(endTime1 - startTime1)) / CLOCKS_PER_SEC;   
    cout << "Time of the Ternary search: " << seconds1 << " seconds" << endl; 

    clock_t startTime2 = clock(); // Замір часу виконання алгоритму золотого перетину  
    for (int t = 0; t < 100000; t++)
    {
        double result2 = GoldenRatioSearch(left, right, eps, a, b); 
        if (t == 0)
        {
            cout << "Minimum value with Golden ratio search: " << result2 << endl; 
        }
    }
    clock_t endTime2 = clock();
    double seconds2 = (double(endTime2 - startTime2)) / CLOCKS_PER_SEC;
    cout << "Time of the Golden Ratio search: " << seconds2 << " seconds" << "\n\n";
    
    return 0;
}

