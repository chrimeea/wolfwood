#ifndef _LINKEDLIST
#define _LINKEDLIST

#include <stdlib.h>

template<class T> class LinkedList;

//@{
// Template class for a linked list node.
// A node in the list stores DATA and a NEXT pointer, to the next node
// in the list. The DATA attribute can be any type, even user defined.
//
// This is a generic Node class and together with LinkedList,
// they make the perfect linked list template class.
// @author Razvan Mocanu
// @version 0.0.1
//@}
template<class T>
class LinkedListNode{
//Attributes
private:
	T* data;                    //@- The data stored in the node

    //@{
    // Pointer to the next node in the list.
    // If this points to NULL, than that means that this node is the
    // last node in the list
    //@}
	LinkedListNode<T>* pNext;
//Methods
private:
    //@{
    // LinkedListNode constructor
    //@}
	LinkedListNode();

    //@{
    // LinkedListNode destructor
    //@}
	~LinkedListNode();

    //@{
    // You can access the node only via the linked list wrapper class.
    //@}
	friend class LinkedList<T>;
};

//@{
// Describes a general-type linked list.
// The linked list stores nodes linked togheter via the LinkedListNode
// mechanics. This class stores info for the first, last and current 
// node.
// 
// IMPORTANT: To parse a list, you can only use the methods provided 
// within this class. You get NO direct access to a node.
// Imagine an invisible pointer that points to head when you call
// the Head() method, and points to the next node when you call Next().
// You check to see if it has reached the end of the list with IsAtEnd().
// When you add a new node to the list using AddNode(), the invisible 
// pointer is positioned on the newly created node.
// An example is shown below for clarity:
// <pre>
//@@ typedef LinkedList<MyData> MDList;
//@@ MDList.Head();
//@@ while(!MDList.IsAtEnd()) {
//@@    MyData* p=MDList.GetData();
//@@    //...manipulate data
//@@    MyData.Next();
//@@ }
// </pre>
// @author Razvan Mocanu
// @version 0.0.1
//@}
template<class T>
class LinkedList{
//Attributes
private:
    //@{
    // Points to the head of the list.
    //@}
	LinkedListNode<T>* pHead;

    //@{
    // Points to the tail of the list.
    //@}
	LinkedListNode<T>* pTail;

    //@{
    // Current node pointer.
    //@}
	LinkedListNode<T>* pCursor;

	LinkedListNode<T>* pPrevious;

	unsigned int nItemsCount;   //@- Number of items in list

//Methods
public:
    //@{
    // LinkedList constructor
    //@}
	LinkedList();

    //@{
    // LinkedList destructor
    //@}
	~LinkedList();

    //@{
    // Add a new node to the list. The template takes care of everything.
    //@}
	void addNode(T*);

	void delCurrentNode();

    //@{
    // Go to the head of the list.
    // @returns pointer to the first node in the list
    //@}
	void head(void) {
		pPrevious = NULL;
		pCursor = pHead;
	}

    //@{
    // Go to the next node in the list.
    // @returns pointer to the next node in the list
    //@}
	void next(void) {
		pPrevious = pCursor;
		pCursor = pCursor->pNext;
	}

    //@{
    // Get the data associated with the current node.
    // The current node is set via the Head,Tail and Next metods
    // @returns pointer to data stored in node.
    //@}
	T* getData(void) { return pCursor->data; }

    //@{
    // Get the total nr of nodes in list.
    // @returns number of nodes in list
    //@}
	unsigned int getCount(void) { return nItemsCount; }

    //@{
    // Checks to see if the list is empty.
    // @returns 1 if the list is empty,0 otherwise
    //@}
	int isEmpty(void) { return (nItemsCount==0); }

    //@{
    // Checks to see if the tail has been reached.
    // @returns 1 if tail has been reached, 0 otherwise
    //@}
    int isAtEnd(void) { return (NULL==pCursor); }
};

//LinkedListNode
template<class T>
LinkedListNode<T>::LinkedListNode()
{
	data = NULL;
}

template<class T>
LinkedListNode<T>::~LinkedListNode()
{
	if(data) delete data;
}

//LinkedList
template<class T>
LinkedList<T>::LinkedList()
{
	pHead = pTail = pCursor = pPrevious = NULL;
	nItemsCount = 0;
}

template<class T>
LinkedList<T>::~LinkedList()
{	
	while(pHead!=NULL)
	{
		pCursor=pHead;
		pHead=pCursor->pNext;
		delete pCursor;
		nItemsCount--;
	}
	pHead = pTail = pCursor = pPrevious = NULL;
}

template<class T>
void LinkedList<T>::addNode(T* newNode)
{
	if(pHead==NULL)
	{
		pHead = new LinkedListNode<T>;
		pHead->data = newNode;
		pHead->pNext=NULL;
		pTail=pHead;
	}
	else
	{
		pTail->pNext = new LinkedListNode<T>;
		pTail = pTail->pNext;
		pTail->data = newNode;
		pTail->pNext=NULL;
	}
	nItemsCount++;
}

template<class T>
void LinkedList<T>::delCurrentNode()
{
	if (pHead == NULL || pCursor == NULL)
	{
		return;
	}
	nItemsCount--;
	if (pPrevious == NULL)
	{
		pHead = pHead->pNext;
		pCursor->data = NULL;
		delete pCursor;
		pCursor = pHead;
		if (pHead == NULL)
		{
			pTail = NULL;
		}
	} else if (pCursor->pNext == NULL) {
		pPrevious->pNext = NULL;
		pTail = pPrevious;
		pCursor->data = NULL;
		delete pCursor;
		pCursor = NULL;
	} else {
		pPrevious->pNext = pCursor->pNext;
		pCursor->data = NULL;
		delete pCursor;
		pCursor = pPrevious->pNext;
	}
}

#endif