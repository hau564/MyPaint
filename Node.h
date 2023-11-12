#pragma once

template <class T>
class Node 
{
public:
	Node() {};
	Node(T data);
	Node(Node<T> *prev, Node<T> *next, T data = T()) : prev(prev), next(next), data(data) {};
	~Node();

	void InsertNext(Node<T> *nxt);
	void InsertNext(T data);
	void EraseSelf();

	bool operator==(Node<T> other) { return this == other; }
	bool operator!=(Node<T> other) { return this != other; }
	Node<T>* operator++() { return next; }
	T operator*() { return data; }

public:
	Node<T>* next, *prev;
	T data;
};


template<class T>
inline Node<T>::Node(T data)
{
	this->data = data;
	this->next = nullptr;
	this->prev = nullptr;
}

template<class T>
Node<T>::~Node()
{
}

template<class T>
void Node<T>::InsertNext(Node<T>* nxt)
{
	assert(next, "Cannot insert next to tail");

	nxt->next = next;
	nxt->prev = this;

	next->prev = nxt;
	next = nxt;
}

template<class T>
void Node<T>::InsertNext(T data)
{
	InsertNext(new Node<T>(this, next, data));
}

template<class T>
void Node<T>::EraseSelf()
{
	assert(next, "Cannot kill tail");
	assert(prev, "Cannot kill head");
	prev->next = next;
	next->prev = prev;
}
