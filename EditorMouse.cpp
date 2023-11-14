#include "EditorMouse.h"

EditorMouse::EditorMouse(DrawingCanvas* parent, std::vector<Path*> _paths)
	:Editor(parent), paths(_paths)
{
	for (auto path : paths)
		path->BuildSelectionBox();
}

void EditorMouse::OnMouseDown(wxMouseEvent &event)
{
	
}

void EditorMouse::OnMouseMove(wxMouseEvent &event)
{
}

void EditorMouse::OnMouseUp(wxMouseEvent &event)
{
}

void EditorMouse::OnMouseLeave(wxMouseEvent &event)
{
}

void EditorMouse::OnKeyDown(wxKeyEvent &event)
{
	if (event.GetKeyCode() == WXK_CONTROL) {
		ctrlHolding = true;
	}
}

void EditorMouse::OnKeyUp(wxKeyEvent &event)
{
	if (event.GetKeyCode() == WXK_CONTROL) {
		ctrlHolding = false;
	}
}

void EditorMouse::Draw(wxGraphicsContext* gc)
{
	
}
