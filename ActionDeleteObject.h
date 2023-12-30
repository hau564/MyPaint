#pragma once

#include<iostream>
#include<vector>
#include "Action.h"
#include "List.h"

template <class T>
class ActionDeleteObject : public Action
{
public:
	ActionDeleteObject(std::vector<T*> objects, std::string name = "Delete Object")
		: Action(name), objects(objects) {
		if (!objects.empty()) return;
	};
	~ActionDeleteObject() {
		//if (object) delete object;
	}

	void Undo() override {
		for (auto object : objects) {
			object->showing = true;
		}
	}
	void Redo() override {
		for (auto object : objects) {
			object->showing = false;
			object->selectionBox.SetSelected(false);
		}
	}

private:
	std::vector<T*> objects;
};