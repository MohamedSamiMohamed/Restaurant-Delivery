#ifndef __LIST_H_
#define __LIST_H_

#include"../Generic_DS/Node.h"

template <class T>
class List {
	Node<T>* Head;
	int Count; //temporary

public:
	//constructors
	List();

	bool isEmpty() const;
	
	//Insertion
	//Inserts an element at the end of the list
	bool InsertEnd(const T &item);
	
	//Removal 
	//removes a certain item from the List
	bool Remove(const T &item);
	//removes the first item from the list
	bool RemoveBeg(T& headItem);
	
	//Getting items
	//returns the item at a certain position in the List
	//returns false if the List is empty or the position is out of bound
	bool GetItemAt(int Pos, T &ItemAtPos) const;
	//Counting
	//returns the number of Nodes in the List
	int GetCount() const;
};



template<class T>
inline List<T>::List() :Head(nullptr), Count(0)
{}

template<class T>
inline bool List<T>::isEmpty() const
{
	if (!Head)
		return true;
	return false;
}

template<class T>
inline bool List<T>::InsertEnd(const T & item)
{
	Node<T>* newNodePtr = new Node<T>(item);
	if (!newNodePtr)
		return false;
	//case 1:First element
	if (isEmpty())
	{
		Head = newNodePtr;
		Count++;
		
		return true;
	}
	//case: general
	Node<T>* ScnPtr = Head;
	while (ScnPtr->getNext())
	{
		ScnPtr = ScnPtr->getNext();
	}
	ScnPtr->setNext(newNodePtr);
	Count++;
	return true;
}

template<class T>
inline bool List<T>::Remove(const T & item)
{
	//case 1:List is Empty
	if (isEmpty())
		return false;
	//case 2:First item is the item to be deleted
	Node<T>* temp;
	if (item == Head->getItem())
	{
		temp = Head;
		Head = Head->getNext();
		temp->setNext(nullptr);
		delete temp;
		Count--;
		return true;
	}

	Node<T>* ScnPtr = Head;
	while (ScnPtr->getNext())
	{
		if (ScnPtr->getNext()->getItem() == item)
		{
			temp = ScnPtr->getNext();
			ScnPtr->setNext(temp->getNext());
			temp->setNext(nullptr);
			delete temp;
			Count--;
			return true;
		}
		ScnPtr = ScnPtr->getNext();
	}
	return false;
}

template<class T>
inline bool List<T>::RemoveBeg(T& headItem)
{
	if (isEmpty()) 
		return false;
	// To return first item in list
	headItem = Head->getItem();
	Node<T>* temp = Head;
	Head = Head->getNext();
	temp->setNext(nullptr);
	delete temp;
	Count--;
	return true;


}

template<class T>
inline bool List<T>::GetItemAt(int Pos, T&ItemAtPos) const
{
	if (Pos < 0 || Pos >= Count)
		return false;

	Node<T>* ScnPtr = Head;
	for (int i = 0; i < Pos; i++)
	{
		ScnPtr = ScnPtr->getNext();
	}

	ItemAtPos = ScnPtr->getItem();
	return true;
}

template<class T>
inline int List<T>::GetCount() const
{
	return Count;
}

#endif