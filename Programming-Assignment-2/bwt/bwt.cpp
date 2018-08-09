#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

string BWT(const string& text) {
  string result = "";

  // write your code here
  const size_t n = text.size();
  vector<string> m;
  for (size_t i = 0; i < n; ++i) {
    string s = text.substr(i, n-i);
    s += text.substr(0,i);
    m.push_back(s);
  }
  std::sort(m.begin(),m.end());
  for (const string& s : m) {
    result += s[n-1];
  }

  return result;
}

int main() {
  string text;
  cin >> text;
  cout << BWT(text) << endl;
  return 0;
}
