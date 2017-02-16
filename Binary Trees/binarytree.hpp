

// Andrew Parker atp23@zips.uakron.edu
#ifndef binarytree_hpp
#define binarytree_hpp

#include "node.hpp"


template<typename T>
class binarytree
{
	public:
		binarytree();
		binarytree(const binarytree<T>&);
		binarytree& operator= (const binarytree<T>&);
		~binarytree();

		void insert(T key);
		void erase(T key);
		void printtree(binarytree<T>*);
		node<T> *find(T key);

	private:
		node<T> *root;
};

template<typename T>
binarytree<T>::binarytree()
{
	root = nullptr;
}

template<typename T>
binarytree<T>::~binarytree()
{
	destroy(root);
}

template<typename T>
void destroy(binarytree<T>*& tree)
{
    if(tree != nullptr)
    {
        destroy(tree->left);
        destroy(tree->right);
        delete tree;
    }
}

template<typename T>
void binarytree<T>::insert(T key)
{
    insert(key, root);
}

template<typename T>
void insert(T key, node<T>* leaf)
{
    if(leaf == nullptr)//base case
    {
        leaf = new node<T>;
        leaf->right = nullptr;
        leaf->left = nullptr;
        leaf->data = key;
    }
    else if(key < leaf->data)
        insert(key, leaf->left);
    else
        insert(key, leaf->right);
}

template<typename T>
binarytree<T>::binarytree(const binarytree<T>& tree)
{
    copytree(root, tree.root);
}

template<typename T>
void copytree(binarytree<T>*& copy, binarytree<T>* original)
{
    if(original == nullptr)
        copy = nullptr;
    else {
        copy = new binarytree<T>;
        copy->data = original->data;
        copytree(copy->left, original->left);
        copytree(copy->right, original->right);
    }
}

template<typename T>
void binarytree<T>::erase(T key)
{
    erase(root, key);
}

template<typename T>
void erase(node<T>* tree, T key)
{
    T info;
    binarytree<T>* temp;
    temp = tree;

    if(key < tree->data)
        erase(tree->left, key);
    else if(key > tree->data)
        erase(tree->right, key);
    else
        {
            if(tree->left == nullptr)//right child 0 or 1 child
            {
                tree = tree->right;
                delete temp;
            }
            else if(tree->right == nullptr)//left child 0 or 1 child
            {
                tree = tree->left;
                delete temp;
            }
            else{
                findparent(tree->left, info);
                tree->data = info;
                erase(tree->left, info);//2 children
            }
        }
}

template<typename T>
void findparent(binarytree<T>* tree, T& info)
{
    while(tree->right != nullptr)
        tree=tree->right;
    info = tree->data;
}

template<typename T>
binarytree<T>& binarytree<T>::operator=(const binarytree& tree)
{
    if(&tree == this)
        return;
    destroy(root);
    copytree(root, tree.root);
}

template<typename T>
node<T> *binarytree<T>::find(T key)
{
    node<T> *temp;

    temp = root;
    while((temp != nullptr) && (temp->key != key))
    {
        if(key <temp->key)
            temp = temp->left;
        else
            temp = temp->right;
    }
    if(temp == nullptr)
        return temp;
    else
        return temp;
}

template<typename T>
void printtree(binarytree<T>* tree)
{
    if(tree!=nullptr){
        printtree(tree->left);
        std::cout<< tree->data;
        printtree(tree->right);
    }
}

#endif
