#pragma once
class Action
{
public:
	virtual void Undo() = 0;
	virtual void Redo() = 0;
};

