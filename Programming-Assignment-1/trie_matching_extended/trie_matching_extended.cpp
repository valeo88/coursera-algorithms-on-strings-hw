#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int const Letters =    4;
int const NA      =   -1;

struct Node
{
	int next [Letters];
	bool patternEnd;

	Node ()
	{
		fill (next, next + Letters, NA);
		patternEnd = false;
	}
};

int letterToIndex (char letter)
{
	switch (letter)
	{
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		default: assert (false); return -1;
	}
}

typedef vector<Node> trie;


trie build_trie(const vector<string> & patterns) {
  trie t;
  // write your code here
  // add root to trie
  Node root;
  t.push_back(root);
  for (const string& pattern : patterns) {
    size_t current_idx = 0;
    for (int i = 0; i < pattern.size(); ++i) {
        char current_symbol = pattern[i];
        if (t[current_idx].next[letterToIndex(current_symbol)] != NA) {
            current_idx = t[current_idx].next[letterToIndex(current_symbol)];
            if (!t[current_idx].patternEnd)
                t[current_idx].patternEnd = (i==pattern.size()-1 ? true : false);
        } else {
            Node new_node;
            new_node.patternEnd = (i==pattern.size()-1 ? true : false);
            t.push_back(new_node);
            const size_t new_idx = t.size()-1;
            //cout << "NodeData idx" << idx.index << " patternEnd: " << idx.patternEnd << endl;
            t[current_idx].next[letterToIndex(current_symbol)] = new_idx;
            current_idx = new_idx;
        }
    }
  }
  return t;
}

int prefix_trie_matching(const string& text, const int start_idx, const trie& t) {
    //cout << "text: " << text << " start_idx: " << start_idx << endl;
    char symbol = text[start_idx];
    int idx = start_idx;
    Node v = t[0];
    while (true) {
        //cout << "symbol: " << symbol << " idx: " << idx << " edge: " << v <<endl;
        if (v.patternEnd) {
            // its a leaf
            return start_idx;
        } else if (idx < text.size() && v.next[letterToIndex(symbol)] != NA) {
            // go to next node in trie
            v = t[v.next[letterToIndex(symbol)]];
            // go to next symbol in text
            idx++;
            symbol = text[idx];
        } else {
            // pattern no found
            return -1;
        }
    }
    return -1;
}

vector <int> solve (const string& text, int n, const vector <string>& patterns)
{
	vector <int> result;

	// write your code here
	trie t = build_trie(patterns);
    /*for (auto& n : t) {
        cout << "[";
        for (int l : n.next) {
            cout << l << ", ";
        }
        cout << "]" << "patternEnd: " << n.patternEnd << endl;
    }*/
	for (int i = 0; i < text.size(); ++i) {
        int res = prefix_trie_matching(text, i, t);
        if (res != -1) {
            result.push_back(res);
        }
	}

	return result;
}

int main (void)
{
	string t;
	cin >> t;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	vector <int> ans;
	ans = solve (t, n, patterns);

	for (int i = 0; i < (int) ans.size (); i++)
	{
		cout << ans[i];
		if (i + 1 < (int) ans.size ())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}
