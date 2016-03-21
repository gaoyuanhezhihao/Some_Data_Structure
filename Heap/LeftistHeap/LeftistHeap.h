#ifndef LEFTISTHEAP_H_INCLUDED
#define LEFTISTHEAP_H_INCLUDED
#include <cstddef> // nullptr
#include <cstdlib> // system()
#include <string>
using namespace std;
template <typename Comparable>
struct TreeNode
{
public:
    Comparable Element;
    TreeNode * LeftChild;
    TreeNode * RightChild;
    int npl;
};

template <typename Comparable>
TreeNode<Comparable>* merge(TreeNode<Comparable> * H1, TreeNode<Comparable> * H2)
{
    TreeNode<Comparable> * master;
    TreeNode<Comparable> * slave;
    if(H1 == nullptr)
    {
        return H2;
    }
    if(H2 == nullptr)
    {
        return H1;
    }
    // who is the real master ?
    if(H1->Element < H2->Element)
    {
        master = H1;
        slave = H2;
    }
    else
    {
        master = H2;
        slave = H1;
    }

    //could the two merged directly ?
    if(master->LeftChild == nullptr)
    {
        master->LeftChild = slave;
        return master;
    }
    // merge the right child with the slave.
    master->RightChild = merge(master->RightChild, slave); // There is a promise: the merge will return the correct merge of right child and slave.
    // Is the npl of right child larger than the left child's ?
    if(master->RightChild->npl > master->LeftChild->npl)
    {
        cout << "going to swap: " << master->RightChild->Element << ',' << master->LeftChild->Element << endl;
        TreeNode<Comparable> * tmp = master->RightChild;
        master -> RightChild = master -> LeftChild;
        master -> LeftChild = tmp;
    }
    // update the npl of the master
    master->npl = master -> RightChild -> npl + 1;

    // !Promise: H1 is merged with H2. And the return is the perfect leftist heap.
    return master;
}

template <typename Comparable>
void insert(Comparable data, TreeNode<Comparable> * root)
{
    // build a heap with only one node.
    TreeNode<Comparable> * new_node = new TreeNode<Comparable>;
    new_node->Element = data;
    new_node->LeftChild = nullptr;
    new_node->RightChild = nullptr;
    new_node->npl = 0;
    merge(root, new_node);
}
template <typename Comparable>
TreeNode<Comparable> * build_from_bina_heap(Comparable * head, int array_size, int id)
{
    /*
    There is a promise the inputed binary heap should also be a leftist heap. So if there
    are any point doesn't exist in the leftist heap, but there should be a element in the
    position of a binary heap, we will fill it with -1.
    */
    if(id >= array_size)
    {
        return nullptr;
    }
    if(*(head+id) == -1)
    {
        return nullptr;
    }
    TreeNode<Comparable> * new_node = new TreeNode<Comparable>;
    new_node->Element = *(head+id);
    new_node->LeftChild = build_from_bina_heap(head, array_size, 2*id);
    new_node->RightChild = build_from_bina_heap(head, array_size, 2*id+1);
    if(new_node->RightChild == nullptr)
    {
        new_node->npl = 0;
    }
    else
    {
        new_node->npl = 1 + new_node->RightChild->npl;
    }
    return new_node;
}

template <typename Comparable>
TreeNode<Comparable> * build_heap(Comparable * head, int array_size)
{
    int i = 0;
    TreeNode<Comparable> * root= new TreeNode<Comparable>;
    root->Element = *(head);
    root->LeftChild = nullptr;
    root->RightChild = nullptr;
    root->npl = 0;

    for(i=1; i< array_size; ++i)
    {
        insert(*(head+i), root);
    }
    cout << "insert :" << array_size << endl;
    return root;
}
template <typename Comparable>
bool show_heap(TreeNode<Comparable> * root,const char file_name[])
{
    string name(file_name);
    ofstream file_stream;
    file_stream.open(name+".dot");
    file_stream<< "	digraph G {\n" << "graph [ordering=\"out\"];" << endl;
    print_node(file_stream, root);
    file_stream<< "}" << endl;
    name = "dot.exe -Tpng "+name+".dot -o " + name + ".png";
    cout <<name << endl;
    system(name.c_str());
	//system("dot.exe -Tpng graphviz_1.dot -o h.png");
	return true;
}

template <typename Comparable>
bool print_node(ofstream & out_file, TreeNode<Comparable> * pNode)
{
    if(pNode->LeftChild != nullptr)
    {
        out_file << '\"'<<pNode->Element<< ','<<pNode->npl<<'\"' << "->" <<'\"'<< pNode->LeftChild->Element<< ','<<pNode->LeftChild->npl<<'\"' << endl;
        print_node(out_file, pNode->LeftChild);
    }
    if(pNode->RightChild != nullptr)
    {
        out_file <<'\"'<< pNode->Element<< ','<<pNode->npl<<'\"' << "->" <<'\"'<< pNode->RightChild->Element<< ','<<pNode->RightChild->npl<<'\"' << endl;
        print_node(out_file, pNode->RightChild);
    }
    return true;
}
#endif // LEFTISTHEAP_H_INCLUDED
