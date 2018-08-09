#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;

// enumerate symbols in text from 1 to ... for each unique symbol
vector<int> enumerate_chars(const string& text) {
    const size_t n = text.size();
    map<char, int> last_num;
    vector<int> nums(n,0);
    for (size_t i = 0; i < n; ++i) {
        const char& c = text[i];
        nums[i] = ++last_num[c];
    }
    return nums;
}

// find index for char with char_num in text string
size_t find_idx_for_char(const string& text, const vector<int>& numbers, const char& c, int char_num) {
    auto it = std::lower_bound(text.begin(), text.end(), c);
    return it - text.begin() + char_num - 1;
}

string InverseBWT(const string& bwt) {
  string text = "";

  // write your code here
  const size_t n = bwt.size();
  // enumerate symbols in bwt
  vector<int> bwt_nums = enumerate_chars(bwt);
  // first column is sorted bwt
  string first_column = bwt;
  std::sort(first_column.begin(), first_column.end());
  vector<int> first_column_nums = enumerate_chars(first_column);
  // get 0 symbol from bwt
  size_t current_idx = 0;
  char current_char = bwt[current_idx];
  text += first_column[current_idx];
  while (text.size() < n) {
    // add only symbols from bwt with current_idx
    text += bwt[current_idx];
    current_idx = find_idx_for_char(first_column, first_column_nums, text.back(), bwt_nums[current_idx]);
  }
  std::reverse(text.begin(), text.end());
  return text;
}

int main() {
  string bwt;
  cin >> bwt;
  cout << InverseBWT(bwt) << endl;
  return 0;
}
