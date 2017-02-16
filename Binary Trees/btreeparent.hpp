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
		node<T> *find(T key);

	private:
		node<T> *root;
};

template<typename T>
binarytree<T>::binarytree()
{
	root = NULL;
	parent = NULL;
}

template<typename T>
binarytree<T>::~binarytree()
{
	destroy(root);
}

template<typename T>
void destroy(binarytree<T>*& tree)
{
    if(tree != NULL)
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
    node<T> temp;
    if(leaf == NULL)//base case
    {
        leaf = new node<T>;
        leaf->parent = leaf;
        leaf->right = NULL;
        leaf->left = NULL;
        leaf->data = key;
    }
    else if(key < leaf->data)
       {
        insert(key, leaf->left);
        leaf->left = temp;
        temp->parent = leaf;
       }
    else{
        insert(key, leaf->right);
        leaf->right = temp;
        temp->parent = leaf;
        }
}

template<typename T>
binarytree<T>::binarytree(const binarytree<T>& tree)
{
    copytree(root, tree.root);
}

template<typename T>
void copytree(binarytree<T>*& copy, binarytree<T>* original)
{
    if(original == NULL)
        copy = NULL;
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
void erase(node<T>* leaf, T key)
{
    T info;
    node<T>* temp;
    temp = leaf;
    if(leaf == NULL)//base case
        return root;
    if(key < leaf->data)
        erase(leaf->left, key);
    else if(key > leaf->data)
        erase(leaf->right, key);
    else
        {
            if(leaf->left == NULL)//right child 0 or 1 child
            {
                leaf = leaf->right;
                delete temp;
            }
            else if(leaf->right == NULL)//left child 0 or 1 child
            {
                leaf = leaf->left;
                delete temp;
            }
            else{                       //two children
                leaf->parent = leaf->right;
                delete leaf;
                }
        }
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
    while((temp != NULL) && (temp->key != key))
    {
        if(key <temp->key)
            temp = temp->left;
        else
            temp = temp->right;
    }
    if(temp == NULL)
        return temp;
    else
        return temp;
}


#endif
