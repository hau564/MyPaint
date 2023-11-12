#pragma once

#include "Node.h"

template <class T>
class List
{
public:
	List();
	~List() {};

	Node<T>* Last() { return tail->prev; }
	Node<T>* First() { return head->next; }
	Node<T>* Head() { return head; }
	Node<T>* Tail() { return tail; }

	Node<T*>* begin() { return First(); }
	Node<T*>* end() { return Tail(); }

	std::vector<T> GetVectorData();

private:
	Node<T>* head, * tail;
};

template<class T>
inline List<T>::List()
{
	head = new Node<T>();
	tail = new Node<T>();
	head->next = tail;
	head->prev = nullptr;

	tail->prev = head;
	tail->next = nullptr;
}

template<class T>
inline std::vector<T> List<T>::GetVectorData()
{
	std::vector<T> result;
	auto it = First();
	while (it != Tail()) {
		result.push_back(it->data);
		it = it->next;
	}
	return result;
}
