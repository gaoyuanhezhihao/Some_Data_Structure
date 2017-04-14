#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <queue>
using namespace std;
struct TrieNode{
        TrieNode * sub_trees[26];
        bool last_of_word=false;
        TrieNode(){
            for(int i = 0; i < 26; ++i){
                sub_trees[i] = NULL;
            }
        }

        ~TrieNode() {
            for(int i = 0; i < 26; ++i) {
                if(NULL != sub_trees[i]) {
                    delete sub_trees[i];
                }
            }
        }
};

class TrieTree{
    private:
        TrieNode head;
    public:
        TrieTree(const vector<string> & dict) {
            build_tree(dict);
        }
        void add_word(const string & word) {
            TrieNode * node = & head;
            //TrieNode * node = head.sub_trees[word[0]-'a'];
            //if(NULL == node) {
                //sub_trees[word[0] - 'a']= new TrieNode();
                //node = sub_trees[word[0] - 'a'];
            //}
            for(int i = 0;  i < word.size(); ++i){
                if(NULL == node->sub_trees[word[i] - 'a']) {
                    node->sub_trees[word[i] - 'a'] = new TrieNode();
                }
                node =node->sub_trees[word[i] - 'a']; 
            }
            node->last_of_word = true;
        }

        const TrieNode * ref_head() const {
            return &head;
        }

        void plot_tree() {
            //TrieNode * node = &head;
            const std::string file_name = "trie_tree.dot";
            std::ofstream file_stream(file_name);
            file_stream << "graph trie"  << "{\n";
            std::queue<pair<TrieNode *, string>> father_que;
            father_que.push({&head, "0"});
            int node_cnt = 0; 
            while(!father_que.empty()) {
                pair<TrieNode *,string> node = father_que.front();
                father_que.pop();

                for(int i = 0; i < 26; ++i) {
                    TrieNode * child = node.first->sub_trees[i];
                    if(child != NULL) {
                        string child_name;
                        child_name += char('a' +i);
                        child_name += to_string(++node_cnt);
                        if(child ->last_of_word) {
                            child_name += '_';
                        }
                        file_stream << node.second << "--" << child_name<< ";\n";
                        father_que.push({child, child_name});
                    }
                }
            }
            file_stream << "}" << std::endl;
            std::string cmd{"dot -Tpng "};
            cmd += file_name;
            string name("trie");
            cmd += (" -o ./"+ name+ ".png");
            std::cout << cmd << std::endl;
            system(cmd.c_str());
        }


        void build_tree(const std::vector<string> & dict) {
            for(const string & word: dict) {
                add_word(word);
            }
        }
};

class TrieWalker{
    private:
        const TrieTree & _tree;
        const TrieNode * node;
    public:
        TrieWalker(const TrieTree & word_tree):_tree(word_tree), node(word_tree.ref_head()){}
        enum WalkState{
            WrongChar,
            Word,
            GoodChar
        };

        WalkState walk_down(const char ch) {
            node = node->sub_trees[ch-'a'];
            //cout << ch <<  " " << node->last_of_word << endl;
            if(node == NULL) {
                return WalkState::WrongChar;
            }else if(node->last_of_word){ 
                return WalkState::Word;
            }else {
                return WalkState::GoodChar;
            }
        }
};
#endif //TREE_H
