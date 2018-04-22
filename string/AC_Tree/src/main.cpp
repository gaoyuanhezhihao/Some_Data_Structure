#include <list>
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <string>
#include <queue>
#include <limits>
#include <sstream>
#include <array>
#include <cassert>
#include <stdio.h>

const int INT_MIN=std::numeric_limits<int>::min();
const int INT_MAX=std::numeric_limits<int>::max();
using namespace std;
const int DOWN_SIZE = 26;
inline unsigned char2id(const char ch) {
    return ch - 'a';
}
inline std::string id2name(const unsigned id) {
    return  std::string(1, id + 'a');
}



struct Node{
    std::array<Node*, DOWN_SIZE> children{{nullptr}};
    Node * fail;
    bool is_pat;
    //std::vector<int> word_idx;
    Node * out;
    int _id = 0;
    Node(int id):fail(nullptr), is_pat(false), out(nullptr), _id(id){
        for(int i = 0; i < DOWN_SIZE; ++i) {
            assert(children[i] == nullptr);
        }
    }
    ~Node() {
        for(auto itr = children.begin(); itr != children.end(); ++itr) {
            if(*itr != nullptr) {
                delete *itr;
            }
        }
    }
    void print_down(std::ostream &out_buf, const std::string &relation_sign, const std::string &sep_sign, const std::string name){
        out_buf << _id << sep_sign;
        out_buf << _id << " [ label=\"" << name  << "\" ] "<< sep_sign;
        if(nullptr != fail) {
            out_buf << _id << relation_sign << fail->_id << " [ color = red ] " << sep_sign;
        }
        if(nullptr != out) {
            out_buf << _id << relation_sign << out->_id << " [ color = blue ] " << sep_sign;
        }


        for(int i = 0; i < DOWN_SIZE; ++i) {
            if(children[i] != nullptr) {
                const std::string child_name = id2name(i);
                out_buf<< _id << relation_sign << children[i]->_id<< sep_sign;
                children[i]->print_down(out_buf, relation_sign, sep_sign, child_name);
            }
        }
    }
};

class Tree{
    public:
        Node * create_node(){
            return new Node(++id);
        }
        std::vector<std::string> dict;
        Tree(const std::vector<std::string> & dict):dict(dict), root(id){buildTree();}
        void print(std::ostream & out) {
            root.print_down(out, "-->", ";\n", "root");
        }
        bool plot_tree() {
            const std::string name("tmp");
            const std::string file_name = name+ ".dot";
            std::ofstream file_stream(file_name);
            if(false == file_stream.is_open()) {
                return false;
            }
            //file_stream << "graph " << name<< "{\n";
            file_stream << "digraph" << "{\n";
            root.print_down(file_stream, " -> ", ";\n", "root"); 
            file_stream << "}" << std::endl;
            std::string cmd{"dot -Tpng "};
            cmd += file_name;
            cmd += (" -o ./"+ name+ ".png");
            std::cout << cmd << std::endl;
            system(cmd.c_str());
            return true;
        }
        bool check_any(const string & str) {
            Node * p = & root;
            assert(nullptr != p);
            auto s = str.cbegin();
            while( s != str.cend()) {
                if(p->is_pat) {
                    return true;
                }
                if(p->out != nullptr) {
                    return true;
                }
                
                Node * child = p->children[char2id(*s)];
                if(nullptr == child) {
                    if(&root == p) {
                        ++s;
                    }else {
                        p = p->fail;
                        assert(nullptr != p);
                    }
                }else{
                    p = child;
                    ++s;
                }
            }
            if(p->is_pat) {
                return true;
            }
            return false;
        }
    private:
        int id = 0;
        Node root;
        void buildTree(){
            const int n = dict.size();
            /* build trie tree */
            for(int i = 0; i < n; ++i) {
                Node * cur = & root;
                //std::cout << dict[i] << std::endl;
                for(char c :dict[i]){
                    if(nullptr == cur->children[char2id(c)]){
                        cur->children[char2id(c)] = create_node();
                    }
                    cur = cur->children[char2id(c)];
                }
                cur->is_pat = true;
            }

            /* fail jmp pointer */
            std::queue<Node *> buf;
            root.fail = nullptr;
            /*special treat for the first level */
            for(Node * child : root.children) {
                if(nullptr != child) {
                    child->fail = & root;
                    buf.push(child);
                }
            }

            //for(Node * & child: root.children) {
            //if(nullptr == child) {
            //child = & root;
            //}
            //}



            while(!buf.empty()) {
                Node * cur = buf.front();
                buf.pop();

                for(int i = 0; i < DOWN_SIZE; ++i) {
                    Node * const child = cur->children[i];
                    if(nullptr != child) {
                        buf.push(child);
                        /* search the fail pointer for child */
                        Node * p = cur->fail;
                        while(p != nullptr) {
                            if(p->children[i] != nullptr) {
                                break;
                            }
                            p = p->fail;
                        }

                        if(nullptr == p) {
                            child->fail = &root;
                        }else {
                            child->fail = p->children[i];
                        }
                        /* output pointer*/
                        if(child->fail->is_pat) {
                            child->out = child->fail;
                        }else {
                            child->out = child->fail->out;
                        }
                    }
                }
            }
        }
};

void solve(const vector<string> & words, const string & src){
    Tree ac_tree(words);
    if(ac_tree.check_any(src)){
        cout << "YES" << endl;
    }else {
        cout << "NO" << endl;
    }
    
}
int main() {
    std::string line;
    getline(cin, line); 
    std::stringstream iss(line);
    int N = 0;
    iss >> N;
    vector<string> pats(N);
    for(int i = 0; i < N; ++i) {
        getline(cin, line); 
        std::stringstream iss(line);
        iss >> pats[i];
    }
    string src;
    getline(cin, src); 

    //for(const string & p: pats) {
        //cout << "\"" << p << "\"" << endl;
    //}
    //cout << "\"" << src<< "\"" << endl;
    solve(pats, src);

    //vector<string> words{"aaabc", "aaac", "abcc", "ac", "bcd", "cd"};
    //string src("aaaaaaaaaaabaaadaaac");
    //solve(words, src);
    return 0;
}
