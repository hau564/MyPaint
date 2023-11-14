#pragma once

#ifndef EDITOR_H
#define EDITOR_H

#include <wx/wx.h>
#include "Action.h"
#include "Path.h"

class DrawingCanvas;

class Editor
{
public:
	Editor(DrawingCanvas *parent);
	virtual ~Editor() {};

	virtual void OnMouseDown(wxMouseEvent &event) = 0;
	virtual void OnMouseMove(wxMouseEvent &event) = 0;
	virtual void OnMouseUp(wxMouseEvent &event) = 0;
	virtual void OnMouseLeave(wxMouseEvent &event) = 0;

	virtual void OnKeyDown(wxKeyEvent& event) {};
	virtual void OnKeyUp(wxKeyEvent &event) {};

	virtual void Draw(wxGraphicsContext* gc) {};
protected:
	DrawingCanvas* parent;
};

#endif