#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::istringstream;
using std::map;
using std::string;
using std::vector;

// Preprocess the Burrows-Wheeler Transform bwt of some text
// and compute as a result:
//   * starts - for each character C in bwt, starts[C] is the first position
//       of this character in the sorted array of
//       all characters of the text.
//   * occ_count_before - for each character C in bwt and each position P in bwt,
//       occ_count_before[C][P] is the number of occurrences of character C in bwt
//       from position 0 to position P inclusive.
void PreprocessBWT(const string& bwt,
                   map<char, int>& starts,
                   map<char, vector<int> >& occ_count_before) {
  // Implement this function yourself
  const size_t n = bwt.size();
  for (size_t i = 0; i < n; ++i) {
    const char& c = bwt[i];
    if (starts.count(c)==0) {
        starts[c] = i;
    }
    if (occ_count_before.count(c)==0) {
        occ_count_before[c].resize(n+1,0);
    }
    if (i > 0) {
        occ_count_before[c][i] = occ_count_before[c][i-1] + 1;
    } else {
        occ_count_before[c][i] = 1;
    }
    for (auto& p : occ_count_before) {
        if (p.first != c) {
            occ_count_before[p.first][i] = occ_count_before[p.first][i-1];
        }
        occ_count_before[p.first][i+1] = occ_count_before[p.first][i];
    }
  }
}

// Compute the number of occurrences of string pattern in the text
// given only Burrows-Wheeler Transform bwt of the text and additional
// information we get from the preprocessing stage - starts and occ_counts_before.
int CountOccurrences(const string& pattern,
                     const string& bwt,
                     const map<char, int>& starts,
                     const map<char, vector<int> >& occ_count_before) {
  // Implement this function yourself
  const size_t n = bwt.size();
  size_t top = 0;
  size_t bottom = n - 1;
  size_t symbol_idx = pattern.size();
  while (top <= bottom) {
    //cout << "top: " << top << " bottom: " << bottom << "\n";
    if (symbol_idx > 0) {
        symbol_idx--;
        char symbol = pattern[symbol_idx];
        if (occ_count_before.at(symbol)[bottom] > occ_count_before.at(symbol)[top]) {
            top = starts.at(symbol) + occ_count_before.at(symbol)[top];
            bottom = starts.at(symbol) + occ_count_before.at(symbol)[bottom+1] - 1;
        } else {
            return 0;
        }
    } else {
        return bottom - top + 1;
    }
  }
  return bottom - top + 1;
}


int main() {
  string bwt;
  cin >> bwt;
  int pattern_count;
  cin >> pattern_count;
  // Start of each character in the sorted list of characters of bwt,
  // see the description in the comment about function PreprocessBWT
  map<char, int> starts;
  // Occurrence counts for each character and each position in bwt,
  // see the description in the comment about function PreprocessBWT
  map<char, vector<int> > occ_count_before;
  // Preprocess the BWT once to get starts and occ_count_before.
  // For each pattern, we will then use these precomputed values and
  // spend only O(|pattern|) to find all occurrences of the pattern
  // in the text instead of O(|pattern| + |text|).
  PreprocessBWT(bwt, starts, occ_count_before);
  for (const auto& p : occ_count_before) {
    //cout << p.first << ": " ;
    //for (int i : p.second) {
    //    cout << i << ", ";
    //}
    //cout << "\n";
  }
  for (int pi = 0; pi < pattern_count; ++pi) {
    string pattern;
    cin >> pattern;
    int occ_count = CountOccurrences(pattern, bwt, starts, occ_count_before);
    printf("%d ", occ_count);
  }
  printf("\n");
  return 0;
}
