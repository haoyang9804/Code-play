#include <iostream>
using namespace std;

int main() {
  int x = 1;
  int& y = x;
  int z = 2;
  y = z;
  cout << x << " " << y << " " << z << endl;
  y = 3;
  cout << x << " " << y << " " << z << endl;
}