#ifndef _P_NODE_H
#define _P_NODE_H

//[MA]: Priority Node Class

template <class T>
class PNode
{
	T Item;
	int Priority;
	PNode* Next;

public:
	//Constructors
	PNode();
	PNode(const T& r_item, int Pri);
	//Setters
	void setItem(const T& r_item);
	void setNext(PNode<T>* r_nxt);
	void setPriority(int Pri);
	//Getters
	T getItem() const;
	PNode<T>* getNext() const;
	int getPriority() const;
};

template <class T>
PNode<T> ::PNode() { Next = nullptr; }

template<class T>
inline PNode<T>::PNode(const T & r_item, int Pri)
{
	Item = r_item;
	Priority = Pri;
	Next = nullptr;
}

template<class T>
inline void PNode<T>::setItem(const T & r_item)
{
	Item = r_item;
}

template<class T>
inline void PNode<T>::setNext(PNode<T>* r_nxt)
{
	Next = r_nxt;
}

template<class T>
inline void PNode<T>::setPriority(int Pri)
{
	Priority = Pri;
}

template<class T>
inline T PNode<T>::getItem() const
{
	return Item;
}

template<class T>
inline PNode<T>* PNode<T>::getNext() const
{
	return Next;
}

template<class T>
inline int PNode<T>::getPriority() const
{
	return Priority;
}


#endif // !P_NODE_H


