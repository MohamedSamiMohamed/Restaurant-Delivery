#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_

#include "PNode.h"

template <class T>
class PriorityQueue
{
private:
	int item_count;
	PNode<T>* frontPtr;
	PNode<T>* backPtr;

public:
	//constructor
	PriorityQueue();
	//operations
	bool isEmpty() const;
	bool enqueue(const T& newentry, int Pri);
	bool dequeue(T& frntentry);
	bool peekFront(T& frntentry) const;
	void set_item_count(int Cnt);
	int get_item_count() const;


};




template<class T>
inline PriorityQueue<T>::PriorityQueue()
{
	frontPtr = nullptr;
	backPtr = nullptr;
	item_count = 0;
}

template<class T>
inline bool PriorityQueue<T>::isEmpty() const
{
	if (!frontPtr)
		return true;
	else
		return false;
}


//enqueue : Adds a new entry according to its priority
//Input: newentry & Priority
//output: True if it can allocate a new Node, false otherwise
template<class T>
inline bool PriorityQueue<T>::enqueue(const T & newentry, int Pri)
{
	//create a node with the new data
	PNode<T>* newentryPtr = new PNode<T>(newentry, Pri);
	//can't allocate
	if (!newentryPtr)
	{
		return false;
	}

	//case 1: EMPTY QUEUE
	if (isEmpty())
	{
		frontPtr = newentryPtr;
		backPtr = frontPtr;
		item_count++;
		return true;
	}
	//case 2: HIGHEST PRIORITY
	if (frontPtr->getPriority() < Pri)
	{
		newentryPtr->setNext(frontPtr);
		frontPtr = newentryPtr;
		item_count++;
		return true;
	}
	//case: general case
	PNode<T>* Ptr = frontPtr;
	while (Ptr->getNext())
	{
		//if the priority of the next element is less than my priority
		if (Ptr->getNext()->getPriority() < Pri)
		{
			newentryPtr->setNext(Ptr->getNext());
			Ptr->setNext(newentryPtr);
			item_count++;
			return true;
		}
		else
		{
			Ptr = Ptr->getNext();
		}
	}
	//case:it exits the loop then the new entry has the lowest priority
	backPtr->setNext(newentryPtr);
	backPtr = backPtr->getNext();
	item_count++;
	return true;

}

//Dequeue : removes the frontt element in the queue
//Input : frntentry by ref to return the entry before deleting the Node
//Output : True if successful false if the queue wa empty 

template<class T>
inline bool PriorityQueue<T>::dequeue(T & frntentry)
{
	if (isEmpty())
		return false;
	PNode<T>* DelPtr = frontPtr;
	frntentry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	//case:one Node left
	if (DelPtr == backPtr)
		backPtr = nullptr;
	DelPtr->setNext(nullptr);
	delete DelPtr;
	item_count--;
	return true;
}

//peekFront Gets the entry at the front without dequeueing
//Input: a place holder to store the front entry
//output: True if the queue has a front entry, false if it is empty

template<class T>
inline bool PriorityQueue<T>::peekFront(T & frntentry) const
{
	//case 1: The queue is empty nothing to peek 
	if (isEmpty())
		return false;
	frntentry = frontPtr->getItem();
	return true;

}

//Sets the Item Count by a certain amount
//Input: Number of elements in the queue
template<class T>
inline void PriorityQueue<T>::set_item_count(int Cnt)
{
	item_count = Cnt;
}

template<class T>
inline int PriorityQueue<T>::get_item_count() const
{
	return item_count;
}

#endif
