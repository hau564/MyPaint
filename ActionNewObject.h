#pragma once

#include<iostream>
#include<vector>
#include "Action.h"
#include "List.h"

template <class T>
class ActionNewObject : public Action
{
public:
	ActionNewObject(Node<T> *object, std::string name = "New Object") 
	: Action(name), object(object) {
		if (!object) return;
		prevObject = object->prev;
	};
	~ActionNewObject() {
		if (object) delete object;
	}

	void Undo() override {
		object->data->showing = false;
		object->EraseSelf();
	}
	void Redo() override {
		prevObject->InsertNext(object);
		object->data->showing = true;
	}

private:
	Node<T>* prevObject;
	Node<T>* object;
};