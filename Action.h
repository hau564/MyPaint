#pragma once
#include <string>
class Action
{
public:
	virtual ~Action() {};
	virtual void Undo() = 0;
	virtual void Redo() = 0;
	virtual std::string GetName() const = 0;
};

