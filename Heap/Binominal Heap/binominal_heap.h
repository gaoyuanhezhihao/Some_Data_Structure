#ifndef BINOMINAL_HEAP_H_INCLUDED
#define BINOMINAL_HEAP_H_INCLUDED

#include <cstddef> // nullptr
#include <cstdlib> // system()
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
template <typename Element_Type>
struct bino_heap_node
{
    bino_heap_node<Element_Type> * p_sister;
    bino_heap_node<Element_Type> * p_child;
    Element_Type element;
    ~bino_heap_node()
    {
        cout <<"bino_heap_node destructor" << endl;
    }
};
template <typename Element_Type>
class Bino_Heap
{
private:
    //Function
    bool print_node(ofstream & out_file, bool have_a_father, Element_Type father_data, bino_heap_node<Element_Type> * pNode);
public:
    // Data
    vector<bino_heap_node<Element_Type> *> sub_heaps;
    // Function
    bino_heap_node<Element_Type> * add_sub_heap(bino_heap_node<Element_Type> * p_node1, bino_heap_node<Element_Type> * p_node2);
    bool merge_bino_heap(Bino_Heap<Element_Type> & guest_heap);
    bool insert_1(const Element_Type & data);
    ~Bino_Heap()
    {
        cout <<"Bino_Heap Destuctor" << endl;
    }
    Element_Type delete_min(Element_Type & min_data);
    bool show_bino_heap(const char file_name[]);
};

template <typename Element_Type>
bool buid_bino_heap(Element_Type * data_head, int num, Bino_Heap<Element_Type> & b_heaps)
{
    int i = 0;
    for(i = 0; i< num; ++i)
    {
        b_heaps.insert_1(*(data_head+i));
    }
    return true;
}

template <typename Element_Type>
void build_bino_heap(vector<bino_heap_node<Element_Type>*> & new_bino_heap_vec, bino_heap_node<Element_Type>* p_heap_tree)
{
    if(p_heap_tree == nullptr)
    {
        return;
    }
    else if(p_heap_tree->p_sister != nullptr)
    {
        build_bino_heap(new_bino_heap_vec, p_heap_tree->p_sister);
    }
    new_bino_heap_vec.push_back(p_heap_tree);
    return;
}

template <typename Element_Type>
bool Bino_Heap<Element_Type>::show_bino_heap(const char file_name[])
{
    string name(file_name);
    ofstream file_stream;
    file_stream.open(name+".dot");
    file_stream<< "	digraph G {\n" << "graph [ordering=\"out\"];" << endl;
    auto it = sub_heaps.begin();
    for(;it != sub_heaps.end();++it)
    {

        print_node(file_stream, false, NULL, *it);
    }
    file_stream<< "}" << endl;
    name = "dot.exe -Tpng "+name+".dot -o " + name + ".png";
    cout <<name << endl;
    system(name.c_str());
	//system("dot.exe -Tpng graphviz_1.dot -o h.png");
	return true;
}

template <typename Element_Type>
bool Bino_Heap<Element_Type>::print_node(ofstream & out_file, bool have_a_father, Element_Type father_data, bino_heap_node<Element_Type> * pNode)
{
    if(nullptr == pNode)
    {
        return false;
    }
    else
    {


        if(have_a_father)
        {
            // let my sisters first.
            if(nullptr != pNode->p_sister)
            {
                print_node(out_file, true, father_data, pNode->p_sister);
            }
            // print myself.
            out_file << '\"'<<father_data<< '\"'<< "->" <<'\"'<<pNode->element <<'\"' << endl;
        }
        // print my children.
        if(nullptr != pNode->p_child)
        {
            print_node(out_file, true, pNode->element, pNode->p_child);
        }
    }
    return true;
}
template <typename Element_Type>
Element_Type Bino_Heap<Element_Type>:: delete_min(Element_Type & min_data)
{
    Element_Type min_value = 0;
    if(sub_heaps.empty())
    {
        return 1;
    }
    // find the min sub_heap_tree
    auto it = this->sub_heaps.begin();
    bino_heap_node<Element_Type> * p_min_node = *it;
    for (; it != sub_heaps.end(); ++it)
    {
        if(*it -> element < p_min_node->element)
        {
            p_min_node = *it;
        }
    }
    min_value = p_min_node->element;
    // split the min sub_heap_tree into a new bino_heap
    Bino_Heap<Element_Type> new_bino_heap;
    build_bino_heap(new_bino_heap.sub_heaps, p_min_node->p_child);
    merge_bino_heap(new_bino_heap);
    return min_value;
}
template <typename Element_Type>
bool Bino_Heap<Element_Type>::insert_1(const Element_Type & data)
{
    Element_Type _debug_tmp;
    Bino_Heap<Element_Type> tmp_bino_heap;
    bino_heap_node<Element_Type> * new_node = new bino_heap_node<Element_Type>;
    if(new_node == nullptr)
    {
        throw;
    }
    new_node->element = data;
    new_node->p_child = nullptr;
    new_node->p_sister = nullptr;
    tmp_bino_heap.sub_heaps.push_back(new_node);
    merge_bino_heap(tmp_bino_heap);
    auto it = tmp_bino_heap.sub_heaps.begin();
    _debug_tmp = (*it)->element;
    cout << _debug_tmp << endl;
    return true;
}

