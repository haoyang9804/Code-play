#include <string>
#include <iostream>
#include <set>
#include <vector>
#include <sstream>
#include <map>
#include <chrono>
#include <utility>
#include <algorithm>
using namespace std;

vector<string> strs;
set<string> str_set;
map<string, int> str_map;
int main() {
  
  stringstream ss;
  for (int i = 0; i < 10000; i++) {
    ss << i;
    string str = ss.str();
    strs.push_back(str);
    str_set.insert(str);
    str_map.insert(make_pair(str, i));
  }
  auto start = std::chrono::high_resolution_clock::now();
  auto pos = find(strs.begin(), strs.end(), "9999");
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  cout << "duration = " << duration.count() << std::endl; 
  cout << *pos << endl;
  cout << "==========" << endl;
  

  auto start2 = std::chrono::high_resolution_clock::now();
  int value = str_map["9999"];
  auto stop2 = std::chrono::high_resolution_clock::now();
  auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop2 - start2);
  cout << "duration = " << duration2.count() << std::endl;  
  
}
