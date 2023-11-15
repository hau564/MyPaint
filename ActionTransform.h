#pragma once

#include<iostream>
#include<vector>
#include "Action.h"
#include "Transform.h"

template <class T>
class ActionTransform : public Action
{
public:
	ActionTransform(std::vector<T*> objects, Transform* transform) 
		: objects(objects), transform(transform) {
		for (auto object : objects)
			memTransforms.push_back(object->selectionBox.GetBaseTransform());
	};
	void Undo() override {
		for (int i = 0; i < (int)objects.size(); ++i) {
			objects[i]->selectionBox.SetTransform(memTransforms[i]);
			objects[i]->selectionBox.SetSelected(false);
		}
	}
	void Redo() override {
		for (auto object : objects) {
			object->selectionBox.DoTransform(transform);
			object->selectionBox.CommitTransform();
			object->selectionBox.SetSelected(true);
		}
	}
	std::string GetName() const override {
		return "Transform Object";
	}

private:
	std::vector<T*> objects;
	std::vector<wxAffineMatrix2D> memTransforms;
	Transform* transform;
};