#include "EditorDraw.h"
#include "DrawingCanvas.h"

EditorDraw::EditorDraw(DrawingCanvas* parent)
	:Editor(parent)
{
}

void EditorDraw::OnMouseDown(wxMouseEvent &event)
{
	path = new Path(parent->GetPenColor(), parent->GetPenSize());
	path->push_back(event.GetPosition());
}

void EditorDraw::OnMouseMove(wxMouseEvent &event)
{
	if (!path) return;
	path->push_back(event.GetPosition());
}

void EditorDraw::OnMouseUp(wxMouseEvent &event)
{
	if (!path) return;
	//path->Rotate(0.5);
	parent->AddPath(path);
	path = nullptr;
}

void EditorDraw::OnMouseLeave(wxMouseEvent &event) 
{
	OnMouseUp(event);
}

void EditorDraw::Draw(wxGraphicsContext* gc)
{
	if (path) path->Draw(gc);
}