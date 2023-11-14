#pragma once

#include "Action.h"
#include "Path.h"

class ActionTransform : public Action
{
public:
	ActionTransform(std::vector<Path*> paths, Transform transform)
		: paths(paths), transform(transform)
	{};

	void Redo() override {
		for (auto path : paths) {
			path->selectionBox.tempTransform = transform;
			path->selectionBox.CommitTransform();
		}
	}

	void Undo() override {
		for (auto path : paths) {
			path->selectionBox.tempTransform = transform;
			path->selectionBox.tempTransform.Invert();
			path->selectionBox.CommitTransform();
		}
	}

	std::string GetName() const override {
		return "Move Object";
	}

private:
	std::vector<Path*> paths;
	Transform transform;
};