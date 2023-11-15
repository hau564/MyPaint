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
		object->selectionBox.SetSelected(false);
}

void EditorMouse::OnMouseDown(wxMouseEvent &event)
{
	mouseDown = event.GetPosition();
	for (auto object : objects) {
		if (object->selectionBox.IsSelected()) {
			transform = object->selectionBox.OnMouseDown(event);
			if (transform) {
				activeObject = object;
				return;
			}
		}
	}

	for (auto object : objects) {
		transform = object->selectionBox.OnMouseDown(event);
		if (transform) {
			if (!ctrlHolding) {
				for (auto p : objects)
					if (p != object) {
						p->selectionBox.SetSelected(false);
					}
			}
			activeObject = object;
			return;
		}
	}

	for (auto object : objects) object->selectionBox.SetSelected(false);
}

void EditorMouse::OnMouseMove(wxMouseEvent &event)
{
	if (!transform) return;
	transform->Modify(mouseDown, event.GetPosition() - mouseDown);

	activeObject->selectionBox.DoTransform(transform);
	for (auto object : objects) if (object != activeObject) {
		if (object->selectionBox.IsSelected())
			object->selectionBox.DoTransform(transform);
	}
}

void EditorMouse::OnMouseUp(wxMouseEvent &event)
{
	if (!transform) return;
	if (abs(event.GetPosition().x - mouseDown.m_x) < 1 &&
		abs(event.GetPosition().y - mouseDown.m_y) < 1) {
		transform = nullptr;
		return;
	}

	std::vector<Object*> selectedObjects;
	for (auto object : objects) {
		if (object->selectionBox.IsSelected()) {
			selectedObjects.push_back(object);
		}
	}

	parent->AddUndoneAction(new ActionTransform<Object>(selectedObjects, transform));

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
