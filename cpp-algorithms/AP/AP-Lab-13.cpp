#include <iostream>
#include <math.h> 

using namespace std;

#define PI 3.14159265358979323846  
#define EQUALITY(A, B, C) (cos(A) + cos(B) + cos(C) <= 1.5)
#define DEGREES_TO_RADIANS(degrees) ((degrees) * PI / 180.0)        

int main()
{
    double A, B, C;
    cout << "Enter the three angles of the triangle (in degrees):\n";
    cout << "A: "; cin >> A;
    cout << "B: "; cin >> B;
    cout << "C: "; cin >> C;

    // Check if the triangle exists
    if (A + B + C == 180)
    {
        // Check if the condition cosA + cosB + cosC <= 3/2 is satisfied 
        A = DEGREES_TO_RADIANS(A);
        B = DEGREES_TO_RADIANS(B);
        C = DEGREES_TO_RADIANS(C);
         
        if (EQUALITY(A, B, C))
        {
            cout << "The triangle exists and satisfies the condition.\n";
        }
        else
        {
            cout << "The triangle exists but does not satisfy the condition.\n";
        }
    }
    else
    {
        cout << "The triangle does not exist.\n";
    }

    return 0;
}

//#include <iostream>
//#include <math.h> 
//#include <iomanip>
//
//using namespace std;
//
//#define PI 3.14159265358979323846  
//#define EQUALITY(A, B, C) (cos(A) + cos(B) + cos(C) <= 1.5)
//#define DEGREES_TO_RADIANS(degrees) ((degrees) * PI / 180.0)        
//#define TRIANGLE_EXISTS(A, B, C) ((A) + (B) > (C) && (A) + (C) > (B) && (B) + (C) > (A))
//
//int main()
//{
//    for (int A = 1; A <= 178; ++A) {
//        for (int B = 1; B <= 178; ++B) {
//            for (int C = 1; C <= 178; ++C) {
//                if (TRIANGLE_EXISTS(A, B, C)) {
//                    double radA = DEGREES_TO_RADIANS(A);
//                    double radB = DEGREES_TO_RADIANS(B);
//                    double radC = DEGREES_TO_RADIANS(C);
//                    if (EQUALITY(radA, radB, radC)) {
//                        cout << "Angles: " << setw(3) << A << ", " << setw(3) << B << ", " << setw(3) << C << " satisfy the condition.\n";
//                    }
//                }
//            }
//        }
//    }
//
//    return 0;
//}