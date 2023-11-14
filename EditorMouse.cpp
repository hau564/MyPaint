#include "EditorMouse.h"
#include "DrawingCanvas.h"

EditorMouse::EditorMouse(DrawingCanvas* parent, std::vector<Path*> _paths)
	:Editor(parent), paths(_paths)
{
	for (auto path : paths)
		path->BuildSelectionBox();

	std::sort(paths.begin(), paths.end(),
		[&](const Path* a, const Path* b) {
			return a->selectionBox.GetArea() < b->selectionBox.GetArea();
		});
}

EditorMouse::~EditorMouse()
{
	for (auto path : paths) path->selectionBox.selected = 0;
}

void EditorMouse::OnMouseDown(wxMouseEvent &event)
{
	for (auto path : paths) {
		bool pathSelected = path->selectionBox.selected;
		if (path->selectionBox.OnMouseDown(event)) {

			if (!pathSelected) {
				if (!ctrlHolding) {
					for (auto p : paths) 
						if (p != path) 
							p->selectionBox.selected = 0;
				}
			}

			return;
		}
	}
	for (auto path : paths) path->selectionBox.selected = 0;
}

void EditorMouse::OnMouseMove(wxMouseEvent &event)
{
	for (auto path : paths) path->selectionBox.OnMouseMove(event);
}

void EditorMouse::OnMouseUp(wxMouseEvent &event)
{
	Transform temp;
	for (auto path : paths) if (path->selectionBox.tempTransform != temp) {
		temp = path->selectionBox.tempTransform;
		break;
	}
	std::vector<Path*> selectedPaths;
	for (auto path : paths) if (path->selectionBox.selected) {
		selectedPaths.push_back(path);
		path->selectionBox.mode = 0;
	}
	
	if (temp.IsIdentity()) return;
	parent->AddUndoneAction(new ActionTransform(selectedPaths, temp));
}

void EditorMouse::OnMouseLeave(wxMouseEvent &event)
{
	OnMouseUp(event);
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
