#pragma once
#include <string>
class Action
{
public:
	Action(std::string name = "Action") : name(name) {};
	virtual ~Action() {};
	virtual void Undo() = 0;
	virtual void Redo() = 0;
	virtual std::string GetName() const {
		return name;
	}
private:
	std::string name;
};

