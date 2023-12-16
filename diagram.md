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


classDiagram
	Node: +Node()
	Node: +Node(T)
	Node: +Node(Node<T>*, Node<T>*, T)
	Node: +~Node()
	Node: +InsertNext(Node<T>*)
	Node: +InsertNext(T)
	Node: +EraseSelf()
	Node: +operator==(Node<T>)
	Node: +operator!=(Node<T>)
	Node: +operator++()
	Node: +operator*()
	Node: T data
	Node: Node<T>* next *prev
