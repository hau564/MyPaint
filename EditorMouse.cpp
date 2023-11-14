#include "EditorMouse.h"
#include "DrawingCanvas.h"

EditorMouse::EditorMouse(DrawingCanvas* parent, std::vector<Object*> _objects)
	:Editor(parent), objects(_objects)
{
	for (auto object : objects) object->BuildSelectionBox();
	std::sort(objects.begin(), objects.end(),
		[&](const Object* a, const Object* b) {
			return a->selectionBox.GetArea() < b->selectionBox.GetArea();
		});
}

EditorMouse::~EditorMouse()
{
	if (transform) delete transform;
	for (auto object : objects)
		object->selectionBox.selected = false;
}

void EditorMouse::OnMouseDown(wxMouseEvent &event)
{
	mouseDown = event.GetPosition();
	for (auto object : objects) {
		if (object->selectionBox.selected) {
			transform = object->selectionBox.OnMouseDown(event);
			if (transform) return;
		}
	}

	for (auto object : objects) {
		transform = object->selectionBox.OnMouseDown(event);
		if (transform) {
			if (!ctrlHolding) {
				for (auto p : objects)
					if (p != object) {
						p->selectionBox.selected = false;
					}
			}
			return;
		}
	}

	for (auto object : objects) object->selectionBox.selected = false;
}

void EditorMouse::OnMouseMove(wxMouseEvent &event)
{
	if (!transform) return;
	transform->adjust = event.GetPosition() - mouseDown;

	for (auto object : objects) {
		if (object->selectionBox.selected)
			object->selectionBox.DoTransform(transform);
	}
}

void EditorMouse::OnMouseUp(wxMouseEvent &event)
{
	if (!transform) return;
	for (auto object : objects) {
		object->selectionBox.CommitTransform();
	}
	delete transform;
	transform = nullptr;
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
