//==================================================================
#include <windows.h> // defines for POINT, and GetCursorPos().
#include <iostream>
#include <conio.h>
#include <Winuser.h>

using namespace std;

//using namespace std;

int main(int argc, char* argv[])
{
 SetConsoleTitle("Ajedrez");
 HWND hwnd;
 for (int i=1;i<20;i++)
    hwnd = FindWindow(NULL, "Ajedrez");
 HDC hdc = GetDC(hwnd);

 POINT aPoint;


 while(1)
 {
  int oe=0;
  //clrscr();
  GetCursorPos(&aPoint);
  ScreenToClient(hwnd,&aPoint);

 cout << "Mouse position (x/y) was: " << aPoint.x << "/" << aPoint.y << endl;
 }
 getch();
 return 0;
}
//===========================================================
