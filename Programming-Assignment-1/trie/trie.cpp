#include <string>
#include <iostream>
#include <vector>
#include <map>

using std::map;
using std::vector;
using std::string;

typedef map<char, int> edges;
typedef vector<edges> trie;

trie build_trie(vector<string> & patterns) {
  trie t;
  // write your code here
  // add root to trie
  edges root;
  t.push_back(root);
  for (const string& pattern : patterns) {
    size_t current_idx = 0;
    for (int i = 0; i < pattern.size(); ++i) {
        char current_symbol = pattern[i];
        if (t[current_idx].count(current_symbol)>0) {
            current_idx = t[current_idx][current_symbol];
        } else {
            edges new_node;
            t.push_back(new_node);
            const size_t new_idx = t.size()-1;
            t[current_idx][current_symbol] = new_idx;
            current_idx = new_idx;
        }
    }
  }
  return t;
}

int main() {
  size_t n;
  std::cin >> n;
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    std::cin >> s;
    patterns.push_back(s);
  }

  trie t = build_trie(patterns);
  for (size_t i = 0; i < t.size(); ++i) {
    for (const auto & j : t[i]) {
      std::cout << i << "->" << j.second << ":" << j.first << "\n";
    }
  }

  return 0;
}
