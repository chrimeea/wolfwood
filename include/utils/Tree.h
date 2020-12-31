#ifndef _TREE
#define _TREE

#include <stdlib.h>

template<class T> class Tree {

private:
	T* data;
	Tree<T>* father;
	Tree<T>* firstSon;
	Tree<T>* sibling;
public:
	Tree();
	~Tree();
	T *GetData() { return data; }
	void SetData(T *d) { data = d; }
	Tree<T> *GetFather() { return father; }
	Tree<T> *GetFirstSon() { return firstSon; }
	Tree<T> *GetSibling() { return sibling; }
	Tree<T> *CreateSon();
	Tree<T> *CreateSibling();
};

template<class T> Tree<T>::Tree()
{
	father = sibling = firstSon = NULL;
	data = NULL;
}

template<class T> Tree<T>::~Tree()
{
	if (data) {
		delete data;
	}
	if (father) {
		father->firstSon = sibling;
	}
	Tree<T> *p, *q;
	p = firstSon;
	while (p)
	{
		q = p->sibling;
		delete p;
		p = q;
	}
}

template<class T> Tree<T> *Tree<T>::CreateSon()
{
	Tree *son = new Tree();
	son->father = this;
	son->sibling = firstSon;
	firstSon = son;
	return son;
}

template<class T> Tree<T> *Tree<T>::CreateSibling()
{
	Tree *sib = new Tree();
	sib->father = father;
	sibling = sib;
	return sib;
}

#endif