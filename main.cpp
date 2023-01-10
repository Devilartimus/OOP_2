#include <iostream>
#include "Prot.cpp"

using namespace std;
using namespace DevMatr;

int main()
{
    int x, y;
    Matrix A;
    Matrix B(2, 3);
    A.Input();
    B.Input();
    cout << B << endl << endl;
    cout << "Enter the dimension of the matrix C: " << endl;
    cout << "x >> ";
    cin >> x;
    cout << "y >> ";
    cin >> y;
    cout << endl;
    Matrix C(x, y, FunctInput);
    cout << C << endl << endl;
    A = B * C;
    cout << A << endl << endl;
    cout << "A[0][1]= ";
    cout << A[0][1] << endl << endl;
    return 0;
}
