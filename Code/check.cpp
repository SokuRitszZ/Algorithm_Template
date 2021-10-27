#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

int main(){
  int x, y;
  ifstream in1("out.out", ios::in);
  ifstream in2("check.out", ios::in);
  
  int i = 0;
  while (in1 >> x, in2 >> y){
    if (x xor y) {
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
      cerr << "Failed. \n";
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
      cerr << "In line " << ++i << endl;
      cerr << "Received: " << x << '.' << endl;
      cerr << "Expected: " << y << '.' << endl;
      return 0;
    }   
    i++ ;
  }
  
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
  cerr << "Passed." << endl;
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
  return 0;
}