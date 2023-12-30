#include "EditorMouse.h"
#include "DrawingCanvas.h"

EditorMouse::EditorMouse(DrawingCanvas* parent, std::vector<Object*> _objects)
	:Editor(parent), objects(_objects)
{
	for (auto object : objects) object->BuildSelectionBox();
	std::reverse(objects.begin(), objects.end());
	/*std::sort(objects.begin(), objects.end(),
		[&](const Object* a, const Object* b) {
			return a->selectionBox.GetArea() < b->selectionBox.GetArea();
		});*/
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
		if (!object->showing) continue;
		if (object->selectionBox.IsSelected()) {
			transform = object->selectionBox.OnMouseDown(event);
			if (transform) {
				activeObject = object;
				return;
			}
		}
	}

	for (auto object : objects) {
		if (!object->showing) continue;
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
	transform->Modify(mouseDown, event.GetPosition() - mouseDown, ctrlHolding ? WXK_CONTROL : -1);

	activeObject->selectionBox.DoTransform(transform);
	for (auto object : objects) if (object != activeObject) {
		if (!object->showing) continue;
		if (object->selectionBox.IsSelected())
			object->selectionBox.DoTransform(transform);
	}
}

void EditorMouse::OnMouseUp(wxMouseEvent &event)
{
	if (!transform) return;
	if (abs(transform->adjust.m_x) < 1 &&
		abs(transform->adjust.m_y) < 1) {
		transform = nullptr;
		return;
	}

	std::vector<Object*> selectedObjects;
	for (auto object : objects) {
		if (!object->showing) continue;
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
	if (event.GetKeyCode() == WXK_DELETE) {
		std::vector<Object*> selectedObjects;
		for (auto object : objects) {
			if (!object->showing) continue;
			if (object->selectionBox.IsSelected()) {
				selectedObjects.push_back(object);
			}
		}
		if (selectedObjects.empty()) return;
		parent->AddUndoneAction(new ActionDeleteObject<Object>(selectedObjects));
	}
	parent->Refresh();
}

void EditorMouse::OnKeyUp(wxKeyEvent &event)
{
	if (event.GetKeyCode() == WXK_CONTROL) {
		ctrlHolding = false;
	}
}

void EditorMouse::Finish()
{
	wxMouseEvent event;
	OnMouseUp(event);
}

void EditorMouse::Reset()
{
	for (auto object : objects) object->selectionBox.SetSelected(false);
}

void EditorMouse::Draw(wxGraphicsContext* gc)
{
	
}
