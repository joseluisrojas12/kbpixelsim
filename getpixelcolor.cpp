#include <iostream>
#include <stdlib.h>
#include <windows.h>
using namespace std;
int main()
{
int x,y;
    cout << "Enter coordanets: "<<endl;
         cout<<"For X : ";
         cin >> x;
         cout<<"For Y : ";
         cin >> y;
         cout<<endl;
             HDC hdc = GetDC(NULL);
             DWORD color = GetPixel(hdc, x, y);
             unsigned int r = GetRValue(color);
             unsigned int g = GetGValue(color);
             unsigned int b = GetBValue(color);
    cout << "Red: " << r << endl;
    cout << "Green: " << g << endl;
    cout << "Blue: " << b << endl;
cin.get();
cin.ignore();
return 0;
}
