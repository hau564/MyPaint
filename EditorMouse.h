#pragma once

#include "Editor.h"
#include "Path.h"

#include "SelectionBox.h"

typedef std::pair<Path*, SelectionBox*> PathBox;

class EditorMouse : public Editor
{
public:
	EditorMouse(DrawingCanvas* parent, std::vector<Object*> objects);
	~EditorMouse();

	void OnMouseDown(wxMouseEvent &event) override;
	void OnMouseMove(wxMouseEvent &event) override;
	void OnMouseUp(wxMouseEvent &event) override;
	void OnMouseLeave(wxMouseEvent &event) override;

	void OnKeyDown(wxKeyEvent& event) override;
	void OnKeyUp(wxKeyEvent& event) override;

	void Draw(wxGraphicsContext* gc) override;

private:
	std::vector<Object*> objects;
	bool ctrlHolding = false;
	Object* activeObject;
	Transform* transform = nullptr;
	wxPoint2DDouble mouseDown;
};

