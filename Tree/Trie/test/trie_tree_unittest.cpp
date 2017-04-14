#include "gtest/gtest.h"
#include "trie/tree.hpp"
#include <string>
using namespace std;
class TrieTreeTest: public ::testing::Test{
    protected:
        virtual void SetUp(){

        }

        virtual void TearDown(){

        }
};
int main(int argc, char **argv) {
      ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();

}

TEST_F(TrieTreeTest, walker) {

    vector<string> dict{"abc", "aec", "d", "de", "dc"};
    TrieTree word_tree(dict);
    TrieWalker dict_walker(word_tree);

    EXPECT_EQ(TrieWalker::GoodChar, dict_walker.walk_down('a'));
    EXPECT_EQ(TrieWalker::GoodChar, dict_walker.walk_down('b'));
    EXPECT_EQ(TrieWalker::Word, dict_walker.walk_down('c'));

    TrieWalker dict_walker1(word_tree);
    EXPECT_EQ(TrieWalker::GoodChar, dict_walker1.walk_down('a'));
    EXPECT_EQ(TrieWalker::GoodChar, dict_walker1.walk_down('e'));
    EXPECT_EQ(TrieWalker::Word, dict_walker1.walk_down('c'));

    TrieWalker dict_walker2(word_tree);
    EXPECT_EQ(TrieWalker::Word, dict_walker2.walk_down('d'));
    EXPECT_EQ(TrieWalker::Word, dict_walker2.walk_down('c'));
    EXPECT_EQ(TrieWalker::WrongChar, dict_walker2.walk_down('e'));

    TrieWalker dict_walker3(word_tree);
    EXPECT_EQ(TrieWalker::Word, dict_walker3.walk_down('d'));
    EXPECT_EQ(TrieWalker::Word, dict_walker3.walk_down('e'));
    EXPECT_EQ(TrieWalker::WrongChar, dict_walker3.walk_down('e'));
    //for(const string & word: dict) {
        //TrieWalker dict_walker(word_tree);
        //const int len = word.size();
        //for(int i = 0; i < len-1; ++i) {
            //EXPECT_EQ(TrieWalker::GoodChar, dict_walker.walk_down(word[i]));
        //}
        //EXPECT_EQ(TrieWalker::Word, dict_walker.walk_down(word[len-1]));
    //}
}


