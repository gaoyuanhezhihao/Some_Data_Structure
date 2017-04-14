#include <iostream>
#include "trie/tree.hpp"
using namespace std;
int main(int argc, char ** argv) {
    vector<string> dict{"abc", "aec", "d", "de", "dc"};
    TrieTree word_tree(dict);
    const TrieNode * head = word_tree.ref_head();
    cout << head->sub_trees[0]->last_of_word << endl;

    TrieWalker dict_walker(word_tree);
    cout <<dict_walker.walk_down('a') << endl;
    word_tree.plot_tree();
}
