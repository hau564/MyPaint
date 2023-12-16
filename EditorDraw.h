#pragma once

#ifndef EDITORDRAW_H
#define EDITORDRAW_H

#include "Editor.h"
#include "Path.h"

class EditorDraw : public Editor
{
public:
	EditorDraw(DrawingCanvas* parent);

	void OnMouseDown(wxMouseEvent &event) override;
	void OnMouseMove(wxMouseEvent &event) override;
	void OnMouseUp(wxMouseEvent &event) override;
	void OnMouseLeave(wxMouseEvent &event) override;
	void Finish() override;

	void Draw(wxGraphicsContext* gc) override;
private:
	Path* path;
};

#endif