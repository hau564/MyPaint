#pragma once

#include<iostream>
#include<vector>
#include "Action.h"
#include "List.h"

template <class T>
class ActionNewObject : public Action
{
public:
	ActionNewObject(Node<T> *object) : object(object) {
		prevObject = object->prev;
	};
	void Undo() override {
		object->EraseSelf();
	}
	void Redo() override {
		prevObject->InsertNext(object);
	}

private:
	Node<T>* prevObject;
	Node<T>* object;
};