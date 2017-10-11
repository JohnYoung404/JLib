#pragma once
#include "jMath.h"

//////////////////////////////////////////////////////////////////////////
// Too old, so Discarded, maybe restored later.
//////////////////////////////////////////////////////////////////////////
namespace jLib {
	template<typename KeyType>
	class jAvlNode
	{
	public:
		KeyType key;
		jAvlNode<KeyType>* left;
		jAvlNode<KeyType>* right;
		int height;
		bool deleted;
	};

	template<typename KeyType>
	class jAvlTree
	{
	public:
		jAvlTree() :root(NULL) {}
		~jAvlTree() {
			// memory leaks here.
		}
		void insert(KeyType key);
		void erase(KeyType key);
		jAvlNode<KeyType>* find(KeyType key);
	public:
		jAvlNode<KeyType>* _insert(KeyType key, jAvlNode<KeyType>* T);
		jAvlNode<KeyType>* _find(KeyType key, jAvlNode<KeyType>* T);
		jAvlNode<KeyType>* singleRotateWithLeft(jAvlNode<KeyType>* T);
		jAvlNode<KeyType>* doubleRotateWithLeft(jAvlNode<KeyType>* T);
		jAvlNode<KeyType>* singleRotateWithRight(jAvlNode<KeyType>* T);
		jAvlNode<KeyType>* doubleRotateWithRight(jAvlNode<KeyType>* T);
		int Height(jAvlNode<KeyType>* T);
		jAvlNode<KeyType>* root;
	};

	template<typename KeyType>
	int jAvlTree<KeyType>::Height(jAvlNode<KeyType>* T) {
		if (T == NULL) return -1;
		return T->height;
	}

	template<typename KeyType>
	void jAvlTree<KeyType>::insert(KeyType key) {
		root = _insert(key, root);
	}

	template<typename KeyType>
	void jAvlTree<KeyType>::erase(KeyType key) {
		jAvlNode<KeyType>* res = find(key);
		if (res != NULL)
		{
			res->deleted = true;
		}
	}

	template<typename KeyType>
	jAvlNode<KeyType>* jAvlTree<KeyType>::find(KeyType key) {
		return _find(key, root);
	}

	template<typename KeyType>
	jAvlNode<KeyType>* jAvlTree<KeyType>::_insert(KeyType key, jAvlNode<KeyType>* T) {
		if (T == NULL)
		{
			T = new jAvlNode<KeyType>;
			T->key = key;
			T->left = T->right = NULL;
			T->height = 0;
			T->deleted = false;
		}
		else if (key < T->key)
		{
			T->left = _insert(key, T->left);
			if (Height(T->left) - Height(T->right) == 2)
				if (key < T->left->key)
					T = singleRotateWithLeft(T);
				else
					T = doubleRotateWithLeft(T);
		}
		else if (key > T->key)
		{
			T->right = _insert(key, T->right);
			if (Height(T->right) - Height(T->left) == 2)
				if (key > T->right->key)
					T = singleRotateWithRight(T);
				else
					T = doubleRotateWithRight(T);
		}
		else if (key == T->key)
		{
			T->deleted = false;
		}
		T->height = max(Height(T->left), Height(T->right)) + 1;
		return T;
	}

	template<typename KeyType>
	jAvlNode<KeyType>* jAvlTree<KeyType>::_find(KeyType key, jAvlNode<KeyType>* T) {
		if (T == NULL)
		{
			return NULL;
		}
		if (key == T->key)
		{
			if (T->deleted == true)
			{
				return NULL;
			}
			else {
				return T;
			}
		}
		else if (key > T->key)
		{
			return _find(key, T->right);
		}
		else {
			return _find(key, T->left);
		}
	}

	template<typename KeyType>
	jAvlNode<KeyType>* jAvlTree<KeyType>::singleRotateWithLeft(jAvlNode<KeyType>* T) {
		jAvlNode<KeyType>* tmp;
		tmp = T->left;
		T->left = tmp->right;
		tmp->right = T;
		T->height = max(Height(T->left), Height(T->right)) + 1;
		tmp->height = max(Height(tmp->left), Height(T)) + 1;
		return tmp;
	}

	template<typename KeyType>
	jAvlNode<KeyType>* jAvlTree<KeyType>::singleRotateWithRight(jAvlNode<KeyType>* T) {
		jAvlNode<KeyType>* tmp;
		tmp = T->right;
		T->right = tmp->left;
		tmp->left = T;
		T->height = max(Height(T->left), Height(T->right)) + 1;
		tmp->height = max(Height(tmp->right), Height(T)) + 1;
		return tmp;
	}

	template<typename KeyType>
	jAvlNode<KeyType>* jAvlTree<KeyType>::doubleRotateWithLeft(jAvlNode<KeyType>* T) {
		T->left = singleRotateWithLeft(T->left);
		return singleRotateWithLeft(T);
	}

	template<typename KeyType>
	jAvlNode<KeyType>* jAvlTree<KeyType>::doubleRotateWithRight(jAvlNode<KeyType>* T) {
		T->right = singleRotateWithRight(T->right);
		return singleRotateWithRight(T);
	}

}