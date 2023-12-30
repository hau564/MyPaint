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
	};
	~ActionNewObject() {

	}

	void Undo() override {
		object->data->showing = false;
		object->data->selectionBox.SetSelected(false);
	}
	void Redo() override {
		object->data->showing = true;
	}

private:
	Node<T>* object;
};