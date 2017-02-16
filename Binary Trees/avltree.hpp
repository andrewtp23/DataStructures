//Andrew Parker atp23@zips.uakron.edu
#ifndef avltree_hpp
#define avltree_hpp

#include "node.hpp"

template<typename T>
class avltree
{
	public:
		avltree();
		avltree(const avltree<T>&);
		avltree& operator= (const avltree<T>&);
		~avltree();

		void insert(T key);
		void erase(T key);
		node<T> *find(T key);
		int height(node<T> *);
		int hdiff(node<T> *);
		node<T> *balance(node<T> *);

		//Rotations
		node<T> *rr_rotation(node<T> *);
		node<T> *ll_rotation(node<T> *);
		node<T> *lr_rotation(node<T> *);
		node<T> *rl_rotation(node<T> *);

	private:
		node<T> *root;
};

template<typename T>
avltree<T>::avltree()
{
	root = nullptr;
}

template<typename T>
avltree<T>::~avltree();
{
	destroy(root);
}

template<typename T>
void destroy(avltree<T>*& tree)
{
	if(tree != nullptr)
	{
		destroy(tree->left);
		destroy(tree->right);
		delete tree;
	}
}

template<typename T>
avltree<T>::avltree(const avltree<T>& tree)
{
	copytree(root, tree.root);
}

template<typename T>
void copytree(avltree<T>*& copy, avltree<T>* original)
{
	if(original == nullptr)
		copy = nullptr;
	else{
		copy = new avltree<T>;
		copy->data = original->data;
		copytree(copy->left, original->left);
		copytree(copy->right, original->right);

	}
}

template<typename T>
avltree<T>& avltree<T>::operator=(const avltree& tree)
{
	if(&tree == this)
		return;
	destroy(root);
	copytree(root, tree.root);
}

template<typename T>
node<T> *avltree<T>::find(T key)
{
	node<T> *temp;

	temp= root;

	while((temp !- nullptr) && (temp->key != key))
	{
		if(key < temp->key)
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
int avltree<T>::height(node<T> *temp)
{
    int h = 0;
    if(temp != NULL)
    {
        int lheight= height(temp->left);
        int rheight = height(temp->right);

        h = (max(lheight,rheight) + 1);
    }

    return h;
}

template<typename T>
int avltree<T>::hdiff(node<T> *temp)
{
    int lheight = height(temp->left);
    int rheight = height(temp->right);
    int diff = (lheight - rheight);

    return diff;
}

template<typename T>
node<T> *avltree<T>::rr_rotation(node<T> *parent)
{
    node<T> *temp;

    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

template<typename T>
node<T> *avltree<T>::ll_rotation(node<T> *parent)
{
    node<T> *temp;

    temp= parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}

template<typename T>
node<T> *avltree<T>::lr_rotation(node<T> *parent)
{
    node<T> *temp;

    temp = parent->left;
    parent->left = rr_rotation(temp);
    return ll_rotation(parent);
}

template<typename T>
node<T> *avltree<T>::rl_rotation(node<T> *parent)
{
    node<T> *temp;

    temp = parent->right;
    parent->right = ll_rotation(temp);
    return rr_rotation(parent);
}

template<typename T>
node<T> *avltree<T>::balance(node<T> *temp)
{
    int bal = hdiff(temp);

    if(bal > 1)
    {
        if(hdiff(temp->left) > 0)
            temp = ll_rotation(temp);
        else
            temp = lr_rotation(temp);
    }
    else if (bal < -1)
    {
        if(hdiff(temp->right) < 0)
            temp = rr_rotation(temp);
        else
            temp = rl_rotation(temp);
    }

    return temp;
}

template<typename T>
void avltree<T>::insert(T key)
{
    insert(T key, root);
}

template<typename T>
void insert(T key, node<T> *leaf)
{
    if(leaf == NULL)
    {
        leaf = new node<T>;
        leaf->data = key;
        root->left = NULL;
        root->right = NULL;
        return leaf;
    }
    else if (key < leaf->data)
    {
        leaf->left = insert(key, leaf->left);
        leaf = balance(leaf);
    }
    else
    {
        leaf->right = insert(key, leaf->right);
        leaf = balance(leaf);
    }
}

template<typename T>
void avltree<T>::erase(T key)
{
	if (root == NULL) //basecase
		return;

	node<T> *n = root;
	node<T> *parent = root;
	node<T> *temp = NULL;
	node<T> *child = root;

	while(child != NULL) {
		parent = n;
		n = child;
		child = temp >= n->key ? n->right : n->left;

		if(key == n->data)
			temp = n;
	}

	if(temp != NULL) {
		temp->data = n->data;
		child = n->left != NULL ? n->left : n->right;

		if(root->data == key)
			root = child;
	}
	else{
		if(parent->left == n) {
			parent->left = child;
		}
		else
			parent->right = child;
	}
	parent = balance(parent);
}
#endif