template <typename Element_Type>
/*
*   the result will be returned in a new node. This just like a family adopt a new child.
*   And the father only need to concern about the new child. Because the new child will take care of her
*   sisters.
*   None of the two bino_heap_node could be null.
*/
bino_heap_node<Element_Type> * Bino_Heap<Element_Type>::add_sub_heap(bino_heap_node<Element_Type> * p_node1, bino_heap_node<Element_Type> * p_node2)
{
    if(p_node1 == nullptr || p_node2 == nullptr)
    {
        throw;
    }
    if(p_node1 == p_node2)
    {
        throw;
    }

    if(p_node1->element < p_node2->element)
    {
        p_node2->p_sister = p_node1->p_child;
        p_node1->p_child = p_node2;
        return p_node1;
    }
    else
    {
        p_node1->p_sister = p_node2->p_child;
        p_node2->p_child = p_node1;
        return p_node2;
    }
}

template <typename Element_Type>
/* Iterate the guest_heap elements one by one. And add the two in the same bit position.*/
bool Bino_Heap<Element_Type>::merge_bino_heap(Bino_Heap<Element_Type> & guest_heap)
{
    auto it_guest = guest_heap.sub_heaps.begin();
    auto it_this = this->sub_heaps.begin();
    bino_heap_node<Element_Type> * carry = nullptr;
    bino_heap_node<Element_Type> * copy_carry = nullptr;
    if(guest_heap.sub_heaps.size()+1 > sub_heaps.size() )
    {
        int size_add = guest_heap.sub_heaps.size() + 1 - sub_heaps.size();
        int i = 0;
        for (i = 0; i< size_add; ++i)
        {
            sub_heaps.push_back(nullptr);
        }
    }
    it_this = this->sub_heaps.begin();
    int _debug_case = 0;
    for(;it_guest != guest_heap.sub_heaps.end(); ++it_guest, ++it_this)
    {
        switch(!! *it_this + 2 * !! *it_guest + 4 * !! carry)
        {
        case 0:
            _debug_case = 0;
            break;
        case 1:
            _debug_case = 1;
            break;
        case 2:
            _debug_case = 2;
            *it_this = *it_guest;
            break;
        case 3:
            _debug_case = 3;
            carry = add_sub_heap(*it_this, *it_guest);
            *it_this = nullptr;
            break;
        case 4:
            _debug_case = 4;
            *it_this = carry;
            carry = nullptr;
            break;
        case 5:
            _debug_case = 5;
            carry = add_sub_heap(*it_this, carry);
            *it_this = nullptr;
            break;
        case 6:
            _debug_case = 6;
            carry = add_sub_heap(*it_guest, carry);
            break;
        case 7:
            _debug_case = 7;
            copy_carry = carry;
            carry = add_sub_heap(*it_this, *it_guest);
            *it_this = copy_carry;
            break;
        default:
            throw;
        }
    }
    auto _debug_p = *it_this;
    while(carry != nullptr)
    {
        _debug_p = *it_this;
        if(carry == *it_this)
        {
            throw;
        }
        if(it_this == sub_heaps.end())
        {
            throw;
        }
        switch(!! *it_this + 2 * !! carry)
        {
        case 0:
            break;
        case 1:
            break;
        case 2:
            *it_this = carry;
            carry = nullptr;
            break;
        case 3:
            carry = add_sub_heap(*it_this, carry);
            *it_this = nullptr;
            ++it_this;
            break;
        default:
            throw;
        }

    }
    if(it_this == sub_heaps.end())
    {
        throw;
    }
    if(it_this+1 == sub_heaps.end())
    {
        sub_heaps.push_back(nullptr);
    }
    return true;
}



#endif // BINOMINAL_HEAP_H_INCLUDED
